#include QMK_KEYBOARD_H

enum preonic_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
    _GAME,
    _NUMERIC
};

#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_KNIGHT
#define RGBLIGHT_DEFAULT_HUE 222 // rose

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT_ortho_5x12(
        KC_GESC           , KC_1          , KC_2    , KC_3    , KC_4       , KC_5   , KC_6   , KC_7       , KC_8    , KC_9    , KC_0    , KC_DEL  ,
        KC_TAB            , KC_Q          , KC_W    , KC_E    , KC_R       , KC_T   , KC_Y   , KC_U       , KC_I    , KC_O    , KC_P    , KC_BSPC ,
        LCTL_T(KC_ESCAPE) , KC_A          , KC_S    , KC_D    , KC_F       , KC_G   , KC_H   , KC_J       , KC_K    , KC_L    , KC_SCLN , KC_ENT  ,
        KC_LSFT           , KC_Z          , KC_X    , KC_C    , KC_V       , KC_B   , KC_N   , KC_M       , KC_COMM , KC_DOT  , KC_SLSH , KC_QUOT ,
        MO(_NUMERIC)      , LCTL(KC_LSFT) , KC_LALT , KC_LGUI , MO(_LOWER) , KC_SPC , KC_SPC , MO(_RAISE) , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT
    ),
	[_LOWER] = LAYOUT_ortho_5x12(
        KC_GRV  , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR  , KC_ASTR , KC_LPRN    , KC_RPRN    , KC_INS  ,
        KC_TRNS , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR  , KC_ASTR , RALT(KC_P) , RALT(KC_Q) , KC_TRNS ,
        KC_TRNS , KC_LBRC , KC_RBRC , KC_LPRN , KC_RPRN , KC_PIPE , KC_PLUS , KC_MINS  , KC_UNDS , KC_EQL     , RALT(KC_W) , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_LCBR , KC_RCBR , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS    , KC_BSLS    , KC_GRV  ,
        KC_NO   , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_HOME , KC_PGDN    , KC_PGUP    , KC_END
    ),
	[_RAISE] = LAYOUT_ortho_5x12(
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_LCBR , KC_RCBR , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_LBRC , KC_RBRC , KC_LPRN , KC_RPRN  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_QUOT , KC_DQUO , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_LCBR , KC_RCBR  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
    ),
	[_ADJUST] = LAYOUT_ortho_5x12(
        KC_SLCK , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
        KC_CAPS , KC_F12  , KC_PSCR , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_MUTE , KC_VOLD , KC_VOLU ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , RGB_MOD , RGB_TOG , RGB_VAD , RGB_VAI ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , BL_BRTG , BL_TOGG , BL_STEP , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , BL_DEC  , BL_INC  , KC_TRNS
    ),
	[_GAME] = LAYOUT_ortho_5x12(
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_LCTL , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
    ),
	[_NUMERIC] = LAYOUT_ortho_5x12(
        TG(_GAME) , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
    )
};

const rgblight_segment_t PROGMEM krig_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_RED}
);
const rgblight_segment_t PROGMEM krig_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_TURQUOISE}
);
const rgblight_segment_t PROGMEM krig_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_PINK}
);
const rgblight_segment_t PROGMEM krig_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM krig_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_SPRINGGREEN}
);
const rgblight_segment_t PROGMEM krig_game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_AZURE}
);


// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM krig_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    krig_base_layer,
    krig_capslock_layer,
    krig_lower_layer,
    krig_raise_layer,
    krig_adjust_layer,
    krig_game_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = krig_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(4, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(5, layer_state_cmp(state, _GAME));
    return state;
}
