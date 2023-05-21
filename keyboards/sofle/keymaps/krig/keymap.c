 /* Copyright 2021 Dane Evans
  * Copyright 2023 kristoffer Gronlund
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */
#include QMK_KEYBOARD_H
#include "krig.h"

#define KG_NUMROW KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, /* ----- ----- */    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL,
#define KG_THUMBROW OSM_ALT, OSM_CTL, OSM_GUI, MO_EXT, KC_SPC, SC_SENT, MO_SYM, OSM_GUI, OSM_CTL, OSM_ALT
#define LAYOUT_wrapper(...)             LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_wrapper(
  KG_NUMROW
   KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, /* ----- ----- */    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  ESC_CTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, /* ----- ----- */    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, CTL_ENT,
  CW_TOGG,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE, KC_MPLY,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_UNDS, SFT_SLS,
  KG_THUMBROW
),
[_HANDS] = LAYOUT_wrapper(
  KG_NUMROW
   KC_TAB,    KC_Q,    KC_C,    KC_H,    KC_P,    KC_V, /* ----- ----- */    KC_Y,    KC_K,    KC_O,    KC_J, KC_QUOT, KC_BSPC,
  CTL_ESC,    KC_R,    KC_S,    KC_N,    KC_T,    KC_G, /* ----- ----- */    KC_W,    KC_U,    KC_E,    KC_I,    KC_A, CTL_ENT,
  CW_TOGG,    KC_X,    KC_M,    KC_L,    KC_D,    KC_B, KC_MUTE, KC_MPLY,    KC_Z,    KC_F, KC_COMM,  KC_DOT, KC_UNDS, SFT_SLS,
  KG_THUMBROW
),
[_GAME] = LAYOUT_wrapper(
   KC_ESC,  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4, /* ----- ----- */    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, MO_FUNS,
   KC_TAB,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R, /* ----- ----- */    KC_T,    KC_Y,    KC_I,    KC_O,    KC_P, KC_BSPC,
  KC_LCTL, KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F, /* ----- ----- */    KC_G,    KC_H,    KC_K,    KC_L, KC_MINS, CTL_ENT,
  KC_LSFT, KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V, KC_MUTE, KC_MPLY,    KC_B,    KC_N, KC_COMM,  KC_DOT, KC_SLSH, SFT_SLS,
  KG_THUMBROW
),
[_EXTEND] = LAYOUT(
    LLOCK, _______, _______, _______, _______, _______,                   _______, _______, _______,  _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, KC_PGDN,   KC_UP,  KC_PGUP, _______, _______,
  _______, _______, _______, _______, _______, _______,                   KC_HOME, KC_LEFT, KC_DOWN,  KC_RGHT,  KC_END, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   SQ_AA,    SQ_AE,   SQ_OE, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
),
[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______,  KC_GRV, KC_TILD, KC_HASH, KC_PERC, _______,                   _______, KC_AMPR, KC_LBRC, KC_RBRC, KC_BSLS, _______,
  _______, KC_EXLM, KC_SLSH, KC_PLUS,  KC_EQL,   KC_AT,                   KC_PIPE,   KC_LT, KC_LPRN, KC_RPRN,   KC_GT, _______,
  _______, KC_QUES, _______, KC_ASTR, _______, _______, _______, _______, KC_CIRC,  KC_DLR, KC_LCBR, KC_RCBR, _______, _______,
                     GUI__X,  GUI__C,  GUI__V, _______,  MO_NUM, _______, _______, _______, _______, _______
),
[_NUM] = LAYOUT(
    LLOCK, _______, _______, _______, _______, _______,                   _______, _______, _______,  _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______,    KC_1,    KC_2,     KC_3, _______, _______,
  _______, _______, _______, _______, _______, _______,                      KC_0,    KC_4,    KC_5,     KC_6, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, SQ_PHEX,    KC_7,    KC_8,     KC_9, _______, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
),
[_FUNS] = LAYOUT(
  DF_QWER,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
  DF_HAND, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,  KC_INS,
  DF_GAME, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

static void render_astronaut(void) {
     for (int i = 0; i < 16*17; ++i) {
         oled_write_char(0, false);
     }
    static const unsigned char PROGMEM raw_logo[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0xe8,
0xe8, 0xe8, 0x10, 0xe0, 0x00, 0x08, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x3f, 0x7f, 0xff, 0xff,
0xff, 0xff, 0xff, 0x7f, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x7f, 0x07,
0x00, 0x03, 0xff, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xc0, 0x40, 0x00, 0xc0, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x40, 0xc0, 0x00,
0xc0, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x20, 0x30, 0x20, 0x30, 0x20, 0x00, 0x00,
0x00, 0x00, 0x07, 0x04, 0x01, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x04, 0x07, 0x01,
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

    };
    oled_write_raw_P((const char*)raw_logo, sizeof(raw_logo));
}


static void print_status_narrow(void) {
    // Print current mode
    oled_write_ln_P(PSTR("krig.\n"), false);


     switch(get_highest_layer(default_layer_state)) {
         case _QWERTY:
             oled_write_ln_P(PSTR("qwrty"), false);
             break;
         case _HANDS:
             oled_write_ln_P(PSTR("hands"), false);
             break;
         case _GAME:
             oled_write_ln_P(PSTR("GAME!"), false);
             break;
         default:
             oled_write_ln_P(PSTR(""), false);
             break;
     }


    if (is_caps_word_on()) {
        oled_write_ln_P(PSTR("CAPSw"), false);
    } else {
        oled_write_ln_P(PSTR("layr:"), false);
    }

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        case _ENGRAM:
        case _GAME:
            oled_write_P(PSTR("....."), false);
            break;
        case _EXTEND:
            oled_write_P(PSTR("< EXT"), false);
            break;
        case _SYMBOL:
            oled_write_P(PSTR("SYM >"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("12345"), false);
            break;
        case _FUNS:
            oled_write_P(PSTR("<FUN>"), false);
            break;
        default:
            oled_write_P(PSTR("nil!?"), false);
    }
    oled_write_ln_P(PSTR(""), false);

}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_astronaut();
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return krig_handle_sequence_keys(keycode, record);
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return state;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
         if (clockwise) {
             tap_code(KC_DOWN);
         } else {
             tap_code(KC_UP);
         }
    }
    return true;
}
