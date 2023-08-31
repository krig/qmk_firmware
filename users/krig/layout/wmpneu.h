#pragma once
// wmpneu
//
// experimental layout
//
// w c m g q* z f o u '
// r s n t p  y h e i a
// x b l d v  j k / . ,
//
// *: swedish layer on hold

#define ALTERN_L1 KC_W, KC_C, KC_M, KC_G, LT(_LANG, KC_Q)
#define ALTERN_L2 KC_R, KC_S, KC_N, KC_T, KC_P
#define ALTERN_L3 KC_X, KC_B, KC_L, KC_D, KC_V
#define ALTERN_R1 KC_Z, KC_F, KC_O, KC_U, KC_QUOT
#define ALTERN_R2 KC_Y, KC_H, KC_E, KC_I, KC_A
#define ALTERN_R3 KC_J, KC_K, KC_SLSH, KC_DOT, KC_COMM
