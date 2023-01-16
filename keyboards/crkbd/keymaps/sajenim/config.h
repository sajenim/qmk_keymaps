#pragma once

// By default, the firmware does not know which side is which; it needs some help to determine that.
#define MASTER_LEFT

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Activate the modifier when another key is pressed and released while the mod-tap is held.
#define PERMISSIVE_HOLD

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// One Shot Keys
#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 2000

// Caps Word
#define CAPS_WORD_IDLE_TIMEOUT 2000
