#pragma once

// By default, the firmware does not know which side is which.
#define MASTER_LEFT

// Tap-Hold configuration for home row mods.
#define TAPPING_TERM 175
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 0

// Timeouts
#define ONESHOT_TIMEOUT        3000
#define CAPS_WORD_IDlE_TIMEOUT 3000

// Combo keys are always checked from layer 0.
#define COMBO_ONLY_FROM_LAYER 0
