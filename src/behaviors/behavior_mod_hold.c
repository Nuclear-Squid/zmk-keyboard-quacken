/*
 * Dead Key Behavior
 * prefix a key press with an unshifted-keycode, to more easilly and reliably
 * use dead keys on the host layout to write more complex symbols.
 */

#define DT_DRV_COMPAT zmk_behavior_mod_hold

#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <drivers/behavior.h>
#include <dt-bindings/zmk/modifiers.h>
#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>
#include <zmk/hid.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/behavior.h>

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

struct behavior_mod_hold_config {
    struct zmk_behavior_binding binding;
    zmk_mod_flags_t mods_to_hold;
};

struct active_mod_hold {
    struct zmk_behavior_binding invoked_binding;
    uint32_t position;
    zmk_mod_flags_t mods_to_hold;
};

#define MOD_HOLD_UNUSED_POISTION UINT32_MAX
#define MOD_HOLD_MAX_HELD CONFIG_ZMK_BEHAVIOR_MOD_HOLD_MAX_HELD
static struct active_mod_hold active_mod_holds[MOD_HOLD_MAX_HELD];


static struct active_mod_hold *store_mod_hold(
    struct zmk_behavior_binding binding,
    zmk_mod_flags_t mods_to_hold,
    uint32_t position
) {
    for (int i = 0; i < MOD_HOLD_MAX_HELD; i++) {
        if (active_mod_holds[i].position != MOD_HOLD_UNUSED_POISTION) continue;

        active_mod_holds[i] = (struct active_mod_hold) {
            .invoked_binding = binding,
            .mods_to_hold = mods_to_hold,
            .position = position,
        };

        return &active_mod_holds[i];
    }

    return NULL;
}


static struct active_mod_hold *find_mod_hold(uint32_t position) {
    for (int i = 0; i < MOD_HOLD_MAX_HELD; i++) {
        if (active_mod_holds[i].position == position) {
            return &active_mod_holds[i];
        }
    }
    return NULL;
}


static void clear_mod_hold(struct active_mod_hold* mod_hold) {
    mod_hold->position = MOD_HOLD_UNUSED_POISTION;
    mod_hold->mods_to_hold = 0;
}


static int on_mod_hold_binding_pressed(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
) {
    const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);
    const struct behavior_mod_hold_config *cfg = dev->config;

    struct zmk_behavior_binding invoked_behavior = *binding;
    invoked_behavior.behavior_dev = cfg->binding.behavior_dev;

    LOG_DBG(
        "Invoking behavior %s %x %x (press)",
        invoked_behavior.behavior_dev,
        invoked_behavior.param1,
        invoked_behavior.param2
    );

    store_mod_hold(invoked_behavior, cfg->mods_to_hold, event.position);
    zmk_behavior_invoke_binding(&invoked_behavior, event, true);

    return ZMK_BEHAVIOR_OPAQUE;
}


static int on_mod_hold_binding_released(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
) {
    const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);
    const struct behavior_mod_hold_config *cfg = dev->config;

    struct active_mod_hold *mod_hold = find_mod_hold(event.position);

    LOG_DBG(
        "Invoking behavior %s %x %x (release)",
        mod_hold->invoked_binding.behavior_dev,
        mod_hold->invoked_binding.param1,
        mod_hold->invoked_binding.param2
    );

    zmk_behavior_invoke_binding(&mod_hold->invoked_binding, event, false);
    zmk_hid_unregister_mods(cfg->mods_to_hold);
    clear_mod_hold(mod_hold);

    return ZMK_BEHAVIOR_OPAQUE;
}


static const struct behavior_driver_api mod_hold_driver_api = {
    .binding_pressed  = on_mod_hold_binding_pressed,
    .binding_released = on_mod_hold_binding_released,
};


static int behavior_mod_hold_init(const struct device *dev) {
    static bool first_run = true;
    if (!first_run) return 0;

    for (int i = 0; i < MOD_HOLD_MAX_HELD; i++) {
        active_mod_holds[i].position = MOD_HOLD_UNUSED_POISTION;
    }

    return 0;
}


// We *should* use the `modifiers_state_changed` event listener, but for some
// reason, this event is never raised, and hasn’t been for the last 5 years
// (and counting), so we’re using the `keycode_state_changed` event instead.
static int mod_hold_keycode_state_changed_listener(const zmk_event_t *eh);

ZMK_LISTENER(behavior_mod_hold, mod_hold_keycode_state_changed_listener);
ZMK_SUBSCRIPTION(behavior_mod_hold, zmk_keycode_state_changed);

static zmk_mod_t keycode_to_mod(uint8_t usage_page, uint32_t keycode) {
    if (!is_mod(usage_page, keycode)) return 0;
    return 1 << (keycode - HID_USAGE_KEY_KEYBOARD_LEFTCONTROL);
}

// Cancle the keycode raised event for the modifiers we want to hold.
static int mod_hold_keycode_state_changed_listener(const zmk_event_t *eh) {
    struct zmk_keycode_state_changed *ev = as_zmk_keycode_state_changed(eh);
    if (ev == NULL || ev->state) return ZMK_EV_EVENT_BUBBLE;

    zmk_mod_t released_mod = keycode_to_mod(ev->usage_page, ev->keycode);
    if (released_mod == 0) return ZMK_EV_EVENT_BUBBLE;

    LOG_DBG("Released mod = %x", released_mod);

    for (int i = 0; i < MOD_HOLD_MAX_HELD; i++) {
        if (active_mod_holds[i].position == MOD_HOLD_UNUSED_POISTION) continue;
        if ((released_mod & active_mod_holds[i].mods_to_hold) != 0) {
            LOG_DBG("Canceling the release of modifier %x", released_mod);
            return ZMK_EV_EVENT_CAPTURED;
        }
    }

    return ZMK_EV_EVENT_BUBBLE;
}


#if 0
static int mod_hold_modifiers_state_changed_listener(const zmk_event_t *eh);

ZMK_LISTENER(behavior_mod_hold, mod_hold_modifiers_state_changed_listener);
ZMK_SUBSCRIPTION(behavior_mod_hold, zmk_modifiers_state_changed);

// Cancle the modifier state changed event if it releases a mod to hold.
static int mod_hold_modifiers_state_changed_listener(const zmk_event_t *eh) {
    struct zmk_modifiers_state_changed *ev = as_zmk_modifiers_state_changed(eh);
    if (ev == NULL || ev->state) return ZMK_EV_EVENT_BUBBLE;

    zmk_mod_flags_t every_held_mods = 0;
    for (int i = 0; i < MOD_HOLD_MAX_HELD; i++) {
        every_held_mods |= active_mod_holds[i].mods_to_hold;
    }

    LOG_DBG("Modifiers before = %x", ev->modifiers);
    ev->modifiers &= ~every_held_mods;
    LOG_DBG("Modifiers after  = %x", ev->modifiers);
    return ev->modifiers == 0 ? ZMK_EV_EVENT_CAPTURED : ZMK_EV_EVENT_BUBBLE;

    // zmk_mod_flags_t mods_to_cancel_release = every_held_mods & ev->modifiers;
    // if (mods_to_cancel_release != 0) {
    //     struct zmk_modifiers_state_changed_event dupe_ev =
    //         copy_raised_zmk_modifiers_state_changed(ev);
    //
    //     dupe_ev.data.modifiers &= ~(mods_to_cancel_release);
    //     ZMK_EVENT_RAISE_AFTER(dupe_ev, behavior_mod_hold);
    //     return ZMK_EV_EVENT_CAPTURED;
    // }
    //
    // return ZMK_EV_EVENT_BUBBLE;
}
#endif


#define INST_KEYMAP_EXTRACT_BINDING(n, binding_name) {                        \
    .behavior_dev = DEVICE_DT_NAME(DT_INST_PHANDLE(n, binding_name)),         \
    .param1 = DT_INST_PHA_BY_IDX_OR(n, binding_name, 0, param1, 0),           \
    .param2 = DT_INST_PHA_BY_IDX_OR(n, binding_name, 1, param2, 0),           \
}

#define mod_hold_INST(n)                                                      \
    static struct behavior_mod_hold_config behavior_mod_hold_config_##n = {   \
        .mods_to_hold = DT_INST_PROP(n, mods_to_hold),                        \
        .binding = INST_KEYMAP_EXTRACT_BINDING(n, binding)                    \
    };                                                                        \
                                                                              \
    BEHAVIOR_DT_INST_DEFINE(                                                  \
        n,     /* Instance Number (Automatically populated by macro) */       \
        behavior_mod_hold_init,  /* Initialization Function */                \
        NULL,  /* Power Management Device Pointer */                          \
        NULL,  /* Behavior Data Pointer */                                    \
        &behavior_mod_hold_config_##n,  /* Behavior Configuration Pointer */  \
        POST_KERNEL,  /* Initialization Level */                              \
        CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,  /* Device Priority */           \
        &mod_hold_driver_api);  // API struct

DT_INST_FOREACH_STATUS_OKAY(mod_hold_INST)

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
