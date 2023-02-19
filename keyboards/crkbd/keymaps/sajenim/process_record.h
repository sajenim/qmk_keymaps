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

#include "quantum.h"
#include "tapdance.h"

// Our custom keycodes
enum custom_keycodes {
  VI_SAVE = SAFE_RANGE,
  VI_EXIT,
  HOME,
  UPDIR
};

// Left-hand thumb key layers
#define LOWER   MO(L_LOWER)
#define FN_PFX  TD(TD_FNPFX)
#define FN_SPC  LT(L_NAVIGATION, KC_SPC)

// Right-hand thumb key layers
#define FN_ENT  LT(L_MACRO, KC_ENT)
#define FN_LDR  TD(TD_FNLDR)
#define RAISE   MO(L_RAISE)

// Left-hand home row mods
#define HOME_C  LGUI_T(KC_C)
#define HOME_R  LALT_T(KC_R)
#define HOME_S  LSFT_T(KC_S)
#define HOME_T  LCTL_T(KC_T)

// Right-hand home row mods
#define HOME_N  RCTL_T(KC_N)
#define HOME_E  RSFT_T(KC_E)
#define HOME_I  RALT_T(KC_I)
#define HOME_A  RGUI_T(KC_A)

// One Shot Keys
#define OS_MEH  OSM(MOD_MEH)
#define OS_SUPR OSM(MOD_LGUI)
#define OS_HYPR OSM(MOD_HYPR)

#define OS_LCTL OSM(MOD_LCTL)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)

#define OS_RCTL OSM(MOD_RCTL)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_RALT OSM(MOD_RALT)
#define OS_RGUI OSM(MOD_RGUI)

// Tap Dance
#define YANK TD(TD_YANK)
#define PSTE TD(TD_PSTE)
#define BAKWORD TD(TD_BAKWORD)
#define DELWORD TD(TD_DELWORD)

// Shortcuts
#define PREFIX  LCTL(KC_B)
#define ST_PSTE LSFT(KC_INSERT)

