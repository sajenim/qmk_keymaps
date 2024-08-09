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
#include "features/achordion.h"

enum layers {
  CANARY,
  NAV,
  NUM,
  SYM,
  MOD,
};

#include "g/keymap_combo.h" // layer names must be defined before engine include

/* Home Row Mods:
 * https://precondition.github.io/home-row-mods */

#define MT_C LGUI_T(KC_C)
#define MT_R LALT_T(KC_R)
#define MT_S LSFT_T(KC_S)
#define MT_T LCTL_T(KC_T)
#define MT_N RCTL_T(KC_N)
#define MT_E RSFT_T(KC_E)
#define MT_I RALT_T(KC_I)
#define MT_A RGUI_T(KC_A)
#define LT_D LT(SYM, KC_D)
#define LT_H LT(SYM, KC_H)

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

#define SPC_NAV LT(NAV, KC_SPC)
#define BAK_NUM LT(NUM, KC_BSPC)

/* Shortcuts:
 * Some useful shortcuts such as copy paste */

#define CK_UNDO LCTL(KC_Z)       // Undo
#define CK_CUT  LCTL(KC_X)       // Cut
#define CK_COPY LCTL(KC_C)       // Copy
#define CK_PSTE LCTL(KC_V)       // Paste
#define DELWORD LCTL(KC_BSPC)    // Delete word
#define WZ_CMOD LCTL(LSFT(KC_X)) // Wezterm activate copy mode.
#define WZ_PSTE LCTL(LSFT(KC_V)) // Wezterm paste from clipboard.

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [CANARY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,    KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,                         KC_Z,    KC_F,    KC_O,    KC_U, KC_QUOT, DELWORD,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    MT_C,    MT_R,    MT_S,    MT_T,    KC_G,                         KC_M,    MT_N,    MT_E,    MT_I,    MT_A, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Q,    KC_J,    KC_V,    LT_D,    KC_K,                         KC_X,    LT_H, KC_SLSH, KC_COMM,  KC_DOT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           QK_REP, BAK_NUM, SPC_NAV,     KC_ENT, OS_LSFT, QK_AREP
                                      //`--------------------------'  `--------------------------'
  ),

  [NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, KC_VOLU,                      WZ_CMOD, KC_HOME,   KC_UP,  KC_END, KC_PGUP,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, KC_VOLD,                      WZ_PSTE, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, CK_UNDO,  CK_CUT, CK_COPY, CK_PSTE, KC_CALC,                         KC_0,    KC_1,    KC_2,    KC_3,    KC_4,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, _______,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,  KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,                      KC_SLSH,    KC_7,    KC_8,    KC_9, KC_MINS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,                      KC_ASTR,    KC_4,    KC_5,    KC_6, KC_PLUS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,                         KC_0,    KC_1,    KC_2,    KC_3,  KC_DOT,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
  [SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, KC_LABK,  KC_DLR, KC_RABK, XXXXXXX,                      XXXXXXX, KC_LBRC, KC_UNDS, KC_RBRC, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MINS, KC_BSLS, KC_LPRN, KC_DQUO, KC_RPRN, KC_HASH,                      KC_PERC, KC_LCBR,  KC_EQL, KC_RCBR, KC_PIPE, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, KC_COLN, KC_ASTR, KC_PLUS, XXXXXXX,                      XXXXXXX, KC_AMPR, KC_CIRC, KC_TILD, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
};

// clang-format on

/* Achordion:
 * https://getreuer.info/posts/keyboards/achordion/index.html */

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode,
                     keyrecord_t *other_record) {
  switch (tap_hold_keycode) {
    // Exceptionally consider the following chords as holds, even though they
    // are on the same hand.
    case SPC_NAV:
    case BAK_NUM: return true; break;
  }
  // Otherwise follow opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}

/* Custom keycodes:
 * Program the behaviour of any keycode */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_achordion(keycode, record)) {
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

/* Alternate repeat key:
 * dynamically adjust output based on the most recent previous keycode */

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
  switch (keycode) {
    case MT_R: return KC_L; // For "RL" bigram.
    case KC_V: return KC_Y; // For "VY" bigram.
    case MT_S: return KC_Y; // For "SY" bigram.
    case KC_Y: return KC_S; // For "YS" bigram.
    case KC_P: return KC_T; // For "PT" bigram.
    case MT_I: return KC_U; // For "IU" bigram.
    case KC_U: return KC_I; // For "UI" bigram.
    case KC_O: return KC_E; // For "OE" bigram.
    case MT_E: return KC_O; // For "EO" bigram.
  }
  return KC_TRNS;
}

/* Custom matrix scanning:
 * This function gets called at every matrix scan */

void matrix_scan_user(void) { achordion_task(); }

#ifdef OLED_ENABLE
// Declare screen rotation for each half
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;
  } else {
    return OLED_ROTATION_180;
  }
  return rotation;
}

// Setup the master screen
void oled_render_master(void) {
  // Layer Status
  switch (get_highest_layer(layer_state)) {
    case CANARY: oled_write(" BAS ", false); break;
    case NAV: oled_write(" NAV ", false); break;
    case NUM: oled_write(" NUM ", false); break;
    case SYM: oled_write(" SYM ", false); break;
    default: oled_write(" UND ", false);
  }

  // Mod Status
  uint8_t this_mod = get_mods();
  uint8_t this_osm = get_oneshot_mods();

  oled_write("-----", false);

  if ((this_mod | this_osm) & MOD_MASK_GUI) {
    oled_write("gui:*", false);
  } else {
    oled_write("gui:.", false);
  }

  if ((this_mod | this_osm) & MOD_MASK_ALT) {
    oled_write("alt:*", false);
  } else {
    oled_write("alt:.", false);
  }

  if ((this_mod | this_osm) & MOD_MASK_SHIFT) {
    oled_write("sft:*", false);
  } else {
    oled_write("sft:.", false);
  }

  if ((this_mod | this_osm) & MOD_MASK_CTRL) {
    oled_write("ctl:*", false);
  } else {
    oled_write("ctl:.", false);
  }

  // Feature Status
  oled_write("-----", false);

  bool autocorrect_enabled = autocorrect_is_enabled();
  if (autocorrect_enabled) {
    oled_write("ac: *", false);
  } else {
    oled_write("ac: .", false);
  }

  bool combo_enabled = is_combo_enabled();
  if (combo_enabled) {
    oled_write("cm: *", false);
  } else {
    oled_write("cm: .", false);
  }

  // WPM Status
  char wpm_str[4];
  sprintf(wpm_str, "%03d", get_current_wpm());
  oled_set_cursor(1, 14);
  oled_write_ln(wpm_str, false);
  oled_write(" wpm", false);
}

// Corne keyboard logo
void oled_render_logo(void) {
  static const char PROGMEM crkbd_logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
      0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa,
      0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5,
      0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
  oled_write_P(crkbd_logo, false);
}

// Render our screens
bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_render_master();
  } else {
    oled_render_logo();
  }
  return false;
}
#endif

/* vim: set foldmarker=#ifdef,#endif: */
/* vim: set foldmethod=marker: */
