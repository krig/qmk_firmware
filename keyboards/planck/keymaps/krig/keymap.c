// Kristoffer Gronlund, 2023
#include QMK_KEYBOARD_H
#include "eeprom.h"


enum planck_keycodes {
  RGB_SLD = SAFE_RANGE,
  DBLCOLN, // ::
  HEXPFIX  // 0x
};

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _GAME,
  _NUMERIC
};


#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
      KC_TAB,         KC_Q,            KC_W,       KC_E,    KC_R,       KC_T,     KC_Y,    KC_U,       KC_I,     KC_O,       KC_P,       KC_BSPC,
      LCTL_T(KC_ESC), KC_A,            KC_S,       KC_D,    KC_F,       KC_G,     KC_H,    KC_J,       KC_K,     KC_L,       KC_SCLN,    KC_ENTER,
      KC_LSFT,        KC_Z,            KC_X,       KC_C,    KC_V,       KC_B,     KC_N,    KC_M,       KC_COMMA, KC_DOT,     KC_SLASH,   KC_QUOTE,
      MO(_NUMERIC),   LCTL(KC_LSFT),   KC_LALT,    KC_LGUI, MO(_LOWER), KC_SPACE, KC_NO,   MO(_RAISE), KC_LEFT,  KC_DOWN,    KC_UP,      KC_RIGHT
  ),

  [_LOWER] = LAYOUT_planck_grid(
       KC_ESC,           KC_1,            KC_2,       KC_3,    KC_4,       KC_5,     KC_6,    KC_7,       KC_8,   KC_9,       KC_0, RALT(KC_W),
      _______,        _______,         _______,    _______, _______,    _______,  _______, KC_UNDS,    _______, _______,  RALT(KC_Q), RALT(KC_P),
      _______,        _______,         _______,    _______, _______,    _______,  _______, _______, LGUI(KC_MINS),LGUI(KC_PLUS),    KC_BSLS,  KC_GRV,
      _______,        _______,         _______,    _______, _______,    _______,    KC_NO, _______,    KC_HOME,   KC_PGDN,    KC_PGUP,  KC_END
  ),

  [_RAISE] = LAYOUT_planck_grid(
      KC_TILD,        KC_QUOT,           KC_LT,      KC_GT, KC_DQUO,      KC_AT,  KC_AMPR, DBLCOLN,    KC_LBRC,  KC_RBRC,    KC_PERC,    KC_DEL,
      _______,        KC_EXLM,         KC_MINS,    KC_PLUS,  KC_EQL,    KC_HASH,  KC_PIPE, KC_COLN,    KC_LPRN,  KC_RPRN,    KC_QUES,    KC_INS,
      _______,        KC_CIRC,         KC_SLSH,    KC_ASTR, KC_BSLS,    KC_UNDS,  KC_TILD,  KC_DLR,    KC_LCBR,  KC_RCBR,    _______,   _______,
      _______,        _______,         _______,    _______, _______,    _______,  KC_NO,   _______,    KC_HOME,  KC_PGDN,    KC_PGUP,    KC_END
  ),

  [_ADJUST] = LAYOUT_planck_grid(
       KC_ESC,    KC_F1,    KC_F2,   KC_F3,   KC_F4,      KC_F5,    KC_F6,   KC_F7,      KC_F8,    KC_F9,     KC_F10,     KC_F11,
      KC_CAPS,   KC_F12,  KC_PSCR, _______, _______,    _______,  _______, RGB_HUD,    RGB_HUI,  KC_MUTE,    KC_VOLD,    KC_VOLU,
      _______,  _______,  _______, _______, _______,    _______,  _______, RGB_VAD,    RGB_VAI,  RGB_TOG,    RGB_MOD,    RGB_SLD,
      _______,  _______,  _______, _______, _______,    _______,  KC_NO,   _______,    _______,   MU_TOGG,     QK_MUSIC_MODE_NEXT,     AU_TOGG
  ),

  [_GAME] = LAYOUT_planck_grid(
      _______,        _______,         _______,    _______, _______,    _______,  _______, _______,    _______,  _______,    _______,    _______,
      KC_LCTL,        _______,         _______,    _______, _______,    _______,  _______, _______,    _______,  _______,    _______,    _______,
      _______,        _______,         _______,    _______, _______,    _______,  _______, _______,    _______,  _______,    _______,    _______,
      _______,        _______,         _______,    _______, _______,    _______,  KC_NO,   _______,    _______,  _______,    _______,    _______
  ),

  [_NUMERIC] = LAYOUT_planck_grid(
      TG(_GAME),      _______,         _______,    _______, _______,    _______,  _______, _______,    _______,  KC_1,       KC_2,       KC_3,
      _______,        _______,         _______,    _______, _______,    _______,  _______, _______,    _______,  KC_4,       KC_5,       KC_6,
      _______,        _______,         _______,    _______, _______,    _______,  _______, _______,    _______,  KC_7,       KC_8,       KC_9,
      _______,        _______,         _______,    _______, _______,    _______,  KC_NO,   _______,    HEXPFIX,  KC_DOT,     KC_0,       KC_COMMA
  ),
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
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},          {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },
    [_NUMERIC] = {
            {WASD_COLOR}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {NUM_COLOR}, {NUM_COLOR}, {NUM_COLOR},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {NUM_COLOR}, {NUM_COLOR}, {NUM_COLOR},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {NUM_COLOR}, {NUM_COLOR}, {NUM_COLOR},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {NUM_COLOR}, {0,0,0} },
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
    case _NUMERIC:
    case _BASE: {
      set_layer_color(layer, layer != _BASE);
    } break;
    case _ADJUST: {
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
    case DBLCOLN:
        if (record->event.pressed) {
            SEND_STRING("::");
        }
        return false;
    case HEXPFIX:
      if (record->event.pressed) {
        SEND_STRING("0x");
      }
      return false;
  }
  return true;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
