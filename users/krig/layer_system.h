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
#define THUMB_L2 LT(_LOWER, KC_ESC)
#define THUMB_L3 QK_REP
#define THUMB_L4 QK_AREP

#define THUMB_R1 LSFT_T(KC_BSPC)
#define THUMB_R2 LT(_RAISE, KC_ENT)
#define THUMB_R3 RGUI_T(KC_TAB)
#define THUMB_R4 RCTL_T(KC_DEL)

#define DF_QWER  DF(_QWERTY)
#define DF_ALTR  DF(_ALTERN)
#define DF_GAME  DF(_GAME)

bool krig_process_default_layers(uint16_t keycode, keyrecord_t* record);

#define NUMROW_L KC_1,     KC_2,    KC_3,    KC_4,    KC_5
#define NUMROW_R KC_6,     KC_7,    KC_8,    KC_9,    KC_0

#ifndef KRIG_NO_LANG
#define K_LANG(key) LT(_LANG, key)
#else
#define K_LANG(key) key
#endif

// standard qwerty layout
#include "layout/qwerty.h"

// lower / nav layer
#include "layout/lower.h"

// symbol layer
#include "layout/symbols.h"

// alternative keyboard layout (highly experimental)
#ifdef KRIG_KANARY
#include "layout/kanary.h"
#else
#include "layout/wmpneu.h"
#endif
