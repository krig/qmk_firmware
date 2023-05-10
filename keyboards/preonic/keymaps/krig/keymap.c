/*
 * Kristoffer Gronlund, 2023
 * Preonic
 */
#include "keycodes.h"
#include "krig.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_preonic_grid(
         KC_1,    KC_2,    KC_3,    KC_4,    KC_5, OSM_ALT, OSM_ALT,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, OSM_CTL, OSM_CTL,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
         KC_A,    KC_S,    KC_D,    KC_F,    KC_G, OSM_GUI, OSM_GUI,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,
         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, OSM_SFT, OSM_SFT,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_MINS,
      CTL_SFT,  KC_MEH,  REPEAT, MO_LSYM,  KC_SPC, KC_BSPC,  KC_ENT, KC_LSFT, MO_RSYM,  ALTREP, KC_PGDN, KC_PGUP
    ),
    [_ENGRAM] = LAYOUT_preonic_grid(
         KC_1,    KC_2,    KC_3,    KC_4,    KC_5, OSM_ALT, OSM_ALT,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
         KC_B,    KC_Y,    KC_O,    KC_U,    KC_Z, OSM_CTL, OSM_CTL,    KC_Q,    KC_L,    KC_D,    KC_W,    KC_V,
         KC_C,    KC_I,    KC_E,    KC_A, KC_COMM, OSM_GUI, OSM_GUI,  KC_DOT,    KC_H,    KC_T,    KC_S,    KC_N,
         KC_G,    KC_X,    KC_J,    KC_K, KC_MINS, OSM_SFT, OSM_SFT, KC_QUOT,    KC_R,    KC_M,    KC_F,    KC_P,
      CTL_SFT,  KC_MEH,  REPEAT, MO_LSYM,  KC_SPC, KC_BSPC,  KC_ENT, KC_LSFT, MO_RSYM,  ALTREP, KC_PGDN, KC_PGUP
    ),
    [_GAME] = LAYOUT_preonic_grid(
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS,
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_MINS, CTL_ENT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, SFT_QUO,
      MO_FUNS, CTL_SFT, KC_LALT, MO_LSYM,  KC_SPC,  KC_SPC,  KC_SPC,  MO_RSYM,  KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_LSYM] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______,  KC_ESC,  KC_TAB, _______, _______, _______, _______, _______, KC_AMPR, KC_LBRC, KC_RBRC, _______,
      OSM_ALT, OSM_CTL, OSM_GUI, OSM_SFT, _______, _______, _______, KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN,
       GUI__Z,  GUI__X,  GUI__C,  GUI__V, _______, _______, _______, KC_TILD,  KC_DLR, KC_LCBR, KC_RCBR, KC_BSLS,
      _______, _______, _______, KC_TRNS, _______, _______, _______,  MO_NAV, MO_MACR, _______, _______, _______
    ),
    [_RSYM] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      KC_CIRC,   KC_LT,   KC_GT, KC_PERC,   KC_AT, _______, _______, _______, _______,  KC_ENT, KC_BSPC, _______,
      KC_EXLM, KC_MINS, KC_PLUS,  KC_EQL, KC_HASH, _______, _______, _______, OSM_SFT, OSM_GUI, OSM_CTL, OSM_ALT,
      KC_TILD, KC_SLSH, KC_ASTR, KC_QUES, _______, _______, _______, _______,   SQ_AA,   SQ_AE,   SQ_OE, _______,
      _______, _______, _______, MO_FUNS,  MO_NUM, _______, _______, _______, KC_TRNS, _______, _______, _______
    ),
    [_NUM] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      SQ_PHEX,    KC_1,    KC_2,    KC_3, _______, _______, _______, _______, _______, _______, _______, _______,
         KC_0,    KC_4,    KC_5,    KC_6, _______, _______, _______, _______, OSM_SFT, OSM_GUI, OSM_CTL, OSM_ALT,
      KC_BSPC,    KC_7,    KC_8,    KC_9, _______, _______, _______, _______, _______, _______, _______, _______,
        LLOCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, GUI_LFT,  GUI__R, GUI_RGT, _______,
      KC_LGUI,  KC_SPC,  KC_GRV,  KC_TAB, _______, _______, _______, _______, KC_HOME,   KC_UP,  KC_END,  GUI__N,
      OSM_ALT, OSM_CTL, OSM_GUI, OSM_SFT, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT,  GUI__T,
      _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______,
        LLOCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_MACROS] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, SQ_AMPR, SQ_LTAR, SQ_RTAR, _______,
      OSM_ALT, OSM_CTL, OSM_GUI, OSM_SFT, _______, _______, _______, SQ_PIPE, SQ_COLN, SQ_LTLT, SQ_GTGT, SQ_PATH,
      _______, _______, _______, _______, _______, _______, _______, _______, SQ_SLAS, _______, _______, _______,
        LLOCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_FUNS] = LAYOUT_preonic_grid(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F11,  KC_F12,    KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,
      _______, _______, _______, _______, _______, DF_QWER, _______,  _______, _______, _______, _______, _______,
      OSM_ALT, OSM_CTL, OSM_GUI, OSM_SFT, _______, DF_ENGR, _______,  _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, DF_GAME, _______,  _______, _______, _______, _______, _______,
        LLOCK, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, QK_BOOT
    )
};


const rgblight_segment_t PROGMEM krig_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_RED}
);
const rgblight_segment_t PROGMEM krig_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_TEAL}
);
const rgblight_segment_t PROGMEM krig_alt_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_CORAL}
);
const rgblight_segment_t PROGMEM krig_game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_GOLDENROD}
);

const rgblight_segment_t PROGMEM krig_lsym_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_BLUE}
);
const rgblight_segment_t PROGMEM krig_rsym_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_GREEN}
);
const rgblight_segment_t PROGMEM krig_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_CYAN}
);
const rgblight_segment_t PROGMEM krig_num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM krig_funs_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_PINK}
);
const rgblight_segment_t PROGMEM krig_macros_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_SPRINGGREEN}
);

enum light_layers {
    _L_CAPS,
    _L_QWERTY,
    _L_ALT,
    _L_GAME,
    _L_LSYM,
    _L_RSYM,
    _L_NAV,
    _L_NUM,
    _L_MACROS,
    _L_FUNS
};

const rgblight_segment_t* const PROGMEM krig_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    krig_capslock_layer,
    krig_qwerty_layer,
    krig_alt_layer,
    krig_game_layer,
    krig_lsym_layer,
    krig_rsym_layer,
    krig_nav_layer,
    krig_num_layer,
    krig_macros_layer,
    krig_funs_layer
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
	if (active) {
        krig_clear_caps_word_last_key();
	}
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
    rgblight_set_layer_state(_L_ALT, layer_state_cmp(state, _ENGRAM));
    rgblight_set_layer_state(_L_GAME, layer_state_cmp(state, _GAME));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_L_LSYM, layer_state_cmp(state, _LSYM));
    rgblight_set_layer_state(_L_RSYM, layer_state_cmp(state, _RSYM));
    rgblight_set_layer_state(_L_NAV, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(_L_NUM, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(_L_MACROS, layer_state_cmp(state, _MACROS));
    rgblight_set_layer_state(_L_FUNS, layer_state_cmp(state, _FUNS));
    return state;
}
