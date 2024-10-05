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
  GALLIUM,
  NAV,
  NUM,
  SYM,
};

#include "g/keymap_combo.h" // layer names must be defined before engine include

enum custom_keycodes {
  HOME = SAFE_RANGE,
  UPDIR,
};

/* Home Row Mods:
 * https://precondition.github.io/home-row-mods */

#define HRM_N LGUI_T(KC_N)
#define HRM_R LALT_T(KC_R)
#define HRM_T LSFT_T(KC_T)
#define HRM_S LCTL_T(KC_S)
#define HRM_H RCTL_T(KC_H)
#define HRM_A RSFT_T(KC_A)
#define HRM_E RALT_T(KC_E)
#define HRM_I RGUI_T(KC_I)

/* One Shot Keys:
 * https://github.com/qmk/qmk_firmware/blob/master/docs/one_shot_keys.md */

#define OS_LCTL OSM(MOD_LCTL)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_RALT OSM(MOD_RALT)
#define OS_RGUI OSM(MOD_RGUI)

/* Mod Tap:
 * https://github.com/qmk/qmk_firmware/blob/master/docs/mod_tap.md */

#define NAV_W   LT(NAV, KC_W)
#define NUM_F   LT(NUM, KC_F)
#define SYM_X   LT(SYM, KC_X)
#define SYM_ENT LT(SYM, KC_ENT)

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [GALLIUM] = LAYOUT_ortho_3x10(
    //,-----------------------------------------------------------------------------------------.
           KC_B,    KC_L,    KC_D,    KC_C,    KC_V,    KC_J,    KC_Y,    KC_O,    KC_U,  QK_REP,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
          HRM_N,   HRM_R,   HRM_T,   HRM_S,    KC_G,    KC_P,   HRM_H,   HRM_A,   HRM_E,   HRM_I,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
          SYM_X,    KC_Q,    KC_M,   NAV_W, KC_BSPC,  KC_SPC,   NUM_F,    KC_K,    KC_Z, SYM_ENT
    //`-----------------------------------------------------------------------------------------'
  ),

  [NAV] = LAYOUT_ortho_3x10(
    //,-----------------------------------------------------------------------------------------.
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_DEL,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_ENT
    //`-----------------------------------------------------------------------------------------'
  ),

  [NUM] = LAYOUT_ortho_3x10(
    //,-----------------------------------------------------------------------------------------.
        KC_SLSH,    KC_7,    KC_8,    KC_9, KC_MINS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_ASTR,    KC_4,    KC_5,    KC_6, KC_PLUS, XXXXXXX, OS_RCTL, OS_RSFT, OS_RALT, OS_RGUI,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
           KC_0,    KC_1,    KC_2,    KC_3,  KC_DOT, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX
    //`-----------------------------------------------------------------------------------------'
  ),

  [SYM] = LAYOUT_ortho_3x10(
    //,-----------------------------------------------------------------------------------------.
         KC_GRV,   KC_AT, KC_CIRC, KC_AMPR,    HOME,   UPDIR, KC_ASTR, KC_MINS, KC_EXLM, KC_QUOT,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_BSLS, KC_LPRN, OS_LSFT, KC_RPRN, KC_PERC, KC_HASH, KC_LBRC, OS_RSFT, KC_RBRC, KC_SCLN,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX,  KC_DLR, XXXXXXX, XXXXXXX,  KC_EQL, KC_SLSH, KC_COMM,  KC_DOT
    //`-----------------------------------------------------------------------------------------'
  ),
};

// clang-format on

/* Custom keycodes:
 * Program the behaviour of any keycode */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case HOME:
      if (record->event.pressed) {
        SEND_STRING("~/");
      }
      return false;
    case UPDIR:
      if (record->event.pressed) {
        SEND_STRING("../");
      }
      return false;
  }
  return true;
}

/* Repeat key:
 * Configure additional keys to be ignored */

bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
  // Forget Shift on letter keys when Shift or AltGr are the only mods.
  switch (keycode) {
    case KC_A ... KC_Z:
      if ((*remembered_mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT))) == 0) {
        *remembered_mods &= ~MOD_MASK_SHIFT;
      }
      break;
  }
  return true;
}
