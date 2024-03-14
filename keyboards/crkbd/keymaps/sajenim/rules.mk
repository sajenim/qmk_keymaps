# We are using a Splinky RP2040 as a drop-in pro-micro replacement
CONVERT_TO = promicro_rp2040
BOOTLOADER = rp2040

# Reduce compiled size of firmware
LTO_ENABLE = yes

# Software features
AUTOCORRECT_ENABLE		= yes
AUTO_SHIFT_ENABLE			= yes
CAPS_WORD_ENABLE			= yes
COMBO_ENABLE					= yes
OLED_ENABLE						= yes
REPEAT_KEY_ENABLE			= yes
RGBLIGHT_ENABLE				= yes


# Feature libraries
SRC += features/sentence_case.c
SRC += features/achordion.c
SRC += features/select_word.c

# Oled display configuration
ifeq ($(OLED_ENABLE),yes)
	OLED_DRIVER = ssd1306
	WPM_ENABLE = yes
endif

# Combo dictionary
ifeq ($(COMBO_ENABLE),yes)
	VPATH += keyboards/gboards
endif

