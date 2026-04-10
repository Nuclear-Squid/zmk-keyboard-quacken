#include <dt-bindings/zmk/keys.h>

/**
 * Action Combos
 */

#define X_UNDO  &kp CMD(W)
#define X_CUT   &kp CMD(X)
#define X_COPY  &kp CMD(C)
#define X_PASTE &kp CMD(V)
#define X_REDO  &kp CMD(Y)

#define X_CTL_W &kp RC(Z)
#define X_SAVE  &kp CMD(S)
#define X_ALL   &kp CMD(Q)

/**
 * Arsenik Symbols:
 *   ^<>$% @&*'`
 *   {()}= \+-/"
 *   ~[]_# |!;:?
 */

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

// extra
#define S_COMMA &kp M
#define S_DOT   &kp LS(COMMA)
#define S_MONEY &kp RA(E)


/**
 * Non-ASCII Symbols
 * https://commons.wikimedia.org/wiki/File:KB_-_AZERTY_-_FR_-_Windows_-_FR.png
 */

/ {
  macros {
    DEAD_KEY(crc, &kp LBKT)   // circumflex
    DEAD_KEY(dia, &kp LBRC)   // diaeresis
    DEAD_KEY(tld, &kp RA(N2)) // tilde

    oe_base: oe_base {
      compatible = "zmk,behavior-macro";
      #binding-cells = <0>;
      bindings = <&macro_tap &kp O &kp E>;
    };
    oe_shift: oe_shift {
      compatible = "zmk,behavior-macro";
      #binding-cells = <0>;
      bindings
        = <&macro_press &kp RSHFT>
        , <&macro_tap &kp O &kp E>
        , <&macro_release &kp LSHFT>
        ;
    };

    ae_base: ae_base {
      compatible = "zmk,behavior-macro";
      #binding-cells = <0>;
      bindings = <&macro_tap &kp Q &kp E>;
    };
    ae_shift: ae_shift {
      compatible = "zmk,behavior-macro";
      #binding-cells = <0>;
      bindings
        = <&macro_press &kp RSHFT>
        , <&macro_tap &kp Q &kp E>
        , <&macro_release &kp LSHFT>
        ;
    };
  };
};

#define SA(key) RS(RA(key))

#define C_EACU &kp N2  // é
#define C_AGRV &kp N0  // à
#define C_EGRV &kp N7  // è
#define C_UGRV &kp SQT // ù
#define C_CCDL &kp N9  // ç

#define C_ACRC &crc Q  // â
#define C_ECRC &crc E  // ê
#define C_ICRC &crc I  // î
#define C_OCRC &crc O  // ô
#define C_UCRC &crc U  // û
#define C_YCRC &crc Y  // ŷ

#define C_ADIA &dia Q  // ä
#define C_EDIA &dia E  // ë
#define C_IDIA &dia I  // ï
#define C_ODIA &dia O  // ö
#define C_UDIA &dia U  // ü

#define C_ATLD &tld Q  // ã
#define C_OTLD &tld O  // õ
#define C_NTLD &tld N  // ñ

#define C_MU &kp PIPE  // µ

// spectal letters
#ifdef LINUX
  #define  C_OE &kp RA(K) // œ
  #define SC_OE &kp SA(K) // Œ
  #define  C_AE &kp RA(X) // æ
  #define SC_AE &kp SA(X) // Æ
#else
  #define  C_OE &oe_base  // oe
  #define SC_OE &oe_shift // OE
  #define  C_AE &ae_base  // ae
  #define SC_AE &ae_shift // AE
#endif
