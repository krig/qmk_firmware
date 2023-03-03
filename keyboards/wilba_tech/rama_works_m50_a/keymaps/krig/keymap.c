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
#include QMK_KEYBOARD_H


#define LOWER TL_LOWR
#define RAISE TL_UPPR


enum custom_keycodes {
    DBLCOLN = SAFE_RANGE, // ::
    HEXPFIX, // 0x
};


enum keyboard_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
    _GAME,
    _NUMERIC
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        LCTL(KC_UP),           KC_TAB,      KC_Q,             KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        LCTL(KC_RGHT), LCTL_T(KC_ESC),  KC_A,             KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        LCTL(KC_LEFT),        KC_LSFT,  KC_Z,             KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_QUOTE) ,
        TG(_GAME),       MO(_NUMERIC),  LCTL(KC_LSFT), KC_LALT, KC_LGUI,   LOWER,  KC_SPC,            RAISE,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),


    [_LOWER] = LAYOUT(
        _______,   KC_ESC,           KC_1,            KC_2,       KC_3,    KC_4,       KC_5,     KC_6,    KC_7,       KC_8,        KC_9,       KC_0, HEXPFIX,
        _______,  _______,        _______,         _______,    _______, _______,    _______,  _______, KC_UNDS, RALT(KC_P),  RALT(KC_Q), RALT(KC_W), _______,
        _______,  _______,        _______,         _______,    _______, _______,    _______,  _______, _______,LGUI(KC_MINS),LGUI(KC_PLUS), KC_BSLS,  KC_GRV,
        _______,  _______,        _______,         _______,    _______, _______,    _______,           _______,    KC_HOME,     KC_PGDN,    KC_PGUP,  KC_END
    ),
    [_RAISE] = LAYOUT(
        _______,  _______,        KC_QUOT,           KC_LT,      KC_GT, KC_DQUO,      KC_AT,  KC_AMPR, DBLCOLN,    KC_LBRC,  KC_RBRC,    KC_PERC,    KC_DEL,
        _______,  _______,        KC_EXLM,         KC_MINS,    KC_PLUS,  KC_EQL,    KC_HASH,  KC_PIPE, KC_COLN,    KC_LPRN,  KC_RPRN,    KC_QUES,    KC_INS,
        _______,  _______,        KC_CIRC,         KC_SLSH,    KC_ASTR, KC_BSLS,    KC_UNDS,  KC_TILD,  KC_DLR,    KC_LCBR,  KC_RCBR,    _______,   _______,
        _______,  _______,        _______,         _______,    _______, _______,    _______,           _______,    KC_HOME,  KC_PGDN,    KC_PGUP,    KC_END
    ),

    [_ADJUST] = LAYOUT(
        QK_BOOTLOADER,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,   KC_F6,   KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,
              _______, KC_CAPS,  KC_F12,  KC_PSCR,  _______,   BR_INC,   EF_INC,  ES_INC,  H1_INC,   S1_INC,   H2_INC,   S2_INC,  _______,
              _______, _______, _______,  _______,  _______,   BR_DEC,   EF_DEC,  ES_DEC,  H1_DEC,   S1_DEC,   H2_DEC,   S2_DEC,  _______,
              _______, _______, _______,  _______,  _______,  _______,  _______,          _______,  _______,  KC_VOLD,  KC_VOLU,  _______
    ),

    [_GAME] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______
    ),

    [_NUMERIC] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_1, KC_2, KC_3,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_4, KC_5, KC_6,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_7, KC_8, KC_9,
        _______, _______, _______, _______, _______, _______, _______,          _______, HEXPFIX, KC_DOT, KC_0, KC_COMMA
    )

};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case DBLCOLN:
            if (record->event.pressed) {
                SEND_STRING("::");
            }
            return false;
        case HEXPFIX:
            if (record->event.pressed) {
                SEND_STRING("0x");
            }
            return false;
    }
    return true;
}


void backlight_set_color( int index, uint8_t red, uint8_t green, uint8_t blue );
void backlight_set_color_all( uint8_t red, uint8_t green, uint8_t blue );

#define LC_FN1 15
#define LC_FN2 16
#define LC_FN3 (36+15)
#define LC_FN4 (36+7)

#define LC_W 12
#define LC_A 5
#define LC_S 4
#define LC_D 3

#define LC_NUM (36+6)
#define LC_NUMP1 (18+4)
#define LC_NUMP2 (18+5)
#define LC_NUMP3 (18+6)
#define LC_NUMP4 (18+12)
#define LC_NUMP5 (18+13)
#define LC_NUMP6 (18+14)
#define LC_NUMP7 (54+4)
#define LC_NUMP8 (54+5)
#define LC_NUMP9 (54+6)
#define LC_NUMP0 (54+13)

#define LC_LOWER (36+2)
#define LC_RAISE (54+10)
#define LC_SPACE (36+1)

static uint8_t modcolor(uint8_t c, float amt) {
    float cf = c * amt;
    if (cf < 0) cf = 0;
    if (cf > 255.f) cf = 255.f;
    return (uint8_t)cf;
}

// Override this to replace backlight
// settings
void backlight_effect_indicators(void) {
    backlight_set_color_all(0, 0, 0);
    uint8_t r = 0xfb, g = 0x85, b = 0x00;
    backlight_set_color(LC_FN4, r/2, g/2, b/2);
    
    if (IS_LAYER_ON(_GAME)) {
        r = 255; g = 0; b = 0;
        backlight_set_color(LC_W, r, g, b);
        backlight_set_color(LC_A, r, g, b);
        backlight_set_color(LC_S, r, g, b);
        backlight_set_color(LC_D, r, g, b);
        backlight_set_color(LC_FN4, r, g, b);
    } else if (IS_LAYER_ON(_NUMERIC)) {
        r = 0x01; g = 0x97; b = 0xf6;
        backlight_set_color(LC_NUM, r, g, b);
        
        backlight_set_color(LC_NUMP1, r, g, b);
        backlight_set_color(LC_NUMP2, r, g, b);
        backlight_set_color(LC_NUMP3, r, g, b);

        r = modcolor(r, 0.6);
        g = modcolor(g, 0.6);
        b = modcolor(b, 0.6);
        backlight_set_color(LC_NUMP4, r, g, b);
        backlight_set_color(LC_NUMP5, r, g, b);
        backlight_set_color(LC_NUMP6, r, g, b);
        
        r = modcolor(r, 0.6);
        g = modcolor(g, 0.6);
        b = modcolor(b, 0.6);
        backlight_set_color(LC_NUMP7, r, g, b);
        backlight_set_color(LC_NUMP8, r, g, b);
        backlight_set_color(LC_NUMP9, r, g, b);
        
        r = modcolor(r, 0.6);
        g = modcolor(g, 0.6);
        b = modcolor(b, 0.6);
        backlight_set_color(LC_NUMP0, r, g, b);

    } else if (IS_LAYER_ON(_ADJUST)) {
        backlight_set_color(LC_FN1, r, g, b);
        r = 0x02; g = 0x30; b = 0x47; 
        backlight_set_color(LC_LOWER, r, g, b);
        backlight_set_color(LC_RAISE, r, g, b);
        backlight_set_color(LC_SPACE, 255, 0, 0);
    } else if (IS_LAYER_ON(_RAISE)) {
        r = 0x02; g = 0x30; b = 0x47; 
        backlight_set_color(LC_RAISE, r, g, b);
        backlight_set_color(LC_SPACE, 0, 0, 255);
    } else if (IS_LAYER_ON(_LOWER)) {
        r = 0x02; g = 0x30; b = 0x47; 
        backlight_set_color(LC_LOWER, r, g, b);
        backlight_set_color(LC_SPACE, 0, 255, 0);
    } else {
    }
}
