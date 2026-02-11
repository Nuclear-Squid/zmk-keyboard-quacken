#include <dt-bindings/zmk/keys.h>

/**
 * Action Combos
 */

#define X_UNDO  &kp CMD(SQT)
#define X_CUT   &kp CMD(Q)
#define X_COPY  &kp CMD(COMMA)
#define X_PASTE &kp CMD(V)
#define X_REDO  &kp CMD(P)

#define X_CLOSE &kp CMD(T)
#define X_SAVE  &kp CMD(S)
#define X_ALL   &kp CMD(A)

/**
 * Arsenik Symbols:
 *   ^<>$% @&*'`
 *   {()}= \+-/"
 *   ~[]_# |!;:?
 */

// first row
#define S_CARET &kp RA(N6)
#define S_LT    &kp RA(N4)
#define S_GT    &kp RA(N7)
#define S_DLLR  &kp GRAVE
#define S_PRCNT &kp EQUAL
#define S_AT    &kp N6
#define S_AMPS  &kp RA(R)
#define S_STAR  &kp KP_MULTIPLY
#define S_SQT   &kp RA(C)
#define S_GRAVE &grave

// second row
#define S_LBRC  &kp LS(RA(N4))
#define S_LPAR  &kp N4
#define S_RPAR  &kp N7
#define S_RBRC  &kp LS(RA(N7))
#define S_EQUAL &kp MINUS
#define S_BSLH  &kp RA(Y)
#define S_PLUS  &kp KP_PLUS
#define S_MINUS &kp KP_MINUS
#define S_FSLH  &kp KP_DIVIDE
#define S_DQT   &kp N1

// third row
#define S_TILDE &kp RA(LBKT)
#define S_LBKT  &kp LS(N4)
#define S_RBKT  &kp LS(N7)
#define S_HASH  &kp N5
#define S_UNDER &kp LS(N3)
#define S_PIPE  &kp RA(Q)
#define S_EXCL  &kp LS(DOT)
#define S_SEMI  &kp LS(N)
#define S_COLON &kp RA(N)
#define S_QMARK &kp LS(O)

// extra
#define S_COMMA &kp DOT
#define S_DOT   &kp N

/ {
  behaviors {
    grave: grave {
      compatible = "zmk,behavior-macro";
      #binding-cells = <0>;
      tap-ms = <0>;
      wait-ms = <0>;
      bindings = <&kp RA(Z) &kp SPACE>;
    };
  };
};
