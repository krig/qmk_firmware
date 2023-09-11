#pragma once

enum custom_layers {
    _QWERTY,
    _ALTERN,
    _GAME,
#ifdef KRIG_EXTRA_DEFAULT_LAYERS
    KRIG_EXTRA_DEFAULT_LAYERS
#endif
    _LANG,
    _LOWER,
    _RAISE,
    _ADJUST,
#ifdef KRIG_EXTRA_LAYERS
    KRIG_EXTRA_LAYERS
#endif
};

#define THUMB_L1 KC_SPC
#define THUMB_R1 LSFT_T(KC_ENT)
#define THUMB_L2 LT(_LOWER, KC_ESC)
#define THUMB_R2 LT(_RAISE, KC_BSPC)

#define DF_QWER  DF(_QWERTY)
#define DF_ALTR  DF(_ALTERN)
#define DF_GAME  DF(_GAME)

bool krig_process_default_layers(uint16_t keycode, keyrecord_t* record);

#define NUMROW_L KC_1,     KC_2,    KC_3,    KC_4,    KC_5
#define NUMROW_R KC_6,     KC_7,    KC_8,    KC_9,    KC_0

// standard qwerty layout
#include "layout/qwerty.h"

// symbol layer
#include "layout/symbols.h"

// alternative keyboard layout (highly experimental)
#ifdef KRIG_KANARY
#include "layout/kanary.h"
#else
#include "layout/wmpneu.h"
#endif
