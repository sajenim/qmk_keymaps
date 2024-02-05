#pragma once

// By default, the firmware does not know which side is which; it needs some help to determine that.
#define MASTER_LEFT

// Alternate way in QMK to enter the embedded mass storage UF2 boot-loader of the RP2040.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

// Enable QK_MAKE keycode
#define ENABLE_COMPILE_KEYCODE

// Tap-Hold Configuration Options
#define TAPPING_TERM 200

// One Shot Keys
#define ONESHOT_TAP_TOGGLE 3
#define ONESHOT_TIMEOUT 2000

// Auto Shift
#define AUTO_SHIFT_TIMEOUT 175

// Caps Word
#define CAPS_WORD_IDLE_TIMEOUT 2000

// Combos
#define COMBO_TERM 50

// Leader key
#define LEADER_TIMEOUT 500
#define LEADER_PER_KEY_TIMING
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
