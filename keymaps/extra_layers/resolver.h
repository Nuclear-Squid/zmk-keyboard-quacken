#if defined CFG_OCSINE + defined CFG_SWIFT + defined CFG_SWALLOW + defined CFG_KINGFISHER > 1
  #error "Please select only up to one keyboard geometry at a time"
#endif

#if defined KB_LAYOUT_ERGOL + defined KB_LAYOUT_AZERTY + defined KB_LAYOUT_QWERTY_LAFAYETTE > 1
  #error "Please select only up to one keyboard layout at a time"
#endif


#ifdef KB_LAYOUT_AZERTY
  #include "azerty.dtsi"

#elif defined KB_LAYOUT_ERGOL && (defined CFG_OCSINE || defined CFG_SWIFT || defined CFG_SWALLOW || defined CFG_KINGFISHER)
  #include "ergol_hummingbird.dtsi"

#endif
