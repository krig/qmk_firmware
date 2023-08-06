#include "krig.h"
#include "oneshot.h"
#include "print.h"

static void print_info(const char *msg, oneshot_state *state, uint16_t mod, uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("%s OS: 0x%x, mod: 0x%04x, kc: 0x%04x, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", msg, *state, mod, keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
}

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
                print_info("r->os_down_unused", state, mod, keycode, record);
            } else {
                print_info("->os_down_unused", state, mod, keycode, record);
            }
            *state = os_down_unused;
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = os_up_queued;
                print_info("->os_up_queued", state, mod, keycode, record);
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                print_info("u->os_up_unqueued", state, mod, keycode, record);
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
                print_info("u->os_up_unqueued (cancel)", state, mod, keycode, record);
            }
            if (!is_oneshot_ignored_key(keycode)) {
                switch (*state) {
                    case os_down_unused:
                        *state = os_up_queued_used;
                        print_info("->os_up_queued_used", state, mod, keycode, record);
                        break;
                    case os_up_queued_used:
                        *state = os_up_unqueued;
                        unregister_code(mod);
                        print_info("u->os_up_unqueued", state, mod, keycode, record);
                        break;
                    default:
                        break;
                }
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                    case os_down_unused:
                        *state = os_down_used;
                        print_info("->os_down_used", state, mod, keycode, record);
                        break;
                    case os_up_queued:
                        *state = os_up_unqueued;
                        unregister_code(mod);
                        print_info("u queued->os_up_unqueued", state, mod, keycode, record);
                        break;
                    case os_up_queued_used:
                        *state = os_up_unqueued;
                        unregister_code(mod);
                        print_info("u queued_qued->os_up_unqueued", state, mod, keycode, record);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

bool update_oneshot_layer(
    oneshot_state *state,
    uint16_t layer,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                layer_on(layer);
            }
            *state = os_down_unused;
            return false;
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the layer while trigger was held, queue it.
                *state = os_up_queued;
                return false;
            case os_down_used:
                // If we did use the layer while trigger was held, turn off it.
                *state = os_up_unqueued;
                layer_off(layer);
                return false;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_layer_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot layer on designated cancel keydown.
                *state = os_up_unqueued;
                layer_off(layer);
                return false;
            }
            uint8_t key_layer = read_source_layers_cache(record->event.key);
            if (key_layer == layer) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    return true;
                case os_up_queued:
                    if (is_oneshot_mod_key(keycode)) {
                        *state = os_up_unqueued;
                        layer_off(layer);
                        return false;
                    } else {
                        *state = os_up_queued_used;
                    }
                    return true;
               case os_up_queued_used:
                    *state = os_up_unqueued;
                    layer_off(layer);
                    return false;
                default:
                    break;
                }
            }
        } else {
            // Ignore key ups from other layers
            uint8_t key_layer = read_source_layers_cache(record->event.key);
            if (key_layer == layer) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_up_queued:
                    *state = os_up_unqueued;
                    layer_off(layer);
                    return true;
                case os_up_queued_used:
                    *state = os_up_unqueued;
                    layer_off(layer);
                    return true;
                default:
                    break;
                }
            }
        }
    }
    return true;
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
    //case THUMB_L1:
    //case THUMB_L2:
    //case THUMB_R1:
    //case THUMB_R2:
    //return true;
    default:
        return false;
    }
}

bool is_oneshot_layer_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case THUMB_L1:
    case THUMB_L2:
    case THUMB_R1:
    case THUMB_R2:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case THUMB_L1:
    case THUMB_L2:
    case THUMB_R1:
    case THUMB_R2:
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

bool is_oneshot_mod_key(uint16_t keycode) {
    switch (keycode) {
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
