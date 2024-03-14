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

// Combo dictionary management
#include "g/keymap_combo.h"

// Awesome features created by getreuer
#include "features/sentence_case.h"
#include "features/achordion.h"
#include "features/select_word.h"
// https://github.com/getreuer/qmk-keymap/tree/main/features

// Our super useful layers, why we run qmk exclusively.
enum layers {
  CANARY, // This layout is the result of collaboration between many of the top layout creators from the AKL community.
  NAV,    // Inspired by the colemak communities extend layer, Brings navigation and editing to the home position.
  NUM,    // Contains our numpad and function keys.
  SYM,    // Contains our symbols.
  MOD,    // Contains keyboard related modifications (and FKEYs :eyeroll:).
};

// Our custom keycodes
enum custom_keycodes {
  SC_TOGG = SAFE_RANGE,
  SELWORD,
};

// This keymap uses home row mods. In addition to mods, I have home row
// layer-tap keys for the SYM layer. The key arrangement is a variation on
// "CAGS-order" home row mods:
//
//             Left hand                          Right hand
// +-------+-------+-------+-------+   +-------+-------+-------+-------+
// |  Ctrl |  Alt  |  Gui  | Shift |   | Shift |  Gui  |  Alt  | Ctrl  |
// +-------+-------+-------+-------+   +-------+-------+-------+-------+
// |  Sym  |                                                   |  Sym  |
// +-------+                                                   +-------+

// Left hand home row mods for CANARY layer.
#define HRM_C   LCTL_T(KC_C)
#define HRM_R   LALT_T(KC_R)
#define HRM_S   LGUI_T(KC_S)
#define HRM_T   LSFT_T(KC_T)
// Right hand home row mods for CANARY layer.
#define HRM_N   RSFT_T(KC_N)
#define HRM_E   RGUI_T(KC_E)
#define HRM_I   RALT_T(KC_I)
#define HRM_A   RCTL_T(KC_A)
// Bottom row home row mods for CANARY layer.
#define HRM_Q   LT(SYM, KC_Q)
#define HRM_DOT LT(SYM, KC_DOT)

// Oneshot mods are available on our navigation and numbers layer.
// This allows easy chords with typical window manager and terminal 
// bindings. Oneshot mods persist through layer changes.

// Left hand one shot keys.
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)
// Right hand one shot keys.
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_RALT OSM(MOD_RALT)
#define OS_RGUI OSM(MOD_RGUI)

// Dual role thumb keys allow us to save space on our keymap
// by having different functions in each the tap and hold slots.
#define SPC_NAV LT(NAV, KC_SPC)
#define ENT_NUM LT(NUM, KC_ENT)

// Shortcuts
#define CK_UNDO LCTL(KC_Z)        // Undo
#define CK_CUT  LCTL(KC_X)        // Cut
#define CK_COPY LCTL(KC_C)        // Copy
#define CK_PSTE LCTL(KC_V)        // Paste

#define WZ_CMOD LCTL(LSFT(KC_X))  // Wezterm activate copy mode.
#define WZ_PSTE LCTL(LSFT(KC_V))  // Wezterm paste from clipboard.

//Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [CANARY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,                         KC_Z,    KC_F,    KC_O,    KC_U, KC_QUOT, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,   HRM_C,   HRM_R,   HRM_S,   HRM_T,    KC_G,                         KC_M,   HRM_N,   HRM_E,   HRM_I,   HRM_A, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      OS_LSFT,   HRM_Q,    KC_J,    KC_V,    KC_D,    KC_K,                         KC_X,    KC_H, KC_SLSH, KC_COMM, HRM_DOT, OS_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           QK_REP, KC_BSPC, SPC_NAV,    ENT_NUM, OS_RSFT, QK_AREP
                                      //`--------------------------'  `--------------------------'
  ),

  [NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLU,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_DEL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, OS_LCTL, OS_LALT, OS_LGUI, OS_LSFT, KC_VOLD,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, CK_UNDO,  CK_CUT, CK_COPY, CK_PSTE, XXXXXXX,                      XXXXXXX, WZ_CMOD, WZ_PSTE, XXXXXXX,  KC_ENT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, _______,    _______, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,  KC_DEL,    KC_7,    KC_8,    KC_9, XXXXXXX,                      XXXXXXX, KC_PLUS, XXXXXXX, KC_MINS, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_BSPC,    KC_4,    KC_5,    KC_6, XXXXXXX,                      XXXXXXX, OS_RSFT, OS_RGUI, OS_RALT, OS_RCTL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_ENT,    KC_1,    KC_2,    KC_3, XXXXXXX,                      XXXXXXX, KC_ASTR, XXXXXXX, KC_BSLS,  KC_DOT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______,    KC_0,    _______, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
  [SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV, XXXXXXX, KC_LABK,  KC_DLR, KC_RABK, XXXXXXX,                      XXXXXXX, KC_LBRC, KC_UNDS, KC_RBRC, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MINS, KC_BSLS, KC_LPRN, KC_DQUO, KC_RPRN, KC_HASH,                      KC_PERC, KC_LCBR,  KC_EQL, KC_RCBR, KC_PIPE, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, KC_COLN, KC_ASTR, KC_PLUS, XXXXXXX,                      XXXXXXX, KC_AMPR, KC_CIRC, KC_TILD, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, XXXXXXX,    XXXXXXX, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [MOD] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      QK_BOOT, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,                      XXXXXXX, CM_TOGG, AS_TOGG, XXXXXXX, XXXXXXX, KC_SLEP,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      QK_MAKE, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,                      XXXXXXX, SC_TOGG, AC_TOGG, XXXXXXX, XXXXXXX, KC_WAKE,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, _______,    _______, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
};

// Layer change
layer_state_t layer_state_set_user(layer_state_t state) {
  // Activate MOD layer
  state = update_tri_layer_state(state, NAV, NUM, MOD);
  return state;
}

// Define the behaviour of our custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_sentence_case(keycode, record)) { return false; }
  if (!process_achordion(keycode, record)) { return false; }
  if (!process_select_word(keycode, record, SELWORD)) { return false; }

  if (record->event.pressed) {
    switch (keycode) {
      case SC_TOGG: // Toggle sentence case on/off.
        sentence_case_toggle();
        return false;
    }
  }

  return true;
}

void matrix_scan_user(void) {
  achordion_task();
}

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
  case CANARY:
    oled_write(" BAS ", false);
    break;
  case NAV:
    oled_write(" NAV ", false);
    break;
  case NUM:
    oled_write(" NUM ", false);
    break;
  case SYM:
    oled_write(" SYM ", false);
    break;
  case MOD:
    oled_write(" MOD ", false);
    break;
  default:
    oled_write(" UND ", false);
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

  bool autoshift_enabled = get_autoshift_state();
  if (autoshift_enabled) {
    oled_write("as: *", false);
  } else {
    oled_write("as: .", false);
  }

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

  bool sentence_case_enabled = is_sentence_case_on();
  if (sentence_case_enabled) {
    oled_write("sc: *", false);
  } else {
    oled_write("sc: .", false);
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
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
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
