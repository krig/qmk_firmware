#pragma once

#include "quantum.h"

/*
 * To use:
 * Add to rules.mk:
 * SRC += features/krig_caps_word.c
 *
 * Add
 *
 * bool caps_word_press_user(uint16_t keycode) {
 *   return krig_caps_word_press(keycode);
 * }
 */

void krig_clear_caps_word_last_key(void);
bool krig_caps_word_press(uint16_t keycode);
