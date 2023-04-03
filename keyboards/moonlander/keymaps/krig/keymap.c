#include "krig.h"
#include "eeprom.h"

#define MOON_LED_LEVEL LED_LEVEL


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_moonlander(
    QK_GESC, KC_1,     KC_2,    KC_3,    KC_4,    KC_5, KC_TILD,   SQ_OE,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS,
    KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T, KC_MINS,   SQ_AE,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
    CTL_ESC, KC_A,     KC_S,    KC_D,    KC_F,    KC_G, KC_UNDS,   SQ_AA,    KC_H,    KC_J,    KC_K,    KC_L, NAV_CLN, KC_QUOT,
    KC_LSFT, KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
    MO_FKEY, CTL_SFT,  KC_LALT, KC_LGUI, MO_SWED,       KC_CIRC,  KC_DLR,          MO_SYMB, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
                                     KC_SPC, KC_BSPC, KC_LGUI,  KC_RGUI,  KC_TAB,  KC_ENT
  ),
  [_SWEDE] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_INS, 
    _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______, _______, _______, SQ_AMPR, KC_UNDS, KC_HASH, _______,  KC_DEL,
    _______, SQ_PHEX, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______, _______, SQ_PIPE, SQ_COLN, SQ_AA,   SQ_OE,     SQ_AE,  KC_GRV,
    _______,  KC_DOT, KC_KP_7, KC_KP_8, KC_KP_9, _______,                   _______, SQ_PATH, ZOOM_UT, ZOOM_IN, KC_BSLS, _______,
    _______, _______, _______, _______, _______,          _______, TG_GAME,          _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, 
    _______, _______, _______, _______, _______, _______
  ),
  [_SYMBOLS] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_CIRC, KC_LABK, KC_RABK, KC_DQUO, KC_QUOT, _______, _______,  KC_GRV, KC_AMPR, KC_LBRC, KC_RBRC, KC_PERC, _______,
    _______, KC_EXLM, KC_MINS, KC_PLUS,  KC_EQL, KC_UNDS, _______, _______, KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_QUES,  KC_GRV,
    _______, KC_TILD, KC_SLSH, KC_ASTR, KC_BSLS, KC_HASH,                   KC_TILD,  KC_DLR, KC_LCBR, KC_RCBR,  KC_AT,  _______,
    _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______
  ),
  [_GAME] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, MO_SWED, _______, _______,  KC_SPC,          _______, _______,          _______, _______, _______, _______, _______,
                                        _______, _______, _______, _______, _______,  _______
  ),
  [_NAV] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, WS_PREV, WS_ALL,  WS_NEXT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, KC_PGDN, KC_PGUP, _______, _______, _______,
    _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______
  ),
  [_FKEYS] = LAYOUT_moonlander(
    _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, _______, _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,      
    _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______,  MO_QMK,
    _______, _______, _______, _______, _______, _______
  ),
  [_FKEYS2] = LAYOUT_moonlander(
    _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, _______, _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,      
    _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______,  MO_QMK,
    _______, _______, _______, _______, _______, _______
  ),
  [_QMKSTUFF] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,  
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______
  ),
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
    [_SWEDE] = LED_LAYOUT_moonlander(
        _TANGR_, _TANGR_, _TANGR_, _TANGR_, _TANGR_, _TANGR_, _TANGR_,  _TANGR_, _TANGR_, _TANGR_, _TANGR_, _TANGR_, _TANGR_, _TANGR_, 
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, __off__, __off__, __off__, __off__,                    __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, __off__, __off__, __off__,          __off__,  _YELLOW,          __off__, __off__, __off__, __off__, __off__, 
                                            __off__, __off__, __off__,  __off__, __off__, __off__ 
    ),
    [_SYMBOLS] = LED_LAYOUT_moonlander(
        _CYAN__, _CYAN__, _CYAN__, _CYAN__, _CYAN__, _CYAN__, _CYAN__,  _CYAN__, _CYAN__, _CYAN__, _CYAN__, _CYAN__, _CYAN__, _CYAN__, 
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, __off__, __off__, __off__, __off__,                    __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, __off__, __off__, __off__,          __off__,  __off__,          __off__, __off__, __off__, __off__, __off__, 
                                            __off__, __off__, __off__,  __off__, __off__, __off__ 
    ),
    [_GAME] = LED_LAYOUT_moonlander(
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, _MINT__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, _MINT__, _MINT__, _MINT__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, __off__, __off__, __off__, _YELLOW,                    __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, _RED___, __off__, __off__, __off__,          __off__,  __off__,          __off__, __off__, __off__, __off__, __off__, 
                                            __off__, __off__, __off__,  __off__, __off__, __off__ 
    ),
    [_FKEYS] = LED_LAYOUT_moonlander(
        _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__,  _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, 
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, __off__, __off__, __off__, __off__,                    __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, __off__, __off__, __off__,          __off__,  __off__,          __off__, __off__, __off__, __off__, _RED___, 
                                            __off__, __off__, __off__,  __off__, __off__, __off__ 
    ),
    [_FKEYS2] = LED_LAYOUT_moonlander(
        _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__,  _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, _BLUE__, 
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, __off__, __off__, __off__, __off__,                    __off__, __off__, __off__, __off__, __off__, __off__, 
        __off__, __off__, __off__, __off__, __off__,          __off__,  __off__,          __off__, __off__, __off__, __off__, _RED___, 
                                            __off__, __off__, __off__,  __off__, __off__, __off__ 
    ),
    [_QMKSTUFF] = LED_LAYOUT_moonlander(
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,  __off__, __off__, __off__, __off__, __off__, __off__, _RED___, 
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
    if (curr == _SWEDE ||
        curr == _SYMBOLS ||
        curr == _GAME ||
        curr == _FKEYS ||
        curr == _FKEYS2 ||
        curr == _QMKSTUFF)
        set_layer_color(curr);
    else if (rgb_matrix_get_flags() == LED_FLAG_NONE)
        rgb_matrix_set_color_all(0, 0, 0);
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return krig_handle_sequence_keys(keycode, record);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _SWEDE, _SYMBOLS, _FKEYS);

    ML_LED_1(false);
    ML_LED_2(false);
    ML_LED_3(false);
    ML_LED_4(false);
    ML_LED_5(false);
    ML_LED_6(false);

    switch (get_highest_layer(state)) {
        case _SWEDE:
            ML_LED_1(1);
            ML_LED_4(1);
            break;
        case _SYMBOLS:
            ML_LED_2(1);
            ML_LED_5(1);
            break;
        case _GAME:
            ML_LED_3(1);
            break;
        case _NAV:
            ML_LED_4(1);
            break;
        case _FKEYS:
        case _FKEYS2:
            ML_LED_5(1);
            break;
        case _QMKSTUFF:
            ML_LED_6(1);
            break;
        default:
            break;
    }

    return state;
}

