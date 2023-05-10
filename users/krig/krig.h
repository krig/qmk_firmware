#include QMK_KEYBOARD_H

enum custom_keycodes {
    RGB_SLD = SAFE_RANGE,
    SQ_COLN, // ::
    SQ_AMPR, // &&
    SQ_PIPE, // ||
    SQ_PATH, // ../
    SQ_SLAS, // //
    SQ_PHEX, // 0x
    SQ_LTLT, // <<
    SQ_GTGT, // >>
    SQ_RTAR, // ->
    SQ_LTAR, // <-
    LLOCK,   // layer lock
    REPEAT,  // repeat key
    ALTREP,  // alternate repeat
};

enum krig_layers {
    // default layers
    _QWERTY,
    _ENGRAM,
    _GAME,

    // primary thumb layers
    _LSYM,
    _RSYM,

    // secondary thumb layers
    _NUM,
    _NAV,
    _MACROS,
    _FUNS,
};

// Default layer switching
#define DF_QWER DF(_QWERTY)
#define DF_ENGR DF(_ENGRAM)
#define DF_GAME DF(_GAME)

// Layer switching
#define MO_LSYM MO(_LSYM)
#define MO_RSYM MO(_RSYM)
#define MO_NUM MO(_NUM)
#define MO_NAV MO(_NAV)
#define MO_MACR MO(_MACROS)
#define MO_FUNS MO(_FUNS)

// Mac OS navigation shortcuts
#define GUI_LFT LGUI(KC_LEFT)
#define GUI_RGT LGUI(KC_RGHT)
#define GUI__C   LGUI(KC_C)
#define GUI__N   LGUI(KC_N)
#define GUI__Q   LGUI(KC_Q)
#define GUI__R   LGUI(KC_R)
#define GUI__T   LGUI(KC_T)
#define GUI__V   LGUI(KC_V)
#define GUI__W   LGUI(KC_W)
#define GUI__X   LGUI(KC_X)
#define GUI__Z   LGUI(KC_Z)
#define GUI_SPC  LGUI(KC_SPC)

// Mac OS spaces navigation
#define WS_PREV LCTL(KC_LEFT)
#define WS_NEXT LCTL(KC_RIGHT)
#define WS_DESK LCTL(KC_DOWN)
#define WS_ALL LCTL(KC_UP)

// One shot modifiers
#define OSM_ALT OSM(MOD_LALT)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_GUI OSM(MOD_LGUI)
#define OSM_SFT OSM(MOD_LSFT)

// Planck specials
#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_ENT RCTL_T(KC_ENT)
#define CTL_SFT LCTL(KC_LSFT)
#define SFT_QUO RSFT_T(KC_QUOT)
#define CTL_QUO LCTL_T(KC_QUOT)
#define SFT_SPC LSFT_T(KC_SPC)

// Swedish letters
#define SQ_AA RALT(KC_W)
#define SQ_OE RALT(KC_P)
#define SQ_AE RALT(KC_Q)

// Convenience
#define ZOOM_IN LGUI(KC_PLUS)
#define ZOOM_UT LGUI(KC_MINS)


void krig_clear_caps_word_last_key(void);
bool krig_handle_sequence_keys(uint16_t keycode, keyrecord_t* record);
