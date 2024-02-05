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
DYNAMIC_MACRO_ENABLE	= yes
LEADER_ENABLE					= yes
MOUSEKEY_ENABLE				= yes
OLED_ENABLE						= yes
REPEAT_KEY_ENABLE			= yes
RGBLIGHT_ENABLE				= yes

# Feature libraries
SRC += features/sentence_case.c

# Behaviour of our custom keycodes
SRC += process_record.c

# Oled display configuration
ifeq ($(OLED_ENABLE),yes)
	SRC += ./oled.c
	OLED_DRIVER = ssd1306
	WPM_ENABLE = yes
endif

# Combo dictionary
ifeq ($(COMBO_ENABLE),yes)
	VPATH += keyboards/gboards
endif

# Leader key dictionary
ifeq ($(LEADER_ENABLE),yes)
	SRC += ./leader.c
endif
