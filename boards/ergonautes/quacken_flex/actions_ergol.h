#include <dt-bindings/zmk/keys.h>

// Action Combos
// clang-format off

#ifndef CMD
#define CMD RC // assume PC shortcuts by default (Ctrl key)
#endif

#define X_UNDO  &kp CMD(Z)
#define X_CUT   &kp CMD(X)
#define X_COPY  &kp CMD(W)
#define X_PASTE &kp CMD(V)
#define X_REDO  &kp CMD(P)

#define X_CLOSE &kp CMD(T)
#define X_SAVE  &kp CMD(S)
#define X_ALL   &kp CMD(A)

#define X_SHTAB &kp RS(TAB)
#define X_PREV  &kp LA(LEFT)
#define X_NEXT  &kp LA(RIGHT)
