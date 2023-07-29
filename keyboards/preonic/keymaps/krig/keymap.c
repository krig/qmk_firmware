/*
 * Kristoffer Gronlund, 2023
 * Preonic
 *
 * Apart from the hands down reference layer, this layout
 * is fairly stable and basically what I use for work.
 */

#include "krig.h"
#include "custom_keys.h"
#include "features/custom_shift_keys.h"
#include "features/krig_caps_word.h"

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

#define M_LOWER MO(_LOWER)
#define M_RAISE MO(_RAISE)
#define T_HAND  TG(_HANDS)
#define T_GAME  TG(_GAME)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_preonic_grid(
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
      CTL_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, CTL_ENT,
      OSM_SFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RALT,
      CW_TOGG, CTL_SFT, KC_LALT, KC_LGUI, M_LOWER,  KC_SPC,  KC_SPC, M_RAISE, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_HANDS] = LAYOUT_preonic_grid(
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
       KC_TAB,    KC_Q,    KC_C,    KC_H,    KC_P,    KC_V,    KC_Y,    KC_K,    KC_O,    KC_J, KC_QUOT, KC_BSPC,
      CTL_ESC,    KC_R,    KC_S,    KC_N,    KC_T,    KC_G,    KC_W,    KC_U,    KC_E,    KC_I,    KC_A, CTL_ENT,
      OSM_SFT,    KC_X,    KC_M,    KC_L,    KC_D,    KC_B,    KC_Z,    KC_F, KC_COMM,  KC_DOT, KC_SLSH, KC_RALT,
      CW_TOGG, CTL_SFT, KC_LALT, KC_LGUI, M_LOWER,  KC_SPC,  KC_SPC, M_RAISE, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_GAME] = LAYOUT_preonic_grid(
      QK_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, CTL_ENT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RALT,
      CW_TOGG, CTL_SFT, KC_LALT, KC_LGUI, M_LOWER,  KC_SPC,  KC_SPC, M_RAISE, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_LOWER] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, KC_1,    KC_2,    KC_3,    _______, _______, SQ_AMPR, SQ_LTLT, SQ_GTGT, _______, _______,
      _______,    KC_0, KC_4,    KC_5,    KC_6,    _______, SQ_PIPE, SQ_COLN, _______, _______, _______, _______,
      _______, SQ_PHEX, KC_7,    KC_8,    KC_9,    _______, _______, SQ_PATH, SQ_LTAR, SQ_RTAR, SQ_EXPI, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END
    ),
    [_RAISE] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______,  KC_GRV, KC_TILD, KC_HASH, KC_PERC,   KC_LT, SQ_COLN, KC_AMPR, KC_LBRC, KC_RBRC, _______, _______,
      _______, KC_EXLM, KC_MINS, KC_PLUS,  KC_EQL,   KC_AT, KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN, _______,
      _______, KC_QUES, KC_SLSH, KC_ASTR, KC_UNDS,   KC_GT, KC_CIRC,  KC_DLR, KC_LCBR, KC_RCBR, KC_BSLS, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT_preonic_grid(
      DF_QWER,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
      DF_HAND, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_INS,
      DF_GAME, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};


const rgblight_segment_t PROGMEM krig_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_RED}
);
const rgblight_segment_t PROGMEM krig_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_TEAL}
);
const rgblight_segment_t PROGMEM krig_funs_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_PINK}
);

enum light_layers {
    _L_CAPS,
    _L_QWERTY,
    _L_FUNS
};

const rgblight_segment_t* const PROGMEM krig_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    krig_capslock_layer,
    krig_qwerty_layer,
    krig_funs_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = krig_rgb_layers;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
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


#ifdef AUDIO_ENABLE
float caps_word_on_song[][2] = SONG(CAPS_LOCK_ON_SOUND);
float caps_word_off_song[][2] = SONG(CAPS_LOCK_OFF_SOUND);
#endif

bool caps_word_press_user(uint16_t keycode) {
    return krig_caps_word_press(keycode);
}


void caps_word_set_user(bool active) {
    krig_caps_word_set(active);
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
    rgblight_set_layer_state(_L_QWERTY, layer_state_cmp(state, _QWERTY));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_L_FUNS, layer_state_cmp(state, _ADJUST));
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
