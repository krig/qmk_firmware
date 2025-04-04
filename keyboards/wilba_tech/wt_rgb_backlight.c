/* Copyright 2017 Jason Williams (Wilba)
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

#if defined(RGB_BACKLIGHT_ZEAL60) || \
    defined(RGB_BACKLIGHT_ZEAL65) || \
    defined(RGB_BACKLIGHT_M60_A) || \
    defined(RGB_BACKLIGHT_M6_B) || \
    defined(RGB_BACKLIGHT_M10_C) || \
    defined(RGB_BACKLIGHT_KOYU) || \
    defined(RGB_BACKLIGHT_M65_B) || \
    defined(RGB_BACKLIGHT_M65_BX) || \
    defined(RGB_BACKLIGHT_HS60) || \
    defined(RGB_BACKLIGHT_NK65) || \
    defined(RGB_BACKLIGHT_NK87) || \
    defined(RGB_BACKLIGHT_KW_MEGA) || \
    defined(RGB_BACKLIGHT_NEBULA12) || \
    defined(RGB_BACKLIGHT_NEBULA68) || \
    defined(RGB_BACKLIGHT_U80_A) || \
    defined(RGB_BACKLIGHT_DAWN60) || \
    defined(RGB_BACKLIGHT_PORTICO) || \
	defined(RGB_BACKLIGHT_PORTICO75) || \
    defined(RGB_BACKLIGHT_WT60_B) || \
    defined(RGB_BACKLIGHT_WT60_BX) || \
    defined(RGB_BACKLIGHT_WT60_C) || \
    defined(RGB_BACKLIGHT_M50_A)
#else
#error wt_rgb_backlight.c compiled without setting configuration symbol
#endif

#ifndef MAX
    #define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif

#ifndef MIN
    #define MIN(a,b) ((a) < (b)? (a): (b))
#endif

#include "quantum.h"
#include "wt_rgb_backlight.h"
#include "wt_rgb_backlight_api.h"
#include "wt_rgb_backlight_keycodes.h"

#if !defined(RGB_BACKLIGHT_HS60) && !defined(RGB_BACKLIGHT_NK65) && !defined(RGB_BACKLIGHT_NK87) && !defined(RGB_BACKLIGHT_NEBULA68) && !defined(RGB_BACKLIGHT_NEBULA12) && !defined (RGB_BACKLIGHT_KW_MEGA)
#include <avr/interrupt.h>
#include "i2c_master.h"
#else
#include <ch.h>
#include <hal.h>
#include "i2c_master.h"
#endif

#if defined(RGB_BACKLIGHT_DAWN60)
#include "ws2812.h"
LED_TYPE g_ws2812_leds[WS2812_LED_TOTAL];
#endif

#include "progmem.h"
#include "quantum/color.h"
#include "eeprom.h"
#include <lib/lib8tion/lib8tion.h>

#include "via.h" // uses EEPROM address, lighting value IDs
#define RGB_BACKLIGHT_CONFIG_EEPROM_ADDR (VIA_EEPROM_CUSTOM_CONFIG_ADDR)

#if VIA_EEPROM_CUSTOM_CONFIG_SIZE == 0
#error VIA_EEPROM_CUSTOM_CONFIG_SIZE was not defined to store backlight_config struct
#endif

#if defined(RGB_BACKLIGHT_M6_B)
#include "drivers/led/issi/is31fl3218.h"
#define BACKLIGHT_LED_COUNT 6
#elif defined(RGB_BACKLIGHT_HS60)
#include "drivers/led/issi/is31fl3733.h"
#define BACKLIGHT_LED_COUNT 64
#elif defined(RGB_BACKLIGHT_NK65) || defined(RGB_BACKLIGHT_NEBULA68) || defined(RGB_BACKLIGHT_KW_MEGA)
#include "drivers/led/issi/is31fl3733.h"
#define BACKLIGHT_LED_COUNT 69
#elif defined(RGB_BACKLIGHT_NK87)
#include "drivers/led/issi/is31fl3733.h"
#define BACKLIGHT_LED_COUNT 128
#elif defined(RGB_BACKLIGHT_PORTICO75)
#include "drivers/led/issi/is31fl3741.h"
#define BACKLIGHT_LED_COUNT 98
#else
#include "drivers/led/issi/is31fl3731.h"
#if defined(RGB_BACKLIGHT_U80_A)
#define BACKLIGHT_LED_COUNT 108
#elif defined(RGB_BACKLIGHT_DAWN60)
#define BACKLIGHT_LED_COUNT 84  //64 + 20
#elif defined(RGB_BACKLIGHT_PORTICO)
#define BACKLIGHT_LED_COUNT 67  //36 + 31
#elif defined(RGB_BACKLIGHT_NEBULA12)
#define BACKLIGHT_LED_COUNT 16
#elif defined(RGB_BACKLIGHT_M10_C)
#define BACKLIGHT_LED_COUNT 12
#else
#define BACKLIGHT_LED_COUNT 72
#endif
#endif

#define BACKLIGHT_EFFECT_MAX 11

backlight_config g_config = {
    .use_split_backspace = RGB_BACKLIGHT_USE_SPLIT_BACKSPACE,
    .use_split_left_shift = RGB_BACKLIGHT_USE_SPLIT_LEFT_SHIFT,
    .use_split_right_shift = RGB_BACKLIGHT_USE_SPLIT_RIGHT_SHIFT,
    .use_7u_spacebar = RGB_BACKLIGHT_USE_7U_SPACEBAR,
    .use_iso_enter = RGB_BACKLIGHT_USE_ISO_ENTER,
    .disable_hhkb_blocker_leds = RGB_BACKLIGHT_DISABLE_HHKB_BLOCKER_LEDS,
    .disable_when_usb_suspended = RGB_BACKLIGHT_DISABLE_WHEN_USB_SUSPENDED,
    .disable_after_timeout = RGB_BACKLIGHT_DISABLE_AFTER_TIMEOUT,
    .brightness = RGB_BACKLIGHT_BRIGHTNESS,
    .effect = RGB_BACKLIGHT_EFFECT,
    .effect_speed = RGB_BACKLIGHT_EFFECT_SPEED,
    .color_1 = RGB_BACKLIGHT_COLOR_1,
    .color_2 = RGB_BACKLIGHT_COLOR_2,
    .caps_lock_indicator = RGB_BACKLIGHT_CAPS_LOCK_INDICATOR,
    .layer_1_indicator = RGB_BACKLIGHT_LAYER_1_INDICATOR,
    .layer_2_indicator = RGB_BACKLIGHT_LAYER_2_INDICATOR,
    .layer_3_indicator = RGB_BACKLIGHT_LAYER_3_INDICATOR,
    .alphas_mods = {
        RGB_BACKLIGHT_ALPHAS_MODS_ROW_0,
        RGB_BACKLIGHT_ALPHAS_MODS_ROW_1,
        RGB_BACKLIGHT_ALPHAS_MODS_ROW_2,
        RGB_BACKLIGHT_ALPHAS_MODS_ROW_3,
        RGB_BACKLIGHT_ALPHAS_MODS_ROW_4 },
#if defined(RGB_BACKLIGHT_M6_B)
    .custom_color = { { 0, 255 }, { 43, 255 }, { 85, 255 }, { 128, 255 }, { 171, 255 }, { 213, 255 } }
#elif defined(RGB_BACKLIGHT_M10_C)
    .custom_color = { { 0, 255 }, { 43, 255 }, { 85, 255 }, { 128, 255 }, { 171, 255 }, { 213, 255 }, { 0, 255 }, { 43, 255 }, { 85, 255 }, { 128, 255 } }
#endif
};

bool g_suspend_state = false;

// Global tick at 20 Hz
uint32_t g_tick = 0;

// Ticks since this key was last hit.
uint8_t g_key_hit[BACKLIGHT_LED_COUNT];

// Ticks since any key was last hit.
uint32_t g_any_key_hit = 0;

#if defined(RGB_BACKLIGHT_HS60)

// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// ADDR_2 is not needed. it is here as a dummy
#define ISSI_ADDR_1 0x50

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, B_1,   A_1,   C_1}, //LA1
    {0, E_1,   D_1,   F_1}, //LA2
    {0, H_1,   G_1,   I_1}, //LA3
    {0, K_1,   J_1,   L_1}, //LA4
    {0, B_2,   A_2,   C_2}, //LA5
    {0, E_2,   D_2,   F_2}, //LA6
    {0, H_2,   G_2,   I_2}, //LA7
    {0, K_2,   J_2,   L_2}, //LA8
    {0, B_3,   A_3,   C_3}, //LA9
    {0, E_3,   D_3,   F_3}, //LA10
    {0, H_3,   G_3,   I_3}, //LA11
    {0, K_3,   J_3,   L_3}, //LA12
    {0, B_4,   A_4,   C_4}, //LA13
    {0, E_4,   D_4,   F_4}, //LA14
    {0, H_4,   G_4,   I_4}, //LA15
    {0, K_4,   J_4,   L_4}, //LA16
    {0, B_5,   A_5,   C_5}, //LA17
    {0, E_5,   D_5,   F_5}, //LA18
    {0, H_5,   G_5,   I_5}, //LA19
    {0, K_5,   J_5,   L_5}, //LA20
    {0, B_6,   A_6,   C_6}, //LA21
    {0, E_6,   D_6,   F_6}, //LA22
    {0, H_6,   G_6,   I_6}, //LA23
    {0, K_6,   J_6,   L_6}, //LA24
    {0, B_7,   A_7,   C_7}, //LA25
    {0, E_7,   D_7,   F_7}, //LA26
    {0, H_7,   G_7,   I_7}, //LA27
    {0, K_7,   J_7,   L_7}, //LA28
    {0, B_8,   A_8,   C_8}, //LA29
    {0, E_8,   D_8,   F_8}, //LA30
    {0, H_8,   G_8,   I_8}, //LA31
    {0, K_8,   J_8,   L_8}, //LA32
    {0, B_9,   A_9,   C_9}, //LA33
    {0, E_9,   D_9,   F_9}, //LA34
    {0, H_9,   G_9,   I_9}, //LA35
    {0, K_9,   J_9,   L_9}, //LA36
    {0, B_10,  A_10,  C_10}, //LA37
    {0, E_10,  D_10,  F_10}, //LA38
    {0, H_10,  G_10,  I_10}, //LA39
    {0, K_10,  J_10,  L_10}, //LA40
    {0, B_11,  A_11,  C_11}, //LA41
    {0, E_11,  D_11,  F_11}, //LA42
    {0, H_11,  G_11,  I_11}, //LA43
    {0, K_11,  J_11,  L_11}, //LA44
    {0, B_12,  A_12,  C_12}, //LA45
    {0, E_12,  D_12,  F_12}, //LA46
    {0, H_12,  G_12,  I_12}, //LA47
    {0, K_12,  J_12,  L_12}, //LA48
    {0, B_13,  A_13,  C_13}, //LA49
    {0, E_13,  D_13,  F_13}, //LA50
    {0, H_13,  G_13,  I_13}, //LA51
    {0, K_13,  J_13,  L_13}, //LA52
    {0, B_14,  A_14,  C_14}, //LA53
    {0, E_14,  D_14,  F_14}, //LA54
    {0, H_14,  G_14,  I_14}, //LA55
    {0, K_14,  J_14,  L_14}, //LA56
    {0, B_15,  A_15,  C_15}, //LA57
    {0, E_15,  D_15,  F_15}, //LA58
    {0, H_15,  G_15,  I_15}, //LA59
    {0, K_15,  J_15,  L_15}, //LA60
    {0, B_16,  A_16,  C_16}, //LA61
    {0, E_16,  D_16,  F_16}, //LA62
    {0, H_16,  G_16,  I_16}, //LA63
    {0, K_16,  J_16,  L_16}, //LA64
};

#elif defined(RGB_BACKLIGHT_NK65) || defined(RGB_BACKLIGHT_NEBULA68) || defined(RGB_BACKLIGHT_NK87) || defined(RGB_BACKLIGHT_KW_MEGA)

// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// ADDR_2 is not needed. it is here as a dummy
#define ISSI_ADDR_1 0x50
#define ISSI_ADDR_2 0x52

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, B_1,   A_1,   C_1}, //LA1
    {0, E_1,   D_1,   F_1}, //LA2
    {0, H_1,   G_1,   I_1}, //LA3
    {0, K_1,   J_1,   L_1}, //LA4
    {0, B_2,   A_2,   C_2}, //LA5
    {0, E_2,   D_2,   F_2}, //LA6
    {0, H_2,   G_2,   I_2}, //LA7
    {0, K_2,   J_2,   L_2}, //LA8
    {0, B_3,   A_3,   C_3}, //LA9
    {0, E_3,   D_3,   F_3}, //LA10
    {0, H_3,   G_3,   I_3}, //LA11
    {0, K_3,   J_3,   L_3}, //LA12
    {0, B_4,   A_4,   C_4}, //LA13
    {0, E_4,   D_4,   F_4}, //LA14
    {0, H_4,   G_4,   I_4}, //LA15
    {0, K_4,   J_4,   L_4}, //LA16
    {0, B_5,   A_5,   C_5}, //LA17
    {0, E_5,   D_5,   F_5}, //LA18
    {0, H_5,   G_5,   I_5}, //LA19
    {0, K_5,   J_5,   L_5}, //LA20
    {0, B_6,   A_6,   C_6}, //LA21
    {0, E_6,   D_6,   F_6}, //LA22
    {0, H_6,   G_6,   I_6}, //LA23
    {0, K_6,   J_6,   L_6}, //LA24
    {0, B_7,   A_7,   C_7}, //LA25
    {0, E_7,   D_7,   F_7}, //LA26
    {0, H_7,   G_7,   I_7}, //LA27
    {0, K_7,   J_7,   L_7}, //LA28
    {0, B_8,   A_8,   C_8}, //LA29
    {0, E_8,   D_8,   F_8}, //LA30
    {0, H_8,   G_8,   I_8}, //LA31
    {0, K_8,   J_8,   L_8}, //LA32
    {0, B_9,   A_9,   C_9}, //LA33
    {0, E_9,   D_9,   F_9}, //LA34
    {0, H_9,   G_9,   I_9}, //LA35
    {0, K_9,   J_9,   L_9}, //LA36
    {0, B_10,  A_10,  C_10}, //LA37
    {0, E_10,  D_10,  F_10}, //LA38
    {0, H_10,  G_10,  I_10}, //LA39
    {0, K_10,  J_10,  L_10}, //LA40
    {0, B_11,  A_11,  C_11}, //LA41
    {0, E_11,  D_11,  F_11}, //LA42
    {0, H_11,  G_11,  I_11}, //LA43
    {0, K_11,  J_11,  L_11}, //LA44
    {0, B_12,  A_12,  C_12}, //LA45
    {0, E_12,  D_12,  F_12}, //LA46
    {0, H_12,  G_12,  I_12}, //LA47
    {0, K_12,  J_12,  L_12}, //LA48
    {0, B_13,  A_13,  C_13}, //LA49
    {0, E_13,  D_13,  F_13}, //LA50
    {0, H_13,  G_13,  I_13}, //LA51
    {0, K_13,  J_13,  L_13}, //LA52
    {0, B_14,  A_14,  C_14}, //LA53
    {0, E_14,  D_14,  F_14}, //LA54
    {0, H_14,  G_14,  I_14}, //LA55
    {0, K_14,  J_14,  L_14}, //LA56
    {0, B_15,  A_15,  C_15}, //LA57
    {0, E_15,  D_15,  F_15}, //LA58
    {0, H_15,  G_15,  I_15}, //LA59
    {0, K_15,  J_15,  L_15}, //LA60
    {0, B_16,  A_16,  C_16}, //LA61
    {0, E_16,  D_16,  F_16}, //LA62
    {0, H_16,  G_16,  I_16}, //LA63
    {0, K_16,  J_16,  L_16}, //LA64

    {1, B_1,   A_1,   C_1}, //LB1
    {1, E_1,   D_1,   F_1}, //LB2
    {1, H_1,   G_1,   I_1}, //LB3
    {1, K_1,   J_1,   L_1}, //LB4
    {1, B_2,   A_2,   C_2}, //LB5
    {1, E_2,   D_2,   F_2}, //LB6
    {1, H_2,   G_2,   I_2}, //LB7
    {1, K_2,   J_2,   L_2}, //LB8
    {1, B_3,   A_3,   C_3}, //LB9
    {1, E_3,   D_3,   F_3}, //LB10
    {1, H_3,   G_3,   I_3}, //LB11
    {1, K_3,   J_3,   L_3}, //LB12
    {1, B_4,   A_4,   C_4}, //LB13
    {1, E_4,   D_4,   F_4}, //LB14
    {1, H_4,   G_4,   I_4}, //LB15
    {1, K_4,   J_4,   L_4}, //LB16
    {1, B_5,   A_5,   C_5}, //LB17
    {1, E_5,   D_5,   F_5}, //LB18
    {1, H_5,   G_5,   I_5}, //LB19
    {1, K_5,   J_5,   L_5}, //LB20
    {1, B_6,   A_6,   C_6}, //LB21
    {1, E_6,   D_6,   F_6}, //LB22
    {1, H_6,   G_6,   I_6}, //LB23
    {1, K_6,   J_6,   L_6}, //LB24
    {1, B_7,   A_7,   C_7}, //LB25
    {1, E_7,   D_7,   F_7}, //LB26
    {1, H_7,   G_7,   I_7}, //LB27
    {1, K_7,   J_7,   L_7}, //LB28
    {1, B_8,   A_8,   C_8}, //LB29
    {1, E_8,   D_8,   F_8}, //LB30
    {1, H_8,   G_8,   I_8}, //LB31
    {1, K_8,   J_8,   L_8}, //LB32
    {1, B_9,   A_9,   C_9}, //LB33
    {1, E_9,   D_9,   F_9}, //LB34
    {1, H_9,   G_9,   I_9}, //LB35
    {1, K_9,   J_9,   L_9}, //LB36
    {1, B_10,  A_10,  C_10}, //LB37
    {1, E_10,  D_10,  F_10}, //LB38
    {1, H_10,  G_10,  I_10}, //LB39
    {1, K_10,  J_10,  L_10}, //LB40
    {1, B_11,  A_11,  C_11}, //LB41
    {1, E_11,  D_11,  F_11}, //LB42
    {1, H_11,  G_11,  I_11}, //LB43
    {1, K_11,  J_11,  L_11}, //LB44
    {1, B_12,  A_12,  C_12}, //LB45
    {1, E_12,  D_12,  F_12}, //LB46
    {1, H_12,  G_12,  I_12}, //LB47
    {1, K_12,  J_12,  L_12}, //LB48
    {1, B_13,  A_13,  C_13}, //LB49
    {1, E_13,  D_13,  F_13}, //LB50
    {1, H_13,  G_13,  I_13}, //LB51
    {1, K_13,  J_13,  L_13}, //LB52
    {1, B_14,  A_14,  C_14}, //LB53
    {1, E_14,  D_14,  F_14}, //LB54
    {1, H_14,  G_14,  I_14}, //LB55
    {1, K_14,  J_14,  L_14}, //LB56
    {1, B_15,  A_15,  C_15}, //LB57
    {1, E_15,  D_15,  F_15}, //LB58
    {1, H_15,  G_15,  I_15}, //LB59
    {1, K_15,  J_15,  L_15}, //LB60
    {1, B_16,  A_16,  C_16}, //LB61
    {1, E_16,  D_16,  F_16}, //LB62
    {1, H_16,  G_16,  I_16}, //LB63
    {1, K_16,  J_16,  L_16}, //LB64
};

#elif defined(RGB_BACKLIGHT_NEBULA12)
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
#define ISSI_ADDR_1 0x74

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C1_1,  C3_2,  C4_2}, //A1
    {0, C1_2,  C2_2,  C4_3}, //A2
    {0, C1_3,  C2_3,  C3_3}, //A3
    {0, C1_4,  C2_4,  C3_4}, //A4
    {0, C1_5,  C2_5,  C3_5}, //A5
    {0, C1_6,  C2_6,  C3_6}, //A6
    {0, C1_7,  C2_7,  C3_7}, //A7
    {0, C1_8,  C2_8,  C3_8}, //A8
    {0, C9_1,  C8_1,  C7_1}, //A9
    {0, C9_2,  C8_2,  C7_2}, //A10
    {0, C9_3,  C8_3,  C7_3}, //A11
    {0, C9_4,  C8_4,  C7_4}, //A12
    {0, C9_5,  C8_5,  C7_5}, //A13
    {0, C9_6,  C8_6,  C7_6}, //A14
    {0, C9_7,  C8_7,  C6_6}, //A15
    {0, C9_8,  C7_7,  C6_7}, //A16
};

#elif defined(RGB_BACKLIGHT_U80_A)

// U80-A prototype uses 3 ISSI drivers
#define ISSI_ADDR_1 0x74  // 11101[00] <- GND
#define ISSI_ADDR_2 0x76  // 11101[10] <- SDA
#define ISSI_ADDR_3 0x75  // 11101[01] <- SCL

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C2_1,  C3_1,  C4_1},  // LA0
    {0, C1_1,  C3_2, C4_2},   // LA1
    {0, C1_2,  C2_2, C4_3},   // LA2
    {0, C1_3,  C2_3, C3_3},   // LA3
    {0, C1_4,  C2_4, C3_4},   // LA4
    {0, C1_5,  C2_5, C3_5},   // LA5
    {0, C1_6,  C2_6, C3_6},   // LA6
    {0, C1_7,  C2_7, C3_7},   // LA7
    {0, C1_8,  C2_8, C3_8},   // LA8
    {0, C9_1,  C8_1, C7_1},   // LA9
    {0, C9_2,  C8_2, C7_2},   // LA10
    {0, C9_3,  C8_3, C7_3},   // LA11
    {0, C9_4,  C8_4, C7_4},   // LA12
    {0, C9_5,  C8_5, C7_5},   // LA13
    {0, C9_6,  C8_6, C7_6},   // LA14
    {0, C9_7,  C8_7, C6_6},   // LA15
    {0, C9_8,  C7_7, C6_7},   // LA16
    {0, C8_8,  C7_8, C6_8},   // LA17

    {0, C2_9,  C3_9,  C4_9},  // LB0
    {0, C1_9,  C3_10, C4_10}, // LB1
    {0, C1_10, C2_10, C4_11}, // LB2
    {0, C1_11, C2_11, C3_11}, // LB3
    {0, C1_12, C2_12, C3_12}, // LB4
    {0, C1_13, C2_13, C3_13}, // LB5
    {0, C1_14, C2_14, C3_14}, // LB6
    {0, C1_15, C2_15, C3_15}, // LB7
    {0, C1_16, C2_16, C3_16}, // LB8
    {0, C9_9,  C8_9,  C7_9},  // LB9
    {0, C9_10, C8_10, C7_10}, // LB10
    {0, C9_11, C8_11, C7_11}, // LB11
    {0, C9_12, C8_12, C7_12}, // LB12
    {0, C9_13, C8_13, C7_13}, // LB13
    {0, C9_14, C8_14, C7_14}, // LB14
    {0, C9_15, C8_15, C6_14}, // LB15
    {0, C9_16, C7_15, C6_15}, // LB16
    {0, C8_16, C7_16, C6_16}, // LB17

    {1, C2_1,  C3_1,  C4_1},  // LC0
    {1, C1_1,  C3_2, C4_2},   // LC1
    {1, C1_2,  C2_2, C4_3},   // LC2
    {1, C1_3,  C2_3, C3_3},   // LC3
    {1, C1_4,  C2_4, C3_4},   // LC4
    {1, C1_5,  C2_5, C3_5},   // LC5
    {1, C1_6,  C2_6, C3_6},   // LC6
    {1, C1_7,  C2_7, C3_7},   // LC7
    {1, C1_8,  C2_8, C3_8},   // LC8
    {1, C9_1,  C8_1,  C7_1},  // LC9
    {1, C9_2,  C8_2, C7_2},   // LC10
    {1, C9_3,  C8_3, C7_3},   // LC11
    {1, C9_4,  C8_4, C7_4},   // LC12
    {1, C9_5,  C8_5, C7_5},   // LC13
    {1, C9_6,  C8_6, C7_6},   // LC14
    {1, C9_7,  C8_7, C6_6},   // LC15
    {1, C9_8,  C7_7, C6_7},   // LC16
    {1, C8_8,  C7_8, C6_8},   // LC17

    {1, C2_9,  C3_9,  C4_9},  // LD0
    {1, C1_9,  C3_10, C4_10}, // LD1
    {1, C1_10, C2_10, C4_11}, // LD2
    {1, C1_11, C2_11, C3_11}, // LD3
    {1, C1_12, C2_12, C3_12}, // LD4
    {1, C1_13, C2_13, C3_13}, // LD5
    {1, C1_14, C2_14, C3_14}, // LD6
    {1, C1_15, C2_15, C3_15}, // LD7
    {1, C1_16, C2_16, C3_16}, // LD8
    {1, C9_9,  C8_9,  C7_9},  // LD9
    {1, C9_10, C8_10, C7_10}, // LD10
    {1, C9_11, C8_11, C7_11}, // LD11
    {1, C9_12, C8_12, C7_12}, // LD12
    {1, C9_13, C8_13, C7_13}, // LD13
    {1, C9_14, C8_14, C7_14}, // LD14
    {1, C9_15, C8_15, C6_14}, // LD15
    {1, C9_16, C7_15, C6_15}, // LD16
    {1, C8_16, C7_16, C6_16}, // LD17

    {2, C2_1,  C3_1,  C4_1},  // LE0
    {2, C1_1,  C3_2, C4_2},   // LE1
    {2, C1_2,  C2_2, C4_3},   // LE2
    {2, C1_3,  C2_3, C3_3},   // LE3
    {2, C1_4,  C2_4, C3_4},   // LE4
    {2, C1_5,  C2_5, C3_5},   // LE5
    {2, C1_6,  C2_6, C3_6},   // LE6
    {2, C1_7,  C2_7, C3_7},   // LE7
    {2, C1_8,  C2_8, C3_8},   // LE8
    {2, C9_1,  C8_1,  C7_1},  // LE9
    {2, C9_2,  C8_2, C7_2},   // LE10
    {2, C9_3,  C8_3, C7_3},   // LE11
    {2, C9_4,  C8_4, C7_4},   // LE12
    {2, C9_5,  C8_5, C7_5},   // LE13
    {2, C9_6,  C8_6, C7_6},   // LE14
    {2, C9_7,  C8_7, C6_6},   // LE15
    {2, C9_8,  C7_7, C6_7},   // LE16
    {2, C8_8,  C7_8, C6_8},   // LE17

    {2, C2_9,  C3_9,  C4_9},  // LF0
    {2, C1_9,  C3_10, C4_10}, // LF1
    {2, C1_10, C2_10, C4_11}, // LF2
    {2, C1_11, C2_11, C3_11}, // LF3
    {2, C1_12, C2_12, C3_12}, // LF4
    {2, C1_13, C2_13, C3_13}, // LF5
    {2, C1_14, C2_14, C3_14}, // LF6
    {2, C1_15, C2_15, C3_15}, // LF7
    {2, C1_16, C2_16, C3_16}, // LF8
    {2, C9_9,  C8_9,  C7_9},  // LF9
    {2, C9_10, C8_10, C7_10}, // LF10
    {2, C9_11, C8_11, C7_11}, // LF11
    {2, C9_12, C8_12, C7_12}, // LF12
    {2, C9_13, C8_13, C7_13}, // LF13
    {2, C9_14, C8_14, C7_14}, // LF14
    {2, C9_15, C8_15, C6_14}, // LF15
    {2, C9_16, C7_15, C6_15}, // LF16
    {2, C8_16, C7_16, C6_16}, // LF17
};
#elif defined(RGB_BACKLIGHT_DAWN60)
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
#define ISSI_ADDR_1 0x74
#define ISSI_ADDR_2 0x76

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C1_1,   C3_2,   C4_2}, //A1
    {0, C1_2,   C2_2,   C4_3}, //A2
    {0, C1_3,   C2_3,   C3_3}, //A3
    {0, C1_4,   C2_4,   C3_4}, //A4
    {0, C1_5,   C2_5,   C3_5}, //A5
    {0, C1_6,   C2_6,   C3_6}, //A6
    {0, C1_7,   C2_7,   C3_7}, //A7
    {0, C1_8,   C2_8,   C3_8}, //A8
    {0, C9_1,   C8_1,   C7_1}, //A9
    {0, C9_2,   C8_2,   C7_2}, //A10
    {0, C9_3,   C8_3,   C7_3}, //A11
    {0, C9_4,   C8_4,   C7_4}, //A12
    {0, C9_5,   C8_5,   C7_5}, //A13
    {0, C9_6,   C8_6,   C7_6}, //A14
    {0, C9_7,   C8_7,   C6_6}, //A15
    {0, C9_8,   C7_7,   C6_7}, //A16

    {0, C1_9,   C3_10,  C4_10}, //B1
    {0, C1_10,  C2_10,  C4_11}, //B2
    {0, C1_11,  C2_11,  C3_11}, //B3
    {0, C1_12,  C2_12,  C3_12}, //B4
    {0, C1_13,  C2_13,  C3_13}, //B5
    {0, C1_14,  C2_14,  C3_14}, //B6
    {0, C1_15,  C2_15,  C3_15}, //B7
    {0, C1_16,  C2_16,  C3_16}, //B8
    {0, C9_9,   C8_9,   C7_9},  //B9
    {0, C9_10,  C8_10,  C7_10}, //B10
    {0, C9_11,  C8_11,  C7_11}, //B11
    {0, C9_12,  C8_12,  C7_12}, //B12
    {0, C9_13,  C8_13,  C7_13}, //B13
    {0, C9_14,  C8_14,  C7_14}, //B14
    {0, C9_15,  C8_15,  C6_14}, //B15
    {0, C9_16,  C7_15,  C6_15}, //B16

    {1, C1_1,   C3_2,   C4_2}, //C1
    {1, C1_2,   C2_2,   C4_3}, //C2
    {1, C1_3,   C2_3,   C3_3}, //C3
    {1, C1_4,   C2_4,   C3_4}, //C4
    {1, C1_5,   C2_5,   C3_5}, //C5
    {1, C1_6,   C2_6,   C3_6}, //C6
    {1, C1_7,   C2_7,   C3_7}, //C7
    {1, C1_8,   C2_8,   C3_8}, //C8
    {1, C9_1,   C8_1,   C7_1}, //C9
    {1, C9_2,   C8_2,   C7_2}, //C10
    {1, C9_3,   C8_3,   C7_3}, //C11
    {1, C9_4,   C8_4,   C7_4}, //C12
    {1, C9_5,   C8_5,   C7_5}, //C13
    {1, C9_6,   C8_6,   C7_6}, //C14
    {1, C9_7,   C8_7,   C6_6}, //C15
    {1, C9_8,   C7_7,   C6_7}, //C16

    {1, C1_9,   C3_10,  C4_10}, //D1
    {1, C1_10,  C2_10,  C4_11}, //D2
    {1, C1_11,  C2_11,  C3_11}, //D3
    {1, C1_12,  C2_12,  C3_12}, //D4
    {1, C1_13,  C2_13,  C3_13}, //D5
    {1, C1_14,  C2_14,  C3_14}, //D6
    {1, C1_15,  C2_15,  C3_15}, //D7
    {1, C1_16,  C2_16,  C3_16}, //D8
    {1, C9_9,    C8_9,   C7_9},  //D9
    {1, C9_10,  C8_10,  C7_10}, //D10
    {1, C9_11,  C8_11,  C7_11}, //D11
    {1, C9_12,  C8_12,  C7_12}, //D12
    {1, C9_13,  C8_13,  C7_13}, //D13
    {1, C9_14,  C8_14,  C7_14}, //D14
    {1, C9_15,  C8_15,  C6_14}, //D15
    {1, C9_16,  C7_15,  C6_15}  //D16
};
#elif defined(RGB_BACKLIGHT_PORTICO)
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
#define ISSI_ADDR_1 0x74
#define ISSI_ADDR_2 0x77

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |   R location
 *   |   |      G location
 *   |   |      |      B location
 *   |   |      |      | */
    { 0, C2_1,  C3_1,  C4_1  },
    { 0, C1_1,  C3_2,  C4_2  },
    { 0, C1_2,  C2_2,  C4_3  },
    { 0, C1_3,  C2_3,  C3_3  },
    { 0, C1_4,  C2_4,  C3_4  },
    { 0, C1_5,  C2_5,  C3_5  },
    { 0, C1_6,  C2_6,  C3_6  },
    { 0, C1_7,  C2_7,  C3_7  },
    { 0, C1_8,  C2_8,  C3_8  },
    { 1, C2_1,  C3_1,  C4_1  },
    { 1, C1_1,  C3_2,  C4_2  },
    { 1, C1_2,  C2_2,  C4_3  },
    { 1, C1_3,  C2_3,  C3_3  },
    { 1, C1_4,  C2_4,  C3_4  },
    { 1, C1_5,  C2_5,  C3_5  },

    { 0, C9_1,  C8_1,  C7_1  },
    { 0, C9_2,  C8_2,  C7_2  },
    { 0, C9_3,  C8_3,  C7_3  },
    { 0, C9_4,  C8_4,  C7_4  },
    { 0, C9_5,  C8_5,  C7_5  },
    { 0, C9_6,  C8_6,  C7_6  },
    { 0, C9_7,  C8_7,  C6_6  },
    { 0, C9_8,  C7_7,  C6_7  },
    { 0, C8_8,  C7_8,  C6_8  },
    { 1, C9_1,  C8_1,  C7_1  },
    { 1, C9_2,  C8_2,  C7_2  },
    { 1, C9_3,  C8_3,  C7_3  },
    { 1, C9_4,  C8_4,  C7_4  },
    { 1, C9_5,  C8_5,  C7_5  },
    { 1, C9_6,  C8_6,  C7_6  },

    { 0, C1_9,  C3_10, C4_10 },
    { 0, C1_10, C2_10, C4_11 },
    { 0, C1_11, C2_11, C3_11 },
    { 0, C1_12, C2_12, C3_12 },
    { 0, C1_13, C2_13, C3_13 },
    { 0, C1_14, C2_14, C3_14 },
    { 0, C1_15, C2_15, C3_15 },
    { 0, C1_16, C2_16, C3_16 },
    { 1, C1_10, C2_10, C4_11 },
    { 1, C1_11, C2_11, C3_11 },
    { 1, C1_12, C2_12, C3_12 },
    { 1, C1_13, C2_13, C3_13 },
    { 1, C1_14, C2_14, C3_14 },
    { 1, C9_7,  C8_7,  C6_6  },

    { 0, C2_9,  C3_9,  C4_9  },
    { 0, C9_12, C8_12, C7_12 },
    { 0, C9_13, C8_13, C7_13 },
    { 0, C9_14, C8_14, C7_14 },
    { 0, C9_15, C8_15, C6_14 },
    { 0, C9_16, C7_15, C6_15 },
    { 1, C2_9,  C3_9,  C4_9  },
    { 1, C1_9,  C3_10, C4_10 },
    { 1, C9_9,  C8_9,  C7_9  },
    { 1, C9_10, C8_10, C7_10 },
    { 1, C9_11, C8_11, C7_11 },
    { 1, C9_14, C8_14, C7_14 },
    { 1, C1_15, C2_15, C3_15 },
    { 1, C1_16, C2_16, C3_16 },

    { 0, C9_9,  C8_9,  C7_9  },
    { 0, C9_10, C8_10, C7_10 },
    { 0, C9_11, C8_11, C7_11 },
    { 0, C8_16, C7_16, C6_16 },
    { 1, C9_12, C8_12, C7_12 },
    { 1, C9_13, C8_13, C7_13 },
    { 1, C9_15, C8_15, C6_14 },
    { 1, C9_16, C7_15, C6_15 },
    { 1, C8_16, C7_16, C6_16 }
};

#elif defined(RGB_BACKLIGHT_PORTICO75)
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
#define ISSI_ADDR_1 0x30
#define ISSI_ADDR_2

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |   R location
 *   |   |      G location
 *   |   |      |      B location
 *   |   |      |      | */
    {0, CS18_SW1, CS17_SW1, CS16_SW1},
    {0, CS18_SW2, CS17_SW2, CS16_SW2},
    {0, CS18_SW3, CS17_SW3, CS16_SW3},
    {0, CS18_SW4, CS17_SW4, CS16_SW4},
    {0, CS18_SW5, CS17_SW5, CS16_SW5},
    {0, CS18_SW6, CS17_SW6, CS16_SW6},
    {0, CS18_SW7, CS17_SW7, CS16_SW7},
    {0, CS18_SW8, CS17_SW8, CS16_SW8},
    {0, CS18_SW9, CS17_SW9, CS16_SW9},

    {0, CS21_SW1, CS20_SW1, CS19_SW1},
    {0, CS21_SW2, CS20_SW2, CS19_SW2},
    {0, CS21_SW3, CS20_SW3, CS19_SW3},
    {0, CS21_SW4, CS20_SW4, CS19_SW4},
    {0, CS21_SW5, CS20_SW5, CS19_SW5},
    {0, CS21_SW6, CS20_SW6, CS19_SW6}, //Encoder, NO_LED

    {0, CS15_SW1, CS14_SW1, CS13_SW1},
    {0, CS15_SW2, CS14_SW2, CS13_SW2},
    {0, CS15_SW3, CS14_SW3, CS13_SW3},
    {0, CS15_SW4, CS14_SW4, CS13_SW4},
    {0, CS15_SW5, CS14_SW5, CS13_SW5},
    {0, CS15_SW6, CS14_SW6, CS13_SW6},
    {0, CS15_SW7, CS14_SW7, CS13_SW7},
    {0, CS15_SW8, CS14_SW8, CS13_SW8},
    {0, CS15_SW9, CS14_SW9, CS13_SW9},

    {0, CS24_SW1, CS23_SW1, CS22_SW1},
    {0, CS24_SW2, CS23_SW2, CS22_SW2},
    {0, CS24_SW3, CS23_SW3, CS22_SW3},
    {0, CS24_SW4, CS23_SW4, CS22_SW4},
    {0, CS24_SW5, CS23_SW5, CS22_SW5},
    {0, CS24_SW6, CS23_SW6, CS22_SW6},

    {0, CS12_SW1, CS11_SW1, CS10_SW1},
    {0, CS12_SW2, CS11_SW2, CS10_SW2},
    {0, CS12_SW3, CS11_SW3, CS10_SW3},
    {0, CS12_SW4, CS11_SW4, CS10_SW4},
    {0, CS12_SW5, CS11_SW5, CS10_SW5},
    {0, CS12_SW6, CS11_SW6, CS10_SW6},
    {0, CS12_SW7, CS11_SW7, CS10_SW7},
    {0, CS12_SW8, CS11_SW8, CS10_SW8},
    {0, CS12_SW9, CS11_SW9, CS10_SW9},

    {0, CS27_SW1, CS26_SW1, CS25_SW1},
    {0, CS27_SW2, CS26_SW2, CS25_SW2},
    {0, CS27_SW3, CS26_SW3, CS25_SW3},
    {0, CS27_SW4, CS26_SW4, CS25_SW4},
    {0, CS27_SW5, CS26_SW5, CS25_SW5},
    {0, CS27_SW6, CS26_SW6, CS25_SW6},

    {0, CS9_SW1, CS8_SW1, CS7_SW1},
    {0, CS9_SW2, CS8_SW2, CS7_SW2},
    {0, CS9_SW3, CS8_SW3, CS7_SW3},
    {0, CS9_SW4, CS8_SW4, CS7_SW4},
    {0, CS9_SW5, CS8_SW5, CS7_SW5},
    {0, CS9_SW6, CS8_SW6, CS7_SW6},
    {0, CS9_SW7, CS8_SW7, CS7_SW7},
    {0, CS9_SW8, CS8_SW8, CS7_SW8},
    {0, CS9_SW9, CS8_SW9, CS7_SW9},

    {0, CS30_SW1, CS29_SW1, CS28_SW1},
    {0, CS30_SW2, CS29_SW2, CS28_SW2},
    {0, CS30_SW3, CS29_SW3, CS28_SW3},
    {0, CS30_SW4, CS29_SW4, CS28_SW4},

    {0, CS6_SW1, CS5_SW1, CS4_SW1},
    {0, CS6_SW2, CS5_SW2, CS4_SW2},
    {0, CS6_SW3, CS5_SW3, CS4_SW3},
    {0, CS6_SW4, CS5_SW4, CS4_SW4},
    {0, CS6_SW5, CS5_SW5, CS4_SW5},
    {0, CS6_SW6, CS5_SW6, CS4_SW6},
    {0, CS6_SW7, CS5_SW7, CS4_SW7},
    {0, CS6_SW8, CS5_SW8, CS4_SW8},
    {0, CS6_SW9, CS5_SW9, CS4_SW9},

    {0, CS33_SW1, CS32_SW1, CS31_SW1},
    {0, CS33_SW2, CS32_SW2, CS31_SW2},
    {0, CS33_SW3, CS32_SW3, CS31_SW3},
    {0, CS33_SW4, CS32_SW4, CS31_SW4},

    {0, CS3_SW1, CS2_SW1, CS1_SW1},
    {0, CS3_SW2, CS2_SW2, CS1_SW2},
    {0, CS3_SW3, CS2_SW3, CS1_SW3},
    {0, CS3_SW6, CS2_SW6, CS1_SW6},
    {0, CS3_SW8, CS2_SW8, CS1_SW8},
    {0, CS3_SW9, CS2_SW9, CS1_SW9},

    {0, CS36_SW1, CS35_SW1, CS34_SW1},
    {0, CS36_SW2, CS35_SW2, CS34_SW2},
    {0, CS36_SW3, CS35_SW3, CS34_SW3},

/*UNDERGLOW*/
    {0, CS39_SW1, CS38_SW1, CS37_SW1},
    {0, CS39_SW2, CS38_SW2, CS37_SW2},
    {0, CS39_SW3, CS38_SW3, CS37_SW3},
    {0, CS39_SW4, CS38_SW4, CS37_SW4},
    {0, CS39_SW5, CS38_SW5, CS37_SW5},
    {0, CS39_SW6, CS38_SW6, CS37_SW6},
    {0, CS39_SW7, CS38_SW7, CS37_SW7},
    {0, CS39_SW8, CS38_SW8, CS37_SW8},
    {0, CS39_SW9, CS38_SW9, CS37_SW9},

    {0, CS36_SW4, CS35_SW4, CS34_SW4},
    {0, CS36_SW5, CS35_SW5, CS34_SW5},
    {0, CS36_SW6, CS35_SW6, CS34_SW6},
    {0, CS36_SW7, CS35_SW7, CS34_SW7},
    {0, CS36_SW8, CS35_SW8, CS34_SW8},
    {0, CS36_SW9, CS35_SW9, CS34_SW9},

    {0, CS33_SW5, CS32_SW5, CS31_SW5},
    {0, CS33_SW6, CS32_SW6, CS31_SW6},
    {0, CS33_SW7, CS32_SW7, CS31_SW7}
};

#elif defined(RGB_BACKLIGHT_M6_B)
    // Driver has fixed mapping of index to the red, green and blue LEDs
#elif defined(RGB_BACKLIGHT_M10_C)
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
#define ISSI_ADDR_1 0x74
#define ISSI_ADDR_2

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, C1_9,  C3_10, C4_10}, // LB1
    {0, C1_10, C2_10, C4_11}, // LB2
    {0, C1_11, C2_11, C3_11}, // LB3
    {0, C1_12, C2_12, C3_12}, // LB4
    {0, C1_13, C2_13, C3_13}, // LB5
    {0, C1_14, C2_14, C3_14}, // LB6
    {0, C9_11, C8_11, C7_11}, // LB11
    {0, C9_12, C8_12, C7_12}, // LB12
    {0, C9_13, C8_13, C7_13}, // LB13
    {0, C9_14, C8_14, C7_14}, // LB14
    {0, C9_15, C8_15, C6_14}, // LB15
    {0, C9_16, C7_15, C6_15}  // LB16
};
#else
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
#define ISSI_ADDR_1 0x74
#define ISSI_ADDR_2 0x76

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C2_1,  C3_1,  C4_1},  // LA0
    {0, C1_1,  C3_2, C4_2},   // LA1
    {0, C1_2,  C2_2, C4_3},   // LA2
    {0, C1_3,  C2_3, C3_3},   // LA3
    {0, C1_4,  C2_4, C3_4},   // LA4
    {0, C1_5,  C2_5, C3_5},   // LA5
    {0, C1_6,  C2_6, C3_6},   // LA6
    {0, C1_7,  C2_7, C3_7},   // LA7
    {0, C1_8,  C2_8, C3_8},   // LA8
    {0, C9_1,  C8_1, C7_1},   // LA9
    {0, C9_2,  C8_2, C7_2},   // LA10
    {0, C9_3,  C8_3, C7_3},   // LA11
    {0, C9_4,  C8_4, C7_4},   // LA12
    {0, C9_5,  C8_5, C7_5},   // LA13
    {0, C9_6,  C8_6, C7_6},   // LA14
    {0, C9_7,  C8_7, C6_6},   // LA15
    {0, C9_8,  C7_7, C6_7},   // LA16
    {0, C8_8,  C7_8, C6_8},   // LA17

    {0, C2_9,  C3_9,  C4_9},  // LB0
    {0, C1_9,  C3_10, C4_10}, // LB1
    {0, C1_10, C2_10, C4_11}, // LB2
    {0, C1_11, C2_11, C3_11}, // LB3
    {0, C1_12, C2_12, C3_12}, // LB4
    {0, C1_13, C2_13, C3_13}, // LB5
    {0, C1_14, C2_14, C3_14}, // LB6
    {0, C1_15, C2_15, C3_15}, // LB7
    {0, C1_16, C2_16, C3_16}, // LB8
    {0, C9_9,  C8_9,  C7_9},  // LB9
    {0, C9_10, C8_10, C7_10}, // LB10
    {0, C9_11, C8_11, C7_11}, // LB11
    {0, C9_12, C8_12, C7_12}, // LB12
    {0, C9_13, C8_13, C7_13}, // LB13
    {0, C9_14, C8_14, C7_14}, // LB14
    {0, C9_15, C8_15, C6_14}, // LB15
    {0, C9_16, C7_15, C6_15}, // LB16
    {0, C8_16, C7_16, C6_16}, // LB17

    {1, C2_1,  C3_1,  C4_1},  // LC0
    {1, C1_1,  C3_2, C4_2},   // LC1
    {1, C1_2,  C2_2, C4_3},   // LC2
    {1, C1_3,  C2_3, C3_3},   // LC3
    {1, C1_4,  C2_4, C3_4},   // LC4
    {1, C1_5,  C2_5, C3_5},   // LC5
    {1, C1_6,  C2_6, C3_6},   // LC6
    {1, C1_7,  C2_7, C3_7},   // LC7
    {1, C1_8,  C2_8, C3_8},   // LC8
    {1, C9_1,  C8_1,  C7_1},  // LC9
    {1, C9_2,  C8_2, C7_2},   // LC10
    {1, C9_3,  C8_3, C7_3},   // LC11
    {1, C9_4,  C8_4, C7_4},   // LC12
    {1, C9_5,  C8_5, C7_5},   // LC13
    {1, C9_6,  C8_6, C7_6},   // LC14
    {1, C9_7,  C8_7, C6_6},   // LC15
    {1, C9_8,  C7_7, C6_7},   // LC16
    {1, C8_8,  C7_8, C6_8},   // LC17

    {1, C2_9,  C3_9,  C4_9},  // LD0
    {1, C1_9,  C3_10, C4_10}, // LD1
    {1, C1_10, C2_10, C4_11}, // LD2
    {1, C1_11, C2_11, C3_11}, // LD3
    {1, C1_12, C2_12, C3_12}, // LD4
    {1, C1_13, C2_13, C3_13}, // LD5
    {1, C1_14, C2_14, C3_14}, // LD6
    {1, C1_15, C2_15, C3_15}, // LD7
    {1, C1_16, C2_16, C3_16}, // LD8
    {1, C9_9,  C8_9,  C7_9},  // LD9
    {1, C9_10, C8_10, C7_10}, // LD10
    {1, C9_11, C8_11, C7_11}, // LD11
    {1, C9_12, C8_12, C7_12}, // LD12
    {1, C9_13, C8_13, C7_13}, // LD13
    {1, C9_14, C8_14, C7_14}, // LD14
    {1, C9_15, C8_15, C6_14}, // LD15
    {1, C9_16, C7_15, C6_15}, // LD16
    {1, C8_16, C7_16, C6_16}, // LD17
};
#endif


typedef struct Point {
    uint8_t x;
    uint8_t y;
} Point;


// index in range 0..71 (LA0..LA17, LB0..LB17, LC0..LC17, LD0..LD17)
// point values in range x=0..224 y=0..64
// origin is center of top-left key (i.e Esc)
#if defined(RGB_BACKLIGHT_ZEAL65)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA0..LA17
    {120,16}, {104,16}, {88,16}, {72,16}, {56,16}, {40,16}, {24,16}, {4,16}, {4,32},
    {128,0}, {112,0}, {96,0}, {80,0}, {64,0}, {48,0}, {32,0}, {16,0}, {0,0},
    // LB0..LB17
    {144,0}, {160,0}, {176,0}, {192,0}, {216,0}, {224,0}, {240,0}, {240,16}, {240,32},
    {136,16}, {152,16}, {168,16}, {184,16}, {200,16}, {220,16}, {240,48}, {240,64}, {224,64},
    // LC0..LC17
    {96,64}, {100,48}, {84,48}, {68,48}, {52,48}, {36,48}, {255,255}, {48,60}, {28,64},
    {108,32}, {92,32}, {76,32}, {60,32}, {44,32}, {28,32}, {20,44}, {10,48}, {4,64},
    // LD0..LD17
    {124,32}, {140,32}, {156,32}, {172,32}, {188,32}, {214,32}, {180,48}, {202,48}, {224,48},
    {116,48}, {132,48}, {148,48}, {164,48}, {255,255}, {144,60}, {164,64}, {188,64}, {208,64}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA0..LA17
    {64,128}, {75,132}, {84,145}, {91,164}, {97,187}, {102,213}, {105,242}, {109,255}, {128,243},
    {61,255}, {67,255}, {72,255}, {77,255}, {82,255}, {86,255}, {90,255}, {93,255}, {96,255},
    // LB0..LB17
    {56,255}, {51,255}, {46,255}, {42,255}, {37,255}, {35,255}, {32,255}, {19,255}, {0,255},
    {53,132}, {44,145}, {37,164}, {31,187}, {26,213}, {22,249}, {237,255}, {224,255}, {221,255},
    // LC0..LC17
    {184,255}, {179,135}, {170,149}, {163,169}, {157,193}, {153,220}, {255,255}, {167,255}, {165,255},
    {128,26}, {128,60}, {128,94}, {128,128}, {128,162}, {128,196}, {145,233}, {148,255}, {161,255},
    // LD0..LD17
    {0,9}, {0,43}, {0,77}, {0,111}, {0,145}, {0,201}, {224,181}, {230,217}, {235,255},
    {189,128}, {200,131}, {210,141}, {218,159}, {255,255}, {201,228}, {206,255}, {213,255}, {218,255}
};
#elif defined(RGB_BACKLIGHT_KOYU)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA0..LA17
    {120,16}, {104,16}, {88,16}, {72,16}, {56,16}, {40,16}, {24,16}, {4,16}, {4,32},
    {128,0}, {112,0}, {96,0}, {80,0}, {64,0}, {48,0}, {32,0}, {16,0}, {0,0},
    // LB0..LB17
    {144,0}, {160,0}, {176,0}, {192,0}, {208,0}, {224,0}, {240,0}, {240,16}, {240,32},
    {136,16}, {152,16}, {168,16}, {184,16}, {200,16}, {220,16}, {240,48}, {240,64}, {224,64},
    // LC0..LC17
    {112,64}, {100,48}, {84,48}, {68,48}, {52,48}, {36,48}, {64,60}, {44,60}, {24,64},
    {108,32}, {92,32}, {76,32}, {60,32}, {44,32}, {28,32}, {255,255}, {10,48}, {4,64},
    // LD0..LD1762

    {124,32}, {140,32}, {156,32}, {172,32}, {188,32}, {214,32}, {180,48}, {202,48}, {224,48},
    {116,48}, {132,48}, {148,48}, {164,48}, {255,255}, {160,60}, {180,64}, {208,64}, {255,255}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA0..LA17
    {64,128}, {75,132}, {84,145}, {91,164}, {97,187}, {102,213}, {105,242}, {109,255}, {128,243},
    {61,255}, {67,255}, {72,255}, {77,255}, {82,255}, {86,255}, {90,255}, {93,255}, {96,255},
    // LB0..LB17
    {56,255}, {51,255}, {46,255}, {42,255}, {38,255}, {35,255}, {32,255}, {19,255}, {0,255},
    {53,132}, {44,145}, {37,164}, {31,187}, {26,213}, {22,249}, {237,255}, {224,255}, {221,255},
    // LC0..LC17
    {189,255}, {179,135}, {170,149}, {163,169}, {157,193}, {153,220}, {172,252}, {169,255}, {165,255},
    {128,26}, {128,60}, {128,94}, {128,128}, {128,162}, {128,196}, {255,255}, {148,255}, {161,255},
    // LD0..LD17
    {0,9}, {0,43}, {0,77}, {0,111}, {0,145}, {0,201}, {224,181}, {230,217}, {235,255},
    {189,128}, {200,131}, {210,141}, {218,159}, {255,255}, {207,238}, {211,255}, {218,255}, {255,255}
};
#elif defined(RGB_BACKLIGHT_M65_B) || defined(RGB_BACKLIGHT_M65_BX)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA0..LA17
    {120,16}, {104,16}, {88,16}, {72,16}, {56,16}, {40,16}, {24,16}, {4,16}, {4,32},
    {128,0}, {112,0}, {96,0}, {80,0}, {64,0}, {48,0}, {32,0}, {16,0}, {0,0},
    // LB0..LB17
    {144,0}, {160,0}, {176,0}, {192,0}, {208,0}, {224,0}, {216,0}, {240,0}, {240,16},
    {136,16}, {152,16}, {168,16}, {184,16}, {200,16}, {220,16}, {240,32}, {240,48}, {240,64},
    // LC0..LC17
    {112,64}, {100,48}, {84,48}, {68,48}, {52,48}, {36,48}, {64,60}, {44,60}, {24,64},
    {108,32}, {92,32}, {76,32}, {60,32}, {44,32}, {28,32}, {255,255}, {10,48}, {4,64},
    // LD0..LD17
    {124,32}, {140,32}, {156,32}, {172,32}, {188,32}, {214,32}, {180,48}, {202,48}, {224,48},
    {116,48}, {132,48}, {148,48}, {164,48}, {255,255}, {160,60}, {180,64}, {208,64}, {224,64}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA0..LA17
    {64,128}, {75,132}, {84,145}, {91,164}, {97,187}, {102,213}, {105,242}, {109,255}, {128,243},
    {61,255}, {67,255}, {72,255}, {77,255}, {82,255}, {86,255}, {90,255}, {93,255}, {96,255},
    // LB0..LB17
    {56,255}, {51,255}, {46,255}, {42,255}, {38,255}, {35,255}, {37,255}, {32,255}, {19,255},
    {53,132}, {44,145}, {37,164}, {31,187}, {26,213}, {22,249}, {0,255}, {237,255}, {224,255},
    // LC0..LC17
    {189,255}, {179,135}, {170,149}, {163,169}, {157,193}, {153,220}, {172,252}, {169,255}, {165,255},
    {128,26}, {128,60}, {128,94}, {128,128}, {128,162}, {128,196}, {255,255}, {148,255}, {161,255},
    // LD0..LD17
    {0,9}, {0,43}, {0,77}, {0,111}, {0,145}, {0,201}, {224,181}, {230,217}, {235,255},
    {189,128}, {200,131}, {210,141}, {218,159}, {255,255}, {207,238}, {211,255}, {218,255}, {221,255}
};
#elif defined(RGB_BACKLIGHT_ZEAL60) || defined(RGB_BACKLIGHT_M60_A)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA0..LA17
    {120,16}, {104,16}, {88,16}, {72,16}, {56,16}, {40,16}, {24,16}, {4,16}, {4,32},
    {128,0}, {112,0}, {96,0}, {80,0}, {64,0}, {48,0}, {32,0}, {16,0}, {0,0},
    // LB0..LB17
    {144,0}, {160,0}, {176,0}, {192,0}, {216,0}, {224,0}, {255,255}, {255,255}, {255,255},
    {136,16}, {152,16}, {168,16}, {184,16}, {200,16}, {220,16}, {255,255}, {255,255}, {255,255},
    // LC0..LC17
    {102,64}, {100,48}, {84,48}, {68,48}, {52,48}, {36,48}, {60,64}, {43,64}, {23,64},
    {108,32}, {92,32}, {76,32}, {60,32}, {44,32}, {28,32}, {20,48}, {2,48}, {3,64},
    // LD0..LD17
    {124,32}, {140,32}, {156,32}, {172,32}, {188,32}, {214,32}, {180,48}, {210,48}, {224,48},
    {116,48}, {132,48}, {148,48}, {164,48}, {144,64}, {161,64}, {181,64}, {201,64}, {221,64}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA0..LA17
    {58,129}, {70,129}, {80,139}, {89,157}, {96,181}, {101,208}, {105,238}, {109,255}, {128,247},
    {58,255}, {64,255}, {70,255}, {75,255}, {80,255}, {85,255}, {89,255}, {93,255}, {96,255},
    // LB0..LB17
    {53,255}, {48,255}, {43,255}, {39,255}, {34,255}, {32,255}, {255,255}, {255,255}, {255,255},
    {48,139}, {39,157}, {32,181}, {27,208}, {23,238}, {19,255}, {255,255}, {255,255}, {255,255},
    // LC0..LC17
    {188,255}, {183,131}, {173,143}, {165,163}, {159,188}, {154,216}, {172,252}, {170,255}, {165,255},
    {128,9}, {128,46}, {128,82}, {128,119}, {128,155}, {128,192}, {150,244}, {147,255}, {161,255},
    // LD0..LD17
    {0,27}, {0,64}, {0,101}, {0,137}, {0,174}, {255,233}, {228,201}, {235,255}, {237,255},
    {195,128}, {206,136}, {215,152}, {222,175}, {205,234}, {209,255}, {214,255}, {219,255}, {223,255}
};
#elif defined(RGB_BACKLIGHT_WT60_B) || defined(RGB_BACKLIGHT_WT60_BX) || defined(RGB_BACKLIGHT_WT60_C)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA0..LA17
    {120,16}, {104,16}, {88,16}, {72,16}, {56,16}, {40,16}, {24,16}, {4,16}, {4,32},
    {128,0}, {112,0}, {96,0}, {80,0}, {64,0}, {48,0}, {32,0}, {16,0}, {0,0},
    // LB0..LB17
    {144,0}, {160,0}, {176,0}, {192,0}, {208,0}, {224,0}, {216,0}, {255,255}, {255,255},
    {136,16}, {152,16}, {168,16}, {184,16}, {200,16}, {220,16}, {255,255}, {255,255}, {255,255},
    // LC0..LC17
    {112,64}, {100,48}, {84,48}, {68,48}, {52,48}, {36,48}, {64,60}, {44,64}, {24,64},
    {108,32}, {92,32}, {76,32}, {60,32}, {44,32}, {28,32}, {255,255}, {10,48}, {4,64},
    // LD0..LD17
    {124,32}, {140,32}, {156,32}, {172,32}, {188,32}, {214,32}, {180,48}, {202,48}, {224,48},
    {116,48}, {132,48}, {148,48}, {164,48}, {255,255}, {160,60}, {180,64}, {200,64}, {220,64}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA0..LA17
    {58,129}, {70,129}, {80,139}, {89,157}, {96,181}, {101,208}, {105,238}, {109,255}, {128,247},
    {58,255}, {64,255}, {70,255}, {75,255}, {80,255}, {85,255}, {89,255}, {93,255}, {96,255},
    // LB0..LB17
    {53,255}, {48,255}, {43,255}, {39,255}, {35,255}, {32,255}, {34,255}, {255,255}, {255,255},
    {48,139}, {39,157}, {32,181}, {27,208}, {23,238}, {19,255}, {255,255}, {255,255}, {255,255},
    // LC0..LC17
    {192,255}, {183,131}, {173,143}, {165,163}, {159,188}, {154,216}, {173,248}, {170,255}, {165,255},
    {128,9}, {128,46}, {128,82}, {128,119}, {128,155}, {128,192}, {255,255}, {148,255}, {161,255},
    // LD0..LD17
    {0,27}, {0,64}, {0,101}, {0,137}, {0,174}, {0,233}, {228,201}, {235,242}, {237,255},
    {195,128}, {206,136}, {215,152}, {222,175}, {255,255}, {211,248}, {214,255}, {219,255}, {223,255}
};
#elif defined(RGB_BACKLIGHT_U80_A)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // Thse are scaled by 14.5 per U
    // LA0..LA17
    {109,36}, {94,36}, {80,36}, {65,36}, {51,36}, {36,36}, {22,36}, {4,36}, {5,51},
    {116,22}, {102,22}, {87,22}, {73,22}, {58,22}, {44,22}, {29,22}, {15,22}, {0,22},
    // LB0..LB17
    {131,22}, {145,22}, {160,22}, {174,22}, {196,22}, {0,0}, {0,0}, {0,0}, {0,0},
    {123,36}, {138,36}, {152,36}, {167,36}, {181,36}, {199,36}, {0,0}, {0,0}, {0,0},
    // LC0..LC17
    {102,80}, {91,65}, {76,65}, {62,65}, {47,65}, {33,65}, {58,76}, {40,80}, {22,80},
    {98,51}, {83,51}, {69,51}, {54,51}, {40,51}, {25,51}, {0,0}, {9,65}, {4,80},
    // LD0..LD17
    {112,51}, {127,51}, {141,51}, {156,51}, {170,51}, {194,51}, {163,65}, {190,65}, {0,0},
    {105,65}, {120,65}, {134,65}, {149,65}, {0,0}, {145,76}, {163,80}, {181,80}, {199,80},
    // LE0..LE17
    {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0},
    {73,0}, {94,0}, {109,0}, {123,0}, {138,0}, {58,0}, {44,0}, {29,0}, {0,0},
    // LF0..LF17
    {160,0}, {174,0}, {189,0}, {203,0}, {225,0}, {239,0}, {254,0}, {254,22}, {254,36},
    {239,22}, {239,36}, {225,22}, {225,36}, {0,0}, {239,65}, {225,80}, {239,80}, {254,80}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA0..LA17
    {59,129}, {69,129}, {80,138}, {88,154}, {95,175}, {100,200}, {104,227}, {107,255}, {128,226},
    {59,255}, {64,255}, {69,255}, {75,255}, {80,255}, {84,255}, {88,255}, {91,255}, {95,255},
    // LB0..LB17
    {53,255}, {48,255}, {44,255}, {40,255}, {35,255}, {255,255}, {255,255}, {255,255}, {255,255},
    {48,138}, {40,154}, {33,175}, {28,200}, {24,227}, {21,255}, {255,255}, {255,255}, {255,255},
    // LC0..LC17
    {192,255}, {184,131}, {174,141}, {166,159}, {160,181}, {155,207}, {174,244}, {171,255}, {166,255},
    {128,9}, {128,43}, {128,77}, {128,111}, {128,145}, {128,179}, {255,255}, {150,252}, {162,255},
    // LD0..LD17
    {0,26}, {0,60}, {0,94}, {0,128}, {0,162}, {0,218}, {227,193}, {234,245}, {255,255},
    {195,128}, {205,135}, {214,149}, {221,169}, {255,255}, {210,244}, {213,255}, {218,255}, {222,255},
    // LE0..LE17
    {255,255}, {255,255}, {255,255}, {255,255}, {255,255}, {255,255}, {255,255}, {255,255}, {255,255},
    {70,255}, {66,255}, {62,255}, {59,255}, {56,255}, {73,255}, {76,255}, {79,255}, {84,255},
    // LF0..LF17
    {52,255}, {49,255}, {47,255}, {44,255}, {41,255}, {38,255}, {37,255}, {25,255}, {14,255},
    {27,255}, {15,255}, {29,255}, {17,255}, {255,255}, {241,255}, {227,255}, {229,255}, {231,255}
};
#elif defined(RGB_BACKLIGHT_HS60) && defined(HS60_ANSI)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA1..LA47
    {0,0}, {4,16}, {6,32}, {10,48}, {16,0}, {24,16}, {28,32}, {36,48}, {32,0}, {40,16}, {44,32}, {52,48},
    {48,0}, {56,16}, {60,32}, {68,48}, {64,0}, {72,16}, {76,32}, {84,48}, {80,0}, {88,16}, {92,32}, {100,48},
    {96,0}, {104,16}, {108,32}, {116,48}, {112,0}, {120,16}, {124,32}, {132,48}, {128,0}, {136,16}, {140,32},
    {148,48}, {144,0}, {152,16}, {156,32}, {164,48}, {160,0}, {168,16}, {172,32}, {180,48}, {176,0}, {184, 16}, {188,32},
    {255,255},// LA48 does not exist, dummy
    // LA49..LA50
    {192,0}, {200,16},
    {255,255},// LA51 does not exit, dummy
    // LA52..LA60
    {210,48}, {216,0}, {220,16}, {214,32}, {222,64}, {2,64}, {22,64}, {42,64}, {102,64},
    {255,255},// LA61 does not exit, dummy
    {162,64}, {182,64}, {202,64}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA1..LA47
    {96,255}, {109,255}, {128,242}, {148,255}, {93,255}, {105,238}, {128,192}, {154,216}, {89,255}, {101,208}, {128,155}, {159,188},
    {85,255}, {96,181}, {128,119}, {165,163}, {81,255}, {89,157}, {128,82}, {173,143}, {75,255}, {81,139}, {128,46}, {183,131},
    {70,255}, {70,129}, {129,9}, {195,128}, {64,255}, {58,129}, {255,27}, {206,136}, {58,255}, {47,139}, {255,64}, {215,152},
    {53,255}, {39,157}, {255,101}, {222,175}, {47,255}, {32,181}, {255,137}, {228,201}, {43,255}, {27,208}, {255, 174},
    {255,255},// LA48 does not exist, dummy
    // LA49..LA50
    {39,255}, {23,238},
    {255,255},// LA51 does not exit, dummy
    // LA52..LA60
    {235,255}, {33,255}, {19,255}, {255,233}, {224,255}, {160,255}, {164,255}, {169,255}, {188,255},
    {255,255},// LA61 does not exit, dummy
    {209,255}, {215,255}, {220,255}
};
#elif defined(RGB_BACKLIGHT_HS60) && defined(HS60_HHKB)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA1..LA60
    {0,0}, {4,16}, {6,32}, {10,48}, {16,0}, {24,16}, {28,32}, {36,48}, {32,0}, {40,16}, {44,32}, {52,48},
    {48,0}, {56,16}, {60,32}, {68,48}, {64,0}, {72,16}, {76,32}, {84,48}, {80,0}, {88,16}, {92,32}, {100,48},
    {96,0}, {104,16}, {108,32}, {116,48}, {112,0}, {120,16}, {124,32}, {132,48}, {128,0}, {136,16}, {140,32},
    {148,48}, {144,0}, {152,16}, {156,32}, {164,48}, {160,0}, {168,16}, {172,32}, {180,48}, {176,0}, {184, 16}, {188,32},
    {224,0}, {192,0}, {200,16}, {202,48}, {224,48}, {208,0}, {220,16}, {214,32}, {220,64}, {4,64}, {24,64}, {44,64}, {112,64},
    {255,255}, {255,255}, // LA61..LA62 does not exit, dummy
    // LA63..LA64
    {180,64}, {200,64}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA1..LA60
    {96,255}, {109,255}, {128,242}, {148,255}, {93,255}, {105,238}, {128,192}, {154,216}, {89,255}, {101,208}, {128,155}, {159,188},
    {85,255}, {96,181}, {128,119}, {165,163}, {81,255}, {89,157}, {128,82}, {173,143}, {75,255}, {81,139}, {128,46}, {183,131},
    {70,255}, {70,129}, {129,9}, {195,128}, {64,255}, {58,129}, {255,27}, {206,136}, {58,255}, {47,139}, {255,64}, {215,152},
    {53,255}, {39,157}, {255,101}, {222,175}, {47,255}, {32,181}, {255,137}, {228,201}, {43,255}, {27,208}, {255, 174}, {32,255},
    {39,255}, {23,238}, {233,242}, {237,255}, {35,255}, {19,255}, {255,233}, {223,255}, {161,255}, {165,255}, {170,255}, {192,255},
    {255,255}, {255,255}, // LA61..LA62 does not exit, dummy
    // LA63..LA64
    {214,255}, {219,255}
};
#elif defined(RGB_BACKLIGHT_HS60) //HS60_ISO
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA1..LA50
    {0,0}, {4,16}, {6,32}, {2,48}, {16,0}, {24,16}, {28,32}, {36,48}, {32,0}, {40,16}, {44,32}, {52,48}, {48,0},
    {56,16}, {60,32}, {68,48}, {64,0}, {72,16}, {76,32}, {84,48}, {80,0}, {88,16}, {92,32}, {100,48}, {96,0}, {104,16},
    {108,32}, {116,48}, {112,0}, {120,16}, {124,32}, {132,48}, {128,0}, {136,16}, {140,32}, {148,48}, {144,0}, {152,16},
    {156,32}, {164,48}, {160,0}, {168,16}, {172,32}, {180,48}, {176,0}, {184, 16}, {188,32}, {20,48}, {192,0}, {200,16},
    {255,255},// LA51 does not exit, dummy
    // LA52..LA60
    {210,48}, {216,0}, {220,16}, {222,24}, {222,64}, {2,64}, {22,64}, {42,64}, {102,64},
    {255,255},// LA61 does not exit, dummy
    {162,64}, {182,64}, {202,64}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA1..LA50
    {96,255}, {109,255}, {128,242}, {147,255}, {93,255}, {105,238}, {128,192}, {154,216}, {89,255}, {101,208}, {128,155}, {159,188}, {85,255},
    {96,181}, {128,119}, {165,163}, {81,255}, {89,157}, {128,82}, {173,143}, {75,255}, {81,139}, {128,46}, {183,131}, {70,255}, {70,129},
    {129,9}, {195,128}, {64,255}, {58,129}, {255,27}, {206,136}, {58,255}, {47,139}, {255,64}, {215,152}, {53,255}, {39,157}, {255,101},
    {222,175}, {47,255}, {32,181}, {255,137}, {228,201}, {43,255}, {27,208}, {255, 174}, {150,246}, {39,255}, {23,238},
    {255,255},// LA51 does not exit, dummy
    // LA52..LA60
    {235,255}, {33,255}, {19,255}, {10,255}, {224,255}, {160,255}, {164,255}, {169,255}, {188,255},
    {255,255},// LA61 does not exit, dummy
    {209,255}, {215,255}, {220,255}
};
#elif defined(RGB_BACKLIGHT_NK65) || defined(RGB_BACKLIGHT_KW_MEGA)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA1..LA60
    {0,0}, {4,16}, {6,32}, {10,48}, {16,0}, {24,16}, {28,32}, {36,48}, {32,0}, {40,16}, {44,32}, {52,48},
    {48,0}, {56,16}, {60,32}, {68,48}, {64,0}, {72,16}, {76,32}, {84,48}, {80,0}, {88,16}, {92,32}, {100,48},
    {96,0}, {104,16}, {108,32}, {116,48}, {112,0}, {120,16}, {124,32}, {132,48}, {128,0}, {136,16}, {140,32},
    {148,48}, {144,0}, {152,16}, {156,32}, {164,48}, {160,0}, {168,16}, {172,32}, {180,48}, {176,0}, {184, 16}, {188,32},
    {160,64}, {192,0}, {200,16}, {210,48}, {224,48}, {216,0}, {220,16}, {214,32}, {224,64}, {2,64}, {22,64}, {42,64}, {102,64},
    {255,255},// LA61 does not exit, dummy
    //LA62..LB5
    {176,64}, {192,64}, {208,64}, {240,0}, {240,16}, {240,48}, {240,64}, {240,32}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA1..LA60
    {96,255}, {109,255}, {128,242}, {148,255}, {93,255}, {105,238}, {128,192}, {154,216}, {89,255}, {101,208}, {128,155}, {159,188},
    {85,255}, {96,181}, {128,119}, {165,163}, {81,255}, {89,157}, {128,82}, {173,143}, {75,255}, {81,139}, {128,46}, {183,131},
    {70,255}, {70,129}, {129,9}, {195,128}, {64,255}, {58,129}, {255,27}, {206,136}, {58,255}, {47,139}, {255,64}, {215,152},
    {53,255}, {39,157}, {255,101}, {222,175}, {47,255}, {32,181}, {255,137}, {228,201}, {43,255}, {27,208}, {255, 174},
    {208,255}, {39,255}, {23,238}, {235,255}, {235,255}, {33,255}, {19,255}, {255,233}, {224,255}, {160,255}, {164,255}, {169,255}, {188,255},
    {255,255},// LA61 does not exit, dummy
    //LA62..LB5
    {221,255}, {225,255}, {229,255}, {22,255}, {12,255}, {244,255}, {234,255}, {255,255}
};
#elif defined(RGB_BACKLIGHT_NK87)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    {0,19}, {4,33}, {6,48}, {9,63}, {15,19}, {22,33}, {26,48}, {33,63}, {30,19}, {37,33}, {41,48}, {48,63}, {44,19}, {52,33}, {56,48}, {63,63},
    {59,19}, {67,33}, {70,48}, {78,63}, {74,19}, {81,33}, {85,48}, {93,63}, {89,19}, {96,33}, {100,48}, {107,63}, {104,19}, {111,33}, {115,48},
    {122,63}, {118,19}, {126,33}, {130,48}, {137,63}, {133,19}, {141,33}, {144,48}, {152,63}, {148,19}, {155,33}, {159,48}, {167,63}, {163,19},
    {170,33}, {174,48}, {226,78}, {178,19}, {185,33}, {194,63}, {241,63}, {200,19}, {204,33}, {198,48}, {241,78}, {4,78}, {22,78}, {41,78}, {104,78},
    {255,255}, {167,78}, {185,78}, {204,78}, {0,0}, {255,255}, {255,255}, {255,255}, {19,0}, {255,255}, {255,255}, {255,255}, {33,0}, {255,255},
    {255,255}, {255,78}, {48,0}, {255,255}, {255,255}, {255,255}, {63,0}, {255,255}, {255,255}, {255,255}, {81,0}, {255,255}, {255,255}, {255,255},
    {96,0}, {255,255}, {255,255}, {255,255}, {111,0}, {255,255}, {255,255}, {255,255}, {126,0}, {255,255}, {255,255}, {255,255}, {144,0}, {255,255},
    {255,255}, {255,255}, {159,0}, {255,255}, {255,255}, {255,255}, {174,0}, {255,255}, {255,255}, {255,255}, {189,0}, {255,255}, {226,33}, {226,19},
    {207,0}, {255,255}, {241,33}, {241,19}, {226,0}, {255,255}, {255,33}, {255,19}, {241,0}, {255,255}, {255,255}, {255,0}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    {104,255}, {120,242}, {141,246}, {157,255}, {101,255}, {119,208}, {143,210}, {162,255}, {99,251}, {118,180}, {145,183}, {165,248}, {95,230},
    {116,153}, {148,158}, {169,232}, {91,212}, {113,126}, {152,133}, {173,218}, {87,195}, {109,100}, {158,111}, {178,207}, {81,182}, {102,75},
    {167,92}, {184,200}, {75,172}, {89,55}, {179,79}, {190,196}, {68,167}, {67,45}, {194,75}, {196,197}, {61,166}, {43,52}, {208,82}, {201,201},
    {55,170}, {29,70}, {220,97}, {207,210}, {48,179}, {21,93}, {227,116}, {214,255}, {43,191}, {16,119}, {216,234}, {226,255}, {36,216}, {12,153},
    {235,155}, {216,255}, {166,255}, {169,255}, {172,255}, {186,255}, {255,255}, {201,255}, {206,255}, {210,255}, {91,255}, {255,255}, {255,255},
    {255,255}, {88,255}, {255,255}, {255,255}, {255,255}, {85,255}, {255,255}, {255,255}, {219,255}, {82,255}, {255,255}, {255,255}, {255,255},
    {79,255}, {255,255}, {255,255}, {255,255}, {75,255}, {255,255}, {255,255}, {255,255}, {72,255}, {255,255}, {255,255}, {255,255}, {68,255},
    {255,255}, {255,255}, {255,255}, {64,255}, {255,255}, {255,255}, {255,255}, {60,255}, {255,255}, {255,255}, {255,255}, {56,255}, {255,255},
    {255,255}, {255,255}, {53,255}, {255,255}, {255,255}, {255,255}, {50,255}, {255,255}, {10,194}, {29,251}, {46,255}, {255,255}, {8,222}, {27,255},
    {42,255}, {255,255}, {7,249}, {24,255}, {40,255}, {255,255}, {255,255}, {37,255}
};
#elif defined(RGB_BACKLIGHT_NEBULA12)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // A1..A16
    {0,0}, {16,0}, {32,0}, {0,16}, {16,16}, {32,16}, {0,32}, {16,32},
    {255,255}, {255,255}, {255,255}, {255,255},
    {32,48}, {16,48}, {0,48}, {32,32}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    // A1..A16
    {72,197}, {64,194}, {56,197}, {85,74}, {64,64}, {43,74}, {171,74}, {192,64},
    {255,255}, {255,255}, {255,255}, {255,255},
    {200,196}, {192,192}, {184,196}, {213,74}
};
#elif defined(RGB_BACKLIGHT_NEBULA68)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA1..LA60
    {0,0}, {4,16}, {6,31}, {10,47}, {16,0}, {24,16}, {27,31}, {35,47}, {31,0}, {39,16}, {43,31}, {51,47},
    {47,0}, {55,16}, {59,31}, {67,47}, {63,0}, {71,16}, {75,31}, {82,47}, {79,0}, {86,16}, {90,31}, {98,47},
    {94,0}, {102,16}, {106,31}, {114,47}, {110,0}, {118,16}, {122,31}, {130,47}, {126,0}, {133,16}, {137,31},
    {145,47}, {141,0}, {149,16}, {153,31}, {161,47}, {157,0}, {165,16}, {169,31}, {177,47}, {173,0}, {181, 16}, {184,31},
    {159,63}, {188,0}, {196,16}, {206,47}, {220,47}, {212,0}, {216,16}, {210,31}, {220,63}, {2,63}, {22,63}, {41,63}, {100,63},
    {255,255},// LA61 does not exit, dummy
    //LA62..LB5
    {179,63}, {198,63}, {224,63}, {239,0}, {239,16}, {255,16}, {255,63}, {255,0}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA1..LA60
    {96,255}, {109,255}, {128,244}, {148,255}, {93,255}, {106,245}, {128,201}, {153,225}, {80,255}, {103,219}, {128,169}, {156,200},
    {87,255}, {99,194}, {128,138}, {161,177}, {83,255}, {94,171}, {128,106}, {167,157}, {79,255}, {87,152}, {128,75}, {174,141}, {74,255},
    {80,138}, {128,43}, {183,131}, {70,255}, {70,129}, {129,12}, {193,128}, {65,255}, {60,128}, {255,20}, {203,133}, {60,255},
    {51,135}, {255,51}, {212,145}, {55,255}, {42,148}, {255,83}, {219,162}, {50,255}, {36,166}, {255,114},
    {202,255}, {46,255}, {30,188}, {228,203}, {231,225}, {40,255}, {25,219}, {255,165}, {217,255}, {160,255}, {164,255}, {168,255}, {183,255},
    {255,255},// LA61 does not exit, dummy
    //LA62..LB5
    {207,255}, {213,255}, {218,255}, {35,255}, {21,255}, {19,255}, {224,255}, {32,255}
};
#elif defined(RGB_BACKLIGHT_M6_B)
// M6-B is really simple:
// 0 3 5
// 1 2 4
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    {0,0}, {0,16}, {16,16}, {16,0}, {32,16}, {32,0}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    {160,255}, {96,255}, {77,255}, {179,255}, {51,255}, {205,255}
};
#elif defined(RGB_BACKLIGHT_M10_C)
// M10-C is really simple:
// 0     1     2
// 3     4     5
// 8     7     6
//       11 10 9
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    {0,0}, {16,0}, {32,0},
    {0,16}, {16,16}, {32,16},
    {32,32}, {16,32}, {0,32},
    {32,48}, {24,48}, {16,48}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    {160,255}, {192,255}, {224,255},
    {128,255}, {0,0}, {0,255},
    {32,255}, {64,255}, {96,255},
    {45,255}, {54,255}, {64,255}
};
#elif defined(RGB_BACKLIGHT_DAWN60)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA1..LA16
    {104, 16}, {88 , 16}, {72 , 16}, {56 , 16}, {40 , 16}, {24 , 16}, {4  , 16}, {6  , 32},
    {112,  0}, {96 ,  0}, {80 ,  0}, {64 ,  0}, {48 ,  0}, {32 ,  0}, {16 ,  0}, {0  ,  0},

    // LB1..LB16
    {128,  0}, {144,  0}, {160,  0}, {176,  0}, {192,  0}, {208,  0}, {224,  0}, {214, 32},
    {120, 16}, {136, 16}, {152, 16}, {168, 16}, {184, 16}, {200, 16}, {220, 16}, {224, 48},

    // LC1..LC16
    {100, 48}, {84 , 48}, {68 , 48}, {52 , 48}, {36 , 48}, {102, 64}, {42 , 64}, {22 , 64},
    {108, 32}, {92 , 32}, {76 , 32}, {60 , 32}, {44 , 32}, {28 , 32}, {10 , 48}, {2  , 64},

    // LD1..LD16
    {124, 32}, {140, 32}, {156, 32}, {172, 32}, {188, 32}, {180, 48}, {202, 48}, {224, 64},
    {116, 48}, {132, 48}, {148, 48}, {164, 48}, {160, 64},  {176, 64}, {192, 64}, {208, 64},

    //RGB UNDERGLOW
    {27 , 3}, {64 , 3}, {100, 3}, {137, 3}, {173, 3}, {209, 3}, {242, 4}, {255, 8}, {255,32}, {255,64},
    {241,64}, {212,64}, {173,64}, {137,64}, {100,64}, {63 ,64}, {28 ,64}, {0  ,64}, {0  ,32}, {0  , 8}, //20
};

const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    //LA1..LA16
    {70,129}, {80,139}, {89,157}, {96,181}, {101,208}, {105,238}, {109,255}, {128,247},
    {64,255}, {70,255}, {75,255}, {80,255}, {85,255},  {89,255},  {93,255},  {96,255},
    //LB1..LB16
    {58,255}, {53,255}, {48,255}, {43,255}, {39,255},  {34,255}, {32,255}, {255,233},
    {58,129}, {48,139}, {39,157}, {32,181}, {27,208}, {23,238}, {19,255}, {237,255},
    //LC1..LC16
    {183,131}, {173,143}, {165,163}, {159,188}, {154,216}, {188,255}, {170,255}, {165,255},
    {128,9}, {128,46}, {128,82}, {128,119}, {128,155}, {128,192}, {147,255}, {161,255},
    //LD1..LD16
    {0,27}, {0,64}, {0,101}, {0,137}, {0,174}, {228,201}, {235,255}, {224,255},
    {195,128}, {206,136}, {215,152}, {222,175}, {208,255}, {213,255}, {217, 255}, {222,225},

    //UNDERGLOW, {A,D}
    //1 - 10
    {91,255}, {84,255}, {74,255}, {60,255}, {48,255}, {39,255}, {32,255}, {27,255}, {0,255}, {236,255},
    //11 - 20
    {234,255}, {222,255}, {213,255}, {197,255}, {180,255}, {167,255}, {152,255}, {147,255}, {128,255}, {101,255}
};
#elif defined(RGB_BACKLIGHT_PORTICO)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    {   0,   0 }, {  15,   0 }, {  30,   0 }, {  45,   0 }, {  60,   0 }, {  75,   0 }, {  90,   0 }, { 105,   0 }, { 120,   0 }, { 135,   0 }, { 150,   0 }, { 165,   0 }, { 180,   0 }, { 203,   0 }, { 224,   0 },
    {   4,  16 }, {  23,  16 }, {  38,  16 }, {  53,  16 }, {  68,  16 }, {  83,  16 }, {  98,  16 }, { 113,  16 }, { 128,  16 }, { 143,  16 }, { 158,  16 }, { 173,  16 }, { 188,  16 }, { 206,  16 }, { 224,  16 },
    {   6,  32 }, {  26,  32 }, {  41,  32 }, {  56,  32 }, {  71,  32 }, {  86,  32 }, { 101,  32 }, { 116,  32 }, { 131,  32 }, { 146,  32 }, { 161,  32 }, { 176,  32 },               { 201,  32 }, { 224,  32 },
    {   9,  48 },               {  34,  48 }, {  49,  48 }, {  64,  48 }, {  79,  48 }, {  94,  48 }, { 109,  48 }, { 124,  48 }, { 139,  48 }, { 154,  48 }, { 169,  48 }, { 189,  48 }, { 210,  48 }, { 224,  48 },
    {   2,  64 }, {  21,  64 }, {  39,  64 },                                           {  96,  64 },                                           { 152,  64 }, { 171,  64 }, { 195,  64 }, { 210,  64 }, { 224,  64 },
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    { 138, 240 }, { 140, 210 }, { 142, 181 }, { 145, 153 }, { 149, 126 }, { 156, 101 }, { 166,  80 }, { 182,  67 }, { 200,  68 }, { 216,  81 }, { 226, 102 }, { 232, 128 }, { 236, 155 }, { 240, 199 }, { 243, 240 }, //Done through here TM 052421 143PM
    { 133, 225 }, { 134, 186 }, { 136, 156 }, { 138, 126 }, { 141,  96 }, { 147,  68 }, { 161,  44 }, { 193,  33 }, { 222,  47 }, { 235,  72 }, { 240, 100 }, { 244, 130 }, { 246, 160 }, { 247, 196 }, { 248, 233 }, //Done through here TM 052421 235PM
    { 127, 218 }, { 127, 177 }, { 127, 146 }, { 127, 115 }, { 127,  84 }, { 127,  54 }, { 127,  23 }, {   0,   8 }, {   0,  39 }, {   0,  70 }, {   0, 101 }, {   0, 132 },               {   0, 183 }, {   0, 231 },
    { 121, 215 },               { 119, 164 }, { 117, 134 }, { 114, 104 }, { 109,  76 }, {  98,  50 }, {  71,  34 }, {  37,  41 }, {  22,  65 }, {  15,  93 }, {  11, 122 }, {   8, 162 }, {   7, 205 }, {   6, 233 },
    { 116, 236 }, { 113, 199 }, { 110, 164 },                                           {  82,  74 },                                           {  27, 106 }, {  20, 138 }, {  15, 183 }, {  13, 212 }, {  11, 240 }
};
#elif defined(RGB_BACKLIGHT_PORTICO75)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    {   0,   0 }, {  18,   0 }, {  33,   0 }, {  48,   0 }, {  62,   0 }, {  81,   0 }, {  96,   0 }, { 110,   0 }, { 125,   0 }, { 143,   0 }, { 158,   0 }, { 173,   0 }, { 187,   0 }, { 205,   0 }, { 224,   0 },
    {   0,  15 }, {  15,  15 }, {  29,  15 }, {  44,  15 }, {  59,  15 }, {  74,  15 }, {  88,  15 }, { 103,  15 }, { 118,  15 }, { 132,  15 }, { 147,  15 }, { 162,  15 }, { 176,  15 }, { 198,  15 }, { 224,  15 },
    {   4,  26 }, {  22,  26 }, {  37,  26 }, {  51,  26 }, {  66,  26 }, {  81,  26 }, {  96,  26 }, { 110,  26 }, { 125,  26 }, { 140,  26 }, { 154,  26 }, { 169,  26 }, { 183,  26 }, { 202,  26 }, { 224,  26 },
    {   5,  38 }, {  25,  38 }, {  40,  38 }, {  54,  38 }, {  69,  38 }, {  84,  38 }, {  98,  38 }, { 113,  38 }, { 128,  38 }, { 143,  38 }, { 157,  38 }, { 172,  38 }, { 197,  38 },
    {   9,  49 }, {  33,  49 }, {  48,  49 }, {  62,  49 }, {  77,  49 }, {  92,  49 }, { 107,  49 }, { 121,  49 }, { 136,  49 }, { 151,  49 }, { 165,  49 }, { 186,  49 }, { 209,  49 },
    {   2,  61 }, {  20,  61 }, {  39,  61 }, {  94,  61 }, { 151,  61 }, { 173,  61 }, { 195,  64 }, { 209,  64 }, { 224,  64 },
	{   2,   0 }, {  46,   0 }, {  90,   0 }, { 134,   0 }, { 178,   0 }, { 222,   0 }, { 224,   2 }, { 224,  32 }, { 224,  62 }, {   2,  64 }, {  46,  64 }, {  90,  64 }, { 134,  64 }, { 178,  64 }, { 222,  64 }, {   0,   2 }, {   0,  32 }, {   0,  62 }
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    { 138, 240 }, { 140, 205 }, { 143, 176 }, { 146, 147 }, { 150, 122 }, { 159,  92 }, { 172,  74 }, { 188,  66 }, { 206,  71 }, { 222,  92 }, { 229, 115 }, { 234, 142 }, { 238, 168 }, { 241, 203 }, { 243, 240 },
    { 133, 233 }, { 134, 203 }, { 135, 175 }, { 137, 144 }, { 140, 115 }, { 144,  86 }, { 152,  61 }, { 171,  40 }, { 204,  37 }, { 226,  54 }, { 236,  80 }, { 241, 109 }, { 244, 136 }, { 246, 181 }, { 248, 233 },
    { 129, 223 }, { 130, 186 }, { 130, 155 }, { 131, 126 }, { 132,  96 }, { 135,  65 }, { 142,  35 }, { 177,  13 }, { 237,  30 }, { 245,  59 }, { 248,  87 }, { 250, 118 }, { 251, 147 }, { 251, 186 }, { 252, 231 },
    { 125, 221 }, { 124, 180 }, { 124, 149 }, { 123, 120 }, { 121,  89 }, { 118,  59 }, { 111,  31 }, {  57,  13 }, {  15,  35 }, {   8,  65 }, {   5,  94 }, {   4, 124 }, {   3, 176 },
    { 120, 215 }, { 118, 166 }, { 117, 136 }, { 114, 109 }, { 109,  80 }, {  99,  54 }, {  75,  37 }, {  44,  40 }, {  25,  61 }, {  17,  88 }, {  13, 115 }, {   9, 156 }, {   7, 203 },
    { 117, 234 }, { 115, 199 }, { 112, 162 }, {  86,  70 }, {  26, 100 }, {  18, 139 }, {  15, 183 }, {  13, 210 }, {  11, 240 },
    { 138, 236 }, { 145, 151 }, { 166,  80 }, { 215,  80 }, { 236, 151 }, { 243, 236 }, { 243, 239 }, {   0, 231 }, {  11, 239 }, { 116, 236 }, { 109, 151 }, { 88,  80 }, {  39,  80 }, {  18, 151 }, {  11, 236 }, { 138, 239 }, { 127, 231 }, { 116, 239 }
};
#elif defined(RGB_BACKLIGHT_M50_A)
const Point g_map_led_to_point[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA0..LA17
    {255,255}, {104,16}, {88,16}, {72,16}, {56,16}, {40,16}, {24,16}, {255,255}, {255,255},
    {104,0}, {88,0}, {72,0}, {56,0}, {40,0}, {24,0}, {0,0}, {0,16}, {255,255},
    // LB0..LB17
    {255,255}, {120,0}, {136,0}, {152,0}, {168,0}, {184,0}, {200,0}, {255,255}, {255,255},
    {120,16}, {136,16}, {152,16}, {168,16}, {184,16}, {200,16}, {255,255}, {255,255}, {255,255},
    // LC0..LC17
    {255,255}, {112,48}, {88,48}, {72,48}, {56,48}, {40,48}, {24,48}, {0,48}, {255,255},
    {104,32}, {88,32}, {72,32}, {56,32}, {40,32}, {24,32}, {0,32}, {255,255}, {255,255},
    // LD0..LD17
    {255,255}, {120,32}, {136,32}, {152,32}, {168,32}, {184,32}, {200,32}, {255,255}, {255,255},
    {255,255}, {136,48}, {152,48}, {168,48}, {184,48}, {200,48}, {255,255}, {255,255}, {255,255}
};
const Point g_map_led_to_point_polar[BACKLIGHT_LED_COUNT] PROGMEM = {
    // LA0..LA17
    {255,255}, {73,88}, {89,104}, {99,130}, {105,162}, {110,197}, {113,233}, {255,255}, {255,255},
    {67,255}, {73,255}, {79,255}, {84,255}, {89,255}, {93,255}, {98,255}, {116,255}, {255,255},
    // LB0..LB17
    {0,0},  {61,255}, {55,255}, {49,255}, {44,255}, {39,255}, {35,255}, {255,255}, {255,255},
    {55,88}, {39,104}, {29,130}, {23,162}, {18,197}, {15,233}, {255,255}, {255,255}, {255,255},
    // LC0..LC17
    {255,255}, {192,255}, {183,255}, {177,255}, {172,255}, {167,255}, {163,255}, {158,255}, {255,255},
    {183,88}, {167,104}, {157,130}, {151,162}, {146,197}, {143,233}, {140,255}, {255,255}, {255,255},
    // LD0..LD17
    {255,255}, {201,88}, {217,104}, {227,130}, {233,162}, {238,197}, {241,233}, {255,255}, {255,255},
    {255,255}, {201,255}, {207,255}, {212,255}, {217,255}, {221,255}, {255,255}, {255,255}, {255,255}
};
#endif

// This may seem counter-intuitive, but it's quite flexible.
// For each LED, get it's position to decide what color to make it.
// This solves the issue of LEDs (and switches) not aligning to a grid,
// or having a large "bitmap" and sampling them.
void map_led_to_point( uint8_t index, Point *point )
{
    // Slightly messy way to get Point structs out of progmem.
    uint8_t *addr = (uint8_t*)&g_map_led_to_point[index];
    point->x = pgm_read_byte(addr);
    point->y = pgm_read_byte(addr+1);

#if defined(RGB_BACKLIGHT_M6_B) || defined(RGB_BACKLIGHT_M10_C) || defined(RGB_BACKLIGHT_HS60) || defined(RGB_BACKLIGHT_NK65) || defined(RGB_BACKLIGHT_PORTICO) || \
    defined(RGB_BACKLIGHT_PORTICO75) || defined(RGB_BACKLIGHT_NK87) || defined(RGB_BACKLIGHT_NEBULA68) || defined(RGB_BACKLIGHT_NEBULA12) || defined(RGB_BACKLIGHT_KW_MEGA)
    return;
#endif

    switch (index)
    {
#if !defined(RGB_BACKLIGHT_DAWN60)
        case 18+4: // LB4A
            if ( g_config.use_split_backspace )
                point->x -= 8;
            break;
#endif
#if defined(RGB_BACKLIGHT_ZEAL60)
        case 18+14: // LB14A
            if ( g_config.use_iso_enter )
                point->y += 8; // extremely pedantic
            break;
        case 54+5: // LD5A
            if ( !g_config.use_iso_enter )
                point->x -= 10;
            break;
        case 36+16: // LC16A
            if ( !g_config.use_split_left_shift )
                point->x += 8;
            break;
#endif
#if defined(RGB_BACKLIGHT_ZEAL60) || defined(RGB_BACKLIGHT_M60_A)
        case 36+0: // LC0A
            if ( g_config.use_7u_spacebar )
                point->x += 10;
            break;
        case 36+6: // LC6A
            if ( g_config.use_7u_spacebar )
                point->x += 4;
            break;
        case 54+7: // LD7A
            if ( !g_config.use_split_right_shift )
                point->x -= 8;
            break;
#endif
#if defined(RGB_BACKLIGHT_DAWN60)
        case 15+6: // LB6A
            if ( !g_config.use_split_backspace )
                point->x += 8;
            break;
        case 31+6: // LC6A
            if ( g_config.use_7u_spacebar )
                point->x = 112;
            break;
        case 47+16: // LD16A
            if ( g_config.use_7u_spacebar )
                point->x -= 8;
            break;
        case 47+6: // LD6A
            if ( g_config.use_split_right_shift )
                point->x += 6;
            break;
        case 47+7: // LD7A
            if ( g_config.use_split_right_shift )
                point->x += 6;
            break;
#endif
    }
}

void map_led_to_point_polar( uint8_t index, Point *point )
{
    // Slightly messy way to get Point structs out of progmem.
    uint8_t *addr = (uint8_t*)&g_map_led_to_point_polar[index];
    point->x = pgm_read_byte(addr);
    point->y = pgm_read_byte(addr+1);
}

//
// Maps switch matrix coordinate (row,col) to LED index
//


#if defined(RGB_BACKLIGHT_ZEAL65)
// Note: Left spacebar stab is at 4,2 (LC7)
// Right spacebar stab is at 4,9 (D14)
//
// A17, A16, A15, A14, A13, A12, A11, A10,  A9,  B0,  B1,  B2,  B3,  B4,  B6
//  A7,  A6,  A5,  A4,  A3,  A2,  A1,  A0,  B9, B10, B11, B12, B13, B14,  B7
//  A8, C14, C13, C12, C11, C10,  C9,  D0,  D1,  D2,  D3,  D4,  D5,  B5,  B8
// C16, C15,  C5,  C4,  C3,  C2,  C1,  D9, D10, D11, D12,  D6,  D7,  D8, B15
// C17,  C8,  C7, ---, ---, ---, ---,  C0, ---, D14, D15, D16, D17, B17, B16
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {  0+17,  0+16,  0+15,  0+14,  0+13,  0+12,  0+11,  0+10,   0+9,  18+0,  18+1,  18+2,  18+3,  18+4,  18+6 },
    {   0+7,   0+6,   0+5,   0+4,   0+3,   0+2,   0+1,   0+0,  18+9, 18+10, 18+11, 18+12, 18+13, 18+14,  18+7 },
    {   0+8, 36+14, 36+13, 36+12, 36+11, 36+10,  36+9,  54+0,  54+1,  54+2,  54+3,  54+4,  54+5,  18+5,  18+8 },
    { 36+16, 36+15,  36+5,  36+4,  36+3,  36+2,  36+1,  54+9, 54+10, 54+11, 54+12,  54+6,  54+7,  54+8, 18+15 },
    { 36+17,  36+8,  36+7,   255,   255,   255,   255,  36+0,  255,  54+14, 54+15, 54+16, 54+17, 18+17, 18+16 }
};
#elif defined(RGB_BACKLIGHT_KOYU)
// Note: Left spacebar stab is at 4,4 (LC6)
// Right spacebar stab is at 4,10 (D14)
//
// A17, A16, A15, A14, A13, A12, A11, A10,  A9,  B0,  B1,  B2,  B3,  B4,  B6
//  A7,  A6,  A5,  A4,  A3,  A2,  A1,  A0,  B9, B10, B11, B12, B13, B14,  B7
//  A8, C14, C13, C12, C11, C10,  C9,  D0,  D1,  D2,  D3,  D4,  D5,  B5,  B8
// C16, C15,  C5,  C4,  C3,  C2,  C1,  D9, D10, D11, D12,  D6,  D7,  D8, B15
// C17,  C8,  C7,  C6, ---, ---, ---,  C0, ---, ---, D14, D15, D16, B17, B16
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {  0+17,  0+16,  0+15,  0+14,  0+13,  0+12,  0+11,  0+10,   0+9,  18+0,  18+1,  18+2,  18+3,  18+4,  18+6 },
    {   0+7,   0+6,   0+5,   0+4,   0+3,   0+2,   0+1,   0+0,  18+9, 18+10, 18+11, 18+12, 18+13, 18+14,  18+7 },
    {   0+8, 36+14, 36+13, 36+12, 36+11, 36+10,  36+9,  54+0,  54+1,  54+2,  54+3,  54+4,  54+5,  18+5,  18+8 },
    { 36+16, 36+15,  36+5,  36+4,  36+3,  36+2,  36+1,  54+9, 54+10, 54+11, 54+12,  54+6,  54+7,  54+8, 18+15 },
    { 36+17,  36+8,  36+7,  36+6,   255,   255,   255,  36+0,  255,    255, 54+14, 54+15, 54+16, 18+17, 18+16 }
};
#elif defined(RGB_BACKLIGHT_M65_B) || defined(RGB_BACKLIGHT_M65_BX)
// Note: Left spacebar stab is at 4,4 (LC6)
// Right spacebar stab is at 4,10 (D14)
//                                                                  (B6)
// A17, A16, A15, A14, A13, A12, A11, A10,  A9,  B0,  B1,  B2,  B3,  B4,  B7
//  A7,  A6,  A5,  A4,  A3,  A2,  A1,  A0,  B9, B10, B11, B12, B13, B14,  B8
//  A8, C14, C13, C12, C11, C10,  C9,  D0,  D1,  D2,  D3,  D4,  D5,  B5, B15
// C16, C15,  C5,  C4,  C3,  C2,  C1,  D9, D10, D11, D12,  D6,  D7,  D8, B16
// C17,  C8,  C7,  C6, ---, ---, ---,  C0, ---, ---, D14, D15, D16, D17, B17
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {  0+17,  0+16,  0+15,  0+14,  0+13,  0+12,  0+11,  0+10,   0+9,  18+0,  18+1,  18+2,  18+3,  18+4,  18+7 },
    {   0+7,   0+6,   0+5,   0+4,   0+3,   0+2,   0+1,   0+0,  18+9, 18+10, 18+11, 18+12, 18+13, 18+14,  18+8 },
    {   0+8, 36+14, 36+13, 36+12, 36+11, 36+10,  36+9,  54+0,  54+1,  54+2,  54+3,  54+4,  54+5,  18+5, 18+15 },
    { 36+16, 36+15,  36+5,  36+4,  36+3,  36+2,  36+1,  54+9, 54+10, 54+11, 54+12,  54+6,  54+7,  54+8, 18+16 },
    { 36+17,  36+8,  36+7,  36+6,   255,   255,   255,  36+0,  255,    255, 54+14, 54+15, 54+16, 54+17, 18+17 }
};
#elif defined(RGB_BACKLIGHT_ZEAL60) || defined(RGB_BACKLIGHT_M60_A)
// Note: Left spacebar stab is at 4,3 (LC6)
// Right spacebar stab is at 4,9 (LD13) or 4,10 (LD14)
//
// A17, A16, A15, A14, A13, A12, A11, A10,  A9,  B0,  B1,  B2,  B3,  B4,
//  A7,  A6,  A5,  A4,  A3,  A2,  A1,  A0,  B9, B10, B11, B12, B13, B14,
//  A8, C14, C13, C12, C11, C10,  C9,  D0,  D1,  D2,  D3,  D4,  D5,  B5,
// C16, C15,  C5,  C4,  C3,  C2,  C1,  D9, D10, D11, D12,  D6,  D7,  D8,
// C17,  C8,  C7,  C6, ---, ---, ---,  C0, ---, D13, D14, D15, D16, D17,
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {  0+17,  0+16,  0+15,  0+14,  0+13,  0+12,  0+11,  0+10,   0+9,  18+0,  18+1,  18+2,  18+3,  18+4 },
    {   0+7,   0+6,   0+5,   0+4,   0+3,   0+2,   0+1,   0+0,  18+9, 18+10, 18+11, 18+12, 18+13, 18+14 },
    {   0+8, 36+14, 36+13, 36+12, 36+11, 36+10,  36+9,  54+0,  54+1,  54+2,  54+3,  54+4,  54+5,  18+5 },
    { 36+16, 36+15,  36+5,  36+4,  36+3,  36+2,  36+1,  54+9, 54+10, 54+11, 54+12,  54+6,  54+7,  54+8 },
    { 36+17,  36+8,  36+7,  36+6,   255,   255,   255,  36+0,  255,  54+13, 54+14, 54+15, 54+16, 54+17 }
};
#elif defined(RGB_BACKLIGHT_WT60_B) || defined(RGB_BACKLIGHT_WT60_BX) || defined(RGB_BACKLIGHT_WT60_C)
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {  0+17,  0+16,  0+15,  0+14,  0+13,  0+12,  0+11,  0+10,   0+9,  18+0,  18+1,  18+2,  18+3,  18+4 },
    {   0+7,   0+6,   0+5,   0+4,   0+3,   0+2,   0+1,   0+0,  18+9, 18+10, 18+11, 18+12, 18+13, 18+14 },
    {   0+8, 36+14, 36+13, 36+12, 36+11, 36+10,  36+9,  54+0,  54+1,  54+2,  54+3,  54+4,  54+5,  18+5 },
    { 36+16,   255,  36+5,  36+4,  36+3,  36+2,  36+1,  54+9, 54+10, 54+11, 54+12,  54+6,  54+7,  54+8 },
    { 36+17,  36+8,  36+7,  36+6,   255,   255,   255,  36+0,  255,    255, 54+14, 54+15, 54+16, 54+17 }
};
#elif defined(RGB_BACKLIGHT_U80_A)
// Note: Left spacebar stab is at 5,3 (LC6)
// Right spacebar stab is at 5,10 (LD14)
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    { 72+17, 72+16, 72+15, 72+14,  72+9, 72+10, 72+11, 72+12, 72+13,  90+0,  90+1,  90+2,  90+3,   255,  90+4,  90+5,  90+6 },
    {  0+17,  0+16,  0+15,  0+14,  0+13,  0+12,  0+11,  0+10,   0+9,  18+0,  18+1,  18+2,  18+3,  18+4, 90+11,  90+9,  90+7 },
    {   0+7,   0+6,   0+5,   0+4,   0+3,   0+2,   0+1,   0+0,  18+9, 18+10, 18+11, 18+12, 18+13, 18+14, 90+12, 90+10,  90+8 },
    {   0+8, 36+14, 36+13, 36+12, 36+11, 36+10,  36+9,  54+0,  54+1,  54+2,  54+3,  54+4,  54+5,   255,   255,   255,   255 },
    { 36+16,   255,  36+5,  36+4,  36+3,  36+2,  36+1,  54+9, 54+10, 54+11, 54+12,  54+6,  54+7,   255,   255, 90+14,   255 },
    { 36+17,  36+8,  36+7,  36+6,   255,   255,   255,  36+0,  255,    255, 54+14, 54+15, 54+16, 54+17, 90+15, 90+16, 90+17 }
};
#elif defined(RGB_BACKLIGHT_HS60) && defined(HS60_ANSI)
//
// LA1,  LA5,  LA9,  LA13, LA17, LA21, LA25, LA29, LA33, LA37, LA41, LA45, LA49, LA53,
// LA2,  LA6,  LA10, LA14, LA18, LA22, LA26, LA30, LA34, LA38, LA42, LA46, LA50,  ---,
// LA3,  LA7,  LA11, LA15, LA19, LA23, LA27, LA31, LA35, LA39, LA43, LA47, LA54, LA55,
// LA4,  ---,   LA8, LA12, LA16, LA20, LA24, LA28, LA32, LA36, LA40, LA44,  ---, LA52,
// LA57, LA58, LA59,  ---,  ---,  ---, LA60,  ---,  ---,  ---, LA62, LA63, LA64, LA56
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {  1-1,  5-1,  9-1, 13-1, 17-1, 21-1, 25-1, 29-1, 33-1, 37-1, 41-1, 45-1, 49-1, 53-1 },
    {  2-1,  6-1, 10-1, 14-1, 18-1, 22-1, 26-1, 30-1, 34-1, 38-1, 42-1, 46-1, 50-1,  255 },
    {  3-1,  7-1, 11-1, 15-1, 19-1, 23-1, 27-1, 31-1, 35-1, 39-1, 43-1, 47-1, 54-1, 55-1 },
    {  4-1,  255,  8-1, 12-1, 16-1, 20-1, 24-1, 28-1, 32-1, 36-1, 40-1, 44-1,  255, 52-1 },
    { 57-1, 58-1, 59-1,  255,  255,  255, 60-1,  255,  255,  255, 62-1, 63-1, 64-1, 56-1 }
};
#elif defined(RGB_BACKLIGHT_HS60) && defined(HS60_HHKB)
//
// LA1,  LA5,   LA9, LA13, LA17, LA21, LA25, LA29, LA33, LA37, LA41, LA45, LA49, LA53,
// LA2,  LA6,  LA10, LA14, LA18, LA22, LA26, LA30, LA34, LA38, LA42, LA46, LA50, LA48,
// LA3,  LA7,  LA11, LA15, LA19, LA23, LA27, LA31, LA35, LA39, LA43, LA47, LA54, LA55,
// LA4,  ---,   LA8, LA12, LA16, LA20, LA24, LA28, LA32, LA36, LA40, LA44, LA51, LA52,
// LA57, LA58, LA59,  ---,  ---,  ---, LA60,  ---,  ---,  ---,  ---, LA63, LA64, LA56
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {  1-1,  5-1,  9-1, 13-1, 17-1, 21-1, 25-1, 29-1, 33-1, 37-1, 41-1, 45-1, 49-1, 53-1 },
    {  2-1,  6-1, 10-1, 14-1, 18-1, 22-1, 26-1, 30-1, 34-1, 38-1, 42-1, 46-1, 50-1, 48-1 },
    {  3-1,  7-1, 11-1, 15-1, 19-1, 23-1, 27-1, 31-1, 35-1, 39-1, 43-1, 47-1, 54-1, 55-1 },
    {  4-1,  255,  8-1, 12-1, 16-1, 20-1, 24-1, 28-1, 32-1, 36-1, 40-1, 44-1, 51-1, 52-1 },
    { 57-1, 58-1, 59-1,  255,  255,  255, 60-1,  255,  255,  255,  255, 63-1, 64-1, 56-1 }
};
#elif defined(RGB_BACKLIGHT_HS60) //HS60_ISO
//
// LA1,  LA5,   LA9, LA13, LA17, LA21, LA25, LA29, LA33, LA37, LA41, LA45, LA49, LA53,
// LA2,  LA6,  LA10, LA14, LA18, LA22, LA26, LA30, LA34, LA38, LA42, LA46, LA50,  ---,
// LA3,  LA7,  LA11, LA15, LA19, LA23, LA27, LA31, LA35, LA39, LA43, LA47, LA54, LA55,
// LA4,  LA48,  LA8, LA12, LA16, LA20, LA24, LA28, LA32, LA36, LA40, LA44,  ---, LA52,
// LA57, LA58, LA59,  ---,  ---,  ---, LA60,  ---,  ---,  ---, LA62, LA63, LA64, LA56
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {  1-1,  5-1,  9-1, 13-1, 17-1, 21-1, 25-1, 29-1, 33-1, 37-1, 41-1, 45-1, 49-1, 53-1 },
    {  2-1,  6-1, 10-1, 14-1, 18-1, 22-1, 26-1, 30-1, 34-1, 38-1, 42-1, 46-1, 50-1,  255 },
    {  3-1,  7-1, 11-1, 15-1, 19-1, 23-1, 27-1, 31-1, 35-1, 39-1, 43-1, 47-1, 54-1, 55-1 },
    {  4-1, 48-1,  8-1, 12-1, 16-1, 20-1, 24-1, 28-1, 32-1, 36-1, 40-1, 44-1,  255, 52-1 },
    { 57-1, 58-1, 59-1,  255,  255,  255, 60-1,  255,  255,  255, 62-1, 63-1, 64-1, 56-1 }
};
#elif defined(RGB_BACKLIGHT_NK65) || defined(RGB_BACKLIGHT_NEBULA68) || defined(RGB_BACKLIGHT_KW_MEGA)
//
// LA1,  LA5,  LA9,  LA13, LA17, LA21, LA25, LA29, LA33, LA37, LA41, LA45, LA49, LA53, LB1,
// LA2,  LA6,  LA10, LA14, LA18, LA22, LA26, LA30, LA34, LA38, LA42, LA46, LA50,  ---, LB2,
// LA3,  LA7,  LA11, LA15, LA19, LA23, LA27, LA31, LA35, LA39, LA43, LA47, LA54, LA55, LB5,
// LA4,  ---,   LA8, LA12, LA16, LA20, LA24, LA28, LA32, LA36, LA40, LA44, LA51, LA52, LB3,
// LA57, LA58, LA59,  ---,  ---,  ---, LA60,  ---,  ---, LA48, LA62, LA63, LA64, LA56, LB4
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {  1-1,  5-1,  9-1, 13-1, 17-1, 21-1, 25-1, 29-1, 33-1, 37-1, 41-1, 45-1, 49-1, 53-1, 1+64-1 },
    {  2-1,  6-1, 10-1, 14-1, 18-1, 22-1, 26-1, 30-1, 34-1, 38-1, 42-1, 46-1, 50-1,  255, 2+64-1 },
    {  3-1,  7-1, 11-1, 15-1, 19-1, 23-1, 27-1, 31-1, 35-1, 39-1, 43-1, 47-1, 54-1, 55-1, 5+64-1 },
    {  4-1,  255,  8-1, 12-1, 16-1, 20-1, 24-1, 28-1, 32-1, 36-1, 40-1, 44-1, 51-1, 52-1, 3+64-1 },
    { 57-1, 58-1, 59-1,  255,  255,  255, 60-1,  255,  255, 48-1, 62-1, 63-1, 64-1, 56-1, 4+64-1 }
};
#elif defined(RGB_BACKLIGHT_NK87)
//
// LB1,  LB5,  LB9,  LB13, LB17, LB21, LB25, LB29, LB33, LB37, LB41, LB45, LB49, LB53, LB57, LB61, LB64,
// LA1,  LA5,  LA9,  LA13, LA17, LA21, LA25, LA29, LA33, LA37, LA41, LA45, LA49, LA53, LB52, LB56, LB60,
// LA2,  LA6,  LA10, LA14, LA18, LA22, LA26, LA30, LA34, LA38, LA42, LA46, LA50,  ---, LB51, LB55, LB59,
// LA3,  LA7,  LA11, LA15, LA19, LA23, LA27, LA31, LA35, LA39, LA43, LA47, LA54, LA55,  ---,  ---,  ---,
// LA4,  ---,   LA8, LA12, LA16, LA20, LA24, LA28, LA32, LA36, LA40, LA44, LA51,  ---,  ---, LA52,  ---,
// LA57, LA58, LA59,  ---,  ---,  ---, LA60,  ---,  ---,  ---,  ---, LA62, LA63, LA64, LA48, LA56, LB12
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    { 1+64-1, 5+64-1,  9+64-1, 13+64-1, 17+64-1, 21+64-1, 25+64-1, 29+64-1, 33+64-1, 37+64-1, 41+64-1, 45+64-1, 49+64-1, 53+64-1, 57+64-1, 61+64-1, 64+64-1 },
    {    1-1,    5-1,     9-1,    13-1,    17-1,    21-1,    25-1,    29-1,    33-1,    37-1,    41-1,    45-1,    49-1,    53-1, 52+64-1, 56+64-1, 60+64-1 },
    {    2-1,    6-1,    10-1,    14-1,    18-1,    22-1,    26-1,    30-1,    34-1,    38-1,    42-1,    46-1,    50-1,     255, 51+64-1, 55+64-1, 59+64-1 },
    {    3-1,    7-1,    11-1,    15-1,    19-1,    23-1,    27-1,    31-1,    35-1,    39-1,    43-1,    47-1,    54-1,    55-1,     255,     255,     255 },
    {    4-1,    255,     8-1,    12-1,    16-1,    20-1,    24-1,    28-1,    32-1,    36-1,    40-1,    44-1,    51-1,     255,     255,    52-1,     255 },
    {   57-1,   58-1,    59-1,     255,     255,     255,    60-1,     255,     255,     255,     255,    62-1,    63-1,    64-1,    48-1,    56-1, 12+64-1 }
};
#elif defined(RGB_BACKLIGHT_NEBULA12)
//
//  A1,   A2,   A3,
//  A4,   A5,   A6,
//  A7,   A8,  A16,
// A15,  A14,  A13,
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {  1-1,  2-1,  3-1 },
    {  4-1,  5-1,  6-1 },
    {  7-1,  8-1, 16-1 },
    { 15-1, 14-1, 13-1 }
};
#elif defined(RGB_BACKLIGHT_M6_B)
// M6-B is really simple:
// 0 3 5
// 1 2 4
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {     0,     3,     5,     1,     2,     4 }
};
#elif defined(RGB_BACKLIGHT_M10_C)
// M10-C is really simple:
// 0     1     2
// 3     4     5
// 8     7     6
//      11 10 9
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    { 0, 1, 2, 3, 4, 5, 8, 7, 6, 10 }
};
#elif defined(RGB_BACKLIGHT_DAWN60)
//Dawn60
// A16, A15, A14, A13, A12, A11, A10,  A9,  B1,  B2,  B3,  B4,  B5,  B6,
//  A7,  A6,  A5,  A4,  A3,  A2,  A1,  B9, B10, B11, B12, B13, B14, B15,
//  A8, C14, C13, C12, C11, C10,  C9,  D1,  D2,  D3,  D4,  D5,  B8,  B7,
// C15,  C5,  C4,  C3,  C2,  C1,  D9, D10, D11, D12, ---,  D6,  D7, B16,
// C16,  C8,  C7, ---, ---,  C6, ---, ---, ---, D13, D14, D15, D16,  D8,
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    { -1+16, -1+15, -1+14, -1+13, -1+12, -1+11, -1+10, -1+9 , 15+1 , 15+2 , 15+3 , 15+4 , 15+5 , 15+6 },
    { -1+7 , -1+6 , -1+5 , -1+4 , -1+3 , -1+2 , -1 +1, 15+9 , 15+10, 15+11, 15+12, 15+13, 15+14, 15+15},
    { -1+8 , 31+14, 31+13, 31+12, 31+11, 31+10, 31+9 , 47+1 , 47+2 , 47+3 , 47+4 , 47+5 , 15+8 , 15+7 },
    { 31+15, 31+5 , 31+4 , 31+3 , 31+2 , 31+1 , 47+9 , 47+10, 47+11, 47+12, 255  ,47+6 , 47+7 , 15+16},
    { 31+16, 31+8 , 31+7 , 255  , 255  , 31+6 , 255  , 255  , 255  , 47+13, 47+14, 47+15, 47+16, 47+8 }
};
#elif defined(RGB_BACKLIGHT_PORTICO)
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {  0,      1,  2,      3,      4,      5,  6,      7,      8,      9, 10, 11, 12,     13, 14 },
    { 15,     16, 17,     18,     19,     20, 21,     22,     23,     24, 25, 26, 27,     28, 29 },
    { 30,     31, 32,     33,     34,     35, 36,     37,     38,     39, 40, 41, 42,    255, 43 },
    { 44,    255, 45,     46,     47,     48, 49,     50,     51,     52, 53, 54, 55,     56, 57 },
    { 58,     59, 60,    255,    255,    255, 61,    255,    255,    255, 62, 63, 64,     65, 66 }
};
#elif defined(RGB_BACKLIGHT_PORTICO75)
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14 },
    {  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29 },
    {  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44 },
    {  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57, 255, 255 },
    {  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70, 255, 255 },
    {  71,  72,  73, 255, 255,  74, 255, 255, 255,  75,  76,  77,  78,  79, 255 }
};
#elif defined(RGB_BACKLIGHT_M50_A)
// LA15, LA14, LA13, LA12, LA11, LA10,  LA9,  LB1,  LB2,  LB3,  LB4,  LB5,  LB6
// LA16,  LA6,  LA5,  LA4,  LA3,  LA2,  LA1,  LB9, LB10, LB11, LB12, LB13, LB14
// LC15, LC14, LC13, LC12, LC11, LC10,  LC9,  LD1,  LD2,  LD3,  LD4,  LD5,  LD6
//  LC7,  LC6,  LC5,  LC4,  LC3,  LC2,  LC1, ----, LD10, LD11, LD12, LD13, LD14
const uint8_t g_map_row_column_to_led[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {  0+15,  0+14,  0+13,  0+12,  0+11,  0+10,   0+9,  18+1,  18+2,  18+3,  18+4,  18+5,  18+6 },
    {  0+16,   0+6,   0+5,   0+4,   0+3,   0+2,   0+1,  18+9, 18+10, 18+11, 18+12, 18+13, 18+14 },
    { 36+15, 36+14, 36+13, 36+12, 36+11, 36+10,  36+9,  54+1,  54+2,  54+3,  54+4,  54+5,  54+6 },
    {  36+7,  36+6,  36+5,  36+4,  36+3,  36+2,  36+1,   255, 54+10, 54+11, 54+12, 54+13, 54+14 },
};
#endif

void map_row_column_to_led( uint8_t row, uint8_t column, uint8_t *led )
{
    *led = 255;
    if ( row < MATRIX_ROWS && column < MATRIX_COLS )
    {
        *led = pgm_read_byte(&g_map_row_column_to_led[row][column]);
    }
}

void backlight_update_pwm_buffers(void)
{
#if defined(RGB_BACKLIGHT_M6_B)
    is31fl3218_update_pwm_buffers();
#elif defined(RGB_BACKLIGHT_PORTICO75)
	is31fl3741_update_pwm_buffers( ISSI_ADDR_1, 0 );
    is31fl3741_update_led_control_registers( ISSI_ADDR_1, 0 );
#elif defined(RGB_BACKLIGHT_M10_C)
    is31fl3731_update_pwm_buffers( ISSI_ADDR_1, 0 );
    is31fl3731_update_led_control_registers( ISSI_ADDR_1, 0 );
#elif defined(RGB_BACKLIGHT_HS60)
    is31fl3733_update_pwm_buffers( ISSI_ADDR_1, 0 );
    is31fl3733_update_led_control_registers( ISSI_ADDR_1, 0 );
#elif defined(RGB_BACKLIGHT_NK65) || defined(RGB_BACKLIGHT_NEBULA68) || defined(RGB_BACKLIGHT_NK87) || defined(RGB_BACKLIGHT_KW_MEGA)
    is31fl3733_update_pwm_buffers( ISSI_ADDR_1, 0 );
    is31fl3733_update_pwm_buffers( ISSI_ADDR_2, 1 );
    is31fl3733_update_led_control_registers( ISSI_ADDR_1, 0 );
    is31fl3733_update_led_control_registers( ISSI_ADDR_2, 1 );
#elif defined(RGB_BACKLIGHT_NEBULA12)
    is31fl3731_update_pwm_buffers( ISSI_ADDR_1, 0 );
    is31fl3731_update_led_control_registers( ISSI_ADDR_1, 0 );
#elif defined(RGB_BACKLIGHT_U80_A)
    static uint8_t driver = 0;
    switch ( driver )
    {
        case 0:
            is31fl3731_update_pwm_buffers( ISSI_ADDR_1, 0 );
            break;
        case 1:
            is31fl3731_update_pwm_buffers( ISSI_ADDR_2, 1 );
            break;
        case 2:
            is31fl3731_update_pwm_buffers( ISSI_ADDR_3, 2 );
            break;
    }
    if ( ++driver > 2 )
    {
        driver = 0;
    }
#else
    is31fl3731_update_pwm_buffers( ISSI_ADDR_1, 0 );
    is31fl3731_update_pwm_buffers( ISSI_ADDR_2, 1 );
    is31fl3731_update_led_control_registers( ISSI_ADDR_1, 0 );
    is31fl3731_update_led_control_registers( ISSI_ADDR_2, 1 );
#endif
}

void backlight_set_color( int index, uint8_t red, uint8_t green, uint8_t blue )
{
#if defined(RGB_BACKLIGHT_M6_B)
    is31fl3218_set_color( index, red, green, blue );
#elif defined(RGB_BACKLIGHT_HS60) || defined(RGB_BACKLIGHT_NK65) || defined(RGB_BACKLIGHT_NEBULA68) || defined(RGB_BACKLIGHT_KW_MEGA)
    is31fl3733_set_color( index, red, green, blue );
#elif defined (RGB_BACKLIGHT_PORTICO)
    is31fl3731_set_color( index, red, green, blue );
#elif defined (RGB_BACKLIGHT_PORTICO75)
    is31fl3741_set_color( index, red, green, blue );
#elif defined(RGB_BACKLIGHT_NK87)
    // This is done to avoid indicator LEDs being set
    if (( index != 63+64-1 ) && ( index != 48+64-1 )) {
        is31fl3733_set_color( index, red, green, blue );
    }
#elif defined(RGB_BACKLIGHT_DAWN60)
    if( index < RGB_MATRIX_LED_COUNT ) {
        is31fl3731_set_color( index, red, green, blue );
    } else {
        g_ws2812_leds[index - RGB_MATRIX_LED_COUNT].r = red;
        g_ws2812_leds[index - RGB_MATRIX_LED_COUNT].g = green;
        g_ws2812_leds[index - RGB_MATRIX_LED_COUNT].b = blue;
        ws2812_setleds(g_ws2812_leds, WS2812_LED_TOTAL);
    }
#else
    is31fl3731_set_color( index, red, green, blue );
#endif
}

void backlight_set_color_all( uint8_t red, uint8_t green, uint8_t blue )
{
#if defined(RGB_BACKLIGHT_M6_B)
    is31fl3218_set_color_all( red, green, blue );
#elif defined(RGB_BACKLIGHT_HS60) || defined(RGB_BACKLIGHT_NK65) || defined(RGB_BACKLIGHT_NEBULA68) || defined(RGB_BACKLIGHT_KW_MEGA)
    // This is done to avoid indicator LEDs being set
    for (int i = 0; i < BACKLIGHT_LED_COUNT; i++) {
        is31fl3733_set_color(i, red, green, blue);
    }
#elif defined (RGB_BACKLIGHT_PORTICO)
    // This is done to avoid indicator LEDs being set
    for (int i = 0; i < BACKLIGHT_LED_COUNT; i++) {
        is31fl3731_set_color(i, red, green, blue);
    }
#elif defined (RGB_BACKLIGHT_PORTICO75)
    // This is done to avoid indicator LEDs being set
    for (int i = 0; i < BACKLIGHT_LED_COUNT; i++) {
        is31fl3741_set_color(i, red, green, blue);
    }
#elif defined(RGB_BACKLIGHT_NK87)
    // This is done to avoid indicator LEDs being set
    for (int i = 0; i < BACKLIGHT_LED_COUNT; i++) {
        if (( i != 63+64-1 ) && ( i != 48+64-1 )) {
            is31fl3733_set_color(i, red, green, blue);
        }
    }
#elif defined(RGB_BACKLIGHT_DAWN60)
    is31fl3731_set_color_all( red, green, blue );
    for (uint8_t i = 0; i < WS2812_LED_TOTAL; i++) {
        g_ws2812_leds[i].r = red;
        g_ws2812_leds[i].g = green;
        g_ws2812_leds[i].b = blue;
    }
    ws2812_setleds(g_ws2812_leds, WS2812_LED_TOTAL);
#else
    is31fl3731_set_color_all( red, green, blue );
#endif
}

void backlight_set_key_hit(uint8_t row, uint8_t column)
{
    uint8_t led;
    map_row_column_to_led(row,column,&led);
    g_key_hit[led] = 0;

    g_any_key_hit = 0;
}

#if !defined(RGB_BACKLIGHT_HS60) && !defined(RGB_BACKLIGHT_NK65) && !defined(RGB_BACKLIGHT_NEBULA68) && !defined(RGB_BACKLIGHT_NEBULA12) && !defined(RGB_BACKLIGHT_NK87) && !defined(RGB_BACKLIGHT_KW_MEGA)
// This is (F_CPU/1024) / 20 Hz
// = 15625 Hz / 20 Hz
// = 781
#define TIMER3_TOP 781

void backlight_timer_init(void)
{
    static uint8_t backlight_timer_is_init = 0;
    if ( backlight_timer_is_init )
    {
        return;
    }
    backlight_timer_is_init = 1;

    // Timer 3 setup
    TCCR3B = _BV(WGM32) |           // CTC mode OCR3A as TOP
             _BV(CS32) | _BV(CS30); // prescale by /1024
    // Set TOP value
    uint8_t sreg = SREG;
    cli();

    OCR3AH = (TIMER3_TOP >> 8) & 0xff;
    OCR3AL = TIMER3_TOP & 0xff;
    SREG = sreg;
}

void backlight_timer_enable(void)
{
    TIMSK3 |= _BV(OCIE3A);
}

void backlight_timer_disable(void)
{
    TIMSK3 &= ~_BV(OCIE3A);
}

#elif defined(RGB_BACKLIGHT_NEBULA12) //STM32, use GPT with TIM3. Enable in halconf.h
static void gpt_backlight_timer_task(GPTDriver *gptp);
// Timer setup at 200Khz, callback at 10k ticks = 20Hz
static GPTConfig gpt3cfg1 = {
    .frequency = 200000U,
    .callback  = gpt_backlight_timer_task
};

void backlight_timer_init(void)
{
    gptStart(&GPTD3, &gpt3cfg1);
}

void backlight_timer_enable(void)
{
    gptStartContinuous(&GPTD3, 10000);
}

void backlight_timer_disable(void)
{
    gptStopTimer(&GPTD3);
}

#else //STM32, use GPT with TIM4. Enable in halconf.h
static void gpt_backlight_timer_task(GPTDriver *gptp);
// Timer setup at 200Khz, callback at 10k ticks = 20Hz
static GPTConfig gpt4cfg1 = {
    .frequency = 200000U,
    .callback  = gpt_backlight_timer_task
};

void backlight_timer_init(void)
{
    gptStart(&GPTD4, &gpt4cfg1);
}

void backlight_timer_enable(void)
{
    gptStartContinuous(&GPTD4, 10000);
}

void backlight_timer_disable(void)
{
    gptStopTimer(&GPTD4);
}
#endif //!defined(RGB_BACKLIGHT_HS60) && !defined(RGB_BACKLIGHT_NK65) && !defined(RGB_BACKLIGHT_NEBULA68) && !defined(RGB_BACKLIGHT_NEBULA12) && !defined(RGB_BACKLIGHT_NK87) && !defined(RGB_BACKLIGHT_KW_MEGA)

void backlight_set_suspend_state(bool state)
{
    g_suspend_state = state;
}

void backlight_effect_rgb_test(void)
{
    // Mask out bits 4 and 5
    // This 2-bit value will stay the same for 16 ticks.
    switch ( (g_tick & 0x30) >> 4 )
    {
        case 0:
        {
            backlight_set_color_all( 255, 0, 0 );
            break;
        }
        case 1:
        {
            backlight_set_color_all( 0, 255, 0 );
            break;
        }
        case 2:
        {
            backlight_set_color_all( 0, 0, 255 );
            break;
        }
        case 3:
        {
            backlight_set_color_all( 255, 255, 255 );
            break;
        }
    }
}

#if defined(RGB_DEBUGGING_ONLY)
// This tests the LEDs
// Note that it will change the LED control registers
// in the LED drivers, and leave them in an invalid
// state for other backlight effects.
// ONLY USE THIS FOR TESTING LEDS!
void backlight_effect_single_LED_test(void)
{
    static uint8_t color = 0; // 0,1,2 for R,G,B
    static uint8_t row = 0;
    static uint8_t column = 0;

    static uint8_t tick = 0;
    tick++;

    if ( tick > 2 )
    {
        tick = 0;
        column++;
    }
    if ( column > 14 )
    {
        column = 0;
        row++;
    }
    if ( row > 4 )
    {
        row = 0;
        color++;
    }
    if ( color > 2 )
    {
        color = 0;
    }

    uint8_t led;
    map_row_column_to_led( row, column, &led );
    backlight_set_color_all( 255, 255, 255 );
    backlight_test_led( led, color==0, color==1, color==2 );
}
#endif // defined(RGB_DEBUGGING_ONLY)

// All LEDs off
void backlight_effect_all_off(void)
{
    backlight_set_color_all( 0, 0, 0 );
}

// Solid color
void backlight_effect_solid_color(void)
{
    HSV hsv = { .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness };
    RGB rgb = hsv_to_rgb( hsv );
    backlight_set_color_all( rgb.r, rgb.g, rgb.b );
}

// alphas = color1, mods = color2
void backlight_effect_alphas_mods(void)
{
    RGB rgb1 = hsv_to_rgb( (HSV){ .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness } );
    RGB rgb2 = hsv_to_rgb( (HSV){ .h = g_config.color_2.h, .s = g_config.color_2.s, .v = g_config.brightness } );
    bool is_alpha = false;
    for ( int row = 0; row < MATRIX_ROWS; row++ )
    {
        for ( int column = 0; column < MATRIX_COLS; column++ )
        {
            uint8_t index;
            map_row_column_to_led( row, column, &index );
            if ( index < BACKLIGHT_LED_COUNT )
            {
#if defined(RGB_BACKLIGHT_U80_A)
                if ( row == 0 )
                {
                    is_alpha = ( column < 16 ) && (( 0b1110000111100001 & (1<<column) ) == 0);
                }
                else
                {
                    is_alpha = ( column < 16 ) && (( g_config.alphas_mods[row-1] & (1<<column) ) == 0);
                }
#elif defined(RGB_BACKLIGHT_NK87)
                if ( row == 0 )
                {
                    is_alpha = ( ( 0b11100000111100001 & (1<<column) ) == 0);
                }
                else
                {
                    is_alpha = ( column < 16 ) && (( g_config.alphas_mods[row-1] & (1<<column) ) == 0);
                }
#elif defined(RGB_BACKLIGHT_PORTICO75)
                if ( row == 0 )
                {
                    is_alpha = ( ( 0b11100000111100001 & (1<<column) ) == 0);
                }
                else
                {
                    is_alpha = ( column < 16 ) && (( g_config.alphas_mods[row-1] & (1<<column) ) == 0);
                }
#else
                is_alpha = ( g_config.alphas_mods[row] & (1<<column) ) == 0;
#endif
                if ( is_alpha )
                {
                    backlight_set_color( index, rgb1.r, rgb1.g, rgb1.b );
                }
                else
                {
                    backlight_set_color( index, rgb2.r, rgb2.g, rgb2.b );
                }
            }
        }
    }
#if defined(RGB_BACKLIGHT_DAWN60)
    for (int i = 0; i < WS2812_LED_TOTAL; i++) {
        if ((RGB_UNDERGLOW_ALPHA_TOP_START <= i && i <= RGB_UNDERGLOW_ALPHA_TOP_END) ||
            (RGB_UNDERGLOW_ALPHA_BOT_START <= i && i <= RGB_UNDERGLOW_ALPHA_BOT_END)) {
            backlight_set_color(i + RGB_MATRIX_LED_COUNT, rgb1.r, rgb1.g, rgb1.b);
        } else {
            backlight_set_color(i + RGB_MATRIX_LED_COUNT, rgb2.r, rgb2.g, rgb2.b);
        }
    }
#endif
}

void backlight_effect_gradient_up_down(void)
{
    int16_t h1 = g_config.color_1.h;
    int16_t h2 = g_config.color_2.h;
    int16_t deltaH = h2 - h1;

    // Take the shortest path between hues
    if ( deltaH > 127 )
    {
        deltaH -= 256;
    }
    else if ( deltaH < -127 )
    {
        deltaH += 256;
    }
    // Divide delta by 4, this gives the delta per row
    deltaH /= 4;

    int16_t s1 = g_config.color_1.s;
    int16_t s2 = g_config.color_2.s;
    int16_t deltaS = ( s2 - s1 ) / 4;

    HSV hsv = { .h = 0, .s = 255, .v = g_config.brightness };
    RGB rgb;
    Point point;
    for ( int i=0; i<BACKLIGHT_LED_COUNT; i++ )
    {
        map_led_to_point( i, &point );
        // The y range will be 0..64, map this to 0..4
        uint8_t y = (point.y>>4);
        // Relies on hue being 8-bit and wrapping
        hsv.h = g_config.color_1.h + ( deltaH * y );
        hsv.s = g_config.color_1.s + ( deltaS * y );
        rgb = hsv_to_rgb( hsv );

        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void backlight_effect_raindrops(bool initialize)
{
    int16_t h1 = g_config.color_1.h;
    int16_t h2 = g_config.color_2.h;
    int16_t deltaH = h2 - h1;
    deltaH /= 4;

    // Take the shortest path between hues
    if ( deltaH > 127 )
    {
        deltaH -= 256;
    }
    else if ( deltaH < -127 )
    {
        deltaH += 256;
    }

    int16_t s1 = g_config.color_1.s;
    int16_t s2 = g_config.color_2.s;
    int16_t deltaS = ( s2 - s1 ) / 4;

    HSV hsv;
    RGB rgb;

    // Change one LED every tick
    uint8_t led_to_change = ( g_tick & 0x000 ) == 0 ? rand() % BACKLIGHT_LED_COUNT : 255;

    for ( int i=0; i<BACKLIGHT_LED_COUNT; i++ )
    {
        // If initialize, all get set to random colors
        // If not, all but one will stay the same as before.
        if ( initialize || i == led_to_change )
        {
            hsv.h = h1 + ( deltaH * ( rand() & 0x03 ) );
            hsv.s = s1 + ( deltaS * ( rand() & 0x03 ) );
            // Override brightness with global brightness control
            hsv.v = g_config.brightness;

            rgb = hsv_to_rgb( hsv );
            backlight_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}

void backlight_effect_cycle_all(void)
{
    uint8_t offset = ( g_tick << g_config.effect_speed ) & 0xFF;

    // Relies on hue being 8-bit and wrapping
    for ( int i=0; i<BACKLIGHT_LED_COUNT; i++ )
    {
        uint16_t offset2 = g_key_hit[i]<<2;
#if !defined(RGB_BACKLIGHT_HS60) && !defined(RGB_BACKLIGHT_NK65) && !defined(RGB_BACKLIGHT_DAWN60) && !defined(RGB_BACKLIGHT_NEBULA68) && !defined(RGB_BACKLIGHT_NEBULA12) && !defined(RGB_BACKLIGHT_NK87) && !defined(RGB_BACKLIGHT_KW_MEGA)
        // stabilizer LEDs use spacebar hits
        if ( i == 36+6 || i == 54+13 || // LC6, LD13
                ( g_config.use_7u_spacebar && i == 54+14 ) ) // LD14
        {
            offset2 = g_key_hit[36+0]<<2;
        }
#endif
        offset2 = (offset2<=63) ? (63-offset2) : 0;

        HSV hsv = { .h = offset+offset2, .s = 255, .v = g_config.brightness };
        RGB rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void backlight_effect_cycle_left_right(void)
{
    uint8_t offset = ( g_tick << g_config.effect_speed ) & 0xFF;
    HSV hsv = { .h = 0, .s = 255, .v = g_config.brightness };
    RGB rgb;
    Point point;
    for ( int i=0; i<BACKLIGHT_LED_COUNT; i++ )
    {
        uint16_t offset2 = g_key_hit[i]<<2;
#if !defined(RGB_BACKLIGHT_HS60) && !defined(RGB_BACKLIGHT_NK65) && !defined(RGB_BACKLIGHT_DAWN60) && !defined(RGB_BACKLIGHT_NEBULA68) && !defined(RGB_BACKLIGHT_NEBULA12) && !defined(RGB_BACKLIGHT_NK87) && !defined(RGB_BACKLIGHT_KW_MEGA)
        // stabilizer LEDs use spacebar hits
        if ( i == 36+6 || i == 54+13 || // LC6, LD13
                ( g_config.use_7u_spacebar && i == 54+14 ) ) // LD14
        {
            offset2 = g_key_hit[36+0]<<2;
        }
#endif
        offset2 = (offset2<=63) ? (63-offset2) : 0;

        map_led_to_point( i, &point );
        // Relies on hue being 8-bit and wrapping
        hsv.h = point.x + offset + offset2;
        rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void backlight_effect_cycle_up_down(void)
{
    uint8_t offset = ( g_tick << g_config.effect_speed ) & 0xFF;
    HSV hsv = { .h = 0, .s = 255, .v = g_config.brightness };
    RGB rgb;
    Point point;
    for ( int i=0; i<BACKLIGHT_LED_COUNT; i++ )
    {
        uint16_t offset2 = g_key_hit[i]<<2;
#if !defined(RGB_BACKLIGHT_HS60) && !defined(RGB_BACKLIGHT_NK65) && !defined(RGB_BACKLIGHT_DAWN60) && !defined(RGB_BACKLIGHT_NEBULA68) && !defined(RGB_BACKLIGHT_NEBULA12) && !defined(RGB_BACKLIGHT_NK87) && !defined(RGB_BACKLIGHT_KW_MEGA)
        // stabilizer LEDs use spacebar hits
        if ( i == 36+6 || i == 54+13 || // LC6, LD13
                ( g_config.use_7u_spacebar && i == 54+14 ) ) // LD14
        {
            offset2 = g_key_hit[36+0]<<2;
        }
#endif
        offset2 = (offset2<=63) ? (63-offset2) : 0;

        map_led_to_point( i, &point );
        // Relies on hue being 8-bit and wrapping
        hsv.h = point.y + offset + offset2;
        rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void backlight_effect_jellybean_raindrops( bool initialize )
{
    HSV hsv;
    RGB rgb;

    // Change one LED every tick
    uint8_t led_to_change = ( g_tick & 0x000 ) == 0 ? rand() % BACKLIGHT_LED_COUNT : 255;

    for ( int i=0; i<BACKLIGHT_LED_COUNT; i++ )
    {
        // If initialize, all get set to random colors
        // If not, all but one will stay the same as before.
        if ( initialize || i == led_to_change )
        {
            hsv.h = rand() & 0xFF;
            hsv.s = rand() & 0xFF;
            // Override brightness with global brightness control
            hsv.v = g_config.brightness;;

            rgb = hsv_to_rgb( hsv );
            backlight_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}

void backlight_effect_cycle_radial1(void)
{
    uint8_t offset = ( g_tick << g_config.effect_speed ) & 0xFF;
    HSV hsv = { .h = 0, .s = 255, .v = g_config.brightness };
    RGB rgb;
    Point point;
    for ( int i=0; i<BACKLIGHT_LED_COUNT; i++ )
    {
        map_led_to_point_polar( i, &point );
        // Relies on hue being 8-bit and wrapping
        hsv.h = point.x + offset;
        hsv.s = point.y;
        rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void backlight_effect_cycle_radial2(void)
{
    uint8_t offset = ( g_tick << g_config.effect_speed ) & 0xFF;

    HSV hsv = { .h = 0, .s = g_config.color_1.s, .v = g_config.brightness };
    RGB rgb;
    Point point;
    for ( int i=0; i<BACKLIGHT_LED_COUNT; i++ )
    {
        map_led_to_point_polar( i, &point );
        uint8_t offset2 = offset + point.x;
        if ( offset2 & 0x80 )
        {
            offset2 = ~offset2;
        }
        offset2 = offset2 >> 2;
        hsv.h = g_config.color_1.h + offset2;
        hsv.s = 127 + ( point.y >> 1 );
        rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

#if defined(RGB_BACKLIGHT_M6_B) || defined(RGB_BACKLIGHT_M10_C)
void backlight_effect_custom_colors(void)
{
    RGB rgb;
    for ( uint8_t i = 0; i < RGB_BACKLIGHT_CUSTOM_COLORS_COUNT; i++ )
    {
        HSV hsv = { .h = g_config.custom_color[i].h, .s = g_config.custom_color[i].s, .v = g_config.brightness };
        rgb = hsv_to_rgb( hsv );
        uint8_t led;
        map_row_column_to_led( 0, i, &led );
        backlight_set_color( led, rgb.r, rgb.g, rgb.b );
#if defined(RGB_BACKLIGHT_M10_C)
        // Set stab LEDs with the same color
        if ( led == 10 ) {
            backlight_set_color( 9, rgb.r, rgb.g, rgb.b );
            backlight_set_color( 11, rgb.r, rgb.g, rgb.b );
        }
#endif
    }
}
#endif

void backlight_set_rowcol_rgb(uint8_t row, uint8_t col, uint8_t r, uint8_t g, uint8_t b)
{
    uint8_t index;
    map_row_column_to_led(row, col, &index );
    backlight_set_color(index, r, g, b);
}

void backlight_set_wasd(uint8_t r, uint8_t g, uint8_t b) {
    struct { uint8_t row; uint8_t col; } keys[4] = {
        {0, 3}, {1, 2}, {1, 3}, {1, 4}
    };
    for (int i = 0; i < 4; ++i) {
        backlight_set_rowcol_rgb(keys[i].row, keys[i].col, r, g, b);
    }
}

void backlight_set_row_rgb(uint8_t row, uint8_t r, uint8_t g, uint8_t b)
{
    for (int i = 0; i < MATRIX_COLS; ++i) {
        backlight_set_rowcol_rgb(row, i, r, g, b);
    }
}

void backlight_set_col_rgb(uint8_t col, uint8_t r, uint8_t g, uint8_t b)
{
    for (int i = 0; i < MATRIX_ROWS; ++i) {
        backlight_set_rowcol_rgb(i, col, r, g, b);
    }
}

void backlight_effect_synthwave(bool initialize)
{
    uint8_t breathing = 8 + scale8(abs8(sin8(g_tick << g_config.effect_speed) - 128) * 2, 128);
    // low intensity breathing all the colours in the background
    // 0 = red
    uint8_t hue = g_config.color_1.h;
    uint8_t sat = g_config.color_1.s;
    if ( IS_LAYER_ON(3) ) {
        sat = 255;
    } else if ( IS_LAYER_ON(2) ) {
        hue = (hue + 4) & 0xff;
    } else if ( IS_LAYER_ON(1) ) {
        hue = (hue - 4) & 0xff;
    }
    HSV hsv = { .h = hue, .s = sat, .v = 0 };
    RGB rgb;
    static uint8_t led_state[BACKLIGHT_LED_COUNT];
    led_state[g_tick % BACKLIGHT_LED_COUNT] = 255;
    for (int i = 0; i < BACKLIGHT_LED_COUNT; ++i) {
        uint8_t val = 255 - g_key_hit[i];

        hsv.v = MIN(g_config.brightness, MAX(val, led_state[i]));
        rgb = hsv_to_rgb(hsv);
        backlight_set_color(i, rgb.r, rgb.g, rgb.b);

        if (led_state[i] > 0) {
            led_state[i] = MAX(led_state[i] - (255/BACKLIGHT_LED_COUNT), 0);
        }
    }
    /* for (int r = 0; r < MATRIX_ROWS; r++) { */
    /*     for (int c = 0; c < MATRIX_COLS; c++) { */
    /*         uint8_t led; */
    /*         map_row_column_to_led(r, c, &led); */
    /*         uint8_t val = 255 - g_key_hit[led]; */

    /*         hsv.v = MIN(255, val + breathing); */
    /*         rgb = hsv_to_rgb(hsv); */
    /*         backlight_set_color(led, rgb.r, rgb.g, rgb.b); */
    /*     } */
    /* } */

    // highlight WASD if gaming layer is enabled
    if ( IS_LAYER_ON(4) )
    {
        hsv.h = g_config.color_2.h;
        hsv.s = g_config.color_2.s;
        hsv.v = (64 + (breathing / 4)) & 0xff;
        rgb = hsv_to_rgb(hsv);
        backlight_set_wasd(rgb.r, rgb.g, rgb.b);
        backlight_set_rowcol_rgb(3, 0, 255, 255, 255);
    }

    // highlight numpad keys if numeric layer is enabled
    if ( IS_LAYER_ON(5) )
    {
        hsv.h = g_config.color_2.h;
        hsv.s = g_config.color_2.s;
        hsv.v = (64 + (breathing / 4)) & 0xff;
        rgb = hsv_to_rgb(hsv);
        for (int row = 0; row < 3; ++row) {
            for (int col = 10; col < 13; ++col) {
                backlight_set_rowcol_rgb(row, col, rgb.r, rgb.g, rgb.b);
            }
        }
        backlight_set_rowcol_rgb(3, 11, rgb.r, rgb.g, rgb.b);
    }
    if ( IS_LAYER_ON(3) )
    {
        backlight_set_rowcol_rgb(0, 0, 255, 255, 255);
    }
    else if ( IS_LAYER_ON(2) )
    {
        backlight_set_rowcol_rgb(1, 0, 255, 255, 255);
    }
    else if ( IS_LAYER_ON(1) )
    {
        backlight_set_rowcol_rgb(2, 0, 255, 255, 255);
    }
}

void backlight_effect_indicators_set_colors( uint8_t index, HS color )
{
    HSV hsv = { .h = color.h, .s = color.s, .v = g_config.brightness };
    RGB rgb = hsv_to_rgb( hsv );
    if ( index == 254 )
    {
        backlight_set_color_all( rgb.r, rgb.g, rgb.b );
    }
    else
    {
        backlight_set_color( index, rgb.r, rgb.g, rgb.b );

        // If the spacebar LED is the indicator,
        // do the same for the spacebar stabilizers
        if ( index == 36+0 ) // LC0
        {
#if defined(RGB_BACKLIGHT_ZEAL65)
            backlight_set_color( 36+7, rgb.r, rgb.g, rgb.b ); // LC7
            backlight_set_color( 54+14, rgb.r, rgb.g, rgb.b ); // LD14
#elif defined(RGB_BACKLIGHT_KOYU) || defined(RGB_BACKLIGHT_M65_B) || defined(RGB_BACKLIGHT_M65_BX)
            backlight_set_color( 36+6, rgb.r, rgb.g, rgb.b ); // LC6
            backlight_set_color( 54+14, rgb.r, rgb.g, rgb.b ); // LD14
#elif defined(RGB_BACKLIGHT_ZEAL60) || defined(RGB_BACKLIGHT_M60_A)
            backlight_set_color( 36+6, rgb.r, rgb.g, rgb.b ); // LC6
            backlight_set_color( 54+13, rgb.r, rgb.g, rgb.b ); // LD13
            if ( g_config.use_7u_spacebar )
            {
                backlight_set_color( 54+14, rgb.r, rgb.g, rgb.b ); // LD14
            }
#endif
        }
    }
}

// This runs after another backlight effect and replaces
// colors already set
__attribute__ ((weak)) void backlight_effect_indicators(void)
{
    if ( g_config.caps_lock_indicator.index != 255 && host_keyboard_led_state().caps_lock )
    {
        backlight_effect_indicators_set_colors( g_config.caps_lock_indicator.index, g_config.caps_lock_indicator.color );
    }
    // This if/else if structure allows higher layers to
    // override lower ones. If we set layer 3's indicator
    // to none, then it will NOT show layer 2 or layer 1
    // indicators, even if those layers are on via the
    // MO13/MO23 Fn combo magic.
    //
    // Basically we want to handle the case where layer 3 is
    // still the backlight configuration layer and we don't
    // want "all LEDs" indicators hiding the backlight effect,
    // but still allow end users to do whatever they want.
    if ( IS_LAYER_ON(3) )
    {
        if ( g_config.layer_3_indicator.index != 255 )
        {
            backlight_effect_indicators_set_colors( g_config.layer_3_indicator.index, g_config.layer_3_indicator.color );
        }
    }
    else if ( IS_LAYER_ON(2) )
    {
        if ( g_config.layer_2_indicator.index != 255 )
        {
            backlight_effect_indicators_set_colors( g_config.layer_2_indicator.index, g_config.layer_2_indicator.color );
        }
    }
    else if ( IS_LAYER_ON(1) )
    {
        if ( g_config.layer_1_indicator.index != 255 )
        {
            backlight_effect_indicators_set_colors( g_config.layer_1_indicator.index, g_config.layer_1_indicator.color );
        }
    }
}

#if !defined(RGB_BACKLIGHT_HS60) && !defined(RGB_BACKLIGHT_NK65) && !defined(RGB_BACKLIGHT_NEBULA68) && !defined(RGB_BACKLIGHT_NEBULA12) && !defined(RGB_BACKLIGHT_NK87) && !defined(RGB_BACKLIGHT_KW_MEGA)
ISR(TIMER3_COMPA_vect)
#else //STM32 interrupt
static void gpt_backlight_timer_task(GPTDriver *gptp)
#endif
{
    // delay 1 second before driving LEDs or doing anything else
    static uint8_t startup_tick = 0;
    if ( startup_tick < 20 )
    {
        startup_tick++;
        return;
    }

    g_tick++;

    if ( g_any_key_hit < 0xFFFFFFFF )
    {
        g_any_key_hit++;
    }

    for ( int led = 0; led < BACKLIGHT_LED_COUNT; led++ )
    {
        if ( g_key_hit[led] < 255 )
        {
            g_key_hit[led]++;
        }
    }

    // Factory default magic value
    if ( g_config.effect == 255 )
    {
        backlight_effect_rgb_test();
        return;
    }

    // Ideally we would also stop sending zeros to the LED driver PWM buffers
    // while suspended and just do a software shutdown. This is a cheap hack for now.
    bool suspend_backlight = ((g_suspend_state && g_config.disable_when_usb_suspended) ||
            (g_config.disable_after_timeout > 0 && g_any_key_hit > g_config.disable_after_timeout * 60 * 20));
    uint8_t effect = suspend_backlight ? 0 : g_config.effect;

    // Keep track of the effect used last time,
    // detect change in effect, so each effect can
    // have an optional initialization.
    static uint8_t effect_last = 255;
    bool initialize = effect != effect_last;
    effect_last = effect;

    // this gets ticked at 20 Hz.
    // each effect can opt to do calculations
    // and/or request PWM buffer updates.
    switch ( effect )
    {
        case 0:
            backlight_effect_all_off();
            break;
        case 1:
            backlight_effect_solid_color();
            break;
        case 2:
#if defined(RGB_BACKLIGHT_M6_B) || defined(RGB_BACKLIGHT_M10_C)
            backlight_effect_custom_colors();
#else
            backlight_effect_alphas_mods();
#endif
            break;
        case 3:
            backlight_effect_gradient_up_down();
            break;
        case 4:
            backlight_effect_raindrops( initialize );
            break;
        case 5:
            backlight_effect_cycle_all();
            break;
        case 6:
            backlight_effect_cycle_left_right();
            break;
        case 7:
            backlight_effect_cycle_up_down();
            break;
        case 8:
            backlight_effect_jellybean_raindrops( initialize );
            break;
        case 9:
            backlight_effect_cycle_radial1();
            break;
        case 10:
            backlight_effect_cycle_radial2();
            break;
        case 11:
            backlight_effect_synthwave( initialize );
            break;
        default:
            backlight_effect_all_off();
            break;
    }

    if ( ! suspend_backlight )
    {
        backlight_effect_indicators();
    }
}

void backlight_set_indicator_index( uint8_t *index, uint8_t row, uint8_t column )
{
    if ( row >= MATRIX_ROWS )
    {
        // Special value, 255=none, 254=all
        *index = row;
    }
    else
    {
        map_row_column_to_led( row, column, index );
    }
}

void backlight_get_indicator_row_col( uint8_t index, uint8_t *row, uint8_t *column )
{
    if ( index == 255 || index == 254 )
    {
        // Special value, 255=none, 254=all
        *row = index;
        *column = 0;
        return;
    }
    for ( uint8_t r = 0; r < MATRIX_ROWS; r++ )
    {
        for ( uint8_t c = 0; c < MATRIX_COLS; c++ )
        {
            uint8_t i = 255;
            map_row_column_to_led( r, c, &i );
            if ( i == index )
            {
                *row = r;
                *column = c;
                return;
            }
        }
    }
}

// Some helpers for setting/getting HSV
void _set_color( HS *color, uint8_t *data )
{
    color->h = data[0];
    color->s = data[1];
}

void _get_color( HS *color, uint8_t *data )
{
    data[0] = color->h;
    data[1] = color->s;
}

void backlight_config_set_value( uint8_t *data )
{
    bool reinitialize = false;
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
#if defined (RGB_BACKLIGHT_ZEAL60) || defined(RGB_BACKLIGHT_ZEAL65)
        case id_use_split_backspace:
        {
            g_config.use_split_backspace = (bool)*value_data;
            reinitialize = true;
            break;
        }
#endif
#if defined (RGB_BACKLIGHT_ZEAL60)
        case id_use_split_left_shift:
        {
            g_config.use_split_left_shift = (bool)*value_data;
            reinitialize = true;
            break;
        }
        case id_use_split_right_shift:
        {
            g_config.use_split_right_shift = (bool)*value_data;
            reinitialize = true;
            break;
        }
        case id_use_7u_spacebar:
        {
            g_config.use_7u_spacebar = (bool)*value_data;
            reinitialize = true;
            break;
        }
        case id_use_iso_enter:
        {
            g_config.use_iso_enter = (bool)*value_data;
            reinitialize = true;
            break;
        }
        case id_disable_hhkb_blocker_leds:
        {
            g_config.disable_hhkb_blocker_leds = (bool)*value_data;
            reinitialize = true;
            break;
        }
#endif
        case id_disable_when_usb_suspended:
        {
            g_config.disable_when_usb_suspended = (bool)*value_data;
            break;
        }
        case id_disable_after_timeout:
        {
            g_config.disable_after_timeout = *value_data;
            break;
        }
        case id_brightness:
        {
            g_config.brightness = *value_data;
            break;
        }
        case id_effect:
        {
            g_config.effect = *value_data;
            break;
        }
        case id_effect_speed:
        {
            g_config.effect_speed = *value_data;
            break;
        }
        case id_color_1:
        {
            _set_color( &(g_config.color_1), value_data );
            break;
        }
        case id_color_2:
        {
            _set_color( &(g_config.color_2), value_data );
            break;
        }
        case id_caps_lock_indicator_color:
        {
            _set_color( &(g_config.caps_lock_indicator.color), value_data );
            break;
        }
        case id_caps_lock_indicator_row_col:
        {
            backlight_set_indicator_index( &(g_config.caps_lock_indicator.index), value_data[0], value_data[1] );
            break;
        }
        case id_layer_1_indicator_color:
        {
            _set_color( &(g_config.layer_1_indicator.color), value_data );
            break;
        }
        case id_layer_1_indicator_row_col:
        {
            backlight_set_indicator_index( &(g_config.layer_1_indicator.index), value_data[0], value_data[1] );
            break;
        }
        case id_layer_2_indicator_color:
        {
            _set_color( &(g_config.layer_2_indicator.color), value_data );
            break;
        }
        case id_layer_2_indicator_row_col:
        {
            backlight_set_indicator_index( &(g_config.layer_2_indicator.index), value_data[0], value_data[1] );
            break;
        }
        case id_layer_3_indicator_color:
        {
            _set_color( &(g_config.layer_3_indicator.color), value_data );
            break;
        }
        case id_layer_3_indicator_row_col:
        {
            backlight_set_indicator_index( &(g_config.layer_3_indicator.index), value_data[0], value_data[1] );
            break;
        }
        case id_alphas_mods:
        {
            for ( int i=0; i<5; i++ )
            {
                g_config.alphas_mods[i] = ( *(value_data+i*2) << 8 ) | ( *(value_data+i*2+1) );
            }
        }
#if defined(RGB_BACKLIGHT_M6_B) || defined(RGB_BACKLIGHT_M10_C)
        case id_custom_color:
        {
            uint8_t index = value_data[0];
            if ( index >= 0 && index < RGB_BACKLIGHT_CUSTOM_COLORS_COUNT )
            {
                _set_color( &(g_config.custom_color[index]), &(value_data[1]) );
            }
        }
#endif
    }

    if ( reinitialize )
    {
        backlight_init_drivers();
    }
}

void backlight_config_get_value( uint8_t *data )
{
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case id_use_split_backspace:
        {
            *value_data = ( g_config.use_split_backspace ? 1 : 0 );
            break;
        }
        case id_use_split_left_shift:
        {
            *value_data = ( g_config.use_split_left_shift ? 1 : 0 );
            break;
        }
        case id_use_split_right_shift:
        {
            *value_data = ( g_config.use_split_right_shift ? 1 : 0 );
            break;
        }
        case id_use_7u_spacebar:
        {
            *value_data = ( g_config.use_7u_spacebar ? 1 : 0 );
            break;
        }
        case id_use_iso_enter:
        {
            *value_data = ( g_config.use_iso_enter ? 1 : 0 );
            break;
        }
        case id_disable_when_usb_suspended:
        {
            *value_data = ( g_config.disable_when_usb_suspended ? 1 : 0 );
            break;
        }
        case id_disable_hhkb_blocker_leds:
        {
            *value_data = ( g_config.disable_hhkb_blocker_leds ? 1 : 0 );
            break;
        }
        case id_disable_after_timeout:
        {
            *value_data = g_config.disable_after_timeout;
            break;
        }
        case id_brightness:
        {
            *value_data = g_config.brightness;
            break;
        }
        case id_effect:
        {
            *value_data = g_config.effect;
            break;
        }
        case id_effect_speed:
        {
            *value_data = g_config.effect_speed;
            break;
        }
        case id_color_1:
        {
            _get_color( &(g_config.color_1), value_data );
            break;
        }
        case id_color_2:
        {
            _get_color( &(g_config.color_2), value_data );
            break;
        }
        case id_caps_lock_indicator_color:
        {
            _get_color( &(g_config.caps_lock_indicator.color), value_data );
            break;
        }
        case id_caps_lock_indicator_row_col:
        {
            backlight_get_indicator_row_col( g_config.caps_lock_indicator.index, &(value_data[0]), &(value_data[1]) );
            break;
        }
        case id_layer_1_indicator_color:
        {
            _get_color( &(g_config.layer_1_indicator.color), value_data );
            break;
        }
        case id_layer_1_indicator_row_col:
        {
            backlight_get_indicator_row_col( g_config.layer_1_indicator.index, &(value_data[0]), &(value_data[1]) );
            break;
        }
        case id_layer_2_indicator_color:
        {
            _get_color( &(g_config.layer_2_indicator.color), value_data );
            break;
        }
        case id_layer_2_indicator_row_col:
        {
            backlight_get_indicator_row_col( g_config.layer_2_indicator.index, &(value_data[0]), &(value_data[1]) );
            break;
        }
        case id_layer_3_indicator_color:
        {
            _get_color( &(g_config.layer_3_indicator.color), value_data );
            break;
        }
        case id_layer_3_indicator_row_col:
        {
            backlight_get_indicator_row_col( g_config.layer_3_indicator.index, &(value_data[0]), &(value_data[1]) );
            break;
        }
        case id_alphas_mods:
        {
            for ( int i=0; i<5; i++ )
            {
                *(value_data+i*2) = g_config.alphas_mods[i] >> 8;
                *(value_data+i*2+1) = g_config.alphas_mods[i] & 0xFF;
            }
        }
#if defined(RGB_BACKLIGHT_M6_B) || defined(RGB_BACKLIGHT_M10_C)
        case id_custom_color:
        {
            uint8_t index = value_data[0];
            if ( index >= 0 && index < RGB_BACKLIGHT_CUSTOM_COLORS_COUNT )
            {
                _get_color( &(g_config.custom_color[index]), &(value_data[1]) );
            }
        }
#endif
    }
}

void backlight_config_set_alphas_mods( uint16_t *alphas_mods )
{
    for ( int i=0; i<5; i++ )
    {
        g_config.alphas_mods[i] = alphas_mods[i];
    }

    backlight_config_save();
}

void backlight_config_load(void)
{
    eeprom_read_block( &g_config, ((void*)RGB_BACKLIGHT_CONFIG_EEPROM_ADDR), sizeof(backlight_config) );
}

void backlight_config_save(void)
{
    eeprom_update_block( &g_config, ((void*)RGB_BACKLIGHT_CONFIG_EEPROM_ADDR), sizeof(backlight_config) );
}

void backlight_init_drivers(void)
{
    // Initialize I2C
    i2c_init();

#if defined(RGB_BACKLIGHT_M6_B)
    is31fl3218_init();
#elif defined(RGB_BACKLIGHT_HS60)
    is31fl3733_init( ISSI_ADDR_1, 0 );

    for ( int index = 0; index < RGB_MATRIX_LED_COUNT; index++ )
    {
#if defined(HS60_ANSI)
        bool enabled = !( ( index == 48-1 ) || //LA48
                          ( index == 51-1 ) || //LA51
                          ( index == 61-1 ) ); //LA61
#elif defined(HS60_HHKB)
        bool enabled = !( ( index == 61-1 ) || //LA61
                          ( index == 62-1 ) ); //LA62
#else //HS60_ISO
        bool enabled = !( ( index == 51-1 ) || //LA51
                          ( index == 61-1 ) ); //LA61
#endif
                // This only caches it for later
        is31fl3733_set_led_control_register( index, enabled, enabled, enabled );
    }
    // This actually updates the LED drivers
    is31fl3733_update_led_control_registers( ISSI_ADDR_1, 0 );
#elif defined(RGB_BACKLIGHT_NK65)
    is31fl3733_init( ISSI_ADDR_1, 0 );
    is31fl3733_init( ISSI_ADDR_2, 0 );

    for ( int index = 0; index < RGB_MATRIX_LED_COUNT; index++ )
    {
        bool enabled = !( ( index == 61-1 )   || //LA61
                          ( index > 6+64-1 ) ); //LB7-LB64
        // This only caches it for later
        is31fl3733_set_led_control_register( index, enabled, enabled, enabled );
    }
    is31fl3733_set_led_control_register( 7+64-1, 0, 1, 0 ); //Enable LB7 green enable for indicators
    // This actually updates the LED drivers
    is31fl3733_update_led_control_registers( ISSI_ADDR_1, 0 );
    is31fl3733_update_led_control_registers( ISSI_ADDR_2, 1 );
#elif defined(RGB_BACKLIGHT_NK87)
    is31fl3733_init( ISSI_ADDR_1, 0 );
    is31fl3733_init( ISSI_ADDR_2, 0 );

    for ( int index = 0; index < RGB_MATRIX_LED_COUNT; index++ )
    {
        bool enabled = !( ( index == 61-1 )   || //LA61
                          ( (index >= 2+64-1) && (index <= 4+64-1) ) ||
                          ( (index >= 6+64-1) && (index <= 8+64-1) ) ||
                          ( index == 10+64-1 ) || ( index == 11+64-1 ) ||
                          ( (index >= 14+64-1) && (index <= 16+64-1) ) ||
                          ( (index >= 18+64-1) && (index <= 20+64-1) ) ||
                          ( (index >= 22+64-1) && (index <= 24+64-1) ) ||
                          ( (index >= 26+64-1) && (index <= 28+64-1) ) ||
                          ( (index >= 30+64-1) && (index <= 32+64-1) ) ||
                          ( (index >= 34+64-1) && (index <= 36+64-1) ) ||
                          ( (index >= 38+64-1) && (index <= 40+64-1) ) ||
                          ( (index >= 42+64-1) && (index <= 44+64-1) ) ||
                          ( (index >= 46+64-1) && (index <= 48+64-1) ) ||
                          ( index == 50+64-1 )   ||
                          ( index == 54+64-1 )   ||
                          ( index == 58+64-1 )   ||
                          ( index == 62+64-1 ) );
        // This only caches it for later
        is31fl3733_set_led_control_register( index, enabled, enabled, enabled );
    }
    is31fl3733_set_led_control_register( 48+64-1, 0, 0, 1 ); //Enable LB48 blue enable for indicators
    // This actually updates the LED drivers
    is31fl3733_update_led_control_registers( ISSI_ADDR_1, 0 );
    is31fl3733_update_led_control_registers( ISSI_ADDR_2, 1 );
#elif defined(RGB_BACKLIGHT_NEBULA68)
    is31fl3733_init( ISSI_ADDR_1, 0 );
    is31fl3733_init( ISSI_ADDR_2, 0 );

    for ( int index = 0; index < RGB_MATRIX_LED_COUNT; index++ )
    {
        bool enabled = !( ( index == 61-1 )   || //LA61
                          ( index > 5+64-1 ) ); //LB6-LB64
        // This only caches it for later
        is31fl3733_set_led_control_register( index, enabled, enabled, enabled );
    }
    // This actually updates the LED drivers
    is31fl3733_update_led_control_registers( ISSI_ADDR_1, 0 );
    is31fl3733_update_led_control_registers( ISSI_ADDR_2, 1 );
#elif defined(RGB_BACKLIGHT_PORTICO75)
    is31fl3741_init( ISSI_ADDR_1 );
	bool enabled = true;
    for ( int index = 0; index < RGB_MATRIX_LED_COUNT; index++ )
    {
        is31fl3741_set_led_control_register( index, enabled, enabled, enabled );
    }
    // This actually updates the LED drivers
    is31fl3741_update_led_control_registers( ISSI_ADDR_1, 0 );
#elif defined(RGB_BACKLIGHT_KW_MEGA)
    is31fl3733_init( ISSI_ADDR_1, 0 );
    is31fl3733_init( ISSI_ADDR_2, 0 );

    for ( int index = 0; index < RGB_MATRIX_LED_COUNT; index++ )
    {
        bool enabled = !( ( index == 61-1 )   || //LA61
                          ( index > 6+64-1 ) ); //LB7-LB64
        // This only caches it for later
        is31fl3733_set_led_control_register( index, enabled, enabled, enabled );
    }
    // This actually updates the LED drivers
    is31fl3733_update_led_control_registers( ISSI_ADDR_1, 0 );
    is31fl3733_update_led_control_registers( ISSI_ADDR_2, 1 );
#else
    // Init the #1 driver
    is31fl3731_init( ISSI_ADDR_1 );
    // Init the #2 driver (if used)
#if !defined(RGB_BACKLIGHT_NEBULA12) && !defined(RGB_BACKLIGHT_M10_C)
    is31fl3731_init( ISSI_ADDR_2 );
#endif
    // Init the #3 driver (if used)
#if defined(RGB_BACKLIGHT_U80_A)
    is31fl3731_init( ISSI_ADDR_3 );
#endif

    // Experimental feature, not in configuration yet
#if defined(RGB_BACKLIGHT_ZEAL60)
    bool disable_spacebar_stab_leds = false;
#endif

    for ( int index = 0; index < RGB_MATRIX_LED_COUNT; index++ )
    {
        // OR the possible "disabled" cases together, then NOT the result to get the enabled state
        // LC6 LD13 not present on Zeal65
#if defined(RGB_BACKLIGHT_ZEAL65)
        bool enabled = !( ( index == 18+5 && !g_config.use_split_backspace ) || // LB5
                          ( index == 36+6 ) || // LC6
                          ( index == 54+13 ) ); // LD13
#elif defined(RGB_BACKLIGHT_KOYU)
        bool enabled = !( ( index == 36+15 ) || // LC15
                          ( index == 54+13 ) || // LD13
                          ( index == 54+17 ) ); // LD17
#elif defined(RGB_BACKLIGHT_M65_B) || defined(RGB_BACKLIGHT_M65_BX)
        bool enabled = !(
        // LB6 not present on M65-B
#if defined(RGB_BACKLIGHT_M65_B)
                          ( index == 18+6 ) || // LB6
#endif
        // LC15 LD13 not present on M65-B, M65-BX
                          ( index == 36+15 ) || // LC15
                          ( index == 54+13 ) ); // LD13
#elif defined(RGB_BACKLIGHT_M60_A)
        bool enabled = !(
        // LB6 LB7 LB8 LB15 LB16 LB17 not present on M60-A
                          ( index == 18+6 ) || // LB6
                          ( index == 18+7 ) || // LB7
                          ( index == 18+8 ) || // LB8
                          ( index == 18+15 ) || // LB15
                          ( index == 18+16 ) || // LB16
                          ( index == 18+17 ) || // LB17
        // HHKB blockers (LC17, LD17) and ISO extra keys (LC15,LD13) not present on M60-A
                          ( index == 36+17 ) || // LC17
                          ( index == 54+17 ) || // LD17
                          ( index == 36+15 ) || // LC15
                          ( index == 54+13 ) ); // LD13
#elif defined(RGB_BACKLIGHT_WT60_B) || defined(RGB_BACKLIGHT_WT60_BX) || defined(RGB_BACKLIGHT_WT60_C)
        bool enabled = !(
        // LB6 not present on WT60-B
#if defined(RGB_BACKLIGHT_WT60_B)
                          ( index == 18+6 ) || // LB6
#endif
        // LB7 LB8 LB15 LB16 LB17 LC15 LD13 not present on WT60-B, WT60-BX, WT60-C
                          ( index == 18+7 ) || // LB7
                          ( index == 18+8 ) || // LB8
                          ( index == 18+15 ) || // LB15
                          ( index == 18+16 ) || // LB16
                          ( index == 18+17 ) || // LB17
                          ( index == 36+15 ) || // LC15
                          ( index == 54+13 ) ); // LD13
#elif defined(RGB_BACKLIGHT_ZEAL60)
        // LB6 LB7 LB8 LB15 LB16 LB17 not present on Zeal60
        bool enabled = !( ( index == 18+5 && !g_config.use_split_backspace ) || // LB5
                          ( index == 36+15 && !g_config.use_split_left_shift ) || // LC15
                          ( index == 54+8 && !g_config.use_split_right_shift ) || // LD8
                          ( index == 54+13 && g_config.use_7u_spacebar ) || // LD13
                          ( index == 36+17 && g_config.disable_hhkb_blocker_leds ) || // LC17
                          ( index == 54+17 && g_config.disable_hhkb_blocker_leds ) ||  // LD17
                          ( index == 18+6 ) || // LB6
                          ( index == 18+7 ) || // LB7
                          ( index == 18+8 ) || // LB8
                          ( index == 18+15 ) || // LB15
                          ( index == 18+16 ) || // LB16
                          ( index == 18+17 ) || // LB17
                          ( index == 36+6 && disable_spacebar_stab_leds ) ||  // LC6
                          ( index == 54+13 && disable_spacebar_stab_leds ) ||  // LD13
                          ( index == 54+14 && disable_spacebar_stab_leds && g_config.use_7u_spacebar ) ); // LD14
#elif defined(RGB_BACKLIGHT_U80_A)
// LB5, LB6, LB7, LB8, LB15, LB16, LB17, LC15, LD8, LD13, LE0-LE8, LF13
        bool enabled = !(
                          ( index == 18+5 ) || // LB5
                          ( index == 18+6 ) || // LB6
                          ( index == 18+7 ) || // LB7
                          ( index == 18+8 ) || // LB8
                          ( index == 18+15 ) || // LB15
                          ( index == 18+16 ) || // LB16
                          ( index == 18+16 ) || // LB17
                          ( index == 36+15 ) || // LC15
                          ( index == 54+8 ) || // LD8
                          ( index == 54+13 ) ||  // LD13
                          ( index >= 72+0 && index <= 72+8 ) ||  // LE0-LE8
                          ( index == 90+13 ) ); // LF13
#elif defined(RGB_BACKLIGHT_DAWN60)
        bool enabled = !( ( index == 15+7 && !g_config.use_split_backspace ) || //other backspace
                          ( index == 47+13 && g_config.use_7u_spacebar ) ||     //LD13
                          ( index == 47+15 && g_config.use_7u_spacebar ) );       //LD15
#elif defined(RGB_BACKLIGHT_NEBULA12)
        bool enabled = !( ( index >= 9-1 && index <= 12-1 ) ); // A9-A12
#elif defined(RGB_BACKLIGHT_M50_A)
        bool enabled = !(
        // LA0, LA7, LA8, LA17
                          ( index == 0+0 ) ||
                          ( index == 0+7 ) ||
                          ( index == 0+8 ) ||
                          ( index == 0+17 ) ||

        // LB0, LB7, LB8, LB15, LB16, LB17,
                          ( index == 18+0 ) ||
                          ( index == 18+7 ) ||
                          ( index == 18+8 ) ||
                          ( index == 18+15 ) ||
                          ( index == 18+16 ) ||
                          ( index == 18+17 ) ||
        // LC0, LC8, LC16, LC17
                          ( index == 36+0 ) ||
                          ( index == 36+8 ) ||
                          ( index == 36+16 ) ||
                          ( index == 36+17 ) ||
        // LD0, LD7, LD8, LD9, LD15, LD16, LD17
                          ( index == 54+0 ) ||
                          ( index == 54+7 ) ||
                          ( index == 54+8 ) ||
                          ( index == 54+9 ) ||
                          ( index == 54+15 ) ||
                          ( index == 54+16 ) ||
                          ( index == 54+17 ) );
#elif defined(RGB_BACKLIGHT_M10_C)
        bool enabled = true;
#elif defined(RGB_BACKLIGHT_PORTICO)
        bool enabled = true;
#endif
        // This only caches it for later
        is31fl3731_set_led_control_register( index, enabled, enabled, enabled );
    }
    // This actually updates the LED drivers
    // TODO: refactor this to use DRIVER_COUNT
    is31fl3731_update_led_control_registers( ISSI_ADDR_1, 0 );
#if !defined(RGB_BACKLIGHT_NEBULA12) && !defined(RGB_BACKLIGHT_M10_C)
    is31fl3731_update_led_control_registers( ISSI_ADDR_2, 1 );
#endif
#if defined(RGB_BACKLIGHT_U80_A)
    is31fl3731_update_led_control_registers( ISSI_ADDR_3, 2 );
#endif
#endif

    // TODO: put the 1 second startup delay here?

    // clear the key hits
    for ( int led=0; led<BACKLIGHT_LED_COUNT; led++ )
    {
        g_key_hit[led] = 255;
    }
}

bool process_record_backlight(uint16_t keycode, keyrecord_t *record)
{
    // Record keypresses for backlight effects
    if ( record->event.pressed )
    {
        backlight_set_key_hit( record->event.key.row, record->event.key.col );
    }

    switch(keycode)
    {
        case BR_INC:
            if (record->event.pressed)
            {
                backlight_brightness_increase();
            }
            return false;
            break;
        case BR_DEC:
            if (record->event.pressed)
            {
                backlight_brightness_decrease();
            }
            return false;
            break;
        case EF_INC:
            if (record->event.pressed)
            {
                backlight_effect_increase();
            }
            return false;
            break;
        case EF_DEC:
            if (record->event.pressed)
            {
                backlight_effect_decrease();
            }
            return false;
            break;
        case ES_INC:
            if (record->event.pressed)
            {
                backlight_effect_speed_increase();
            }
            return false;
            break;
        case ES_DEC:
            if (record->event.pressed)
            {
                backlight_effect_speed_decrease();
            }
            return false;
            break;
        case H1_INC:
            if (record->event.pressed)
            {
                backlight_color_1_hue_increase();
            }
            return false;
            break;
        case H1_DEC:
            if (record->event.pressed)
            {
                backlight_color_1_hue_decrease();
            }
            return false;
            break;
        case S1_INC:
            if (record->event.pressed)
            {
                backlight_color_1_sat_increase();
            }
            return false;
            break;
        case S1_DEC:
            if (record->event.pressed)
            {
                backlight_color_1_sat_decrease();
                break;
            }
            return false;
            break;
        case H2_INC:
            if (record->event.pressed)
            {
                backlight_color_2_hue_increase();
            }
            return false;
            break;
        case H2_DEC:
            if (record->event.pressed)
            {
                backlight_color_2_hue_decrease();
            }
            return false;
            break;
        case S2_INC:
            if (record->event.pressed)
            {
                backlight_color_2_sat_increase();
            }
            return false;
            break;
        case S2_DEC:
            if (record->event.pressed)
            {
                backlight_color_2_sat_decrease();
                break;
            }
            return false;
            break;
    }

    return true;
}

// Deals with the messy details of incrementing an integer
uint8_t increment( uint8_t value, uint8_t step, uint8_t min, uint8_t max )
{
    int16_t new_value = value;
    new_value += step;
    return MIN( MAX( new_value, min ), max );
}

uint8_t decrement( uint8_t value, uint8_t step, uint8_t min, uint8_t max )
{
    int16_t new_value = value;
    new_value -= step;
    return MIN( MAX( new_value, min ), max );
}

void backlight_effect_increase(void)
{
    g_config.effect = increment( g_config.effect, 1, 0, BACKLIGHT_EFFECT_MAX );
    backlight_config_save();
}

void backlight_effect_decrease(void)
{
    g_config.effect = decrement( g_config.effect, 1, 0, BACKLIGHT_EFFECT_MAX );
    backlight_config_save();
}

void backlight_effect_speed_increase(void)
{
    g_config.effect_speed = increment( g_config.effect_speed, 1, 0, 3 );
    backlight_config_save();
}

void backlight_effect_speed_decrease(void)
{
    g_config.effect_speed = decrement( g_config.effect_speed, 1, 0, 3 );
    backlight_config_save();
}

void backlight_brightness_increase(void)
{
    g_config.brightness = increment( g_config.brightness, 8, 0, 255 );
    backlight_config_save();
}

void backlight_brightness_decrease(void)
{
    g_config.brightness = decrement( g_config.brightness, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_1_hue_increase(void)
{
    g_config.color_1.h = increment( g_config.color_1.h, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_1_hue_decrease(void)
{
    g_config.color_1.h = decrement( g_config.color_1.h, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_1_sat_increase(void)
{
    g_config.color_1.s = increment( g_config.color_1.s, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_1_sat_decrease(void)
{
    g_config.color_1.s = decrement( g_config.color_1.s, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_2_hue_increase(void)
{
    g_config.color_2.h = increment( g_config.color_2.h, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_2_hue_decrease(void)
{
    g_config.color_2.h = decrement( g_config.color_2.h, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_2_sat_increase(void)
{
    g_config.color_2.s = increment( g_config.color_2.s, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_2_sat_decrease(void)
{
    g_config.color_2.s = decrement( g_config.color_2.s, 8, 0, 255 );
    backlight_config_save();
}

#if defined(RGB_DEBUGGING_ONLY)
void backlight_test_led( uint8_t index, bool red, bool green, bool blue )
{
    for ( int i=0; i<BACKLIGHT_LED_COUNT; i++ )
    {
        if ( i == index )
        {
            is31fl3731_set_led_control_register( i, red, green, blue );
        }
        else
        {
            is31fl3731_set_led_control_register( i, false, false, false );
        }
    }
}

void backlight_debug_led( bool state )
{
    if (state)
    {
        // Output high.
        DDRE |= (1<<6);
        PORTE |= (1<<6);
    }
    else
    {
        // Output low.
        DDRE &= ~(1<<6);
        PORTE &= ~(1<<6);
    }
}
#endif // defined(RGB_DEBUGGING_ONLY)

void backlight_device_indication(uint8_t value)
{
    static uint8_t current_effect = 0;
    static uint8_t alternate_effect = 0;
    if ( value == 0 ) {
        current_effect = g_config.effect;
        alternate_effect = g_config.effect > 0 ? 0 : 1;
    }
    g_config.effect = value % 2 == 0 ? alternate_effect : current_effect;
}
