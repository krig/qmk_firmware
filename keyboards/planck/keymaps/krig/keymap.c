// Kristoffer Gronlund, 2023
#include "krig.h"
#include "eeprom.h"

enum planck_layers {
    _BASE,
    _SWEDE,
    _SYMBOLS,
    _GAME,
    _NAV,
    _FKEYS,
    _QMKSTUFF
};

#define MO_SWED MO(_SWEDE)
#define MO_SYMB MO(_SYMBOLS)
#define MO_FKEY MO(_FKEYS)
#define MO_NAV MO(_NAV)
#define TG_GAME TG(_GAME)
#define MO_QMK MO(_QMKSTUFF)
#define NAV_CLN LT(_NAV, KC_SCLN)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
      CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,       KC_G,    KC_H,    KC_J,    KC_K,    KC_L, NAV_CLN, KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, SFT_QUO,
      MO_FKEY, CTL_SFT, KC_LALT, KC_LGUI, MO_SWED,  KC_SPC,   KC_NO, MO_SYMB, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
  ),
  [_SWEDE] = LAYOUT_planck_grid(
       KC_ESC, _______, KC_7,    KC_8,    KC_9,    _______, _______, SQ_AMPR, KC_UNDS, KC_HASH, _______, KC_DEL,
      _______, SQ_PHEX, KC_4,    KC_5,    KC_6,    _______, SQ_PIPE, SQ_COLN, SQ_AA,   SQ_OE,   SQ_AE,   _______,
      _______, KC_0,    KC_1,    KC_2,    KC_3,    _______, _______, SQ_PATH, ZOOM_UT, ZOOM_IN, KC_BSLS, KC_GRV,
      _______, _______, _______, _______, _______, _______, KC_NO,   _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),
  [_SYMBOLS] = LAYOUT_planck_grid(
      _______, KC_CIRC, KC_LT,   KC_GT,   KC_DQUO, KC_QUOT, KC_GRV,  KC_AMPR, KC_LBRC, KC_RBRC, KC_PERC, KC_INS,
      _______, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_UNDS, KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_QUES, _______,
      _______, KC_TILD, KC_SLSH, KC_ASTR, KC_BSLS, KC_HASH, KC_TILD, KC_DLR,  KC_LCBR, KC_RCBR, KC_AT,   KC_GRV,
      _______, _______, _______, _______, _______, _______, KC_NO,   _______, _______, _______, _______, _______
  ),
  [_GAME] = LAYOUT_planck_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [_NAV] = LAYOUT_planck_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, WS_PREV,  WS_ALL, WS_NEXT, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [_FKEYS] = LAYOUT_planck_grid(
      _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, KC_NO,   _______, _______, _______, _______, _______
  ),
  [_QMKSTUFF] = LAYOUT_planck_grid(
      TG_GAME, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};


#define KRIG_ANIM RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define WASD_COLOR 0xeb, 0x2f, 0x06
#define NUM_COLOR 0x78, 0xe0, 0x8f


void keyboard_post_init_user(void) {
  rgb_matrix_enable();
  rgb_matrix_mode_noeeprom(KRIG_ANIM);
}


const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [_BASE] = {
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {NUM_COLOR}, {0,0,0}, {0,0,0}, {NUM_COLOR}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},          {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },
    [_GAME] = {
            {0,0,0}, {0,0,0}, {WASD_COLOR}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {WASD_COLOR}, {WASD_COLOR}, {WASD_COLOR}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},          {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} }
};


void set_layer_color(layer_state_t layer, bool clear) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
      uint8_t r, g, b;
      r = ledmap[layer][i][0];
      g = ledmap[layer][i][1];
      b = ledmap[layer][i][2];
      if ((clear && r == 0 && g == 0 && b == 0) ||
        (r != 0 || g != 0 || b != 0)) {
        rgb_matrix_set_color(i, r, g, b);
      }
  }
}


bool rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) {
      return false;
  }
  layer_state_t layer = get_highest_layer(layer_state|default_layer_state);
  switch(layer) {
    case _GAME:
    case _BASE: {
      set_layer_color(layer, layer != _BASE);
    } break;
    case _FKEYS: {
      rgb_matrix_set_color_all(0xb7, 0x15, 0x40);
    } break;
  }
  if (rgb_matrix_get_flags() == LED_FLAG_NONE)
    rgb_matrix_set_color_all(0, 0, 0);
  else if (rgb_matrix_get_mode() != KRIG_ANIM)
    rgb_matrix_mode_noeeprom(KRIG_ANIM);
  return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_SLD:
            if (record->event.pressed) {
                rgblight_mode(1);
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
    }
    return true;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SWEDE, _SYMBOLS, _FKEYS);
}
