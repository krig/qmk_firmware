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
#include "krig.h"

#define KG_THUMBROW OS_ALT, OS_CTL, OS_GUI, THUMB_L2, THUMB_L1, THUMB_R1, THUMB_R2, OS_GUI, OS_CTL, OS_RALT
#define LAYOUT_wrapper(...)             LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_wrapper(
       KC_GRV,     NUMROW_L,     NUMROW_R,  KC_DEL,
   KC_TAB,    QWERTY_L1, /* ----- ----- */    QWERTY_R1, KC_BSPC,
  CTL_ESC,    QWERTY_L2, /* ----- ----- */    QWERTY_R2, CTL_ENT,
  OSM_SFT,    QWERTY_L3, KC_MUTE, KC_MPLY,    QWERTY_R3, KC_RSFT,
  KG_THUMBROW
),
[_ALTERN] = LAYOUT_wrapper(
       KC_GRV,     NUMROW_L,     NUMROW_R,  KC_DEL,
   KC_TAB,    ALTERN_L1, /* ----- ----- */    ALTERN_R1, KC_BSPC,
  CTL_ESC,    ALTERN_L2, /* ----- ----- */    ALTERN_R2, CTL_ENT,
  OSM_SFT,    ALTERN_L3, KC_MUTE, KC_MPLY,    ALTERN_R3, KC_RSFT,
  KG_THUMBROW
),
[_GAME] = LAYOUT_wrapper(
   KC_ESC,  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4, /* ----- ----- */    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL,
   KC_TAB,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R, /* ----- ----- */    KC_T,    KC_Y,    KC_I,    KC_O,    KC_P, KC_BSPC,
  KC_LCTL, KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F, /* ----- ----- */    KC_G,    KC_H,    KC_K,    KC_L, KC_QUOT, CTL_ENT,
  KC_LSFT, KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V, KC_MUTE, KC_MPLY,    KC_B,    KC_N, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  KG_THUMBROW
),
[_LANG] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______,   SQ_AA,   SQ_AE,   SQ_OE, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_LOWER] = LAYOUT_wrapper(
    LLOCK, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______,   LOWER_L1,                   LOWER_R1, _______,
  _______,   LOWER_L2,                   LOWER_R2, _______,
  _______,   LOWER_L3, _______, _______, LOWER_R3, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_RAISE] = LAYOUT_wrapper(
  _______, SYMBOLS_L0,                   SYMBOLS_R0, _______,
  _______, SYMBOLS_L1,                   SYMBOLS_R1, _______,
  _______, SYMBOLS_L2,                   SYMBOLS_R2, _______,
  _______, SYMBOLS_L3, _______, _______, SYMBOLS_R3, _______,
                     GUI__X,  GUI__C,  GUI__V, _______, _______, _______, _______, _______, _______, _______
),
[_ADJUST] = LAYOUT(
  DF_QWER,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  DF_ALTR, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,  KC_INS,
  DF_GAME, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {

     // Print current mode
     oled_set_cursor(0, 0);
     if (is_caps_word_on()) {
         oled_write_P(PSTR("(O_O)"), false);
     } else if (get_mods() & MOD_MASK_SHIFT) {
         oled_write_P(PSTR(" o_O "), false);
     } else {
         oled_write_P(PSTR(" ._. "), false);
     }

     oled_set_cursor(0, 3);
     switch(get_highest_layer(default_layer_state)) {
         case _QWERTY:
             oled_write_P(PSTR("qwrty"), false);
             break;
         case _ALTERN:
             oled_write_P(PSTR("alter"), false);
             break;
         case _GAME:
             oled_write_P(PSTR("GAME!"), false);
             break;
         default:
             oled_write_P(PSTR("wat"), false);
             break;
     }


     oled_set_cursor(0, 6);
     oled_write_P(PSTR("layer"), false);
     oled_set_cursor(0, 7);
     switch (get_highest_layer(layer_state)) {
         case _QWERTY:
         case _ALTERN:
         case _GAME:
             oled_write_P(PSTR("....."), false);
             break;
         case _LOWER:
             oled_write_P(PSTR("lower"), false);
             break;
         case _RAISE:
             oled_write_P(PSTR("raise"), false);
             break;
         case _LANG:
             oled_write_P(PSTR("lang"), false);
             break;
         case _ADJUST:
             oled_write_P(PSTR("adjst"), false);
             break;
         default:
             oled_write_P(PSTR("nil!?"), false);
     }

 }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
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
