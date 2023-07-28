#include "krig.h"
#include "features/layer_lock.h"
#include "features/custom_shift_keys.h"
#include "features/oneshot.h"
#include "quantum.h"

const custom_shift_key_t custom_shift_keys[] = {
};

uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

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
        case MO_EXT:
            if (record->event.pressed) {
                layer_on(_EXTEND);
                update_tri_layer(_EXTEND, _SYMBOL, _FUNS);
            } else {
                layer_off(_EXTEND);
                update_tri_layer(_EXTEND, _SYMBOL, _FUNS);
            }
            return false;
        case MO_SYM:
            if (record->event.pressed) {
                layer_on(_SYMBOL);
                update_tri_layer(_EXTEND, _SYMBOL, _FUNS);
            } else {
                layer_off(_SYMBOL);
                update_tri_layer(_EXTEND, _SYMBOL, _FUNS);
            }
            return false;
        case MO_FUNS:
            if (record->event.pressed) {
                layer_on(_FUNS);
            } else {
                layer_off(_FUNS);
            }
            return false;
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
    return true;
}


