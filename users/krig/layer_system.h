#pragma once

#include "quantum.h"

enum krig_layers {
    // default layers
    _QWERTY,
    _HANDS,
    _GAME,

    // primary layers
    _EXTEND,
    _SYMBOL,

    // secondary layers
    _NUM,
    _FUNS,
};

// Default layer switching
// #define DF_QWER DF(_QWERTY)
// #define DF_HAND DF(_HANDS)
// #define DF_GAME DF(_GAME)

// Layer switching
// #define MO_EXT MO(_EXTEND)
// #define MO_SYM MO(_SYMBOL)
// #define MO_NUM MO(_NUM)
// #define MO_FUNS MO(_FUNS)
#define TT_EXT TT(_EXTEND)
#define TT_SYM TT(_SYMBOL)
#define TT_NUM TT(_NUM)
#define TT_FUNS TT(_FUNS)

bool krig_handle_sequence_keys(uint16_t keycode, keyrecord_t* record);
