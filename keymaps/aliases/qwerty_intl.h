#include <dt-bindings/zmk/keys.h>

/**
 * Action Combos
 */

#define X_UNDO  &kp CMD(Z)
#define X_CUT   &kp CMD(X)
#define X_COPY  &kp CMD(C)
#define X_PASTE &kp CMD(V)
#define X_REDO  &kp CMD(Y)

#define X_CTL_W &kp RC(W)
#define X_SAVE  &kp CMD(S)
#define X_ALL   &kp CMD(A)

/**
 * Arsenik Symbols:
 *   ^<>$% @&*'`
 *   {()}= \+-/"
 *   ~[]_# |!;:?
 */

// first row
#define S_CARET &spc CARET
#define S_LT    &kp LT
#define S_GT    &kp GT
#define S_DLLR  &kp DLLR
#define S_PRCNT &kp PRCNT
#define S_AT    &kp AT
#define S_AMPS  &kp AMPS
#define S_STAR  &kp STAR
#define S_SQT   &spc SQT
#define S_GRAVE &spc GRAVE

// second row
#define S_LBRC  &kp LBRC
#define S_LPAR  &kp LPAR
#define S_RPAR  &kp RPAR
#define S_RBRC  &kp RBRC
#define S_EQUAL &kp EQUAL
#define S_BSLH  &kp BSLH
#define S_PLUS  &kp PLUS
#define S_MINUS &kp MINUS
#define S_FSLH  &kp FSLH
#define S_DQT   &spc DQT

// third row
#define S_TILDE &kp TILDE
#define S_LBKT  &kp LBKT
#define S_RBKT  &kp RBKT
#define S_UNDER &kp UNDER
#define S_HASH  &kp HASH
#define S_PIPE  &kp PIPE
#define S_EXCL  &kp EXCL
#define S_SEMI  &kp SEMI
#define S_COLON &kp COLON
#define S_QMARK &kp QMARK

// extra
#define S_COMMA &kp COMMA
#define S_DOT   &kp DOT
#define S_MONEY &kp DLLR


/**
 * Qwerty-intl-specific Symbols
 */

/ {
  macros {
    DEAD_KEY(acu, &kp SQT)    // acute accent or cedilla
    DEAD_KEY(dia, &kp DQT)    // diaeresis
    DEAD_KEY(grv, &kp GRAVE)  // grave accent
    DEAD_KEY(crc, &kp CARET)  // circumflex accent
    DEAD_KEY(tld, &kp TILDE)  // tilde

    DEAD_KEY_SHIFT(acus, &kp SQT)
    DEAD_KEY_SHIFT(dias, &kp DQT)
    DEAD_KEY_SHIFT(grvs, &kp GRAVE)
    DEAD_KEY_SHIFT(crcs, &kp CARET)
    DEAD_KEY_SHIFT(tlds, &kp TILDE)
  };
};

#define  C_AACU &acu  A  // á
#define SC_AACU &acus A  // Á
#define  C_EACU &acu  E  // é
#define SC_EACU &acus E  // É
#define  C_IACU &acu  I  // í
#define SC_IACU &acus I  // Í
#define  C_OACU &acu  O  // ó
#define SC_OACU &acus O  // Ó
#define  C_UACU &acu  U  // ú
#define SC_UACU &acus U  // Ú
#define  C_YACU &acu  Y  // ý
#define SC_YACU &acus Y  // Ý
#define  C_CCDL &acu  C  // ç
#define SC_CCDL &acus C  // ç

#define  C_AGRV &grv  A  // à
#define SC_AGRV &grvs A  // À
#define  C_EGRV &grv  E  // è
#define SC_EGRV &grvs E  // È
#define  C_IGRV &grv  I  // ì
#define SC_IGRV &grvs I  // Ì
#define  C_OGRV &grv  O  // ò
#define SC_OGRV &grvs O  // Ò
#define  C_UGRV &grv  U  // ù
#define SC_UGRV &grvs U  // Ù
#define  C_YGRV &grv  Y  // ỳ
#define SC_YGRV &grvs Y  // Ỳ

#define  C_ACRC &crc  A  // â
#define SC_ACRC &crcs A  // Â
#define  C_ECRC &crc  E  // ê
#define SC_ECRC &crcs E  // Ê
#define  C_ICRC &crc  I  // î
#define SC_ICRC &crcs I  // Î
#define  C_OCRC &crc  O  // ô
#define SC_OCRC &crcs O  // Ô
#define  C_UCRC &crc  U  // û
#define SC_UCRC &crcs U  // Û
#define  C_YCRC &crc  Y  // ŷ
#define SC_YCRC &crcs Y  // Ŷ

#define  C_ADIA &dia  A  // ä
#define SC_ADIA &dias A  // Ä
#define  C_EDIA &dia  E  // ë
#define SC_EDIA &dias E  // Ë
#define  C_IDIA &dia  I  // ï
#define SC_IDIA &dias I  // Ï
#define  C_ODIA &dia  O  // ö
#define SC_ODIA &dias O  // Ö
#define  C_UDIA &dia  U  // ü
#define SC_UDIA &dias U  // Ü
#define  C_YDIA &dia  Y  // ÿ
#define SC_YDIA &dias Y  // Ÿ

#define  C_NTLD &tld  N  // ñ
#define SC_NTLD &tlds N  // Ñ

#define C_MU &kp PIPE  // µ
