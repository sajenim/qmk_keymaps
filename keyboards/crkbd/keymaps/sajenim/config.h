#pragma once

// By default, the firmware does not know which side is which; it needs some help to determine that.
#define MASTER_LEFT

// Alternate way in QMK to enter the embedded mass storage UF2 boot-loader of the RP2040.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

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

// Auto Shift
#define AUTO_SHIFT_TIMEOUT 175
#define AUTO_SHIFT_REPEAT
#define AUTO_SHIFT_MODIFIERS

// Retro Shift
#define RETRO_SHIFT 500

// Caps Word
#define CAPS_WORD_IDLE_TIMEOUT 2000
