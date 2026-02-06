#include <dt-bindings/zmk/keys.h>

// PC / Mac

#ifdef MACOS
#define CMD RG // Mac: Cmd key as main modifier
#else
#define CMD RC // PC: Ctrl key as main modifier
#endif

// Keyboard Layout

#ifdef KB_LAYOUT_ERGOL
#include "aliases_ergol.h"

#elifdef KB_LAYOUT_AZERTY
#include "aliases_azerty.h"

#elifdef KB_LAYOUT_QWERTY_LAFAYETTE
#include "aliases_qwerty_lafayette.h"

#else
#include "aliases_qwerty.h"

#endif

// Non-Alpha Actions

#define X_SHTAB &kp RS(TAB)
#define X_PREV  &kp LA(LEFT)
#define X_NEXT  &kp LA(RIGHT)
