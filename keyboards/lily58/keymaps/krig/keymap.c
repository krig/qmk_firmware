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
#include "custom_keys.h"
#include "features/custom_shift_keys.h"
#include "features/krig_caps_word.h"

enum custom_layers {
    _QWERTY,
    _HANDS,
    _GAME,
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
#define DF_HAND  DF(_HANDS)
#define DF_GAME  DF(_GAME)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_QWERTY] = LAYOUT(
   KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
   KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  CTL_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, KC_RALT,
  OSM_SFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC, KC_RBRC,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
                             KC_LALT, KC_LGUI, M_LOWER,  KC_SPC, SC_SENT, M_RAISE, KC_PGDN, KC_PGUP
 ),
 [_HANDS] = LAYOUT(
   KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
   KC_TAB,    KC_Q,    KC_C,    KC_H,    KC_P,    KC_V,                      KC_Y,    KC_K,    KC_O,    KC_J, KC_QUOT, KC_BSPC,
  CTL_ESC,    KC_R,    KC_S,    KC_N,    KC_T,    KC_G,                      KC_W,    KC_U,    KC_E,    KC_I,    KC_A, KC_RALT,
  OSM_SFT,    KC_X,    KC_M,    KC_L,    KC_D,    KC_B, KC_LBRC, KC_RBRC,    KC_Z,    KC_F, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
                             KC_LALT, KC_LGUI, M_LOWER,  KC_SPC, SC_SENT, M_RAISE, KC_PGDN, KC_PGUP
 ),
 [_GAME] = LAYOUT(
   KC_ESC,  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
   KC_TAB,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  KC_LSFT, KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,                      KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, KC_RALT,
  KC_LCTL, KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V, KC_LBRC, KC_RBRC,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
                             KC_LALT, KC_LGUI, M_LOWER,  KC_SPC, SC_SENT, M_RAISE, KC_PGDN, KC_PGUP
 ),
 [_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, KC_1,    KC_2,    KC_3,    _______,                   _______, SQ_AMPR, SQ_LTLT, SQ_GTGT, _______, _______,
  _______,    KC_0, KC_4,    KC_5,    KC_6,    _______,                   SQ_PIPE, SQ_COLN, _______, _______, _______, _______,
  _______, SQ_PHEX, KC_7,    KC_8,    KC_9,    _______, _______, _______, _______, SQ_PATH, SQ_LTAR, SQ_RTAR, SQ_EXPI, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
 ),
 [_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______,  KC_GRV, KC_TILD, KC_HASH, KC_PERC,   KC_LT,                   SQ_COLN, KC_AMPR, KC_LBRC, KC_RBRC, _______, _______,
  _______, KC_EXLM, KC_MINS, KC_PLUS,  KC_EQL,   KC_AT,                   KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN, _______,
  _______, KC_QUES, KC_SLSH, KC_ASTR, KC_UNDS,   KC_GT, _______, _______, KC_CIRC,  KC_DLR, KC_LCBR, KC_RCBR, KC_BSLS, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
 ),
 [_ADJUST] = LAYOUT(
  DF_QWER,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  DF_HAND, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,  KC_INS,
  DF_GAME, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
 )
};

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
        case DF_HAND:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_HANDS);
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
    krig_caps_word_set(active);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
