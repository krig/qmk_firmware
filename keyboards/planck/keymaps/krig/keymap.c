#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"


enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
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
      LCTL_T(KC_ESC), KC_A,            KC_S,       KC_D,    KC_F,       KC_G,     KC_H,    KC_J,       KC_K,     KC_L,       KC_SCLN,  KC_ENTER,
      KC_LSFT,      KC_Z,            KC_X,       KC_C,    KC_V,       KC_B,     KC_N,    KC_M,       KC_COMMA, KC_DOT,     KC_SLASH,   KC_QUOTE,
      MO(_NUMERIC),   LCTL(KC_LSFT), KC_LALT,    KC_LGUI, MO(_LOWER), KC_SPACE, KC_NO,   MO(_RAISE), KC_LEFT,  KC_DOWN,    KC_UP,      KC_RIGHT
  ),

  [_LOWER] = LAYOUT_planck_grid(
      KC_TILD,        KC_EXLM,         KC_AT,      KC_HASH, KC_DLR,     KC_PERC,  KC_CIRC, KC_AMPR,    KC_ASTR,  RALT(KC_P), RALT(KC_Q), _______,
      _______,        _______,         _______,    KC_LPRN, KC_RPRN,    KC_PIPE,  KC_PLUS, KC_MINUS,   KC_UNDS,  KC_EQUAL,   RALT(KC_W), _______,
      _______,        _______,         _______,    _______, _______,    _______,  _______, _______,    _______,  _______,    KC_BSLS,  KC_GRAVE,
      _______,        _______,         _______,    _______, _______,    _______,  KC_NO,   _______,    KC_HOME,  KC_PGDN,  KC_PGUP,    KC_END
  ),

  [_RAISE] = LAYOUT_planck_grid(
      KC_ESC,         KC_1,            KC_2,       KC_3,    KC_4,       KC_5,     KC_6,    KC_7,       KC_8,     KC_9,       KC_0,       KC_DELETE,
      _______,        _______,         _______,    KC_LCBR, KC_RCBR,    KC_LABK,  KC_RABK, KC_LBRC,    KC_RBRC,  KC_QUOT,    KC_DQUO,    KC_INSERT,
      _______,        _______,         _______,    _______, _______,    _______,  _______, _______,    _______,  _______,    _______,    _______,
      _______,        _______,         _______,    _______, _______,    _______,  KC_NO,   _______,    KC_HOME,  KC_PGDN,  KC_PGUP,    KC_END
  ),

  [_ADJUST] = LAYOUT_planck_grid(
      KC_SCRL,  KC_F1,           KC_F2,      KC_F3,   KC_F4,      KC_F5,    KC_F6,   KC_F7,      KC_F8,    KC_F9,      KC_F10,     KC_F11,
      KC_CAPS,    KC_F12,          KC_PSCR, _______, _______,    _______,  _______, RGB_HUD,    RGB_HUI,  KC_MUTE,    KC_VOLD,    KC_VOLU,
      _______,        _______,         _______,    _______, _______,    _______,  _______, RGB_VAD,    RGB_VAI,  RGB_TOG,    RGB_MOD,    RGB_SLD,
      _______,        _______,         _______,    _______, _______,    _______,  KC_NO,   _______,    _______,  MU_TOG,     MU_MOD,     AU_TOG
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
      _______,        _______,         _______,    _______, _______,    _______,  KC_NO,   _______,    _______,  KC_DOT,     KC_0,       KC_COMMA
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
    [_GAME] = { {0,0,0}, {0,0,0}, {WASD_COLOR}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {WASD_COLOR}, {WASD_COLOR}, {WASD_COLOR}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },
    [_NUMERIC] = { {WASD_COLOR}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {NUM_COLOR}, {NUM_COLOR}, {NUM_COLOR},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {NUM_COLOR}, {NUM_COLOR}, {NUM_COLOR},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {NUM_COLOR}, {NUM_COLOR}, {NUM_COLOR},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {NUM_COLOR}, {0,0,0} },
};

void set_layer_color(void) {
  const bool gaming = layer_state_is(_GAME);
  const bool numeric = layer_state_is(_NUMERIC);
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
      uint8_t r = 0, g = 0, b = 0;
      if (gaming) {
          r = ledmap[_GAME][i][0];
          g = ledmap[_GAME][i][1];
          b = ledmap[_GAME][i][2];
      }
      if (numeric && (ledmap[_NUMERIC][i][0] || ledmap[_NUMERIC][i][1] || ledmap[_NUMERIC][i][2])) {
          r = ledmap[_NUMERIC][i][0];
          g = ledmap[_NUMERIC][i][1];
          b = ledmap[_NUMERIC][i][2];
      }
      rgb_matrix_set_color(i, r, g, b);
  }
}

bool rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) {
      return false;
  }

  if (layer_state_is(_GAME) || layer_state_is(_NUMERIC))
    set_layer_color();
  else if (layer_state_is(_ADJUST))
    rgb_matrix_set_color_all(0xb7, 0x15, 0x40);
  else if (rgb_matrix_get_flags() == LED_FLAG_NONE)
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
  }
  return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
        #else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
        #else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        #endif
        }
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case MO(_RAISE):
    case MO(_LOWER):
        return false;
    default:
        return true;
    }
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
