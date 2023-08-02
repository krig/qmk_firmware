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

#ifdef KRIG_34KEY
#define M_LOWER LT(_LOWER, KC_ESC)
#define M_RAISE LT(_RAISE, KC_BSPC)
#else
#define M_LOWER MO(_LOWER)
#define M_RAISE MO(_RAISE)
#endif

#define DF_QWER  DF(_QWERTY)
#define DF_ALTR  DF(_ALTERN)
#define DF_GAME  DF(_GAME)
#define M_LANG LT(_LANG, KC_SLSH)
#define M_LANG2 LT(_LANG, KC_DOT)

bool krig_process_default_layers(uint16_t keycode, keyrecord_t* record);

#define NUMROW_L KC_1,     KC_2,    KC_3,    KC_4,    KC_5
#define NUMROW_R KC_6,     KC_7,    KC_8,    KC_9,    KC_0

// standard qwerty layout
#include "layout/qwerty.h"

// alternative keyboard layouts, only include one
//#include "layout/middlemaknh.h"
#include "layout/middlemakmodkg.h"
//#include "layout/handsref.h"
//#include "layout/aptv3.h"
//#include "layout/colemakdh.h"

