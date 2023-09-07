/* Copyright 2022  CyanDuck
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
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
#include "features/oneshot.h"
#include "features/swapper.h"

#define LAYOUT_wrapper(...)             LAYOUT(__VA_ARGS__)
#define THUMB_ROW KC_MPRV,      THUMB_L2,  THUMB_L1,  KC_DEL, KC_MCTL, KC_MPLY,  KC_TAB, THUMB_R1, THUMB_R2,          KC_MNXT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_wrapper(
    QWERTY_L1, QWERTY_R1,
    QWERTY_L2, QWERTY_R2,
    QWERTY_L3, QWERTY_R3,
    THUMB_ROW
  ),
  [_ALTERN] = LAYOUT_wrapper(
    ALTERN_L1, ALTERN_R1,
    ALTERN_L2, ALTERN_R2,
    ALTERN_L3, ALTERN_R3,
    THUMB_ROW
  ),
  [_GAME] = LAYOUT_wrapper(
     KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,     KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,     KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
    THUMB_ROW
  ),
  [_LANG] = LAYOUT(
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  _______,   SQ_AA,   SQ_AE,   SQ_OE, _______,
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [_LOWER] = LAYOUT(
    _______, CW_TOGG, CMD_GRV, CMD_TAB, _______,   KC_INS, KC_PGDN,   KC_UP, KC_PGUP,  KC_DEL,
     OS_CTL,  OS_ALT,  OS_GUI,  OS_SFT, OS_RALT,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END,
     GUI__Z,  GUI__X,  GUI__C,  KC_TAB,  GUI__V,  _______, _______, _______, _______, _______,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [_RAISE] = LAYOUT_wrapper(
    SYMBOLS_L1, SYMBOLS_R1,
    SYMBOLS_L2, SYMBOLS_R2,
    SYMBOLS_L3, SYMBOLS_R3,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [_ADJUST] = LAYOUT(
    _______,    KC_1,    KC_2,    KC_3, DF_QWER,  _______,   KC_F1,   KC_F2,   KC_F3, _______,
       KC_0,    KC_4,    KC_5,    KC_6, DF_GAME,  _______,   KC_F4,   KC_F5,   KC_F6,  KC_F10,
    _______,    KC_7,    KC_8,    KC_9, _______,  _______,   KC_F7,   KC_F8,   KC_F9, _______,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};

static oneshot_context os_ctx;

bool process_record_keymap(uint16_t keycode, keyrecord_t* record) {
    process_record_swapper(keycode, record);
    process_record_oneshot(&os_ctx, keycode, record);
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // Left roller
        if (clockwise) {
            tap_code(KC_RIGHT);
        } else {
            tap_code(KC_LEFT);
        }
    } else if (index == 1) { // Left encoder
        if (clockwise) {
            tap_code(KC_BRIU);
        } else {
            tap_code(KC_BRID);
        }
    } else if (index == 2) { // Right roller
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    } else if (index == 3) { // Right encoder
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }

    return false;
}

static void print_oneshot_state(oneshot_state state, const char* up, const char* down) {
    switch (state) {
        case os_up_unqueued:
            oled_write_P(PSTR("-"), false);
        break;
        case os_up_queued:
            oled_write_P(up, false);
        break;
        case os_up_queued_used:
            oled_write_P(PSTR("^"), false);
        break;
        case os_down_unused:
            oled_write_P(PSTR("?"), false);
        break;
        case os_down_used:
            oled_write_P(down, false);
        break;
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_oneshot_state(os_ctx.ctrl, PSTR("C"), PSTR("c"));
        print_oneshot_state(os_ctx.alt, PSTR("A"), PSTR("a"));
        print_oneshot_state(os_ctx.gui, PSTR("G"), PSTR("g"));
        print_oneshot_state(os_ctx.shift, PSTR("S"), PSTR("s"));
        print_oneshot_state(os_ctx.r_alt, PSTR("R"), PSTR("r"));
        oled_write_P(PSTR("\n"), false);
        // Host Keyboard Layer Status
        if (layer_state_cmp(default_layer_state, _QWERTY)) {
            oled_write_P(PSTR("qwerty\n"), false);
        } else if (layer_state_cmp(default_layer_state, _ALTERN)) {
            oled_write_P(PSTR("altern\n"), false);
        } else if (layer_state_cmp(default_layer_state, _GAME)) {
            oled_write_P(PSTR("uhc\n"), false);
        } else {
            oled_write_P(PSTR("wat\n"), false);
        }
        oled_write_P(PSTR("\n"), false);

        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
            case _ALTERN:
            case _GAME:
                oled_write_P(PSTR("...\n\n"), false);
                break;
            case _LANG:
                oled_write_P(PSTR("lang\n\n"), false);
                break;
            case _LOWER:
                oled_write_P(PSTR("lower\n\n"), false);
                break;
            case _RAISE:
                oled_write_P(PSTR("raise\n\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("adjust\n\n"), false);
                break;
            default:
                oled_write_ln_P(PSTR("unknown\n\n"), false);
                break;
        }
        if (is_caps_word_on()) {
            oled_write_ln_P(PSTR("CAPS!!!\n"), false);

        } else {
            oled_write_ln_P(PSTR("\n"), false);

        }
        return false;
    }
    return true;
}
