/* Copyright 2022 @ sajenim (https://github.com/sajenim)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// By default, the firmware does not know which side is which; it needs some help to determine that.
#define MASTER_LEFT

// Alternate way in QMK to enter the embedded mass storage UF2 boot-loader of the RP2040.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

// Tap-Hold Configuration Options
// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200
// Activate the modifier when another key is pressed and released while the mod-tap is held.
#define PERMISSIVE_HOLD
// Makes tap and hold keys (like Layer Tap) work better for fast typists
#define HOLD_ON_OTHER_KEY_PRESS
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

// Leader Key
#define LEADER_TIMEOUT 500
#define LEADER_NO_TIMEOUT
#define LEADER_PER_KEY_TIMING

// Combos
#define COMBO_TERM 50

