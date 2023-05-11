/*
 * Kristoffer Gronlund, 2023
 * Preonic Conservative
 */

#include QMK_KEYBOARD_H
#include "custom_shift_keys.h"

enum custom_keycodes {
    SQ_COLN = SAFE_RANGE, // ::
    SQ_AMPR, // &&
    SQ_PIPE, // ||
    SQ_PATH, // ../
    SQ_SLAS, // //
    SQ_PHEX, // 0x
    SQ_LTLT, // <<
    SQ_GTGT, // >>
    SQ_RTAR, // ->
    SQ_LTAR, // <-
};

enum custom_layers {
    _BASE,
    _HAND,
    _GAME,
    _LOWER,
    _RAISE,
    _ADJUST,
};


const custom_shift_key_t custom_shift_keys[] = {
    {KC_DOT, KC_EXLM}, // Shift . is !
    {KC_COMM, KC_QUES}, // Shift , is ?
    {KC_UNDS, KC_MINS}, // Shift _ is -
    {KC_SLSH, KC_HASH}, // Shift / is #
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);


#define ESC_CTL LCTL_T(KC_ESC)
#define ENT_CTL RCTL_T(KC_ENT)
#define CTL_SFT LCTL(KC_LSFT)
#define OSM_SFT OSM(MOD_LSFT)
#define SFT_QUO RSFT_T(KC_QUOT)
#define M_LOWER MO(_LOWER)
#define M_RAISE MO(_RAISE)
#define T_HAND  TG(_HAND)
#define T_GAME  TG(_GAME)


// Swedish letters
#define SQ_AA RALT(KC_W)
#define SQ_OE RALT(KC_P)
#define SQ_AE RALT(KC_Q)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_preonic_grid(
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
      ESC_CTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_UNDS, ENT_CTL,
      OSM_SFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, SFT_QUO,
       KC_MEH, CTL_SFT, KC_LALT, KC_LGUI, M_LOWER,  KC_SPC,  KC_SPC, M_RAISE, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_HAND] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______,    KC_Q,    KC_C,    KC_H,    KC_P,    KC_V,    KC_Y,    KC_K,    KC_O,    KC_J, KC_SLSH, _______,
      _______,    KC_R,    KC_S,    KC_N,    KC_T,    KC_G,    KC_W,    KC_U,    KC_E,    KC_I,    KC_A, _______,
      _______,    KC_X,    KC_M,    KC_L,    KC_D,    KC_B,    KC_Z,    KC_F, KC_UNDS, KC_COMM,  KC_DOT, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_GAME] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_LOWER] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______,  KC_GRV,   KC_LT,   KC_GT, KC_DQUO, KC_PERC, KC_CIRC, KC_AMPR, KC_LBRC, KC_RBRC,   KC_AT, _______,
      _______, KC_QUOT, KC_MINS, KC_PLUS,  KC_EQL, KC_BSLS, KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN, _______,
      _______, KC_TILD, KC_SLSH, KC_ASTR, KC_EXLM, _______, _______,  KC_DLR, KC_LCBR, KC_RCBR, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END
    ),
    [_RAISE] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, KC_6,    KC_5,    KC_4,    _______, _______, SQ_AMPR, SQ_LTLT, SQ_GTGT, _______, _______,
      _______,    KC_0, KC_3,    KC_2,    KC_1,    _______, SQ_PIPE, SQ_COLN, SQ_AA,   SQ_AE,   SQ_OE,   _______,
      _______, SQ_PHEX, KC_9,    KC_8,    KC_7,    _______, _______, SQ_PATH, SQ_LTAR, SQ_RTAR, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT_preonic_grid(
       T_HAND,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
       T_GAME, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_INS,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
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
    if (!process_custom_shift_keys(keycode, record)) { return false; }
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
        case SQ_SLAS: //
            if (record->event.pressed) {
                SEND_STRING("//");
            }
            return false;
        case SQ_LTLT: // <<
            if (record->event.pressed) {
                SEND_STRING("<<");
            }
            return false;
        case SQ_GTGT: // >>
            if (record->event.pressed) {
                SEND_STRING(">>");
            }
            return false;
        case SQ_RTAR: // ->
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            return false;
        case SQ_LTAR: // <-
            if (record->event.pressed) {
                SEND_STRING("<-");
            }
            return false;
    }
    return true;
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
    rgblight_set_layer_state(_L_QWERTY, layer_state_cmp(state, _BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_L_FUNS, layer_state_cmp(state, _ADJUST));
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
