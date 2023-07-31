/*
 * Kristoffer Gronlund, 2023
 * Preonic
 *
 * Apart from the alternate layout layer, this layout
 * is fairly stable and basically what I use for work.
 */

#include "krig.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_preonic_grid(
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
      CTL_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, CTL_ENT,
      OSM_SFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT,  M_LANG, KC_RSFT,
      CW_TOGG, CTL_SFT, KC_LALT, KC_LGUI, M_LOWER,  KC_SPC,  KC_SPC, M_RAISE, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_APTV3] = LAYOUT_preonic_grid(
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
       KC_TAB,    KC_W,    KC_G,    KC_D,    KC_F,    KC_B,    KC_Q,    KC_L,    KC_U,    KC_O,    KC_Y, KC_BSPC,
      CTL_ESC,    KC_R,    KC_S,    KC_T,    KC_H,    KC_K,    KC_J,    KC_N,    KC_E,    KC_A,    KC_I, CTL_ENT,
      OSM_SFT,    KC_X,    KC_C,    KC_M,    KC_P,    KC_V,    KC_Z, KC_COMM,  KC_DOT, KC_QUOT,  M_LANG, KC_RSFT,
      CW_TOGG, CTL_SFT, KC_LALT, KC_LGUI, M_LOWER,  KC_SPC,  KC_SPC, M_RAISE, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_GAME] = LAYOUT_preonic_grid(
      QK_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, CTL_ENT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT,  M_LANG, KC_RSFT,
      CW_TOGG, CTL_SFT, KC_LALT, KC_LGUI, M_LOWER,  KC_SPC,  KC_SPC, M_RAISE, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_LANG] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,   SQ_AA,   SQ_AE,   SQ_OE, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_TRNS, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_LOWER] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, KC_1,    KC_2,    KC_3,    _______,  KC_INS, KC_PGDN,   KC_UP, KC_PGUP,  KC_DEL, _______,
      _______,    KC_0, KC_4,    KC_5,    KC_6,    _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, _______,
      _______, SQ_PHEX, KC_7,    KC_8,    KC_9,    _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_RAISE] = LAYOUT_preonic_grid(
      _______, _______, SQ_LTLT, SQ_GTGT, SQ_PATH, _______, SQ_PIPE, SQ_AMPR, SQ_LTAR, SQ_RTAR, _______, _______,
      _______,  KC_GRV, KC_TILD, KC_HASH, KC_PERC,   KC_LT, SQ_COLN, KC_AMPR, KC_LBRC, KC_RBRC, SQ_EXPI, _______,
      _______, KC_EXLM, KC_MINS, KC_PLUS,  KC_EQL,   KC_AT, KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN, _______,
      _______, KC_QUES, KC_SLSH, KC_ASTR, KC_UNDS,   KC_GT, KC_CIRC,  KC_DLR, KC_LCBR, KC_RCBR, KC_BSLS, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT_preonic_grid(
      DF_QWER,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
       DF_APT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_INS,
      DF_GAME, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};


const rgblight_segment_t PROGMEM lightlayer_0[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});
const rgblight_segment_t PROGMEM lightlayer_1[] = RGBLIGHT_LAYER_SEGMENTS({3, 3, HSV_GREEN});
const rgblight_segment_t PROGMEM lightlayer_2[] = RGBLIGHT_LAYER_SEGMENTS({RGBLED_NUM-3, 3, HSV_GREEN});
const rgblight_segment_t PROGMEM lightlayer_3[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_YELLOW}, {RGBLED_NUM-1, 1, HSV_BLUE});
const rgblight_segment_t PROGMEM lightlayer_4[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_MAGENTA});
const rgblight_segment_t PROGMEM lightlayer_5[] = RGBLIGHT_LAYER_SEGMENTS({RGBLED_NUM-4, 4, HSV_AZURE});
const rgblight_segment_t PROGMEM lightlayer_6[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_ORANGE});
const rgblight_segment_t PROGMEM lightlayer_capsword[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_RED}, {RGBLED_NUM-2, 2,});

const rgblight_segment_t* const PROGMEM lightlayers[] = RGBLIGHT_LAYERS_LIST(
    lightlayer_0,
    lightlayer_1,
    lightlayer_2,
    lightlayer_3,
    lightlayer_4,
    lightlayer_5,
    lightlayer_6,
    lightlayer_capsword
);

void keyboard_post_init_user(void) {
    rgblight_layers = lightlayers;
}

#ifdef AUDIO_ENABLE
float caps_word_on_song[][2] = SONG(CAPS_LOCK_ON_SOUND);
float caps_word_off_song[][2] = SONG(CAPS_LOCK_OFF_SOUND);
#endif

void caps_word_set_keymap(bool active) {
    rgblight_set_layer_state(_ADJUST+1, active);
    #ifdef AUDIO_ENABLE
    if (active) {
        PLAY_SONG(caps_word_on_song);
    } else {
        PLAY_SONG(caps_word_off_song);
    }
    #endif
}

layer_state_t default_layer_state_set_keymap(layer_state_t state) {
    for (int i = 0; i <= _GAME; ++i) {
        rgblight_set_layer_state(i, layer_state_cmp(state, i));
    }
    return state;
}

layer_state_t layer_state_set_keymap(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    for (int i = 0; i <= _ADJUST; ++i) {
        rgblight_set_layer_state(i, layer_state_cmp(state, i));
    }
    return state;
}
