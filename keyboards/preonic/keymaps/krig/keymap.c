/*
 * Kristoffer Gronlund, 2023
 */
#include "krig.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_preonic_grid(
      QK_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
      CTL_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, NAV_CLN,  KC_ENT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, SFT_QUO,
      MO_FKEY, CTL_SFT, KC_LALT, KC_LGUI, MO_SWED,  KC_SPC,  KC_SPC, MO_SYMB, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_SWEDE] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,
      _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   _______, _______, SQ_AMPR, KC_UNDS, KC_HASH, _______, KC_DEL,
      _______, SQ_PHEX, KC_P4,   KC_P5,   KC_P6,   _______, SQ_PIPE, SQ_COLN, SQ_AA,   SQ_OE,   SQ_AE,   _______,
      _______, KC_DOT,  KC_P7,   KC_P8,   KC_P9,   _______, _______, SQ_PATH, ZOOM_UT, ZOOM_IN, KC_BSLS, KC_GRV,
      _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),
    [_SYMBOLS] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, KC_CIRC, KC_LT,   KC_GT,   KC_DQUO, KC_QUOT, KC_GRV,  KC_AMPR, KC_LBRC, KC_RBRC, KC_PERC, _______,
      _______, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_UNDS, KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_QUES, _______,
      _______, KC_TILD, KC_SLSH, KC_ASTR, KC_BSLS, KC_HASH, KC_TILD, KC_DLR,  KC_LCBR, KC_RCBR, KC_AT,   KC_GRV,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_GAME] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, WS_PREV,  WS_ALL, WS_NEXT, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_FKEYS] = LAYOUT_preonic_grid(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  MO_QMK
    ),
    [_FKEYS2] = LAYOUT_preonic_grid(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  MO_QMK
    ),
    [_QMKSTUFF] = LAYOUT_preonic_grid(
      TG_GAME, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};


const rgblight_segment_t PROGMEM krig_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_RED}
);
const rgblight_segment_t PROGMEM krig_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(

    {0, RGBLED_NUM, HSV_BLACK}
);
const rgblight_segment_t PROGMEM krig_swede_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_BLUE}
);
const rgblight_segment_t PROGMEM krig_symbols_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_GREEN}
);
const rgblight_segment_t PROGMEM krig_game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_GOLDENROD}
);
const rgblight_segment_t PROGMEM krig_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_CYAN}
);
const rgblight_segment_t PROGMEM krig_fkeys_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_PINK}
);
const rgblight_segment_t PROGMEM krig_qmkstuff_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_SPRINGGREEN}
);

enum light_layers {
    _L_BASE,
    _L_CAPS,
    _L_SWEDE,
    _L_SYMBOLS,
    _L_GAME,
    _L_NAV,
    _L_FKEYS,
    _L_QMKSTUFF
};

const rgblight_segment_t* const PROGMEM krig_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    krig_base_layer,
    krig_capslock_layer,
    krig_swede_layer,
    krig_symbols_layer,
    krig_game_layer,
    krig_nav_layer,
    krig_fkeys_layer,
    krig_qmkstuff_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = krig_rgb_layers;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    return krig_handle_sequence_keys(keycode, record);
}

#ifdef AUDIO_ENABLE
float caps_word_on_song[][2] = SONG(CAPS_LOCK_ON_SOUND);
float caps_word_off_song[][2] = SONG(CAPS_LOCK_OFF_SOUND);
#endif

void caps_word_set_user(bool active) {
    rgblight_set_layer_state(_L_CAPS, active);
    #ifdef AUDIO_ENABLE
    if (active) {
        PLAY_SONG(caps_word_on_song);
    } else {
        PLAY_SONG(caps_word_off_song);
    }
    #endif
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_L_BASE, layer_state_cmp(state, _BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _SWEDE, _SYMBOLS, _FKEYS);
    rgblight_set_layer_state(_L_SWEDE, layer_state_cmp(state, _SWEDE));
    rgblight_set_layer_state(_L_SYMBOLS, layer_state_cmp(state, _SYMBOLS));
    rgblight_set_layer_state(_L_GAME, layer_state_cmp(state, _GAME));
    rgblight_set_layer_state(_L_NAV, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(_L_FKEYS, layer_state_cmp(state, _FKEYS) || layer_state_cmp(state, _FKEYS2));
    rgblight_set_layer_state(_L_QMKSTUFF, layer_state_cmp(state, _QMKSTUFF));
    return state;
}
