#include <behaviors.dtsi>
#include <dt-bindings/zmk/keys.h>

// clang-format off

/**
 * Home-Row Mods
 */

#ifndef HRM
#define HRM_S &kp S
#define HRM_D &kp D
#define HRM_F &kp F
#define HRM_J &kp J
#define HRM_K &kp K
#define HRM_L &kp L
#else
#define HRM_S &hrm LGUI S
#define HRM_D &hrm LCTL D
#define HRM_F &hrm LALT F
#define HRM_J &hrm LALT J
#define HRM_K &hrm RCTL K
#define HRM_L &hrm RGUI L
#endif

/**
 * Timing is Key!
 */

#ifndef TAPPING_TERM
#define TAPPING_TERM 300
#endif

#define EZ_SL(layer) bsl (layer) (layer)
#define EZ_SK(mod)   bsk (mod) (mod)
&sl{ quick-release; }; // seems useless (works fine without)
&sk{ quick-release; }; // must have (lots of false positives otherwise)

/ {
  behaviors {
    hrm: homerow_mods {
      compatible = "zmk,behavior-hold-tap";
      #binding-cells = <2>;
      tapping-term-ms = <TAPPING_TERM>;
      flavor = "tap-preferred";
      bindings = <&kp>, <&kp>;
    };
    sc: space_cadet { // same as lt, but with hold-preferred
      compatible = "zmk,behavior-hold-tap";
      #binding-cells = <2>;
      tapping-term-ms = <TAPPING_TERM>;
      flavor = "hold-preferred";
      bindings = <&mo>, <&kp>;
    };

    // like ZMK's sticky layer (sl) but with a more robust timing
    osl: one_shot_layer {
      compatible = "zmk,behavior-macro-one-param";
      #binding-cells = <1>;
      tap-ms = <0>;
      wait-ms = <0>;
      bindings = <&macro_param_1to1>, <&macro_tap &sl MACRO_PLACEHOLDER>;
    };
    bsl: better_sticky_layer {
      compatible = "zmk,behavior-hold-tap";
      #binding-cells = <2>;
      tapping-term-ms = <TAPPING_TERM>;
      flavor = "tap-preferred";
      bindings = <&mo>, <&osl>;
    };

    // like ZMK's sticky key (sk) but with a more robust timing
    osm: one_shot_modifier {
      compatible = "zmk,behavior-macro-one-param";
      #binding-cells = <1>;
      tap-ms = <0>;
      wait-ms = <0>;
      bindings = <&macro_param_1to1>, <&macro_tap &sk MACRO_PLACEHOLDER>;
    };
    bsk: better_sticky_key {
      compatible = "zmk,behavior-hold-tap";
      #binding-cells = <2>;
      tapping-term-ms = <TAPPING_TERM>;
      flavor = "tap-preferred";
      bindings = <&kp>, <&osm>;
    };
  };
};
