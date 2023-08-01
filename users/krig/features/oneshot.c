#include "krig.h"
#include "oneshot.h"

void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                register_code(mod);
            }
            *state = os_down_unused;
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = os_up_queued;
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                unregister_code(mod);
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    break;
                case os_up_queued:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void process_record_oneshot(oneshot_context* ctx, uint16_t keycode, keyrecord_t* record)
{
    update_oneshot(&(ctx->shift), KC_LSFT, OS_SFT, keycode, record);
    update_oneshot(&(ctx->ctrl), KC_LCTL, OS_CTL, keycode, record);
    update_oneshot(&(ctx->alt), KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&(ctx->r_alt), KC_RALT, OS_RALT, keycode, record);
    update_oneshot(&(ctx->gui), KC_LGUI, OS_GUI, keycode, record);
}

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
    case SFT_ENT:
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

