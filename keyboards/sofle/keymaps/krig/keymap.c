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
#include "keycodes.h"
#include "krig.h"
#include "features/custom_shift_keys.h"
#include "features/repeat_key.h"

enum combos {
    CO_CAPSWORD,
    CO_AA,
    CO_AE,
    CO_OE,
    CO_COPY,
    CO_PASTE,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM capsword_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM aa_combo[] = {KC_Z, KC_J, COMBO_END};
const uint16_t PROGMEM ae_combo[] = {KC_Z, KC_K, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_Z, KC_L, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};

combo_t key_combos[] = {
    [CO_CAPSWORD] = COMBO(capsword_combo, QK_CAPS_WORD_TOGGLE),
    [CO_AA] = COMBO(aa_combo, SQ_AA),
    [CO_AE] = COMBO(ae_combo, SQ_AE),
    [CO_OE] = COMBO(oe_combo, SQ_OE),
    [CO_COPY] = COMBO(copy_combo, LGUI(KC_C)),
    [CO_PASTE] = COMBO(paste_combo, LGUI(KC_V)),
};

const custom_shift_key_t custom_shift_keys[] = {
    {KC_DOT, KC_COLN},
    {KC_COMM, KC_SCLN},
    {KC_BSPC, KC_DEL},
    {KC_GT, KC_LT},
};

uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

#define KG_NUMROW KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, /* ----- ----- */    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, REPEAT,
#define KG_THUMBROW KC_LALT, KC_LCTL, KC_LGUI, MO_LOWR, KC_SPC, NAV_BSP, MO_RAIS, KC_RGUI, KC_RCTL, KC_LALT
#define LAYOUT_wrapper(...)             LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_wrapper(
  KG_NUMROW
   KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, /* ----- ----- */    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  CTL_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, /* ----- ----- */    KC_H,    KC_J,    KC_K,    KC_L, KC_MINS, CTL_ENT,
  OSM_SFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE, MO_FUNS,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, RSFT_T(KC_GT),
  KG_THUMBROW
),
[_ENGRAM] = LAYOUT_wrapper(
  KG_NUMROW
   KC_TAB,    KC_B,    KC_Y,    KC_O,    KC_U, KC_QUOT, /* ----- ----- */ KC_SLSH,    KC_L,    KC_D,    KC_W,    KC_V, KC_BSPC,
  CTL_ESC,    KC_C,    KC_I,    KC_E,    KC_A, KC_COMM, /* ----- ----- */  KC_DOT,    KC_H,    KC_T,    KC_S,    KC_N, CTL_ENT,
  OSM_SFT,    KC_G,    KC_X,    KC_J,    KC_K, KC_MINS, KC_MUTE, MO_FUNS,   KC_GT,    KC_R,    KC_M,    KC_F,    KC_P, RSFT_T(KC_BSLS),
  KG_THUMBROW
),
[_GAME] = LAYOUT_wrapper(
   KC_ESC,  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4, /* ----- ----- */    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, REPEAT,
   KC_TAB,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R, /* ----- ----- */    KC_T,    KC_Y,    KC_I,    KC_O,    KC_P, KC_BSPC,
  KC_LCTL, KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F, /* ----- ----- */    KC_G,    KC_H,    KC_K,    KC_L, KC_MINS, CTL_ENT,
  KC_LSFT, KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V, KC_MUTE, MO_FUNS,    KC_B,    KC_N, KC_COMM,  KC_DOT, KC_SLSH, RSFT_T(KC_GT),
  KG_THUMBROW
),
[_LOWER] = LAYOUT(
    LLOCK, _______, _______, _______, _______, _______,                   _______, _______, _______,  _______, _______,  KC_INS,
  _______, SQ_PHEX,   KC_P1,   KC_P2,   KC_P3, _______,                   _______, SQ_AMPR, KC_UNDS,  KC_HASH, _______,  KC_DEL,
  _______,   KC_P0,   KC_P4,   KC_P5,   KC_P6, _______,                   SQ_PIPE, SQ_COLN,   SQ_AA,    SQ_AE,   SQ_OE,  KC_GRV,
  _______,  KC_DOT,   KC_P7,   KC_P8,   KC_P9, _______, _______, _______, _______, SQ_PATH, ZOOM_UT,  ZOOM_IN, KC_BSLS, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
),
[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_CIRC,  KC_GRV, KC_QUOT, KC_DQUO,   KC_LT,                   _______, KC_AMPR, KC_LBRC, KC_RBRC, _______, _______,
  _______, KC_EXLM, KC_HASH, KC_PLUS,  KC_EQL,   KC_GT,                   KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN,  KC_GRV,
  _______, KC_TILD, KC_SLSH, KC_ASTR, KC_BSLS, KC_HASH, _______, _______, KC_HASH,  KC_DLR, KC_LCBR, KC_RCBR, KC_PERC, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_NAV] = LAYOUT(
    LLOCK, _______, _______, _______, _______, _______,                   _______, GUI_LFT,  GUI__R, GUI_RGT, _______, _______,
  _______,  GUI__Q,  GUI__W, _______, _______, _______,                   _______, KC_HOME,  KC_END,  GUI__T,  GUI__N, _______,
  _______, _______, WS_PREV,  WS_ALL, WS_NEXT, _______,                   _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_FUNS] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  _______, DF_QWER, DF_ENGR, DF_GAME, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_FUNS2] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

static void render_astronaut(void) {
    static const unsigned char PROGMEM raw_logo[] = {

// 'oled', 32x128px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
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
         case _ENGRAM:
             oled_write_ln_P(PSTR("engrm"), false);
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
        case _LOWER:
            oled_write_P(PSTR("<<<<<"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR(">>>>>"), false);
            break;
        case _FUNS:
            oled_write_P(PSTR("FFFFF"), false);
            break;
        case _FUNS2:
            oled_write_P(PSTR("fffff"), false);
            break;
        case _NAV:
            oled_write_P(PSTR(" nav "), false);
            break;
        default:
            oled_write_P(PSTR("none!"), false);
    }
    oled_write_ln_P(PSTR(""), false);

}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_astronaut();
        print_status_narrow();
    } else {
        render_astronaut();
    }
    return true;
}

bool g_caps_word_last_key_was_space = false;

bool caps_word_press_user(uint16_t keycode) {
	switch (keycode) {
		// Keycodes that continue Caps Word, without shifting.
		case KC_LEFT:
		case KC_RIGHT:
		case KC_UP:
		case KC_DOWN:
		case A(KC_LEFT):
		case A(KC_RIGHT):
		case A(KC_UP):
		case A(KC_DOWN):
		case G(KC_LEFT):
		case G(KC_RIGHT):
		case G(KC_UP):
		case G(KC_DOWN):
			add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
			return true;

		case KC_SPACE:
			// If the last key was NOT a space, then register it having been pressed and
			// move on as normal
			if (!g_caps_word_last_key_was_space) {
				g_caps_word_last_key_was_space = true;
				return true;
			}
				// if this is the second space in a row, delete one and exit Caps Word
			else {
				tap_code16(KC_BACKSPACE);
				return false;
			}

		// Keys that do NOT break the Caps Word state
		case KC_A ... KC_Z:
		case KC_1 ... KC_0:
		case KC_MINS:
		case KC_UNDERSCORE:
		case KC_BACKSPACE:
			// If we're continuing on after a space, then we need to "address" that prior
			// space in some way. The way we do that depends on what mode we're in. But
			// in all cases, first we need to remove that space and then replace it with
			// another character or another operating mode (ex. OSM)
			if (g_caps_word_last_key_was_space) {
				tap_code16(KC_BACKSPACE);
				tap_code16(KC_UNDERSCORE);
				g_caps_word_last_key_was_space = false;
			}
			if (KC_A <= keycode && keycode <= KC_Z) {
				add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
			}
			return true;

		default:
			return false;  // Deactivate Caps Word
	}
}

void caps_word_set_user(bool active) {
	if (active) {
		g_caps_word_last_key_was_space = false;
	}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_repeat_key_with_alt(keycode, record, REPEAT, ALTREP)) {
        return false;
    }
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }
    return krig_handle_sequence_keys(keycode, record);
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    if ((mods & MOD_MASK_CTRL)) {
        switch (keycode) {
            case KC_C: return C(KC_V);
        }
    }
    return KC_TRNS;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _FUNS);
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
        switch (get_highest_layer(layer_state)) {
            case _LOWER:
            case _RAISE:
                if (clockwise) {
                    tap_code(KC_DOWN);
                } else {
                    tap_code(KC_UP);
                }
                break;
            default:
                if (clockwise) {
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
                break;
        }
    }
    return true;
}
