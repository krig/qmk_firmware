CONSOLE_ENABLE = no
ENCODER_ENABLE = yes
EXTRAKEY_ENABLE = yes
LTO_ENABLE = no
MOUSEKEY_ENABLE = no
OLED_DRIVER = SSD1306
OLED_ENABLE = yes
RGBLIGHT_ENABLE = no

SRC += features/custom_shift_keys.c
SRC += features/krig_caps_word.c
SRC += layer_system.c
