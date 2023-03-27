/* Copyright 2020 Jason Williams (Wilba)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "krig.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
       WS_ALL,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
      WS_NEXT, CTL_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, NAV_CLN,  KC_ENT,
      WS_PREV, KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, SFT_QUO,
      TG_GAME, MO_FKEY, CTL_SFT, KC_LALT, KC_LGUI, MO_SWED,  KC_SPC,          MO_SYMB, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_SWEDE] = LAYOUT(
      _______, _______, _______,  KC_7,   KC_8,    KC_9,    _______, _______, SQ_AMPR, KC_UNDS, KC_HASH, _______, KC_DEL,
      _______, _______, SQ_PHEX,  KC_4,   KC_5,    KC_6,    _______, SQ_PIPE, SQ_COLN, SQ_AA,   SQ_OE,   SQ_AE,   _______,
      _______, _______, KC_0,     KC_1,   KC_2,    KC_3,    _______, _______, SQ_PATH, ZOOM_UT, ZOOM_IN, KC_BSLS, KC_GRV,
      _______, _______, _______, _______, _______, _______, _______,          _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),
    [_SYMBOLS] = LAYOUT(
      _______, _______, KC_CIRC, KC_LT,   KC_GT,   KC_DQUO, KC_QUOT, KC_GRV,  KC_AMPR, KC_LBRC, KC_RBRC, KC_PERC, KC_INS,
      _______, _______, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_UNDS, KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_QUES, _______,
      _______, _______, KC_TILD, KC_SLSH, KC_ASTR, KC_BSLS, KC_HASH, KC_TILD, KC_DLR,  KC_LCBR, KC_RCBR, KC_AT,   KC_GRV,
      _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______
    ),
    [_GAME] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, WS_PREV,  WS_ALL, WS_NEXT, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______
    ),
    [_FKEYS] = LAYOUT(
      _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,  MO_QMK
    ),
    [_QMKSTUFF] = LAYOUT(
      _______, TG_GAME, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    return krig_handle_sequence_keys(keycode, record);
}

void backlight_set_color( int index, uint8_t red, uint8_t green, uint8_t blue );
void backlight_set_color_all( uint8_t red, uint8_t green, uint8_t blue );

const uint8_t m50_rowcol_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {  0+15,  0+14,  0+13,  0+12,  0+11,  0+10,   0+9,  18+1,  18+2,  18+3,  18+4,  18+5,  18+6 },
    {  0+16,   0+6,   0+5,   0+4,   0+3,   0+2,   0+1,  18+9, 18+10, 18+11, 18+12, 18+13, 18+14 },
    { 36+15, 36+14, 36+13, 36+12, 36+11, 36+10,  36+9,  54+1,  54+2,  54+3,  54+4,  54+5,  54+6 },
    {  36+7,  36+6,  36+5,  36+4,  36+3,  36+2,  36+1,   255, 54+10, 54+11, 54+12, 54+13, 54+14 },
};

#define LC_FN1 m50_rowcol_to_led[0][0]
#define LC_FN2 m50_rowcol_to_led[1][0]
#define LC_FN3 m50_rowcol_to_led[2][0]
#define LC_FN4 m50_rowcol_to_led[3][0]

#define LC_W m50_rowcol_to_led[0][3]
#define LC_A m50_rowcol_to_led[1][2]
#define LC_S m50_rowcol_to_led[1][3]
#define LC_D m50_rowcol_to_led[1][4]

#define LC_LOWER m50_rowcol_to_led[3][5]
#define LC_RAISE m50_rowcol_to_led[3][8]
#define LC_SPACE m50_rowcol_to_led[3][6]
#define LC_BOOT m50_rowcol_to_led[0][12]
#define LC_QMK m50_rowcol_to_led[3][12]
#define LC_GAME m50_rowcol_to_led[0][1]


// Override this to replace backlight
// settings
void backlight_effect_indicators(void) {
    backlight_set_color_all(0, 0, 0);
    uint8_t r = 0xfb, g = 0x85, b = 0x00;
    backlight_set_color(LC_FN4, r/2, g/2, b/2);
    
    if (IS_LAYER_ON(_GAME)) {
        backlight_set_color(LC_FN4, r, g, b);
        r = 255; g = 0; b = 0;
        backlight_set_color(LC_W, r, g, b);
        backlight_set_color(LC_A, r, g, b);
        backlight_set_color(LC_S, r, g, b);
        backlight_set_color(LC_D, r, g, b);
    } else if (IS_LAYER_ON(_FKEYS) || IS_LAYER_ON(_FKEYS2)) {
        backlight_set_color(LC_FN1, r, g, b);
        r = 0x02; g = 0x30; b = 0x47; 
        for (int i = 1; i < 12; ++i) {
            backlight_set_color(m50_rowcol_to_led[0][i], r, g, b);
        }
        backlight_set_color(LC_LOWER, r, g, b);
        backlight_set_color(LC_RAISE, r, g, b);
        backlight_set_color(LC_SPACE, r, g, b);
        backlight_set_color(LC_QMK, 255, 0, 0);
    } else if (IS_LAYER_ON(_SYMBOLS)) {
        r = 0x02; g = 0x30; b = 0x47; 
        backlight_set_color(LC_RAISE, r, g, b);
        backlight_set_color(LC_SPACE, r, g, b);
    } else if (IS_LAYER_ON(_SWEDE)) {
        r = 0x02; g = 0x30; b = 0x47; 
        backlight_set_color(LC_LOWER, r, g, b);
        backlight_set_color(LC_SPACE, r, g, b);
    } else if (IS_LAYER_ON(_QMKSTUFF)) {
        backlight_set_color(LC_QMK, 255, 0, 0);
        backlight_set_color(LC_BOOT, 255, 0, 0);
        backlight_set_color(LC_GAME, 0, 255, 0);
    } else {
    }
}
