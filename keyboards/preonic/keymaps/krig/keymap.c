/*
 * Kristoffer Gronlund, 2023
 */
#include "krig.h"
#include "features/custom_shift_keys.h"
#include "features/repeat_key.h"

enum combos {
    CO_OSCAPS,
    CO_AA,
    CO_AE,
    CO_OE,
    CO_COPY,
    CO_PASTE,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM oscaps_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM aa_combo[] = {KC_Z, KC_COMM, COMBO_END};
const uint16_t PROGMEM ae_combo[] = {KC_Z, KC_DOT, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_Z, KC_MINS, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_D, COMBO_END};

combo_t key_combos[] = {
    [CO_OSCAPS] = COMBO(oscaps_combo, OSM(MOD_LSFT)),
    [CO_AA] = COMBO(aa_combo, SQ_AA),
    [CO_AE] = COMBO(ae_combo, SQ_AE),
    [CO_OE] = COMBO(oe_combo, SQ_OE),
    [CO_COPY] = COMBO(copy_combo, LGUI(KC_C)),
    [CO_PASTE] = COMBO(paste_combo, LGUI(KC_V)),
};

const custom_shift_key_t custom_shift_keys[] = {
    {KC_DOT, KC_COLN},
    {KC_COMM, KC_SCLN},
    {KC_BSPC, KC_DEL},
    {KC_UNDS, KC_MINS},
    {KC_DQUO, KC_QUOT},
};

uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_preonic_grid(
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS,
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, KC_UNDS, KC_BSPC,
      CTL_ESC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, CTL_ENT,
      OSM_SFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, SFT_QUO,
      MO_FUNS, CTL_SFT, KC_LALT, KC_LGUI, MO_LOWR,  KC_SPC,  REPEAT, MO_RAIS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_CTGAP] = LAYOUT_preonic_grid(
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS,
       KC_TAB,    KC_Q,    KC_P,    KC_L,    KC_C,    KC_J,    KC_K,    KC_F,    KC_O,    KC_U, KC_QUOT, KC_BSPC,
      CTL_ESC,    KC_R,    KC_N,    KC_T,    KC_S,    KC_G,    KC_Y,    KC_H,    KC_E,    KC_I,    KC_A, CTL_ENT,
      OSM_SFT,    KC_Z,    KC_B,    KC_M,    KC_W,    KC_V,    KC_X,    KC_D, KC_UNDS,  KC_COMM, KC_DOT, SFT_QUO,
      MO_FUNS, CTL_SFT, KC_LALT, KC_LGUI, MO_LOWR,  KC_SPC,  REPEAT, MO_RAIS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_QWERTY] = LAYOUT_preonic_grid(
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS,
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
      CTL_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_UNDS, CTL_ENT,
      OSM_SFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, SFT_QUO,
      MO_FUNS, CTL_SFT, KC_LALT, KC_LGUI, MO_LOWR,  KC_SPC,  REPEAT, MO_RAIS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_GAME] = LAYOUT_preonic_grid(
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS,
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_UNDS, CTL_ENT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, SFT_QUO,
      MO_FUNS, CTL_SFT, KC_LALT, KC_LGUI, MO_LOWR,  KC_SPC,  REPEAT, MO_RAIS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_LOWER] = LAYOUT_preonic_grid(
        LLOCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,
      _______, SQ_PHEX,   KC_P1,   KC_P2,   KC_P3, _______, _______, SQ_AMPR, KC_UNDS, KC_HASH, _______, KC_DEL,
      _______,   KC_P0,   KC_P4,   KC_P5,   KC_P6, _______, SQ_PIPE, SQ_COLN, SQ_AA,   SQ_AE,   SQ_OE,   _______,
      _______,  KC_DOT,   KC_P7,   KC_P8,   KC_P9, _______, _______, SQ_PATH, ZOOM_UT, ZOOM_IN, KC_BSLS, KC_GRV,
      _______, _______, _______, _______, _______, _______,  MO_NAV, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),
    [_RAISE] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, KC_CIRC,  KC_GRV, KC_QUOT, KC_DQUO,   KC_LT, _______, KC_AMPR, KC_LBRC, KC_RBRC, _______, _______,
      _______, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,    KC_GT, KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN, _______,
      _______, KC_TILD, KC_SLSH, KC_ASTR, KC_BSLS, KC_HASH, KC_HASH,  KC_DLR, KC_LCBR, KC_RCBR, KC_PERC,  KC_GRV,
      _______, _______, _______, _______, _______,  ALTREP, _______, _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT_preonic_grid(
        LLOCK, _______, _______, _______, _______, _______, _______, GUI_LFT,  GUI__R, GUI_RGT, _______, _______,
      _______,  GUI__Q,  GUI__W, _______, _______, _______, _______, KC_HOME,  KC_END,  GUI__T,  GUI__N, _______,
      _______, _______, WS_PREV,  WS_ALL, WS_NEXT, _______, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______,
      _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_FUNS] = LAYOUT_preonic_grid(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
      _______, DF_QWER, DF_COLE, DF_GAME, DF_CTGA, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT
    ),
    [_FUNS2] = LAYOUT_preonic_grid(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};


const rgblight_segment_t PROGMEM krig_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_RED}
);

const rgblight_segment_t PROGMEM krig_colemak_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM krig_ctgap_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_CORAL}
);
const rgblight_segment_t PROGMEM krig_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_BLACK}
);
const rgblight_segment_t PROGMEM krig_game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_GOLDENROD}
);

const rgblight_segment_t PROGMEM krig_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_BLUE}
);
const rgblight_segment_t PROGMEM krig_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_GREEN}
);
const rgblight_segment_t PROGMEM krig_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_CYAN}
);
const rgblight_segment_t PROGMEM krig_funs_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_PINK}
);
const rgblight_segment_t PROGMEM krig_funs2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_SPRINGGREEN}
);

enum light_layers {
    _L_CAPS,
    _L_COLEMAK,
    _L_CTGAP,
    _L_QWERTY,
    _L_GAME,
    _L_LOWER,
    _L_RAISE,
    _L_NAV,
    _L_FUNS
};

const rgblight_segment_t* const PROGMEM krig_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    krig_capslock_layer,
    krig_colemak_layer,
    krig_ctgap_layer,
    krig_qwerty_layer,
    krig_game_layer,
    krig_lower_layer,
    krig_raise_layer,
    krig_nav_layer,
    krig_funs_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = krig_rgb_layers;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_repeat_key_with_alt(keycode, record, REPEAT, ALTREP)) {
        return false;
    }
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }
    return krig_handle_sequence_keys(keycode, record);
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    if ((mods & MOD_MASK_CTRL)) {
        switch (keycode) {
            case KC_C: return C(KC_V);
        }
    }
    return KC_TRNS;
}

#ifdef AUDIO_ENABLE
float caps_word_on_song[][2] = SONG(CAPS_LOCK_ON_SOUND);
float caps_word_off_song[][2] = SONG(CAPS_LOCK_OFF_SOUND);
#endif

bool g_caps_word_last_key_was_space = false;

bool caps_word_press_user(uint16_t keycode) {
	switch (keycode) {
		// Keycodes that continue Caps Word, without shifting.
		case KC_LEFT:
		case KC_RIGHT:
		case KC_UP:
		case KC_DOWN:
		case A(KC_LEFT):
		case A(KC_RIGHT):
		case A(KC_UP):
		case A(KC_DOWN):
		case G(KC_LEFT):
		case G(KC_RIGHT):
		case G(KC_UP):
		case G(KC_DOWN):
			add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
			return true;

		case KC_SPACE:
			// If the last key was NOT a space, then register it having been pressed and
			// move on as normal
			if (!g_caps_word_last_key_was_space) {
				g_caps_word_last_key_was_space = true;
				return true;
			}
				// if this is the second space in a row, delete one and exit Caps Word
			else {
				tap_code16(KC_BACKSPACE);
				return false;
			}

		// Keys that do NOT break the Caps Word state
		case KC_A ... KC_Z:
		case KC_1 ... KC_0:
		case KC_MINS:
		case KC_UNDERSCORE:
		case KC_BACKSPACE:
			// If we're continuing on after a space, then we need to "address" that prior
			// space in some way. The way we do that depends on what mode we're in. But
			// in all cases, first we need to remove that space and then replace it with
			// another character or another operating mode (ex. OSM)
			if (g_caps_word_last_key_was_space) {
				tap_code16(KC_BACKSPACE);
				tap_code16(KC_UNDERSCORE);
				g_caps_word_last_key_was_space = false;
			}
			if (
				KC_A <= keycode && keycode <= KC_Z
			) {
				add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
			}
			return true;

		default:
			return false;  // Deactivate Caps Word
	}
}

void caps_word_set_user(bool active) {
	if (active) {
		g_caps_word_last_key_was_space = false;
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
    rgblight_set_layer_state(_L_COLEMAK, layer_state_cmp(state, _COLEMAK));
    rgblight_set_layer_state(_L_CTGAP, layer_state_cmp(state, _CTGAP));
    rgblight_set_layer_state(_L_QWERTY, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(_L_GAME, layer_state_cmp(state, _GAME));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _FUNS);
    rgblight_set_layer_state(_L_LOWER, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(_L_RAISE, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(_L_NAV, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(_L_FUNS, layer_state_cmp(state, _FUNS) || layer_state_cmp(state, _FUNS2));
    return state;
}


