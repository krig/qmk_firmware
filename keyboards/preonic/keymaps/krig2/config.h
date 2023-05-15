/*
 * Kristoffer Gronlund, 2023
 * Preonic Conservative
 */
#pragma once

#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYER_BLINK
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_KNIGHT
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_DEFAULT_HUE 222 // rose

#ifdef AUDIO_ENABLE
#undef STARTUP_SONG
#    define STARTUP_SONG SONG(PREONIC_SOUND)
#endif

#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 1
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

