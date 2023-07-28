#pragma once
#include QMK_KEYBOARD_H

enum custom_keycodes {
    SQ_COLN = SAFE_RANGE, // ::
    SQ_AMPR,              // &&
    SQ_PIPE,              // ||
    SQ_PATH,              // ../
    SQ_SLAS,              // //
    SQ_PHEX,              // 0x
    SQ_LTLT,              // <<
    SQ_GTGT,              // >>
    SQ_RTAR,              // ->
    SQ_LTAR,              // <-
    SQ_EXPI,              // |>
    LLOCK,                // layer lock
    OS_SFT,
    OS_ALT,
    OS_CTL,
    OS_GUI,

    DF_QWER,
    DF_HAND,
    DF_GAME,
    MO_EXT,
    MO_SYM,
    MO_NUM,
    MO_FUNS,

};

