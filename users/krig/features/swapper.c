#include "swapper.h"

void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (*active) {
        unregister_code(cmdish);
        *active = false;
    }
}

#include "krig.h"

static bool cmd_tab_active = false;
static bool cmd_grv_active = false;

void process_record_swapper(uint16_t keycode, keyrecord_t* record) {
    update_swapper(&cmd_tab_active, KC_LGUI, KC_TAB, CMD_TAB, keycode, record);
    update_swapper(&cmd_grv_active, KC_LGUI, KC_GRV, CMD_GRV, keycode, record);
}
