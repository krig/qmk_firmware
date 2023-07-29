LTO_ENABLE = no
VIA_ENABLE = yes
BOOTLOADER = rp2040
CONVERT_TO = promicro_rp2040

SRC += features/custom_shift_keys.c
SRC += features/krig_caps_word.c
SRC += features/oneshot.c
SRC += features/swapper.c
