#include <dt-bindings/zmk/keys.h>

// clang-format off

// Available keyboard layouts
#define QWERTY 0
#define AZERTY 1
#define ERGOL  2


// Import the correct alias file
#ifndef KEYBOARD_LAYOUT
  #define KEYBOARD_LAYOUT QWERTY
#endif

#if KEYBOARD_LAYOUT == QWERTY
  #include "aliases_qwerty.h"
#elif KEYBOARD_LAYOUT == AZERTY
  #include "aliases_azerty.h"
#elif KEYBOARD_LAYOUT == ERGOL
  #include "aliases_ergol.h"
#else
  #error "Unknown keyboard layout"
#endif
