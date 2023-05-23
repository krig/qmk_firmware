#include "krig.h"
#include "features/layer_lock.h"
#include "features/custom_shift_keys.h"
#include "features/oneshot.h"

const custom_shift_key_t custom_shift_keys[] = {
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


bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case MO_SYM:
    case MO_EXT:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case MO_SYM:
    case MO_EXT:
    case KC_LSFT:
    case OS_SFT:
    case OS_CTL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool krig_handle_callum_oneshots(uint16_t keycode, keyrecord_t* record) {
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_GUI,
        keycode, record
    );
    return true;
}

bool krig_handle_sequence_keys(uint16_t keycode, keyrecord_t* record) {
    if (!krig_handle_callum_oneshots(keycode, record)) {
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

