/*
 * Kristoffer Gronlund, 2023
 */
#include QMK_KEYBOARD_H


enum custom_keycodes {
    SQ_COLN = SAFE_RANGE, // ::
    SQ_AMPR,
    SQ_PIPE,
    SQ_PATH,
    SQ_PHEX // 0x
};


enum preonic_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
    _GAME,
    _LAYERS
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_preonic_grid(
      QK_GESC,        KC_1,            KC_2,    KC_3,    KC_4,       KC_5,     KC_6,     KC_7,       KC_8,     KC_9,       KC_0,       KC_BSLS,
      KC_TAB,         KC_Q,            KC_W,    KC_E,    KC_R,       KC_T,     KC_Y,     KC_U,       KC_I,     KC_O,       KC_P,       KC_BSPC,
      LCTL_T(KC_ESC), KC_A,            KC_S,    KC_D,    KC_F,       KC_G,     KC_H,     KC_J,       KC_K,     KC_L,       KC_SCLN,    KC_ENTER,
      KC_LSFT,        KC_Z,            KC_X,    KC_C,    KC_V,       KC_B,     KC_N,     KC_M,       KC_COMMA, KC_DOT,     KC_SLASH,   KC_QUOTE,
      MO(_LAYERS),   LCTL(KC_LSFT),   KC_LALT, KC_LGUI, MO(_LOWER), KC_SPACE, KC_SPACE, MO(_RAISE), KC_LEFT,  KC_DOWN,    KC_UP,      KC_RIGHT
    ),
    [_LOWER] = LAYOUT_preonic_grid(
      _______,        _______,         _______,    _______, _______,    _______,  _______, _______, _______,  _______, _______, KC_INS,
      _______,        _______,           KC_P7,      KC_P8,   KC_P9,    _______,  _______, SQ_AMPR, _______,  _______, RALT(KC_W), KC_DEL,
      _______,        SQ_PHEX,           KC_P4,      KC_P5,   KC_P6,    _______,  SQ_PIPE, SQ_COLN, _______,  RALT(KC_P), RALT(KC_Q), _______,
      _______,          KC_P0,           KC_P1,      KC_P2,   KC_P3,    _______,  _______, SQ_PATH,LGUI(KC_MINS),LGUI(KC_PLUS),KC_BSLS,  KC_GRV,
      _______,        _______,         _______,    _______, _______,    _______,  _______, _______,    KC_HOME,     KC_PGDN,    KC_PGUP,  KC_END
    ),
    [_RAISE] = LAYOUT_preonic_grid(
      _______,        _______,         _______, _______, _______,    _______,  _______,  _______,    _______,  _______,    _______,    _______,
      _______,        KC_TILD,           KC_LT,      KC_GT, KC_DQUO,    KC_QUOT,   KC_GRV, KC_AMPR,    KC_LBRC,  KC_RBRC,    KC_PERC,  _______,
      _______,        KC_EXLM,         KC_MINS,    KC_PLUS,  KC_EQL,    KC_UNDS,  KC_PIPE, KC_COLN,    KC_LPRN,  KC_RPRN,    KC_QUES,  _______,
      _______,        KC_CIRC,         KC_SLSH,    KC_ASTR, KC_BSLS,    KC_HASH,  KC_TILD,  KC_DLR,    KC_LCBR,  KC_RCBR,      KC_AT,   KC_GRV,
      _______,        _______,         _______,    _______, _______,    _______,  _______, _______,    _______,  _______,    _______,  _______
    ),
    [_ADJUST] = LAYOUT_preonic_grid(
      KC_SCRL,        KC_F1,           KC_F2,   KC_F3,   KC_F4,      KC_F5,    KC_F6,    KC_F7,      KC_F8,    KC_F9,      KC_F10,     KC_F11,
      KC_CAPS,        KC_F12,          KC_PSCR, _______, _______,    _______,  _______,  _______,    _______,  KC_MUTE,    KC_VOLD,    KC_VOLU,
      _______,        _______,         _______, _______, _______,    _______,  _______,  _______,    RGB_MOD,  RGB_TOG,    RGB_VAD,    RGB_VAI,
      _______,        _______,         _______, _______, _______,    _______,  _______,  _______,    BL_BRTG,  BL_TOGG,    BL_STEP,    _______,
      _______,        _______,         _______, _______, _______,    _______,  _______,  _______,    _______,  BL_DOWN,     BL_UP,     _______
    ),
    [_GAME] = LAYOUT_preonic_grid(
      _______,        _______,         _______, _______, _______,    _______,  _______,  _______,    _______,  _______,    _______,    KC_F9,
      _______,        _______,         _______, _______, _______,    _______,  _______,  _______,    _______,  _______,    _______,    _______,
      KC_LCTL,        _______,         _______, _______, _______,    _______,  _______,  _______,    _______,  _______,    _______,    _______,
      _______,        _______,         _______, _______, _______,    _______,  _______,  _______,    _______,  _______,    _______,    _______,
      _______,        _______,         _______, _______, _______,    _______,  _______,  _______,    _______,  _______,    _______,    _______
    ),
    [_LAYERS] = LAYOUT_preonic_grid(
      TG(_GAME),      _______,         _______, _______, _______,    _______,  _______,  _______,    _______,  _______,    _______,    _______,
      _______,        _______,         _______, _______, _______,    _______,  _______,  _______,    _______,  _______,    _______,    _______,
      _______,        _______,         _______, _______, _______,    _______,  _______,  _______,    _______,  _______,    _______,    _______,
      _______,        _______,         _______, _______, _______,    _______,  _______,  _______,    _______,  _______,    _______,    _______,
      _______,        _______,         _______, _______, _______,    _______,  _______,  _______,    _______,  _______,    _______,    _______
    )
};

#define HSV_ORANGE2 18, 255, 255

const rgblight_segment_t PROGMEM krig_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_RED}
);
const rgblight_segment_t PROGMEM krig_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(

    {0, RGBLED_NUM, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM krig_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_BLUE}
);
const rgblight_segment_t PROGMEM krig_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_GREEN}
);
const rgblight_segment_t PROGMEM krig_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_MAGENTA}
);
const rgblight_segment_t PROGMEM krig_game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_ORANGE2}
);
const rgblight_segment_t PROGMEM krig_numeric_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_SPRINGGREEN}
);

enum light_layers {
    _L_BASE,
    _L_CAPS,
    _L_LOWER,
    _L_RAISE,
    _L_GAME,
    _L_LAYERS,
    _L_ADJUST
};

const rgblight_segment_t* const PROGMEM krig_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    krig_base_layer,
    krig_capslock_layer,
    krig_lower_layer,
    krig_raise_layer,
    krig_game_layer,
    krig_numeric_layer,
    krig_adjust_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = krig_rgb_layers;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
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

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(_L_CAPS, led_state.caps_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_L_BASE, layer_state_cmp(state, _BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    rgblight_set_layer_state(_L_LOWER, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(_L_RAISE, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(_L_GAME, layer_state_cmp(state, _GAME));
    rgblight_set_layer_state(_L_LAYERS, layer_state_cmp(state, _LAYERS));
    rgblight_set_layer_state(_L_ADJUST, layer_state_cmp(state, _ADJUST));
    return state;
}
