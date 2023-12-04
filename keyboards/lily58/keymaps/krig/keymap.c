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
   KC_GRV,         NUMROW_L,                    NUMROW_R, KC_RALT,
   KC_TAB,        QWERTY_L1,                   QWERTY_R1, KC_BSPC,
  CTL_ESC,        QWERTY_L2,                   QWERTY_R2, KC_RCTL,
  OSM_SFT,        QWERTY_L3, MO(_NUM),  QK_REP, QWERTY_R3, KC_RSFT,
  KC_LALT, KC_LGUI, THUMB_L2,  THUMB_L1, THUMB_R1, THUMB_R2, RGUI_T(KC_PGDN), RALT_T(KC_PGUP)
 ),
 [_ALTERN] = LAYOUT_wrapper(
   KC_GRV,         NUMROW_L,                    NUMROW_R, KC_RALT,
   KC_TAB,        ALTERN_L1,                   ALTERN_R1, KC_BSPC,
  CTL_ESC,        ALTERN_L2,                   ALTERN_R2, KC_RCTL,
  OSM_SFT,        ALTERN_L3, MO(_NUM),  QK_REP, ALTERN_R3, KC_RSFT,
  KC_LALT, KC_LGUI, THUMB_L2,  THUMB_L1, THUMB_R1, THUMB_R2, RGUI_T(KC_PGDN), RALT_T(KC_PGUP)
 ),
 [_GAME] = LAYOUT_wrapper(
   KC_ESC,  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_RALT,
   KC_TAB,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  KC_LCTL, KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,                      KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, KC_RCTL,
  KC_LSFT, KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V, MO(_NUM),  QK_REP,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
                             KC_LALT, KC_LGUI, THUMB_L2,  THUMB_L1, THUMB_R1, THUMB_R2, RGUI_T(KC_PGDN), RALT_T(KC_PGUP)
 ),
 [_NAV] = LAYOUT_wrapper(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, L_NAV_L1,                   L_NAV_R1, _______,
  _______, L_NAV_L2,                   L_NAV_R2, _______,
  _______, L_NAV_L3, _______, _______, L_NAV_R3, _______,
                             _______, _______, _______, _______, KC_TAB, _______, _______, _______
 ),
 [_NUM] = LAYOUT_wrapper(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, L_NUM_L1,                   L_NUM_R1, _______,
  _______, L_NUM_L2,                   L_NUM_R2, _______,
  _______, L_NUM_L3, _______, _______, L_NUM_R3, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
 ),
 [_SYM] = LAYOUT_wrapper(
  _______, L_SYM_L0,                   L_SYM_R0, _______,
  _______, L_SYM_L1,                   L_SYM_R1, _______,
  _______, L_SYM_L2,                   L_SYM_R2, _______,
  _______, L_SYM_L3, _______, _______, L_SYM_R3, _______,
                             _______, _______, _______, _______,  _______, _______, _______, _______
 ),
 [_ADJUST] = LAYOUT(
  DF_QWER,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  _______, _______, _______, _______, _______, _______,                   RGB_TOG, RGB_MOD, RGB_M_P, RGB_M_B, _______,  KC_INS,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
                             _______, _______, _______, _______, _______, _______, _______, _______
 )
};

void oled_render_keylog_r2g(void);
void oled_render_logo_r2g(void);

bool oled_task_user() {
     if (is_keyboard_master()) {
         switch (get_highest_layer(default_layer_state)) {
             case _ALTERN: oled_write_ln_P(PSTR("altern"), false); break;
             case _QWERTY: oled_write_ln_P(PSTR("qwerty"), false); break;
             case _GAME: oled_write_ln_P(PSTR("uhc"), false); break;
         }
         switch (get_highest_layer(layer_state)) {
             case _NAV: oled_write_ln_P(PSTR("nav"), false); break;
             case _NUM: oled_write_ln_P(PSTR("num"), false); break;
             case _SYM: oled_write_ln_P(PSTR("sym"), false); break;
             case _ADJUST: oled_write_ln_P(PSTR("adj"), false); break;
         }
         oled_render_keylog_r2g();
     } else {
         oled_render_logo_r2g();
     }
     return false;
 }
