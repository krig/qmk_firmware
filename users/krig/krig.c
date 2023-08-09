#include "krig.h"

#ifdef KRIG_CUSTOM_SHIFT
#include "features/custom_shift_keys.h"
const custom_shift_key_t custom_shift_keys[] = {
    { KC_UNDS, KC_MINS },
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys)/sizeof(custom_shift_key_t);
#endif

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
#ifdef KRIG_CUSTOM_LAYERS
    if ((keycode & QK_LAYER_TAP) == QK_LAYER_TAP) {
        if (QK_LAYER_TAP_GET_LAYER(keycode) != _LANG) {
            return true;
        }
    }
#endif
    switch (keycode) {
        case LSFT_T(KC_ENT):
            return true;
        default:
            return false;
    }
}


__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t* record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
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
