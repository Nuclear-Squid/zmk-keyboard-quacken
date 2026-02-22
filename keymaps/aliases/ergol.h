#include <dt-bindings/zmk/keys.h>
#include "../hold_taps.dtsi"

/**
 * Action Combos
 */

#define X_UNDO  &kp CMD(Z)
#define X_CUT   &kp CMD(X)
#define X_COPY  &kp CMD(W)
#define X_PASTE &kp CMD(V)
#define X_REDO  &kp CMD(P)

#define X_CLOSE &kp CMD(T)
#define X_SAVE  HRM_GUI(CMD(S))
#define X_ALL   HRM_SFT(CMD(A))

/**
 * Arsenik Symbols:
 *   ^<>$% @&*'`
 *   {()}= \+-/"
 *   ~[]_# |!;:?
 */

// first row
#define S_CARET &kp CARET
#define S_LT    &kp RA(W)
#define S_GT    &kp RA(E)
#define S_DLLR  &kp DLLR
#define S_PRCNT &kp PRCNT
#define S_AT    &kp RPAR
#define S_AMPS  &kp AMPS
#define S_STAR  &kp STAR
#define S_SQT   &kp SQT
#define S_GRAVE &kp GRAVE

// second row
#define S_LBRC  HRM_SFT(LBRC)
#define S_LPAR  HRM_GUI(RA(S))
#define S_RPAR  HRM_CTL(RA(D))
#define S_RBRC  HRM_ALT(RBRC)
#define S_EQUAL &kp EQUAL
#define S_BSLH  &kp BSLH
#define S_PLUS  HRM_ALT(PLUS)
#define S_MINUS HRM_CTL(C)
#define S_FSLH  HRM_GUI(MINUS)
#define S_DQT   HRM_SFT(DQT)

// third row
#define S_TILDE &kp TILDE
#define S_LBKT  &kp LBKT
#define S_RBKT  &kp RBKT
#define S_UNDER &kp UNDER
#define S_HASH  &kp LPAR
#define S_PIPE  &kp PIPE
#define S_EXCL  &kp RA(M)
#define S_SEMI  &kp RA(COMMA)
#define S_COLON &kp RA(DOT)
#define S_QMARK &kp RA(FSLH)

// extra
#define S_COMMA &kp DOT
#define S_DOT   &kp N
#define S_MONEY &kp LS(N1)

