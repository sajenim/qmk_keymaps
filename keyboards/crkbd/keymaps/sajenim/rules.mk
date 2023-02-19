# We are using a Splinky RP2040 as a drop-in replacement controller
CONVERT_TO = promicro_rp2040

# Bootloader selection
BOOTLOADER = rp2040

# Default features 
LTO_ENABLE = yes
OLED_DRIVER = SSD1306

# Toggleable through keymap
AUTO_SHIFT_ENABLE = yes
AUTOCORRECT_ENABLE = yes
CAPS_WORD_ENABLE = yes

# Optional features
OLED_ENABLE = yes
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = yes
# Only required if OLED_ENABLE = yes
WPM_ENABLE = yes

# Source required c files
SRC += ./process_record.c

# Contitionally source optional c files
ifeq ($(OLED_ENABLE),yes)
	SRC += ./oled.c
endif

ifeq ($(COMBO_ENABLE),yes)
	VPATH += keyboards/gboards
endif

ifeq ($(TAP_DANCE_ENABLE),yes)
	SRC += ./tapdance.c
endif

ifeq ($(LEADER_ENABLE),yes)
	SRC += ./leader.c
endif
