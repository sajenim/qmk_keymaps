/* Copyright 2022 @ Keychron (https://www.keychron.com)
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
  _BASE,
  _FN1,
  _FN2,
  _EXT,
};

#include "g/keymap_combo.h" // layer names must be defined before engine include

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

/* Shortcuts:
 * Some useful shortcuts such as copy paste */

#define CK_UNDO LCTL(KC_Z)       // Undo
#define CK_CUT  LCTL(KC_X)       // Cut
#define CK_COPY LCTL(KC_C)       // Copy
#define CK_PSTE LCTL(KC_V)       // Paste
#define DELWORD LCTL(KC_BSPC)    // Delete word
#define WZ_CMOD LCTL(LSFT(KC_X)) // Wezterm activate copy mode.
#define WZ_PSTE LCTL(LSFT(KC_V)) // Wezterm paste from clipboard

/* Extend:
 * https://colemakmods.github.io/ergonomic-mods/extend.html */
#define EXTEND MO(_EXT)

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ansi_61(
    QK_GESC, KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
    KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
    EXTEND,  KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,
    KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            KC_RSFT,
    KC_LCTL, KC_LGUI,  KC_LALT,                            KC_SPC,                             KC_RALT,  MO(_FN1), MO(_FN2), KC_RCTL),

  [_FN1] = LAYOUT_ansi_61(
    KC_GRV,  KC_BRID,  KC_BRIU, KC_NO,   KC_NO,   RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  RGB_MOD,
    RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, KC_APP,  KC_SCRL, KC_INS,   KC_PGUP,  KC_HOME,  _______,
    _______, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, KC_UP,   KC_PSCR, KC_PGDN,  KC_END,             _______,
    _______,           _______, _______, _______, _______, _______, NK_TOGG, KC_LEFT, KC_DOWN, KC_RIGHT, KC_DEL,             _______,
    _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______),

  [_FN2] = LAYOUT_ansi_61(
    KC_TILD, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,
    RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______,  _______,  _______,  _______,
    _______, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______,  _______,            _______,
    _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
    _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______),

  [_EXT] = LAYOUT_ansi_61(
    QK_BOOT, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   DELWORD,
    _______, KC_MPLY,  KC_MSTP, KC_MPRV, KC_MNXT, KC_VOLU, WZ_CMOD, KC_HOME, KC_UP,   KC_END,  KC_PGUP,  KC_DEL,   _______,  _______,
    _______, OS_LGUI,  OS_LALT, OS_LSFT, OS_LCTL, KC_VOLD, WZ_PSTE, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,  KC_BSPC,            _______,
    _______,           CK_UNDO, CK_CUT,  CK_COPY, CK_PSTE, KC_0,    KC_1,    KC_2,    KC_3,    KC_4,     KC_ENT,             _______,
    _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______)
};

// clang-format on
