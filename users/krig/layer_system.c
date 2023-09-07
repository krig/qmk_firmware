#include "krig.h"
#include "layer_system.h"

bool krig_process_default_layers(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case DF_QWER:
            if (record->event.pressed) {
                if (layer_state_cmp(default_layer_state, _QWERTY)) {
                    set_single_persistent_default_layer(_ALTERN);
                } else {
                    set_single_persistent_default_layer(_QWERTY);
                }
            }
            return false;
        case DF_ALTR:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_ALTERN);
            }
            return false;
        // don't persist gaming layer
    };
    return true;
}
