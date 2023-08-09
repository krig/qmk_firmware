#include "krig.h"
#include "features/achordion.h"

#ifdef KRIG_CUSTOM_SHIFT
#include "features/custom_shift_keys.h"
const custom_shift_key_t custom_shift_keys[] = {
    { KC_UNDS, KC_MINS },
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys)/sizeof(custom_shift_key_t);
#endif

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t* record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_achordion(keycode, record)) {
        return false;
    }
    if (!process_record_keymap(keycode, record)) {
        return false;
    }
    #ifdef KRIG_CUSTOM_SHIFT
    // handle custom shift keys like ./:, ,/; etc.
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }
    #endif
    #ifdef KRIG_CUSTOM_SEQUENCES
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
        case SQ_EXPI: // <-
            if (record->event.pressed) {
                SEND_STRING("|>");
            }
            return false;
    }
    #endif
    #ifdef KRIG_CUSTOM_LAYERS
    if (!krig_process_default_layers(keycode, record)) {
        return false;
    }
    #endif
    return true;
}

#ifdef KRIG_CUSTOM_LAYERS
__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return layer_state_set_keymap(state);
}

__attribute__ ((weak))
layer_state_t default_layer_state_set_keymap (layer_state_t state) {
  return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    return default_layer_state_set_keymap(state);
}
#endif


void matrix_scan_user(void) {
  achordion_task();
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
    // Get base keycode
    if ((tap_hold_keycode >= QK_MOD_TAP && tap_hold_keycode <= QK_MOD_TAP_MAX) ||
        (tap_hold_keycode >= QK_LAYER_TAP && tap_hold_keycode <= QK_LAYER_TAP_MAX)) {
        tap_hold_keycode &= 0xff;
    }
    // Allow same-hand holds if the held key is non-alpha
    if (tap_hold_keycode > KC_Z) { return true; }

    // Otherwise, follow the opposite hands rule.
    return achordion_opposite_hands(tap_hold_record, other_record);
}
