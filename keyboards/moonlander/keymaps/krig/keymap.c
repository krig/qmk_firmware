#include "krig.h"

#define MOON_LED_LEVEL LED_LEVEL
#define LAYOUT_wrapper(...)             LAYOUT_moonlander(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_wrapper(
     KC_GRV,  NUMROW_L,    KC_0,   KC_PGUP,     NUMROW_R, KC_DEL,
     KC_TAB, QWERTY_L1, CW_TOGG,   KC_PGDN,    QWERTY_R1,  SQ_AA,
    CTL_ESC, QWERTY_L2, OSM_SFT,   OSM_SFT,    QWERTY_R2,  SQ_AE,
    KC_LSFT, QWERTY_L3,                        QWERTY_R3,  SQ_OE,
    CW_TOGG,   CTL_SFT, KC_LALT, KC_LGUI, THUMB_L2,       OSM_SFT,  KC_RGUI,          THUMB_R2, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
                                     THUMB_L1, KC_ESC, QK_REP,  QK_AREP,    KC_BSPC,  THUMB_R1
  ),
  [_ALTERN] = LAYOUT_wrapper(
     KC_GRV,  NUMROW_L,    KC_0,   KC_PGUP,     NUMROW_R, KC_DEL,
     KC_TAB, ALTERN_L1, CW_TOGG,   KC_PGDN,    ALTERN_R1,  SQ_AA,
    CTL_ESC, ALTERN_L2, OSM_SFT,   OSM_SFT,    ALTERN_R2,  SQ_AE,
    KC_LSFT, ALTERN_L3,                        ALTERN_R3,  SQ_OE,
    CW_TOGG, CTL_SFT,  KC_LALT, KC_LGUI, THUMB_L2,        OSM_SFT,  KC_RGUI,          THUMB_R2, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
                                     THUMB_L1, KC_ESC, QK_REP,  QK_AREP,     KC_BSPC,  THUMB_R1
  ),
  [_GAME] = LAYOUT_wrapper(
     KC_ESC, KC_GRV,   KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_1,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL,
     KC_TAB, KC_TAB,   KC_Q,     KC_W,    KC_E,    KC_R,    KC_T, KC_PGUP,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, SQ_AA,
    KC_LSFT, KC_LCTL,  KC_A,     KC_S,    KC_D,    KC_F,    KC_G, KC_PGDN,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, SQ_AE,
    KC_LCTL, KC_LSFT,  KC_Z,     KC_X,    KC_C,    KC_V,                      KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, SQ_OE,
    CW_TOGG, CTL_SFT,  KC_LALT, KC_LGUI, THUMB_L2,        OSM_SFT,  KC_RGUI,          THUMB_R2, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
                                     THUMB_L1, KC_ESC, QK_REP,  QK_AREP,     KC_BSPC,  THUMB_R1
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
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_TOG,
    _______, _______,    KC_1,    KC_2,    KC_3, _______, _______, _______,  KC_INS, KC_PGDN,   KC_UP, KC_PGUP,  KC_DEL, _______,
    _______,    KC_0,    KC_4,    KC_5,    KC_6, _______, _______, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, _______,
    _______, SQ_PHEX,    KC_7,    KC_8,    KC_9, _______,                   _______, SQ_PATH, ZOOM_UT, ZOOM_IN, KC_BSLS, _______,
    _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, KC_TAB
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

