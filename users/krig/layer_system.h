#pragma once

enum custom_layers {
    _QWERTY,
    _APTV3,
    _GAME,
    _LANG,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#ifdef KRIG_34KEY
#define M_LOWER LT(_LOWER, KC_ESC)
#define M_RAISE LT(_RAISE, KC_BSPC)
#else
#define M_LOWER MO(_LOWER)
#define M_RAISE MO(_RAISE)
#endif

#define DF_QWER  DF(_QWERTY)
#define DF_APT  DF(_APTV3)
#define DF_GAME  DF(_GAME)
#define M_LANG LT(_LANG, KC_SLSH)

bool krig_process_default_layers(uint16_t keycode, keyrecord_t* record);
