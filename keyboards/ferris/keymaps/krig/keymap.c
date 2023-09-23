/*
 * Kristoffer Gronlund, 2023
 * Ferris Sweep
 */

#include "krig.h"
#include "features/flow.h"
#include "features/swapper.h"

#define LAYOUT_wrapper(...)             LAYOUT(__VA_ARGS__)
#define CTL_W LCTL(KC_W)
#define CTL_U LCTL(KC_U)
#define CTL_D LCTL(KC_D)

// flow_config should correspond to following format:
// * layer keycode
// * modifier keycode
const uint16_t flow_config[FLOW_COUNT][2] = {
    {_LOWER, OS_ALT},
    {_LOWER, OS_GUI},
    {_LOWER, OS_CTL},
    {_LOWER, OS_SFT},
    {_LOWER, OS_RALT},
};
// for layers configuration follow this format:
// * custom layer key
// * layer name
const uint16_t flow_layers_config[FLOW_LAYERS_COUNT][2] = {
    {OS_ADJUST, _ADJUST},
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_wrapper(
    QWERTY_L1, QWERTY_R1,
    QWERTY_L2, QWERTY_R2,
    QWERTY_L3, QWERTY_R3,
    THUMB_L2, THUMB_L1, THUMB_R1, THUMB_R2
  ),
  [_ALTERN] = LAYOUT_wrapper(
    ALTERN_L1, ALTERN_R1,
    ALTERN_L2, ALTERN_R2,
    ALTERN_L3, ALTERN_R3,
    THUMB_L2, THUMB_L1, THUMB_R1, THUMB_R2
  ),
  [_GAME] = LAYOUT(
     KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,     KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,     KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
    THUMB_L2, THUMB_L1, THUMB_R1, THUMB_R2
  ),
  [_LANG] = LAYOUT(
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  _______,   SQ_AA,   SQ_AE,   SQ_OE, _______,
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [_LOWER] = LAYOUT_wrapper(
    LOWER_L1, LOWER_R1,
    LOWER_L2, LOWER_R2,
    LOWER_L3, LOWER_R3,
    KC_TRNS, KC_TRNS,  KC_TAB, KC_TRNS
  ),
  [_RAISE] = LAYOUT_wrapper(
    SYMBOLS_L1, SYMBOLS_R1,
    SYMBOLS_L2, SYMBOLS_R2,
    SYMBOLS_L3, SYMBOLS_R3,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [_ADJUST] = LAYOUT(
    _______,    KC_1,    KC_2,    KC_3, DF_QWER,  _______,   KC_F1,   KC_F2,   KC_F3, _______,
       KC_0,    KC_4,    KC_5,    KC_6, DF_GAME,  _______,   KC_F4,   KC_F5,   KC_F6,  KC_F10,
    _______,    KC_7,    KC_8,    KC_9, _______,  _______,   KC_F7,   KC_F8,   KC_F9, QK_BOOT,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};

bool process_record_keymap(uint16_t keycode, keyrecord_t* record) {
    process_record_swapper(keycode, record);
    if (!update_flow(keycode, record->event.pressed, record->event.key)) return false;
    return true;
}

void matrix_scan_keymap(void) {
    flow_matrix_scan();
}
