# Software features
COMBO_ENABLE = yes

# Combo dictionary
ifeq ($(COMBO_ENABLE),yes)
	VPATH += keyboards/gboards
endif
