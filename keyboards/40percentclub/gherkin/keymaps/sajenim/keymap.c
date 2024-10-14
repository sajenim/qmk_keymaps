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

#define REPEAT QK_REP
#define MAGIC  QK_AREP

enum custom_keycodes {
  MG_OR = SAFE_RANGE,
  MG_AS,
  MG_ON,
  MG_ER,
  MG_HA,
  MG_BUT,
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

#define NAV_BAK LT(NAV, KC_BSPC)
#define NUM_SPC LT(NUM, KC_SPC)
#define SYM_F   LT(SYM, KC_F)
#define SYM_DOT LT(SYM, KC_DOT)

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [GALLIUM] = LAYOUT_ortho_3x10(
    //,-----------------------------------------------------------------------------------------.
           KC_B,    KC_L,    KC_D,  REPEAT,    KC_V,    KC_K,   MAGIC,    KC_O,    KC_U, KC_COMM,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
          HRM_N,   HRM_R,   HRM_T,   HRM_S,    KC_G,    KC_P,   HRM_H,   HRM_A,   HRM_E,   HRM_I,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
          SYM_F,    KC_W,    KC_M, NAV_BAK,    KC_C,    KC_Y, NUM_SPC, KC_QUOT, KC_QUES, SYM_DOT
    //`-----------------------------------------------------------------------------------------'
  ),

  [NAV] = LAYOUT_ortho_3x10(
    //,-----------------------------------------------------------------------------------------.
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_DEL,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,  KC_SPC,  KC_TAB, XXXXXXX,  KC_ENT
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
         KC_GRV, KC_LABK, KC_RABK, KC_MINS, XXXXXXX, XXXXXXX, KC_PLUS, KC_LBRC, KC_RBRC, KC_UNDS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_EXLM, KC_LPRN, KC_RPRN,  KC_EQL, KC_HASH, KC_PERC,  KC_DLR, KC_LCBR, KC_RCBR, KC_SCLN,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_COLN, KC_CIRC,   KC_AT,  KC_DLR, XXXXXXX, XXXXXXX, KC_SLSH, KC_ASTR, KC_BSLS, KC_PIPE
    //`-----------------------------------------------------------------------------------------'
  ),
};

// clang-format on

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

/* Alternate repeat key:
 * dynamically adjust output based on the most recent previous keycode */

// clang-format off
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
  switch (keycode) {
    case HRM_R: return KC_L;    // "RL" sfb (0.114%)
    case  KC_G: return KC_S;    // "GS" sfb (0.102%)
    case  KC_U: return KC_E;    // "UE" sfb (0.090%)
    case HRM_S: return KC_C;    // "SC" sfb (0.084%)
    case  KC_L: return KC_W;    // "LW" sfb (0.042%)
    case  KC_O: return KC_A;    // "OA" sfb (0.041%)
    case  KC_W: return KC_R;    // "WR" sfb (0.040%)
    case HRM_N: return KC_F;    // "NF" sfb (0.036%)
    case HRM_E: return KC_QUES; // "E?" sfb (0.035%)

    // Magic Keycodes
    case   SYM_F: return MG_OR;
    case   HRM_I: return MG_ON;
    case    KC_V: return MG_ER;
    case   HRM_T: return MG_HA;
    case KC_COMM: return MG_BUT;
  }
  return KC_TRNS;
}
// clang-format on

/* Custom keycodes:
 * Program the behaviour of any keycode */

// clang-format off
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    int rep_count = get_repeat_key_count();
    switch (keycode) {
      case  MG_OR: SEND_STRING(/*f*/ "or"  ); return false; // "for"   trigram (1.181%)
      case  MG_ON: SEND_STRING(/*i*/ "on"  ); return false; // "ion"   trigram (0.851%)
      case  MG_ER: SEND_STRING(/*v*/ "er"  ); return false; // "ver"   trigram (1.273%)
      case  MG_HA: SEND_STRING(/*t*/ "ha"  ); return false; // "tha"   trigram (1.864%)
      case MG_BUT: SEND_STRING(/*,*/ " but"); return false; // ", but" brief
    }
    if (rep_count > 0) {
      switch (keycode) {
        case   HRM_H: SEND_STRING(/*h*/ "y"   ); return false; // "HY"    sfb     (0.050%)
        case   HRM_A: SEND_STRING(/*a*/ "nd"  ); return false; // "and"   trigram (3.293%)
        case   HRM_I: SEND_STRING(/*i*/ "ng"  ); return false; // "ing"   trigram (3.476%)
        case    KC_Y: SEND_STRING(/*y*/ "ou"  ); return false; // "you"   trigram (3.492%)
        case KC_COMM: SEND_STRING(/*,*/ " and"); return false; // ", and" brief
        case NUM_SPC: SEND_STRING(/* */ "the" ); return false; // " the"  brief
      }
    }
  }
  return true;
}
// clang-format on
