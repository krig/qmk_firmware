#include QMK_KEYBOARD_H

enum custom_keycodes {
    RGB_SLD = SAFE_RANGE,
    SQ_COLN, // ::
    SQ_AMPR, // &&
    SQ_PIPE, // ||
    SQ_PATH, // ../
    SQ_SLAS, // //
    SQ_PHEX, // 0x
	LLOCK,   // layer lock
    REPEAT,  // repeat key
    ALTREP,  // alternate repeat
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
#define CTL_QUO LCTL_T(KC_QUOT)
#define SFT_SPC LSFT_T(KC_SPC)

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

#define OSM_SFT OSM(MOD_LSFT)

enum krig_layers {
    // default layers
    _COLEMAK,
    _CTGAP,
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
#define TT_NAV TT(_NAV)
#define DF_GAME DF(_GAME)
#define DF_QWER DF(_QWERTY)
#define DF_COLE DF(_COLEMAK)
#define DF_CTGA DF(_CTGAP)
#define NAV_CLN LT(_NAV, KC_SCLN)
#define NAV_MIN LT(_NAV, KC_MINS)
#define NAV_SPC LT(_NAV, KC_SPC)
#define NAV_BSP LT(_NAV, KC_BSPC)
#define GUI_LFT LGUI(KC_LEFT)
#define GUI_RGT LGUI(KC_RGHT)
#define GUI__R   LGUI(KC_R)
#define GUI__T   LGUI(KC_T)
#define GUI__N   LGUI(KC_N)
#define GUI__Q   LGUI(KC_Q)
#define GUI__W   LGUI(KC_W)
#define GUI_SPC  LGUI(KC_SPC)

#define LOW_TAB  LT(_LOWER, KC_TAB)
#define RAI_BSP  LT(_RAISE, KC_BSPC)
#define RAI_ENT  LT(_RAISE, KC_ENT)

bool krig_handle_sequence_keys(uint16_t keycode, keyrecord_t* record);
