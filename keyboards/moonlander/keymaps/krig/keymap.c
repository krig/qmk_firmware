#include "krig.h"

#define MOON_LED_LEVEL LED_LEVEL
#define LAYOUT_wrapper(...)             LAYOUT_moonlander(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_wrapper(
     KC_GRV, NUMROW_L, KC_TILD,   SQ_OE,    NUMROW_R, KC_DEL,
     KC_TAB, QWERTY_L1, KC_MINS,   SQ_AE,    QWERTY_R1, KC_BSPC,
    CTL_ESC, QWERTY_L2, KC_UNDS,   SQ_AA,    QWERTY_R2, CTL_ENT,
    OSM_SFT, QWERTY_L3,                      QWERTY_R3, KC_RSFT,
    CW_TOGG, CTL_SFT,  KC_LALT, KC_LGUI, THUMB_L2,       KC_CIRC,  KC_DLR,          THUMB_R2, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
                                     THUMB_L1, KC_TAB, KC_LGUI,  KC_RGUI,  KC_BSPC,  THUMB_R1
  ),
  [_ALTERN] = LAYOUT_wrapper(
     KC_GRV, NUMROW_L, KC_TILD,   SQ_OE,    NUMROW_R, KC_DEL,
     KC_TAB, ALTERN_L1, KC_MINS,   SQ_AE,    ALTERN_R1, KC_BSPC,
    CTL_ESC, ALTERN_L2, KC_UNDS,   SQ_AA,    ALTERN_R2, CTL_ENT,
    OSM_SFT, ALTERN_L3,                      ALTERN_R3, KC_RSFT,
    CW_TOGG, CTL_SFT,  KC_LALT, KC_LGUI, THUMB_L2,       KC_CIRC,  KC_DLR,          THUMB_R2, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
                                     THUMB_L1, KC_TAB, KC_LGUI,  KC_RGUI,  KC_BSPC,  THUMB_R1
  ),
  [_GAME] = LAYOUT_wrapper(
     KC_ESC, KC_GRV,   KC_1,     KC_2,    KC_3,    KC_4,    KC_5,   SQ_OE,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL,
     KC_TAB, KC_TAB,   KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,   SQ_AE,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
    KC_LSFT, KC_LCTL,  KC_A,     KC_S,    KC_D,    KC_F,    KC_G,   SQ_AA,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, CTL_ENT,
    KC_LCTL, KC_LSFT,  KC_Z,     KC_X,    KC_C,    KC_V,                      KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
    CW_TOGG, CTL_SFT,  KC_LALT, KC_LGUI, THUMB_L2,       KC_CIRC,  KC_DLR,          THUMB_R2, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
                                     THUMB_L1, KC_TAB, KC_LGUI,  KC_RGUI,  KC_BSPC,  THUMB_R1
  ),
  [_LANG] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,   SQ_AA,   SQ_AE,   SQ_OE, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
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
  [_RAISE] = LAYOUT_wrapper(
    _______, SYMBOLS_L0, _______, _______, SYMBOLS_R0, _______,
    _______, SYMBOLS_L1, _______, _______, SYMBOLS_R1, _______,
    _______, SYMBOLS_L2, _______, _______, SYMBOLS_R2, _______,
    _______, SYMBOLS_L3,                   SYMBOLS_R3, _______,
    _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______
  ),
  [_ADJUST] = LAYOUT_moonlander(
    DF_QWER,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, _______, _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
    DF_ALTR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
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

void caps_word_set_keymap(bool active) {
    ML_LED_6(active);
}

layer_state_t default_layer_state_set_keymap(layer_state_t state) {
    bool led_1 = false;
    bool led_2 = false;
    bool led_3 = false;
    if (layer_state_cmp(state, _QWERTY)) {
            led_1 = true;
    } else if (layer_state_cmp(state, _ALTERN)) {
            led_2 = true;
    } else if (layer_state_cmp(state, _GAME)) {
            led_3 = true;
    }
    ML_LED_1(led_1);
    ML_LED_2(led_2);
    ML_LED_3(led_3);
    return state;
}

layer_state_t layer_state_set_keymap(layer_state_t state) {
    bool led_4 = false;
    bool led_5 = false;
    bool led_6 = is_caps_word_on();

    switch (get_highest_layer(state)) {
        case _LOWER:
            led_4 = true;
            break;
        case _RAISE:
            led_5 = true;
            break;
        case _LANG:
            led_4 = led_5 = led_6 = true;
            break;
        case _ADJUST:
            led_4 = led_5 = true;
            break;
        default:
            break;
    }

    ML_LED_4(led_4);
    ML_LED_5(led_5);
    ML_LED_6(led_6);
    return state;
}

