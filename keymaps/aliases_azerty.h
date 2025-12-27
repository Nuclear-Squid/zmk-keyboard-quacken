#include <dt-bindings/zmk/keys.h>

// clang-format off

/**
 * Action Combos
 */

#ifndef CMD
#define CMD RC // assume PC shortcuts by default (Ctrl key)
#endif

#define X_UNDO  &kp CMD(W)
#define X_CUT   &kp CMD(X)
#define X_COPY  &kp CMD(C)
#define X_PASTE &kp CMD(V)
#define X_REDO  &kp CMD(Y)

#define X_CLOSE &kp CMD(Z)
#define X_SAVE  &kp CMD(S)
#define X_ALL   &kp CMD(Q)

#define X_SHTAB &kp RS(TAB)
#define X_PREV  &kp LA(LEFT)
#define X_NEXT  &kp LA(RIGHT)

/**
 * Arsenik Symbols:
 *   ^<>$% @&*'`
 *   {()}= \+-/"
 *   ~[]_# |!;:?
 */

#ifdef SYMBOLS_ON_ALTGR
  #include "symbols_altgr.h"
#else
  // first row
  #define S_CARET &kp RA(N9)
  #define S_LT    &kp NUBS
  #define S_GT    &kp PIPE2
  #define S_DLLR  &kp RBKT
  #define S_PRCNT &kp LS(SQT)
  #define S_AT    &kp RA(N0)
  #define S_AMPS  &kp N1
  #define S_STAR  &kp BSLH
  #define S_SQT   &kp N4
  #define S_GRAVE &spc RA(N7)
  // second row
  #define S_LBRC  &kp RA(N4)
  #define S_LPAR  &kp N5
  #define S_RPAR  &kp MINUS
  #define S_RBRC  &kp RA(EQUAL)
  #define S_EQUAL &kp EQUAL
  #define S_BSLH  &kp RA(N8)
  #define S_PLUS  &kp PLUS
  #define S_MINUS &kp N6
  #define S_FSLH  &kp LS(DOT)
  #define S_DQT   &kp N3
  // third row
  #define S_TILDE &spc RA(N2)
  #define S_LBKT  &kp RA(N5)
  #define S_RBKT  &kp RA(MINUS)
  #define S_UNDER &kp N8
  #define S_HASH  &kp RA(N3)
  #define S_PIPE  &kp RA(N6)
  #define S_EXCL  &kp FSLH
  #define S_SEMI  &kp COMMA
  #define S_COLON &kp DOT
  #define S_QMARK &kp LS(M)
#endif

#define S_COMMA &kp M
#define S_DOT   &kp LS(COMMA)

/ {
  macros {
  kpc:
    circumflex {
      compatible = "zmk,behavior-macro-one-param";
      #binding-cells = <1>;
      tap-ms = <0>;
      wait-ms = <0>;
      bindings
        = <&macro_tap &kp LBKT>
        , <&macro_pause_for_release>
        , <&macro_param_1to1>
        , <&kp MACRO_PLACEHOLDER>
        ;
    };
  spc:
    space_after_dk {
      compatible = "zmk,behavior-macro-one-param";
      #binding-cells = <1>;
      tap-ms = <0>;
      wait-ms = <0>;
      bindings
        = <&macro_param_1to1>
        , <&kp MACRO_PLACEHOLDER>
        , <&macro_pause_for_release>
        , <&macro_tap &kp SPACE>
        ;
    };
  };
};
