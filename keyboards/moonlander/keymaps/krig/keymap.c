#include "krig.h"
#include "custom_keys.h"
#include "features/custom_shift_keys.h"
#include "features/krig_caps_word.h"
#include "eeprom.h"

enum custom_layers {
    _QWERTY,
    _APTV3,
    _GAME,
    _LANG,
    _LOWER,
    _RAISE,
    _ADJUST,
};

const custom_shift_key_t custom_shift_keys[] = {
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys)/sizeof(custom_shift_key_t);

#define M_LOWER MO(_LOWER)
#define M_RAISE MO(_RAISE)
#define DF_QWER  DF(_QWERTY)
#define DF_APT  DF(_APTV3)
#define DF_GAME  DF(_GAME)
#define M_LANG LT(_LANG, KC_SLSH)

#define MOON_LED_LEVEL LED_LEVEL


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_moonlander(
     KC_GRV, KC_1,     KC_2,    KC_3,    KC_4,    KC_5, KC_TILD,   SQ_OE,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL,
     KC_TAB, KC_Q,     KC_W,    KC_E,    KC_R,    KC_T, KC_MINS,   SQ_AE,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
    CTL_ESC, KC_A,     KC_S,    KC_D,    KC_F,    KC_G, KC_UNDS,   SQ_AA,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, CTL_ENT,
    OSM_SFT, KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M, KC_COMM,  KC_DOT,  M_LANG, KC_RSFT,
    CW_TOGG, CTL_SFT,  KC_LALT, KC_LGUI, M_LOWER,       KC_CIRC,  KC_DLR,          M_RAISE, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
                                     KC_SPC, KC_TAB, KC_LGUI,  KC_RGUI,  KC_BSPC,  SC_SENT
  ),
  [_APTV3] = LAYOUT_moonlander(
     KC_GRV, KC_1,     KC_2,    KC_3,    KC_4,    KC_5, KC_TILD,   SQ_OE,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL,
     KC_TAB, KC_W,     KC_G,    KC_D,    KC_F,    KC_B, KC_MINS,   SQ_AE,    KC_Q,    KC_L,    KC_U,    KC_O,    KC_Y, KC_BSPC,
    CTL_ESC, KC_R,     KC_S,    KC_T,    KC_H,    KC_K, KC_UNDS,   SQ_AA,    KC_J,    KC_N,    KC_E,    KC_A,    KC_I, CTL_ENT,
    OSM_SFT, KC_X,     KC_C,    KC_M,    KC_P,    KC_V,                      KC_Z, KC_COMM,  KC_DOT,  KC_QUOT, M_LANG, KC_RSFT,
    CW_TOGG, CTL_SFT,  KC_LALT, KC_LGUI, M_LOWER,       KC_CIRC,  KC_DLR,          M_RAISE, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
                                     KC_SPC, KC_TAB, KC_LGUI,  KC_RGUI,  KC_BSPC,  SC_SENT
  ),
  [_GAME] = LAYOUT_moonlander(
     KC_ESC, KC_GRV,   KC_1,     KC_2,    KC_3,    KC_4,    KC_5,   SQ_OE,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL,
     KC_TAB, KC_TAB,   KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,   SQ_AE,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
    KC_LSFT, KC_LCTL,  KC_A,     KC_S,    KC_D,    KC_F,    KC_G,   SQ_AA,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, CTL_ENT,
    KC_LCTL, KC_LSFT,  KC_Z,     KC_X,    KC_C,    KC_V,                      KC_N,    KC_M, KC_COMM,  KC_DOT,  M_LANG, KC_RSFT,
    CW_TOGG, CTL_SFT,  KC_LALT, KC_LGUI, M_LOWER,       KC_CIRC,  KC_DLR,          M_RAISE, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
                                     KC_SPC, KC_TAB, KC_LGUI,  KC_RGUI,  KC_BSPC,  SC_SENT
  ),
  [_LANG] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,   SQ_AA,   SQ_AE,   SQ_OE, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, KC_TRNS, _______,
    _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______
  ),
  [_LOWER] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,    KC_1,    KC_2,    KC_3, _______, _______, _______,  KC_INS, KC_PGDN,   KC_UP, KC_PGUP,  KC_DEL, _______,
    _______,    KC_0,    KC_4,    KC_5,    KC_6, _______, _______, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, _______,
    _______, SQ_PHEX,    KC_7,    KC_8,    KC_9, _______,                   _______, SQ_PATH, ZOOM_UT, ZOOM_IN, KC_BSLS, _______,
    _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______
  ),
  [_RAISE] = LAYOUT_moonlander(
    _______, _______, SQ_LTLT, SQ_GTGT, SQ_PATH, _______, _______, _______, SQ_PIPE, SQ_AMPR, SQ_LTAR, SQ_RTAR, _______, _______,
    _______,  KC_GRV, KC_TILD, KC_HASH, KC_PERC,   KC_LT, _______, _______, SQ_COLN, KC_AMPR, KC_LBRC, KC_RBRC, SQ_EXPI, _______,
    _______, KC_EXLM, KC_MINS, KC_PLUS,  KC_EQL,   KC_AT, _______, _______, KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN, _______,
    _______, KC_QUES, KC_SLSH, KC_ASTR, KC_UNDS,   KC_GT,                   KC_CIRC,  KC_DLR, KC_LCBR, KC_RCBR, KC_BSLS, _______,
    _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______
  ),
  [_ADJUST] = LAYOUT_moonlander(
    DF_QWER,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, _______, _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
     DF_APT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    DF_GAME, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, QK_BOOT,
    _______, _______, _______, _______, _______, _______
  )
};


extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

#define __off__ {0, 0, 0}
#define _YELLOW {0xff, 0xea, 0x00}
#define _RED___ {0xff, 0x24, 0x00}
#define _BLUE__ {0x00, 0x7f, 0xff}
#define _CYAN__ {0x14, 0xa3, 0xc7}
#define _MINT__ {0x9a, 0xe9, 0xa1}
#define _TANGR_ {0xff, 0x84, 0x00}

const uint8_t PROGMEM ledrgb[][RGB_MATRIX_LED_COUNT][3] = {
    [_GAME] = LED_LAYOUT_moonlander(
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, _MINT__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, _MINT__, _MINT__, _MINT__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__, __off__,                    __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__,          __off__,  __off__,          __off__, __off__, __off__, __off__, __off__,
                                            __off__, __off__, __off__,  __off__, __off__, __off__
    ),
    [_LOWER] = LED_LAYOUT_moonlander(
        _TANGR_, _TANGR_, _TANGR_, _TANGR_, _TANGR_, _TANGR_, _TANGR_,  _TANGR_, _TANGR_, _TANGR_, _TANGR_, _TANGR_, _TANGR_, _TANGR_,
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__, __off__,                    __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__,          __off__,  __off__,          __off__, __off__, __off__, __off__, __off__,
                                            __off__, __off__, __off__,  __off__, __off__, __off__
    ),
    [_RAISE] = LED_LAYOUT_moonlander(
        _CYAN__, _CYAN__, _CYAN__, _CYAN__, _CYAN__, _CYAN__, _CYAN__,  _CYAN__, _CYAN__, _CYAN__, _CYAN__, _CYAN__, _CYAN__, _CYAN__,
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__, __off__,                    __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__,          __off__,  __off__,          __off__, __off__, __off__, __off__, __off__,
                                            __off__, __off__, __off__,  __off__, __off__, __off__
    ),
    [_ADJUST] = LED_LAYOUT_moonlander(
        _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__,  _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__,
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__, __off__,                    __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__,          __off__,  __off__,          __off__, __off__, __off__, __off__, _RED___,
                                            __off__, __off__, __off__,  __off__, __off__, __off__
    )
};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    RGB rgb;
    rgb.r = ledrgb[layer][i][0];
    rgb.g = ledrgb[layer][i][1];
    rgb.b = ledrgb[layer][i][2];
    if (!rgb.r && !rgb.g && !rgb.b) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
    if (keyboard_config.disable_layer_led) {
        return false;
    }

    uint8_t curr = biton32(layer_state);
    if (curr == _LOWER ||
        curr == _RAISE ||
        curr == _GAME ||
        curr == _ADJUST)
        set_layer_color(curr);
    else if (rgb_matrix_get_flags() == LED_FLAG_NONE)
        rgb_matrix_set_color_all(0, 0, 0);
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // handle custom shift keys like ./:, ,/; etc.
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }
    // handle sequence keys like ::, && etc.
    if (!process_custom_keycodes(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case DF_QWER:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case DF_APT:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_APTV3);
            }
            return false;
        case DF_GAME:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_GAME);
            }
            return false;
    };
    return true;
}

bool caps_word_press_user(uint16_t keycode) {
    return krig_caps_word_press(keycode);
}

void caps_word_set_user(bool active) {
    ML_LED_6(active);
    krig_caps_word_set(active);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    ML_LED_1(false);
    ML_LED_2(false);
    ML_LED_3(false);
    ML_LED_4(false);
    ML_LED_5(false);

    if (default_layer_state == _QWERTY) {
            ML_LED_1(1);
    } else if (default_layer_state == _APTV3) {
            ML_LED_2(1);
    } else if (default_layer_state == _GAME) {
            ML_LED_3(1);
    }

    switch (get_highest_layer(state)) {
        case _LOWER:
            ML_LED_4(1);
            break;
        case _RAISE:
            ML_LED_5(1);
            break;
        case _LANG:
            ML_LED_1(1);
            ML_LED_2(1);
            ML_LED_3(1);
            break;
        case _ADJUST:
            ML_LED_4(1);
            ML_LED_5(1);
            break;
        default:
            break;
    }

    return state;
}

