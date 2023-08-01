/*
 * Kristoffer Gronlund, 2023
 * Ferris Sweep
 */

#include "krig.h"
#include "features/oneshot.h"
#include "features/swapper.h"

#define LAYOUT_wrapper(...)             LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_wrapper(
        QWERTY_L1, QWERTY_R1,
        QWERTY_L2, QWERTY_R2,
        QWERTY_L3, QWERTY_R3,
        M_LOWER,  KC_SPC,  SFT_ENT, M_RAISE
  ),
  [_ALTERN] = LAYOUT_wrapper(
        ALTERN_L1, ALTERN_R1,
        ALTERN_L2, ALTERN_R2,
        ALTERN_L3, ALTERN_R3,
        M_LOWER,  KC_SPC,  SFT_ENT, M_RAISE
  ),
  [_GAME] = LAYOUT(
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
     KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,     KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,
     KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,     KC_N,    KC_M, KC_COMM,  KC_DOT,  M_LANG,
                                M_LOWER,  KC_SPC,  SFT_ENT, M_RAISE
  ),
  [_LANG] = LAYOUT(
     _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______,  _______,   SQ_AA,   SQ_AE,   SQ_OE, _______,
     _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
                               KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS
  ),
  [_LOWER] = LAYOUT(
     _______, CW_TOGG, CMD_GRV, CMD_TAB, _______,   KC_INS, KC_PGDN,   KC_UP, KC_PGUP,  KC_DEL,
      OS_CTL,  OS_ALT,  OS_GUI,  OS_SFT, OS_RALT,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END,
      GUI__Z,  GUI__X,  GUI__C,  KC_TAB,  GUI__V,  _______, _______, _______, _______, _______,
                               KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS
  ),
  [_RAISE] = LAYOUT(
      KC_GRV, KC_TILD, KC_HASH, KC_PERC,   KC_LT,  SQ_COLN, KC_AMPR, KC_LBRC, KC_RBRC, SQ_EXPI,
     KC_EXLM, KC_MINS, KC_PLUS,  KC_EQL,   KC_AT,  KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN,
     KC_QUES, KC_SLSH, KC_ASTR, KC_UNDS,   KC_GT,  KC_CIRC,  KC_DLR, KC_LCBR, KC_RCBR, KC_BSLS,
                                KC_TRNS, GUI_SPC, KC_TRNS, KC_TRNS
  ),
  [_ADJUST] = LAYOUT(
     _______,    KC_1,    KC_2,    KC_3, DF_QWER,  _______,   KC_F1,   KC_F2,   KC_F3, _______,
        KC_0,    KC_4,    KC_5,    KC_6, DF_ALTR,  _______,   KC_F4,   KC_F5,   KC_F6,  KC_F10,
     _______,    KC_7,    KC_8,    KC_9, DF_GAME,  _______,   KC_F7,   KC_F8,   KC_F9, _______,
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};

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

static oneshot_state os_shft_state = os_up_unqueued;
static oneshot_state os_ctrl_state = os_up_unqueued;
static oneshot_state os_alt_state = os_up_unqueued;
static oneshot_state os_ralt_state = os_up_unqueued;
static oneshot_state os_gui_state = os_up_unqueued;
static bool cmd_tab_active = false;
static bool cmd_grv_active = false;

bool process_record_keymap(uint16_t keycode, keyrecord_t* record) {
    update_swapper(&cmd_tab_active, KC_LGUI, KC_TAB, CMD_TAB, keycode, record);
    update_swapper(&cmd_grv_active, KC_LGUI, KC_GRV, CMD_GRV, keycode, record);
    update_oneshot(&os_shft_state, KC_LSFT, OS_SFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTL, keycode, record);
    update_oneshot( &os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot( &os_ralt_state, KC_RALT, OS_RALT, keycode, record);
    update_oneshot( &os_gui_state, KC_LGUI, OS_GUI, keycode, record);
    return true;
}

