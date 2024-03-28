#pragma once

// By default, the firmware does not know which side is which; it needs some help to determine that.
#define MASTER_LEFT

// Alternate way in QMK to enter the embedded mass storage UF2 boot-loader of the RP2040.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

// Enable QK_MAKE keycode
#define ENABLE_COMPILE_KEYCODE

// Tap-Hold configuration for home row mods.
#define TAPPING_TERM 175  // time window in which you need to release the key in order to register a tap
#define PERMISSIVE_HOLD   // activates the modifier when another key is pressed and released while the mod-tap is held, regardless of the tapping term
#define QUICK_TAP_TERM 0  // disable the auto-repeat feature entirely
#define ACHORDION_STREAK  // disables hold behaviors when in a typing streak

// Timeouts
#define ONESHOT_TIMEOUT 3000
#define CAPS_WORD_IDlE_TIMEOUT 3000

// combos' keys are always checked from layer 0
#define COMBO_ONLY_FROM_LAYER 0

// RGB
#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_SLEEP
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
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif
