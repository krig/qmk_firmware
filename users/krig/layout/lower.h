#ifdef KRIG_34KEY
#define LOWER_L1 _______, CW_TOGG, CMD_GRV, CMD_TAB, SW_CTLW
#define LOWER_L2  OS_CTL,  OS_ALT,  OS_GUI,  OS_SFT, OS_RALT
#define LOWER_L3  GUI__Z,  GUI__X,  GUI__C,  GUI__V, MO(_LANG)
#else
#define LOWER_L1 _______, KC_1,    KC_2,    KC_3,       KC_K
#define LOWER_L2    KC_0, KC_4,    KC_5,    KC_6,       KC_J
#define LOWER_L3 SQ_PHEX, KC_7,    KC_8,    KC_9,    S(KC_G)
#endif

#define LOWER_R1 KC_INS, KC_HOME,   KC_UP,  KC_END, QK_AREP
#define LOWER_R2 KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT,  QK_REP
#define LOWER_R3 _______, KC_PGDN, KC_PGUP, ZOOM_IN, ZOOM_UT

