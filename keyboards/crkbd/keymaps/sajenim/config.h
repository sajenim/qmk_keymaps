#pragma once

// By default, the firmware does not know which side is which.
#define MASTER_LEFT

// Alternate way in QMK to enter the embedded mass storage UF2 boot-loader.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

// Tap-Hold configuration for home row mods.
#define TAPPING_TERM 175
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 0

// Timeouts
#define ONESHOT_TIMEOUT        3000
#define CAPS_WORD_IDlE_TIMEOUT 3000

// Combo keys are always checked from layer 0.
#define COMBO_ONLY_FROM_LAYER 0

// Oled font to use.
#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP  10
#define RGBLIGHT_SAT_STEP  17
#define RGBLIGHT_VAL_STEP  17
#endif
