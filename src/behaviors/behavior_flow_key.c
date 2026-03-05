#define DT_DRV_COMPAT zmk_behavior_flow_key

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>
#include <zmk/behavior.h>
#include <zmk/keymap.h>
#include <zmk/hid.h>

#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>
#include <zmk/events/keycode_state_changed.h>
#include <dt-bindings/zmk/keys.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

struct behavior_flow_key_config {
    uint32_t timeout_ms;
    uint32_t bindings_count;
    struct zmk_behavior_binding bindings[];
};

struct behavior_flow_key_data {
    const struct zmk_behavior_binding* invoked_behavior;
};

struct behavior_history_item {
    int64_t timestamp;
    const struct zmk_behavior_binding* binding;
};

struct behavior_history_item behavior_history[2];
struct zmk_keycode_state_changed last_keycode_event;

bool bindings_are_equal(
    const struct zmk_behavior_binding *b1,
    const struct zmk_behavior_binding *b2
) {
#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_LOCAL_IDS_IN_BINDINGS)
    if (b1->locol_id != b2->locol_id) return false;
#endif

    LOG_DBG(
        "comparing %s %x %x with %s %x %x",
        b1->behavior_dev, b1->param1, b1->param2,
        b2->behavior_dev, b2->param1, b2->param2
    );

    if (strcmp(b1->behavior_dev, b2->behavior_dev) != 0) return false;
    if (b1->param1 != b2->param1) return false;
    if (b1->param2 != b2->param2) return false;

    LOG_DBG("Behaviors are matching.");
    return true;
}

// Mutates `data` by pointer
void perform_binding_substitution(
    const struct behavior_flow_key_config *cfg,
    const struct zmk_behavior_binding **behavior
) {
    if (!behavior_history[1].binding) return;

    struct zmk_behavior_binding last_keycode_as_kp = {
        .behavior_dev = "key_press",
        .param1 = ZMK_HID_USAGE(
            last_keycode_event.usage_page,
            APPLY_MODS(
                last_keycode_event.implicit_modifiers,
                last_keycode_event.keycode
            )
        ),
    };

    // Bindings are specified as a key-value pair, with the key being odd indexes.
    // (bindings[0] is the default case)
    for (int i = 1; i < cfg->bindings_count; i += 2) {
        if (bindings_are_equal(&cfg->bindings[i], behavior_history[1].binding)
            || bindings_are_equal(&cfg->bindings[i], &last_keycode_as_kp)
        ) {
            *behavior = &cfg->bindings[i + 1];
            return;
        }
    }

    // If the last binding is just a key with no value, use it as a default case
    if (cfg->bindings_count % 2 == 0 && cfg->timeout_ms > 0) {
        *behavior = &cfg->bindings[cfg->bindings_count - 1];
    }
}

static int on_flow_key_binding_pressed(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
) {
    const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);
    const struct behavior_flow_key_config *cfg = dev->config;
    struct behavior_flow_key_data *data = dev->data;

    data->invoked_behavior = &cfg->bindings[0];
    if (cfg->timeout_ms == 0 || cfg->timeout_ms > event.timestamp - behavior_history[1].timestamp) {
        perform_binding_substitution(cfg, &data->invoked_behavior);
    }

    zmk_behavior_invoke_binding(data->invoked_behavior, event, true);
    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_flow_key_binding_released(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
) {
    const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);
    struct behavior_flow_key_data *data = dev->data;
    zmk_behavior_invoke_binding(data->invoked_behavior, event, false);
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_flow_key_driver_api = {
    .binding_pressed = on_flow_key_binding_pressed,
    .binding_released = on_flow_key_binding_released,
#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
    .get_parameter_metadata = zmk_behavior_get_empty_param_metadata,
#endif
};

static int flow_key_listener(const zmk_event_t *eh);

ZMK_LISTENER(behavior_flow_key, flow_key_listener);
ZMK_SUBSCRIPTION(behavior_flow_key, zmk_position_state_changed);
ZMK_SUBSCRIPTION(behavior_flow_key, zmk_keycode_state_changed);

static const struct zmk_behavior_binding *get_behavior_at_position(uint16_t position) {
    zmk_keymap_layers_state_t layers = zmk_keymap_layer_state();
    // for (uint32_t i = 1 << 32; i > 0; i >> 1) {
    for (int8_t i = ZMK_KEYMAP_LAYERS_LEN; i > 0; i--) {
        if (!(layers & (1 << i))) continue;

        zmk_keymap_layer_id_t layer_id = zmk_keymap_layer_index_to_id(i);
        const struct zmk_behavior_binding *binding =
            zmk_keymap_get_layer_binding_at_idx(layer_id, position);

        if (binding == NULL) continue;
        if (strcmp(binding->behavior_dev, "transparent") == 0) continue;

        return binding;
    }

    return NULL;
}

static int position_state_changed_listener(const struct zmk_position_state_changed *ev) {
    if (!ev->state) return ZMK_EV_EVENT_BUBBLE;

    behavior_history[1] = behavior_history[0];
    behavior_history[0] = (struct behavior_history_item) {
        .timestamp = ev->timestamp,
        .binding   = get_behavior_at_position(ev->position),
    };

    return ZMK_EV_EVENT_BUBBLE;
}

static int keycode_state_changed_listener(const struct zmk_keycode_state_changed *ev) {
    if (ev->state) last_keycode_event = *ev;
    return ZMK_EV_EVENT_BUBBLE;
}

static int flow_key_listener(const zmk_event_t *eh) {
    struct zmk_keycode_state_changed *keycode_event;
    struct zmk_position_state_changed *position_event;

    if ((position_event = as_zmk_position_state_changed(eh)) != NULL) {
        return position_state_changed_listener(position_event);
    } else if ((keycode_event = as_zmk_keycode_state_changed(eh)) != NULL) {
        return keycode_state_changed_listener(keycode_event);
    }
    return ZMK_EV_EVENT_BUBBLE;
}


#define TRANSFORMED_BEHAVIORS(node)                                                                \
    {LISTIFY(DT_PROP_LEN(node, bindings), ZMK_KEYMAP_EXTRACT_BINDING, (, ), node)},

#define KR_INST(n)                                                                                 \
    static struct behavior_flow_key_data behavior_flow_key_data_##n = {};                          \
    static struct behavior_flow_key_config behavior_flow_key_config_##n = {                        \
        .timeout_ms = DT_INST_PROP_OR(n, timeout_ms, CONFIG_ZMK_flow_key_DEFAULT_TIMEOUT_MS),      \
        .bindings_count = DT_INST_PROP_LEN(n, bindings),                                           \
        .bindings = TRANSFORMED_BEHAVIORS(DT_DRV_INST(n))                                          \
    };                                                                                             \
    BEHAVIOR_DT_INST_DEFINE(                                                                       \
        n,                                   /* Instance Number (Automatically populated by macro) */ \
        NULL,                                /* Initialization Function */                            \
        NULL,                                /* Power Management Device Pointer */                    \
        &behavior_flow_key_data_##n,         /* Behavior Data Pointer */                              \
        &behavior_flow_key_config_##n,       /* Behavior Configuration Pointer */                     \
        POST_KERNEL,                         /* Initialization Level */                               \
        CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, /* Device Priority */                                    \
        &behavior_flow_key_driver_api        /* API struct */                                         \
    );

DT_INST_FOREACH_STATUS_OKAY(KR_INST)

#endif
