# We are using a Splinky RP2040 as a drop-in pro-micro replacement
CONVERT_TO = helios
BOOTLOADER = rp2040

# Reduce compiled size of firmware
LTO_ENABLE = yes

# Software features
AUTOCORRECT_ENABLE = yes
CAPS_WORD_ENABLE	 = yes
COMBO_ENABLE			 = yes
REPEAT_KEY_ENABLE	 = yes

# Combo dictionary
ifeq ($(COMBO_ENABLE),yes)
	VPATH += keyboards/gboards
endif

