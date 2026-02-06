#include <dt-bindings/zmk/keys.h>

#ifdef KB_LAYOUT_ERGOL
#include "aliases_ergol.h"
#elifdef KB_LAYOUT_AZERTY
#include "aliases_azerty.h"
#else
#include "aliases_qwerty.h"
#endif
