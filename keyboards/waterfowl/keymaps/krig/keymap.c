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
#include "custom_keys.h"
#include "features/custom_shift_keys.h"
#include "features/krig_caps_word.h"
#include "features/oneshot.h"
#include "features/swapper.h"
#define KRIG_34KEY
#include "layer_system.h"

const custom_shift_key_t custom_shift_keys[] = {
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys)/sizeof(custom_shift_key_t);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M, KC_COMM,  KC_DOT,  M_LANG,
     KC_MPRV,          M_LOWER,  KC_SPC,  KC_DEL, KC_MCTL, KC_MPLY,  KC_TAB, SC_SENT, M_RAISE,          KC_MNXT
  ),
  [_APTV3] = LAYOUT(
        KC_W,    KC_G,    KC_D,    KC_F,    KC_B,                      KC_Q,    KC_L,    KC_U,    KC_O,    KC_Y,
        KC_R,    KC_S,    KC_T,    KC_H,    KC_K,                      KC_J,    KC_N,    KC_E,    KC_A,    KC_I,
        KC_X,    KC_C,    KC_M,    KC_P,    KC_V,                      KC_Z, KC_COMM,  KC_DOT, KC_QUOT,  M_LANG,
     KC_MPRV,          M_LOWER,  KC_SPC,  KC_DEL, KC_MCTL, KC_MPLY,  KC_TAB, SC_SENT, M_RAISE,          KC_MNXT
  ),
  [_GAME] = LAYOUT(
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
     KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,                      KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,
     KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,                      KC_N,    KC_M, KC_COMM,  KC_DOT,  M_LANG,
     KC_MPRV,          M_LOWER,  KC_SPC,  KC_DEL, KC_MCTL, KC_MPLY,  KC_TAB, SC_SENT, M_RAISE,          KC_MNXT
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
  [_RAISE] = LAYOUT(
      KC_GRV, KC_TILD, KC_HASH, KC_PERC,   KC_LT,  SQ_COLN, KC_AMPR, KC_LBRC, KC_RBRC, SQ_EXPI,
     KC_EXLM, KC_MINS, KC_PLUS,  KC_EQL,   KC_AT,  KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN,
     KC_QUES, KC_SLSH, KC_ASTR, KC_UNDS,   KC_GT,  KC_CIRC,  KC_DLR, KC_LCBR, KC_RCBR, KC_BSLS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [_ADJUST] = LAYOUT(
     _______,    KC_1,    KC_2,    KC_3, DF_QWER,  _______,   KC_F1,   KC_F2,   KC_F3, _______,
        KC_0,    KC_4,    KC_5,    KC_6,  DF_APT,  _______,   KC_F4,   KC_F5,   KC_F6,  KC_F10,
     _______,    KC_7,    KC_8,    KC_9, DF_GAME,  _______,   KC_F7,   KC_F8,   KC_F9, _______,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case M_LOWER:
    case M_RAISE:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case M_LOWER:
    case M_RAISE:
    case SC_SENT:
    case OS_SFT:
    case OS_CTL:
    case OS_ALT:
    case OS_RALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

static oneshot_state os_shft_state = os_up_unqueued;
static oneshot_state os_ctrl_state = os_up_unqueued;
static oneshot_state os_alt_state = os_up_unqueued;
static oneshot_state os_ralt_state = os_up_unqueued;
static oneshot_state os_gui_state = os_up_unqueued;
static bool cmd_tab_active = false;
static bool cmd_grv_active = false;

bool krig_handle_callum_oneshots(uint16_t keycode, keyrecord_t* record) {
    update_oneshot(&os_shft_state, KC_LSFT, OS_SFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTL, keycode, record);
    update_oneshot( &os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot( &os_ralt_state, KC_RALT, OS_RALT, keycode, record);
    update_oneshot( &os_gui_state, KC_LGUI, OS_GUI, keycode, record);
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // handle cmd+tab key
    update_swapper(&cmd_tab_active, KC_LGUI, KC_TAB, CMD_TAB, keycode, record);
    update_swapper(&cmd_grv_active, KC_LGUI, KC_GRV, CMD_GRV, keycode, record);
    // handle one shot mods
    if (!krig_handle_callum_oneshots(keycode, record)) {
        return false;
    }
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
    krig_caps_word_set(active);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
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
        print_oneshot_state(os_ctrl_state, PSTR("C"), PSTR("c"));
        print_oneshot_state(os_alt_state, PSTR("A"), PSTR("a"));
        print_oneshot_state(os_gui_state, PSTR("G"), PSTR("g"));
        print_oneshot_state(os_shft_state, PSTR("S"), PSTR("s"));
        print_oneshot_state(os_ralt_state, PSTR("R"), PSTR("r"));
        oled_write_P(PSTR("\n"), false);
        // Host Keyboard Layer Status
        if (layer_state_cmp(default_layer_state, _QWERTY)) {
            oled_write_P(PSTR("qwerty\n"), false);
        } else if (layer_state_cmp(default_layer_state, _APTV3)) {
            oled_write_P(PSTR("APTv3\n"), false);
        } else if (layer_state_cmp(default_layer_state, _GAME)) {
            oled_write_P(PSTR("uhc\n"), false);
        } else {
            oled_write_P(PSTR("wat\n"), false);
        }
        oled_write_P(PSTR("\n"), false);

        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
            case _APTV3:
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
