#include QMK_KEYBOARD_H

enum custom_keycodes {
    SQ_COLN = SAFE_RANGE, // ::
    SQ_AMPR,
    SQ_PIPE,
    SQ_PATH,
    SQ_PHEX // 0x
};


#define SQ_AA RALT(KC_W)
#define SQ_OE RALT(KC_P)
#define SQ_AE RALT(KC_Q)
#define ZOOM_IN LGUI(KC_PLUS)
#define ZOOM_UT LGUI(KC_MINS)
#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_SFT LCTL(KC_LSFT)
#define SFT_QUO RSFT_T(KC_QUOT)

#define WS_PREV LCTL(KC_LEFT)
#define WS_NEXT LCTL(KC_RIGHT)
#define WS_ALL LCTL(KC_UP)
