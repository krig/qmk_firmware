/*
 * Kristoffer Gronlund, 2023
 * Ferris Sweep
 */

#include "krig.h"
#include "custom_keys.h"
#include "features/custom_shift_keys.h"
#include "features/krig_caps_word.h"
#include "features/oneshot.h"
#include "features/swapper.h"

enum custom_layers {
    _QWERTY,
    _HANDS,
    _GAME,
    _LOWER,
    _RAISE,
    _ADJUST,
};

const custom_shift_key_t custom_shift_keys[] = {
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys)/sizeof(custom_shift_key_t);

#define M_LOWER LT(_LOWER, KC_TAB)
#define M_RAISE LT(_RAISE, KC_BSPC)
#define DF_QWER  DF(_QWERTY)
#define DF_HAND  DF(_HANDS)
#define DF_GAME  DF(_GAME)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
                                M_LOWER,  KC_SPC,  SC_SENT, M_RAISE
  ),
  [_HANDS] = LAYOUT(
        KC_Q,    KC_C,    KC_H,    KC_P,    KC_V,     KC_Y,    KC_K,    KC_O,    KC_J, KC_QUOT,
        KC_R,    KC_S,    KC_N,    KC_T,    KC_G,     KC_W,    KC_U,    KC_E,    KC_I,    KC_A,
        KC_X,    KC_M,    KC_L,    KC_D,    KC_B,     KC_Z,    KC_F, KC_COMM,  KC_DOT, KC_SLSH,
                                M_LOWER,  KC_SPC,  SC_SENT, M_RAISE
  ),
  [_GAME] = LAYOUT(
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
     KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,     KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,
     KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,     KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
                                M_LOWER,  KC_SPC,  SC_SENT, M_RAISE
  ),
  [_LOWER] = LAYOUT(
      KC_ESC, CW_TOGG, CMD_GRV, CMD_TAB, _______,  _______, KC_PGDN,   KC_UP, KC_PGUP,  KC_DEL,
      OS_ALT,  OS_CTL,  OS_GUI,  OS_SFT, _______,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END,
      GUI__Z,  GUI__X,  GUI__C,  GUI__V, _______,  _______,   SQ_AA,   SQ_AE,   SQ_OE,  KC_INS,
                               KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS
  ),
  [_RAISE] = LAYOUT(
      KC_GRV, KC_TILD, KC_HASH, KC_PERC,   KC_LT,  SQ_COLN, KC_AMPR, KC_LBRC, KC_RBRC, SQ_EXPI,
     KC_EXLM, KC_MINS, KC_PLUS,  KC_EQL,   KC_AT,  KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN,
     KC_QUES, KC_SLSH, KC_ASTR, KC_UNDS,   KC_GT,  KC_CIRC,  KC_DLR, KC_LCBR, KC_RCBR, KC_BSLS,
                                KC_TRNS, GUI_SPC, KC_TRNS, KC_TRNS
  ),
  [_ADJUST] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,
     DF_QWER, DF_HAND, DF_GAME, _______, _______,  _______, _______, _______, _______, QK_BOOT,
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
    case SC_SENT:
    case OS_SFT:
    case OS_CTL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

static oneshot_state os_shft_state = os_up_unqueued;
static oneshot_state os_ctrl_state = os_up_unqueued;
static oneshot_state os_alt_state = os_up_unqueued;
static oneshot_state os_gui_state = os_up_unqueued;
static bool cmd_tab_active = false;
static bool cmd_grv_active = false;

bool krig_handle_callum_oneshots(uint16_t keycode, keyrecord_t* record) {
    update_oneshot(&os_shft_state, KC_LSFT, OS_SFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTL, keycode, record);
    update_oneshot( &os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot( &os_gui_state, KC_LGUI, OS_GUI, keycode, record);
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // handle cmd+tab key
    update_swapper(&cmd_tab_active, KC_LGUI, KC_TAB, CMD_TAB, keycode, record);
    update_swapper(&cmd_grv_active, KC_LGUI, KC_GRV, CMD_GRV, keycode, record);
    // handle one shot mods
    if (!krig_handle_callum_oneshots(keycode, record)) {
        return false;
    }
    // handle custom shift keys like ./:, ,/; etc.
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }
    // handle sequence keys like ::, && etc.
    if (!process_custom_keycodes(keycode, record)) {
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
    };
    return true;
}

bool caps_word_press_user(uint16_t keycode) {
    return krig_caps_word_press(keycode);
}

void caps_word_set_user(bool active) {
    krig_caps_word_set(active);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
