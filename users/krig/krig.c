#include "krig.h"
#include "features/layer_lock.h"
#include "features/custom_shift_keys.h"
#include "features/repeat_key.h"

// needed for repeat key
combo_t key_combos[] = {};
uint16_t COMBO_LEN = 0;

const custom_shift_key_t custom_shift_keys[] = {
    {KC_COMM, KC_SCLN},
    {KC_DOT,  KC_COLN},
    {KC_UNDS, KC_MINS},
};

uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    if ((mods & MOD_MASK_CTRL)) {
        switch (keycode) {
            case KC_C: return C(KC_V);
        }
    }
    return KC_TRNS;
}

bool krig_handle_sequence_keys(uint16_t keycode, keyrecord_t* record) {
    if (!process_repeat_key_with_alt(keycode, record, REPEAT, ALTREP)) {
        return false;
    }
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }
    if (!process_layer_lock(keycode, record, LLOCK)) {
        return false;
    }
    switch (keycode) {
        case SQ_COLN:
            if (record->event.pressed) {
                SEND_STRING("::");
            }
            return false;
        case SQ_PIPE:
            if (record->event.pressed) {
                SEND_STRING("||");
            }
            return false;
        case SQ_AMPR:
            if (record->event.pressed) {
                SEND_STRING("&&");
            }
            return false;
        case SQ_PATH:
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            return false;
        case SQ_PHEX:
            if (record->event.pressed) {
                SEND_STRING("0x");
            }
            return false;
        case SQ_SLAS: //
            if (record->event.pressed) {
                SEND_STRING("//");
            }
            return false;
        case SQ_LTLT: // <<
            if (record->event.pressed) {
                SEND_STRING("<<");
            }
            return false;
        case SQ_GTGT: // >>
            if (record->event.pressed) {
                SEND_STRING(">>");
            }
            return false;
        case SQ_RTAR: // ->
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            return false;
        case SQ_LTAR: // <-
            if (record->event.pressed) {
                SEND_STRING("<-");
            }
            return false;
    }
    return true;
}

bool g_caps_word_last_key_was_space = false;

void krig_clear_caps_word_last_key(void) {
    g_caps_word_last_key_was_space = false;
}

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
			if (
				KC_A <= keycode && keycode <= KC_Z
			) {
				add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
			}
			return true;

		default:
			return false;  // Deactivate Caps Word
	}
}

