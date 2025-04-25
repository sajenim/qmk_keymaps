/* Copyright 2024 @ sajenim (https://github.com/sajenim)
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

#include QMK_KEYBOARD_H

enum layers {
  MW5,
};

#include "g/keymap_combo.h" // layer names must be defined before engine include

/* Movement */
#define TH_UP   KC_W    // Throttle Up
#define TH_DOWN KC_S    // Throttle Down
#define TH_LEFT KC_A    // Throttle Left
#define TH_RGHT KC_D    // Throttle Right
#define TH_OFF  KC_X    // Full Stop
#define TH_JJ   KC_SPC  // Jump Jets
#define MV_CLUT KC_F    // Centre Legs Under Torso
#define TG_MASC KC_LALT // Toggle Masc
#define ZOOM    KC_Z    // Cycle Zoom

/* Weapons */
#define TARGET KC_R // Target Enemy
#define NIGHT  KC_N // Toggle Night Vision

/* Mech Functions */
#define INTRACT KC_E    // Interact
#define POWER   KC_P    // Toggle Mech Power
#define OVERIDE KC_O    // Toggel Heat Override
#define ARM_LOC KC_LSFT // Arm Lock
#define ASTRIKE KC_H    // Toggle Airstrike Scope
#define SWITCH  KC_Y    // Switch Mech
#define ECM     KC_J    // Toggle ECM Mode
#define GRID    KC_B    // Show Battlegrid

/* Mod Keybinds */
#define LAU_UAV KC_HOME    // YAML Launch UAV
#define CL_SHOT KC_INSERT  // YAML Cool Shot
#define MS_LBX  LCTL(KC_2) // Swith between cluster/slug
#define STEALTH KC_M       // Toggle Stealth

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [MW5] = LAYOUT_ortho_3x10(
    //,-----------------------------------------------------------------------------------------.
        ASTRIKE,  TARGET,   TH_UP, CL_SHOT,     ECM, XXXXXXX, XXXXXXX, XXXXXXX, OVERIDE,   POWER,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        ARM_LOC, TH_LEFT, TH_DOWN, TH_RGHT, STEALTH, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, INTRACT,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
         MS_LBX, TG_MASC,  TH_OFF, MV_CLUT,   TH_JJ, XXXXXXX,    GRID,   NIGHT, XXXXXXX,  SWITCH
    //`-----------------------------------------------------------------------------------------'
  ),
};

// clang-format on
