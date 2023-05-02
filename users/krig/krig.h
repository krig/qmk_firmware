#include QMK_KEYBOARD_H

enum custom_keycodes {
    RGB_SLD = SAFE_RANGE,
    SQ_COLN, // ::
    SQ_AMPR, // &&
    SQ_PIPE, // ||
    SQ_PATH, // ../
    SQ_SLAS, // //
    SQ_PHEX, // 0x
	LLOCK    // layer lock
};


#define SQ_AA RALT(KC_W)
#define SQ_OE RALT(KC_P)
#define SQ_AE RALT(KC_Q)
#define ZOOM_IN LGUI(KC_PLUS)
#define ZOOM_UT LGUI(KC_MINS)
#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_ENT RCTL_T(KC_ENT)
#define CTL_SFT LCTL(KC_LSFT)
#define SFT_QUO RSFT_T(KC_QUOT)

#define MT_Z LSFT_T(KC_Z)
#define MT_X LALT_T(KC_X)
#define MT_C LGUI_T(KC_C)
#define MT_V LCTL_T(KC_V)

#define MT_SLSH LSFT_T(KC_SLSH)
#define MT_DOT LALT_T(KC_DOT)
#define MT_COMM LGUI_T(KC_COMM)
#define MT_M LCTL_T(KC_M)

#define WS_PREV LCTL(KC_LEFT)
#define WS_NEXT LCTL(KC_RIGHT)
#define WS_ALL LCTL(KC_UP)

enum krig_layers {
    // default layers
    _COLEMAK,
    _QWERTY,
    _GAME,

    // layer stack
    _LOWER,
    _RAISE,
    _NAV,
    _FUNS,
    _FUNS2 // Can't have a dedicated fkeys button otherwise
};

#define MO_LOWR MO(_LOWER)
#define MO_RAIS MO(_RAISE)
#define MO_FUNS MO(_FUNS2)
#define MO_NAV MO(_NAV)
#define DF_GAME DF(_GAME)
#define DF_QWER DF(_QWERTY)
#define DF_COLE DF(_COLEMAK)
#define NAV_CLN LT(_NAV, KC_SCLN)
#define NAV_MIN LT(_NAV, KC_MINS)
#define NAV_SPC LT(_NAV, KC_SPC)

bool krig_handle_sequence_keys(uint16_t keycode, keyrecord_t* record);
