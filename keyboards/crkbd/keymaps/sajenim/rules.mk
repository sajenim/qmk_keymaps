# We are using a Splinky RP2040 as a drop-in replacement controller
CONVERT_TO = promicro_rp2040
BOOTLOADER = rp2040

# Default features 
LTO_ENABLE = yes

# Optional features
OLED_ENABLE 				= yes
RGBLIGHT_ENABLE			= yes
# Toggleable through keymap
AUTO_SHIFT_ENABLE		= yes
AUTOCORRECT_ENABLE	= yes
CAPS_WORD_ENABLE  	= yes
COMBO_ENABLE 				= yes

SRC += process_record.c
SRC += features/sentence_case.c

ifeq ($(OLED_ENABLE),yes)
	SRC += ./oled.c
	OLED_DRIVER = SSD1306
	WPM_ENABLE = yes
endif

ifeq ($(COMBO_ENABLE),yes)
	VPATH += keyboards/gboards
endif
