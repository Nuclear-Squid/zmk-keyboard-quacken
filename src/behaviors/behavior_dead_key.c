#define DT_DRV_COMPAT zmk_behavior_dead_key

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

struct behavior_dead_key_config {
    uint32_t dead_keycode;
};

static int on_dead_key_binding_pressed(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
) {
    const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);
    const struct behavior_dead_key_config *cfg = dev->config;

    struct zmk_behavior_binding kp_binding = {
        .behavior_dev = "key_press",
        .param1 = cfg->dead_keycode,
    };

    zmk_mod_flags_t mods_before = zmk_hid_get_explicit_mods();
    zmk_hid_masked_modifiers_set(MOD_LSFT | MOD_RSFT);

    zmk_behavior_invoke_binding(&kp_binding, event, true);
    zmk_behavior_invoke_binding(&kp_binding, event, false);

    zmk_mod_flags_t mods_after = zmk_hid_get_explicit_mods();
    zmk_hid_masked_modifiers_clear();

    zmk_mod_flags_t sticky_mods = mods_before ^ mods_after;
    if (sticky_mods != 0) zmk_hid_register_mods(sticky_mods);

    kp_binding.param1 = binding->param1;
    zmk_behavior_invoke_binding(&kp_binding, event, true);

    if (sticky_mods != 0) zmk_hid_unregister_mods(sticky_mods);

    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_dead_key_binding_released(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
) {
    const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);

    struct zmk_behavior_binding kp_binding = {
        .behavior_dev = "key_press",
        .param1 = binding->param1,
    };

    zmk_behavior_invoke_binding(&kp_binding, event, false);

    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api dead_key_driver_api = {
    .binding_pressed  = on_dead_key_binding_pressed,
    .binding_released = on_dead_key_binding_released,
};

#define DEAD_KEY_INST(n)                                                      \
    static struct behavior_dead_key_config behavior_dead_key_config_##n = {   \
        .dead_keycode = DT_INST_PROP(n, dead_keycode)                         \
    };                                                                        \
                                                                              \
    BEHAVIOR_DT_INST_DEFINE(                                                  \
        n,     /* Instance Number (Automatically populated by macro) */       \
        NULL,  /* Initialization Function */                                  \
        NULL,  /* Power Management Device Pointer */                          \
        NULL,  /* Behavior Data Pointer */                                    \
        &behavior_dead_key_config_##n,  /* Behavior Configuration Pointer */  \
        POST_KERNEL,  /* Initialization Level */                              \
        CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,  /* Device Priority */           \
        &dead_key_driver_api);  // API struct

DT_INST_FOREACH_STATUS_OKAY(DEAD_KEY_INST)

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
