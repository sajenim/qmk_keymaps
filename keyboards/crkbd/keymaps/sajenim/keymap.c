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

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "config.h"
#include "features/sentence_case.h"
#include "process_record.h"
#include "g/keymap_combo.h"
#include "layers.h"

/* Keymaps */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_CANARY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_LEAD,    KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,                         KC_Z,    KC_F,    KC_O,    KC_U, KC_QUOT, DELWORD,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TABCTRL,    KC_C,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_A, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      OS_LSFT,    KC_Q,    KC_J,    KC_V,    KC_D,    KC_K,                         KC_X,    KC_H, KC_SLSH, KC_COMM,  KC_DOT, OS_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          OS_LGUI, BAK_LWR, SPACEFN,    ENTERFN, DEL_RSE, OS_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [L_EXTEND] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_DEL, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, XXXXXXX,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, _______,    _______, WZ_CMOD, WZ_PSTE
                                      //`--------------------------'  `--------------------------'
  ),

  [L_MACRO] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, KC_WH_U, KC_MS_U, KC_WH_D, DM_REC1,                      DM_REC2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, DM_PLY1,                      DM_PLY2, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          ALTREP3, ALTREP2, QK_AREP,    _______, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [L_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_SLSH,    KC_7,    KC_8,    KC_9, KC_MINS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, XXXXXXX,                      KC_ASTR,    KC_4,    KC_5,    KC_6, KC_PLUS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_0,    KC_1,    KC_2,    KC_3, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, _______,    _______, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [L_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV, XXXXXXX, KC_LABK,  KC_DLR, KC_RABK, XXXXXXX,                      XXXXXXX, KC_LBRC, KC_UNDS, KC_RBRC, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MINS, KC_BSLS, KC_LPRN, KC_DQUO, KC_RPRN, KC_HASH,                      KC_PERC, KC_LCBR,  KC_EQL, KC_RCBR, KC_PIPE, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, KC_COLN, KC_ASTR, KC_PLUS, XXXXXXX,                      XXXXXXX, KC_AMPR, KC_CIRC, KC_TILD, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, _______,    _______, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [L_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      QK_BOOT, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,                      AS_TOGG, CM_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, KC_SLEP,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      QK_MAKE, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,                      AC_TOGG, SC_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, KC_WAKE,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, XXXXXXX,    XXXXXXX, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
};

/* Layer Change */

layer_state_t layer_state_set_user(layer_state_t state) {
  // Activate adjust layer
  state = update_tri_layer_state(state, L_LOWER, L_RAISE, L_ADJUST);
  return state;
}

/* Post Init */

void keyboard_post_init_user(void) {
    autoshift_disable();
    autocorrect_disable();
    combo_disable();
    sentence_case_off();
}

