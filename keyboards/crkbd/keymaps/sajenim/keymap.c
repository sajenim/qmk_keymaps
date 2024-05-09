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

// Awesome features created by getreuer
#include "features/sentence_case.h"
#include "features/achordion.h"
#include "features/select_word.h"
#include "features/layer_lock.h"
// https://github.com/getreuer/qmk-keymap/tree/main/features

// Our super useful layers, why we run qmk exclusively.
enum layers {
  CANARY, // This layout is the result of collaboration between many of the top layout creators from the AKL community.
  NAV,    // Inspired by the colemak communities extend layer, Brings navigation and editing to the home position.
  NUM,    // Contains our numpad and function keys.
  SYM,    // Contains our symbols.
  MOD,    // Contains keyboard related modifications.
};

// Combo dictionary management (layer names must be defined before engine include)
#include "g/keymap_combo.h"

// Our custom keycodes
enum custom_keycodes {
  SC_TOGG = SAFE_RANGE,
  LLOCK,
  SELWORD,

  // Magic keycodes
  MG_THE,
  MG_BUT,
  MG_BEFORE,
  MG_JUST,
  MG_MENT,
  MG_NION,
  MG_TMENT,
  MG_WHICH,
  MG_XES,
};

// This keymap uses Magic Canary, it is inspired by Ikcelaks' Magic Sturdy layout.
// The magic key is triggered with the fn combo. Currently only SFB and some common words are considered.
// https://github.com/Ikcelaks/keyboard_layouts

// This keymap uses home row mods. In addition to mods, I have home row
// layer-tap keys for the SYM layer. The key arrangement is a variation on
// "GASC-order" home row mods:
//
//             Left hand                          Right hand
// +-------+-------+-------+-------+   +-------+-------+-------+-------+
// |  Gui  |  Alt  | Shift |  Ctrl |   |  Ctrl | Shift |  Alt  |  Gui  |
// +-------+-------+-------+-------+   +-------+-------+-------+-------+
//                         |  Sym  |   |  Sym  |
//                         +-------+   +-------+

// Left hand home row mods for CANARY layer.
#define HRM_C   LGUI_T(KC_C)
#define HRM_R   LALT_T(KC_R)
#define HRM_S   LSFT_T(KC_S)
#define HRM_T   LCTL_T(KC_T)
// Right hand home row mods for CANARY layer.
#define HRM_N   RCTL_T(KC_N)
#define HRM_E   RSFT_T(KC_E)
#define HRM_I   RALT_T(KC_I)
#define HRM_A   RGUI_T(KC_A)
// Bottom row mods for CANARY layer.
#define HRM_D   LT(SYM, KC_D)
#define HRM_H   LT(SYM, KC_H)

// Oneshot mods are available on our navigation layer.
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

// Dual role keys allow us to save space on our keymap
// by having different functions in each the tap and hold slots.
// Excluded from bilateral combinations.
#define SPC_NAV LT(NAV, KC_SPC)
#define ENT_SFT LSFT_T(KC_ENT)
#define BAK_NUM LT(NUM, KC_BSPC)

// Shortcuts
#define CK_UNDO LCTL(KC_Z)        // Undo
#define CK_CUT  LCTL(KC_X)        // Cut
#define CK_COPY LCTL(KC_C)        // Copy
#define CK_PSTE LCTL(KC_V)        // Paste

#define DELWORD LCTL(KC_BSPC)     // Delete word
#define WZ_CMOD LCTL(LSFT(KC_X))  // Wezterm activate copy mode.
#define WZ_PSTE LCTL(LSFT(KC_V))  // Wezterm paste from clipboard.

//Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [CANARY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,    KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,                         KC_Z,    KC_F,    KC_O,    KC_U, KC_QUOT, DELWORD,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   HRM_C,   HRM_R,   HRM_S,   HRM_T,    KC_G,                         KC_M,   HRM_N,   HRM_E,   HRM_I,   HRM_A, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Q,    KC_J,    KC_V,   HRM_D,    KC_K,                         KC_X,   HRM_H, KC_SLSH, KC_COMM,  KC_DOT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_TAB, BAK_NUM, SPC_NAV,    ENT_SFT,  QK_REP, SELWORD
                                      //`--------------------------'  `--------------------------'
  ),

  [NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, KC_VOLU,                      WZ_CMOD, KC_HOME,   KC_UP,  KC_END, KC_PGUP,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, KC_VOLD,                      WZ_PSTE, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, CK_UNDO,  CK_CUT, CK_COPY, CK_PSTE, KC_CALC,                         KC_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, _______,    _______, _______, _______
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
                                          XXXXXXX, _______, XXXXXXX,    _______, _______, _______
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

  [MOD] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      QK_MAKE, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,                      XXXXXXX, CM_TOGG, AS_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       QK_RBT, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,                      XXXXXXX, SC_TOGG, AC_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
};

// Bilateral combination exceptions
bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record) {
  switch (tap_hold_keycode) {
    // Excempt some mod/layer taps.
    case SPC_NAV:
    case ENT_SFT:
    case BAK_NUM:
      return true;
      break;
  }

  // Otherwise follow opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
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

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
  switch (keycode) {
    // Minimize SFB on canary layout
    case HRM_R:   return KC_L;
    case KC_V:    return KC_Y;
    case HRM_S:   return KC_Y;
    case KC_Y:    return KC_S;
    case KC_P:    return KC_T;
    case HRM_I:   return KC_U;
    case KC_U:    return KC_I;
    case KC_O:    return KC_E;
    case HRM_E:   return KC_O;
    // Remove problem scissors bigrams
    case KC_L:    return KC_V;

    // Briefs
    case SPC_NAV: return MG_THE;
    case KC_COMM: return MG_BUT;
    case KC_B:    return MG_BEFORE;
    case KC_J:    return MG_JUST;
    case KC_M:    return MG_MENT;
    case HRM_N:   return MG_NION;
    case HRM_T:   return MG_TMENT;
    case KC_W:    return MG_WHICH;
    case KC_X:    return MG_XES;

    // vim optimisations
    case HRM_C:   return KC_W; // change word
    case HRM_D:   return KC_W; // delete word
  }

  return KC_TRNS;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_sentence_case(keycode, record)) { return false; }
  if (!process_achordion(keycode, record)) { return false; }
  if (!process_select_word(keycode, record, SELWORD)) { return false; }
  if (!process_layer_lock(keycode, record, LLOCK)) { return false; }
  
  if (record->event.pressed) {
    int rep_count = get_repeat_key_count();
    // Define the behaviour of our custom keycodes.
    switch (keycode) {
      case SC_TOGG: // Toggle sentence case on/off.
        sentence_case_toggle();
        return false;
      // Magic key briefs
      case MG_THE:
        SEND_STRING(/* */"the");
        return false;
      case MG_BUT:
        SEND_STRING(/*,*/" but");
        return false;
      case MG_BEFORE:
        SEND_STRING(/*b*/"efore");
        return false;
      case MG_JUST:
        SEND_STRING(/*j*/"ust");
        return false;
      case MG_MENT:
        SEND_STRING(/*m*/"ent");
        return false;
      case MG_NION:
        SEND_STRING(/*n*/"ion");
        return false;
      case MG_TMENT:
        SEND_STRING(/*t*/"ment");
        return false;
      case MG_WHICH:
        SEND_STRING(/*w*/"hich");
        return false;
      case MG_XES:
        SEND_STRING(/*x*/"es");
        return false;
    }
    if (rep_count > 0) {
      // Repeat key overrides.
      switch (keycode) {
        // Minimize SFB on canary layout
        case HRM_N: SEND_STRING(/*n*/"f"); return false;
        // Briefs
        case SPC_NAV:
          SEND_STRING(/* */"for");
          return false;
        case KC_COMM:
          SEND_STRING(/*,*/" and");
          return false;
        case HRM_A:
          SEND_STRING(/*a*/"nd");
          return false;
        case HRM_I:
          SEND_STRING(/*i*/"ng");
          return false;
        case KC_Y:
          SEND_STRING(/*y*/"ou");
          return false;
        case KC_B:
          SEND_STRING(/*b*/"ecause");
          return  false;
        case KC_W:
          SEND_STRING(/*w*/"ould");
          return false;
      }
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
