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

enum layers {
  CANARY,
  NAV,
  NUM,
  SYM,
  FUN,
};

#include "g/keymap_combo.h" // layer names must be defined before engine include

#define NAV_REP LT(NAV, QK_REP)
#define NUM_MAG LT(NUM, QK_AREP)

enum custom_keycodes {
  // Magic Keycodes
  MG_OR = SAFE_RANGE,
  MG_ON,
  MG_ER,
  MG_HA,
  MG_BUT
};

/* Home Row Mods:
 * https://precondition.github.io/home-row-mods */

#define HRM_C LSFT_T(KC_C)
#define HRM_R LCTL_T(KC_R)
#define HRM_S LALT_T(KC_S)
#define HRM_T LGUI_T(KC_T)
#define HRM_N RGUI_T(KC_N)
#define HRM_E RALT_T(KC_E)
#define HRM_I RCTL_T(KC_I)
#define HRM_A RSFT_T(KC_A)
#define HRM_D LT(SYM, KC_D)
#define HRM_H LT(SYM, KC_H)

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
#define WZ_PSTE LCTL(LSFT(KC_V)) // Wezterm paste from clipboard.

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [CANARY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_GESC,    KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,                         KC_Z,    KC_F,    KC_O,    KC_U, KC_QUOT, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,   HRM_C,   HRM_R,   HRM_S,   HRM_T,    KC_G,                         KC_M,   HRM_N,   HRM_E,   HRM_I,   HRM_A,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      OS_LSFT,    KC_Q,    KC_J,    KC_V,   HRM_D,    KC_K,                         KC_X,   HRM_H, KC_SLSH, KC_COMM,  KC_DOT, OS_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          OS_LGUI, NAV_REP, DELWORD,     KC_SPC, NUM_MAG, OS_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, KC_VOLU,                      WZ_CMOD, KC_HOME,   KC_UP,  KC_END, KC_PGUP,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, KC_VOLD,                      WZ_PSTE, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, CK_UNDO,  CK_CUT, CK_COPY, CK_PSTE, KC_CALC,                         KC_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, XXXXXXX,    _______, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_MINS,    KC_7,    KC_8,    KC_9, KC_SLSH,                      XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_PLUS,    KC_4,    KC_5,    KC_6, KC_ASTR,                      XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F11, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_0,    KC_1,    KC_2,    KC_3,  KC_DOT,                      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F12, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, _______,    XXXXXXX, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,  KC_GRV, KC_LABK, KC_MINS, KC_RABK, XXXXXXX,                      XXXXXXX, KC_LBRC, KC_UNDS, KC_RBRC, KC_PLUS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_EXLM, KC_LPRN,  KC_EQL, KC_RPRN, KC_HASH,                      KC_PERC, KC_LCBR,  KC_DLR, KC_RCBR, KC_SCLN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_COLN, KC_AMPR, KC_CIRC,   KC_AT, XXXXXXX,                      XXXXXXX, KC_ASTR, KC_SLSH, KC_BSLS, KC_PIPE, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [FUN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, XXXXXXX,    XXXXXXX, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};

// clang-format on

/* Repeat key:
 * Configure additional key */

bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
  switch (keycode) {
    case NAV_REP: return false;
    case NUM_MAG: return false;
    // Forget Shift on letter keys when Shift or AltGr are the only mods.
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
    case  KC_Y: return KC_S;     // "YS" sfb (0.123%)
    case HRM_E: return KC_O;     // "EO" sfb (0.121%)
    case HRM_R: return KC_L;     // "RL" sfb (0.114%)
    case  KC_U: return KC_I;     // "UI" sfb (0.073%)
    case  KC_O: return KC_E;     // "OE" sfb (0.060%)
    case  KC_P: return KC_T;     // "PT" sfb (0.050%)
    case HRM_N: return KC_F;     // "NF" sfb (0.036%)
    case HRM_S: return KC_Y;     // "SY" sfb (0.024%)
    case HRM_D: return KC_G;     // "DG" sfb (0.021%)
    
    // Magic Keycodes
    case    KC_F: return MG_OR;
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
  switch (keycode) {
    case NAV_REP:
      if (record->tap.count) {
        process_repeat_key(QK_REP, record);
        return false;
      }
    case NUM_MAG:
      if (record->tap.count) {
        process_repeat_key(QK_AREP, record);
        return false;
      }
  }

  if (record->event.pressed) {
    int rep_count = get_repeat_key_count();
    switch (keycode) {
      case   MG_OR: SEND_STRING(/*f*/ "or"  ); return false; // "for"   trigram (1.181%)
      case   MG_ON: SEND_STRING(/*i*/ "on"  ); return false; // "ion"   trigram (0.851%)
      case   MG_ER: SEND_STRING(/*v*/ "er"  ); return false; // "ver"   trigram (1.273%)
      case   MG_HA: SEND_STRING(/*t*/ "ha"  ); return false; // "tha"   trigram (1.864%)
      case  MG_BUT: SEND_STRING(/*,*/ " but"); return false; // ", but" brief
    }
    if (rep_count > 0) {
      switch (keycode) {
        case   HRM_A: SEND_STRING(/*a*/ "nd"  ); return false; // "and"   trigram (3.293%)
        case   HRM_I: SEND_STRING(/*i*/ "ng"  ); return false; // "ing"   trigram (3.476%)
        case    KC_Y: SEND_STRING(/*y*/ "ou"  ); return false; // "you"   trigram (3.492%)
        case KC_COMM: SEND_STRING(/*,*/ " and"); return false; // ", and" brief
        case  KC_SPC: SEND_STRING(/* */ "the" ); return false; // " the"  brief
      }
    }
  }
  return true;
}
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, NAV, NUM, FUN); }

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
    case FUN: oled_write(" FUN ", false); break;
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
