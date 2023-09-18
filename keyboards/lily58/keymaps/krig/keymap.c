 /* Copyright 2020 Naoki Katahira
  * Copyright 2023 Elliot Powell
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
#define LAYOUT_wrapper(...)             LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_QWERTY] = LAYOUT_wrapper(
   KC_GRV,         NUMROW_L,                    NUMROW_R,  KC_DEL,
   KC_TAB,        QWERTY_L1,                   QWERTY_R1, KC_BSPC,
  CTL_ESC,        QWERTY_L2,                   QWERTY_R2, KC_RALT,
  OSM_SFT,        QWERTY_L3, CW_TOGG,  QK_REP, QWERTY_R3, KC_RSFT,
  KC_LALT, KC_LGUI, THUMB_L2,  THUMB_L1, THUMB_R1, THUMB_R2, KC_PGDN, KC_PGUP
 ),
 [_ALTERN] = LAYOUT_wrapper(
   KC_GRV,         NUMROW_L,                    NUMROW_R,  KC_DEL,
   KC_TAB,        ALTERN_L1,                   ALTERN_R1, KC_BSPC,
  CTL_ESC,        ALTERN_L2,                   ALTERN_R2, KC_RALT,
  OSM_SFT,        ALTERN_L3, CW_TOGG,  QK_REP, ALTERN_R3, KC_RSFT,
  KC_LALT, KC_LGUI, THUMB_L2,  THUMB_L1, THUMB_R1, THUMB_R2, KC_PGDN, KC_PGUP
 ),
 [_GAME] = LAYOUT_wrapper(
   KC_ESC,  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
   KC_TAB,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  KC_LCTL, KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,                      KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, KC_RALT,
  KC_LSFT, KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V, CW_TOGG,  QK_REP,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
                             KC_LALT, KC_LGUI, THUMB_L2,  THUMB_L1, THUMB_R1, THUMB_R2, KC_PGDN, KC_PGUP
 ),
 [_LOWER] = LAYOUT_wrapper(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, LOWER_L1,                   LOWER_R1, SQ_AA,
  _______, LOWER_L2,                   LOWER_R2, SQ_AE,
  _______, LOWER_L3, _______, QK_AREP, LOWER_R3, SQ_OE,
                             _______, _______, _______, _______, _______, _______, _______, _______
 ),
 [_RAISE] = LAYOUT_wrapper(
  _______, SYMBOLS_L0,                   SYMBOLS_R0, _______,
  _______, SYMBOLS_L1,                   SYMBOLS_R1, _______,
  _______, SYMBOLS_L2,                   SYMBOLS_R2, _______,
  _______, SYMBOLS_L3, _______, QK_AREP, SYMBOLS_R3, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
 ),
 [_ADJUST] = LAYOUT(
  DF_QWER,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  DF_GAME, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,  KC_INS,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
                             _______, _______, _______, _______, _______, _______, _______, _______
 )
};

void oled_render_keylog_r2g(void);
void oled_render_logo_r2g(void);

void oled_render_state_krig(void) {
     if (layer_state_cmp(default_layer_state, _QWERTY)) {
            oled_write_ln_P(PSTR("QWERTY"), false);
     } else if (layer_state_cmp(default_layer_state, _ALTERN)) {
            oled_write_ln_P(PSTR("ALTERN"), false);
     } else if (layer_state_cmp(default_layer_state, _GAME)) {
            oled_write_ln_P(PSTR("UHC"), false);
     }
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        case _ALTERN:
        case _GAME:
            oled_write_ln_P(PSTR("-"), false);
            break;
         #ifndef KRIG_NO_LANG
        case _LANG:
            oled_write_ln_P(PSTR("Lang"), false);
            break;
         #endif
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Unknown"), false);
            break;
    }

 }

bool oled_task_user() {
     if (is_keyboard_master()) {
         oled_render_state_krig();
         oled_render_keylog_r2g();
     } else {
         oled_render_logo_r2g();
     }
     return false;
 }
