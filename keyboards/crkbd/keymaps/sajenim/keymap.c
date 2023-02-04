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
#include "keycodes.h"

/* Enumeration */

enum layers {
  L_CANARY,
  L_LOWER,
  L_RAISE,
  L_ADJUST,
  L_NAVIGATION,
  L_SYMBOLS,
  L_NUMBERS,
  L_OPERATORS,
  L_MACRO
};

enum custom_keycodes {
  VI_SAVE = SAFE_RANGE,
  VI_EXIT,
  HOME,
  UPDIR
};

enum td_keycodes {
  YANK,
  PSTE
};

enum combos {
  NE_ESCAPE,
  SE_CAPWRD,
  COMBO_LENGTH
};


/* Tapdance */

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void yank_finished(qk_tap_dance_state_t *state, void *user_data);
void yank_reset(qk_tap_dance_state_t *state, void *user_data);

void pste_finished(qk_tap_dance_state_t *state, void *user_data);
void pste_reset(qk_tap_dance_state_t *state, void *user_data);


/* Combos */

// Programmatically declare the size of the Combo data structure
uint16_t COMBO_LEN = COMBO_LENGTH;

// Define key sequences
const uint16_t PROGMEM ne_combo[] = {HOME_N, HOME_E, COMBO_END};
const uint16_t PROGMEM se_combo[] = {HOME_S, HOME_E, COMBO_END};

// List the combination of keys and there resulting action
combo_t key_combos[] = {
  [NE_ESCAPE] = COMBO(ne_combo, KC_ESC),
  [SE_CAPWRD] = COMBO(se_combo, CW_TOGG),
};


/* Keymaps */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_CANARY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      PREFIX,    KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,                         KC_Z,    KC_F,    KC_O,    KC_U,  KC_QUOT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,  HOME_C,  HOME_R,  HOME_S,  HOME_T,    KC_G,                         KC_M,  HOME_N,  HOME_E,  HOME_I,  HOME_A,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       OS_MEH,    KC_Q,    KC_J,    KC_V,    KC_D,    KC_K,                         KC_X,    KC_H, KC_SLSH, KC_COMM,  KC_DOT, OS_HYPR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            LOWER, NUMBERS, SPACEFN,    ENTERFN, SYMBOLS,   RAISE
                                      //`--------------------------'  `--------------------------'

  ),

  [L_NAVIGATION] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,     KC_TAB, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [L_SYMBOLS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, KC_LABK,  KC_DLR, KC_RABK, XXXXXXX,                      XXXXXXX, KC_LBRC, KC_UNDS, KC_RBRC, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MINS, KC_BSLS, KC_LPRN, KC_DQUO, KC_RPRN, KC_HASH,                      KC_PERC, KC_LCBR,  KC_EQL, KC_RCBR, KC_PIPE, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, KC_COLN, KC_ASTR, KC_PLUS, XXXXXXX,                      XXXXXXX, KC_AMPR, KC_CIRC, KC_TILD, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [L_OPERATORS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [L_NUMBERS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_SLSH,    KC_7,    KC_8,    KC_9, KC_MINS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, XXXXXXX,                      KC_ASTR,    KC_4,    KC_5,    KC_6, KC_PLUS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_1,    KC_2,    KC_3,  KC_DOT, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,       KC_0, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [L_MACRO] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         HOME, XXXXXXX, XXXXXXX, TD_YANK, TD_PSTE, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   UPDIR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      DELWORD, XXXXXXX, XXXXXXX, VI_SAVE, VI_EXIT, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, ST_PSTE,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [L_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [L_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_MUTE,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX,                      KC_MSEL, KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, KC_SLEP,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_VOLU,   KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX,                      KC_WHOM, KC_WREF, KC_WSTP, KC_WBAK, KC_WFWD, KC_BRIU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_VOLD,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [L_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AS_TOGG,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AC_TOGG,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CM_TOGG,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
};


/* OLED */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;
  } else {
    return OLED_ROTATION_180;
  }
  return rotation;
}

void oled_render_master(void) {
    // Layer Status
    switch (get_highest_layer(layer_state)) {
      case L_CANARY:
          oled_write("CANRY", false);
          break;
      case L_LOWER:
          oled_write("LOWER", false);
          break;
      case L_RAISE:
          oled_write("RAISE", false);
          break;
      case L_ADJUST:
          oled_write("ADJST", false);
          break;
      case L_NAVIGATION:
          oled_write_ln(" NAV", false);
          break;
      case L_SYMBOLS:
          oled_write_ln(" SYM", false);
          break;
      case L_NUMBERS:
          oled_write_ln(" NUM", false);
          break;
      case L_OPERATORS:
          oled_write("OPER8", false);
          break;
      case L_MACRO:
          oled_write("MACRO", false);
          break;
      default:
          oled_write_ln(" UND", false);
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
    
    bool is_autoshift_enabled = get_autoshift_state();
    if (is_autoshift_enabled) {
        oled_write("as: *", false);
    } else {
        oled_write("as: .", false);
    }

    bool is_autocorrect_enabled = autocorrect_is_enabled();
    if (is_autocorrect_enabled) {
        oled_write("ac: *", false);
    } else {
        oled_write("ac: .", false);
    }

    if (is_combo_enabled()) {
        oled_write("cm: *", false);
    } else {
        oled_write("cm: .", false);
    }

    // Caps Word
    oled_write("-----", false);

    if (is_caps_word_on()) {
        oled_write("cap:*", false);
    } else {
        oled_write("cap:.", false);
    }
    
    // WPM Status
    char wpm_str [4];
    sprintf(wpm_str, "%03d", get_current_wpm());
    oled_set_cursor(1, 14);
    oled_write_ln(wpm_str, false);
    oled_write(" wpm", false);
}

void oled_render_slave(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_master();
    } else {
        oled_render_slave();
    }
    return false;
}
#endif // OLED_ENABLE


/* Custom Keycodes */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case VI_SAVE:
        if (record->event.pressed) {
            tap_code(KC_ESC);
            SEND_STRING(":w");
            tap_code(KC_ENT);
        }
        break;

    case VI_EXIT:
        if (record->event.pressed) {
            tap_code(KC_ESC);
            SEND_STRING(":q!");
            tap_code(KC_ENT);
        }
        break;

    case HOME:
        if (record->event.pressed) {
            SEND_STRING("cd ~/");
            tap_code(KC_ENT);
        }
        break;

    case UPDIR:
        if (record->event.pressed) {
            SEND_STRING("cd ../");
            tap_code(KC_ENT);
        }
        break;

    }
    return true;
};


/* Tapdance Functions */

// Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) {
        if (state->interrupted || !state->pressed) return TD_DOUBLE_TAP;
        else return TD_DOUBLE_HOLD;      
    }

    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

void yank_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_mods(MOD_BIT(KC_LCTL));
            register_code(KC_C);
            break;
        case TD_DOUBLE_TAP:
            register_mods(MOD_BIT(KC_LCTL));
            register_mods(MOD_BIT(KC_LSFT));
            register_code(KC_C);
            break;
        default:
            break;
    }
}

void yank_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_mods(MOD_BIT(KC_LCTL));
            unregister_code(KC_C);
            break;
        case TD_DOUBLE_TAP:
            unregister_mods(MOD_BIT(KC_LCTL));
            unregister_mods(MOD_BIT(KC_LSFT));
            unregister_code(KC_C);
            break;
        default:
            break;
    }
}

void pste_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_mods(MOD_BIT(KC_LCTL));
            register_code(KC_V);
            break;
        case TD_DOUBLE_TAP:
            register_mods(MOD_BIT(KC_LCTL));
            register_mods(MOD_BIT(KC_LSFT));
            register_code(KC_V);
            break;
        default:
            break;
    }
}

void pste_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_mods(MOD_BIT(KC_LCTL));
            unregister_code(KC_V);
            break;
        case TD_DOUBLE_TAP:
            unregister_mods(MOD_BIT(KC_LCTL));
            unregister_mods(MOD_BIT(KC_LSFT));
            unregister_code(KC_V);
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [YANK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, yank_finished, yank_reset),
    [PSTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pste_finished, pste_reset)
};


/* Add Home Row Mods to Auto Shift */

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        // Left hand home-row mods
        case HOME_C:
            return true;
        case HOME_R:
            return true;
        case HOME_S:
            return true;
        case HOME_T:
            return true;
        
        // Right hand home-row mods
        case HOME_N:
            return true;
        case HOME_E:
            return true;
        case HOME_I:
            return true;
        case HOME_A:
            return true;

        default:
            return false;
    }
}


/* Layer Change */

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, L_NUMBERS, L_SYMBOLS, L_OPERATORS);
    state = update_tri_layer_state(state, L_LOWER, L_RAISE, L_ADJUST);
    return state;
}


/* Post Init */

void keyboard_post_init_user(void) {
    autoshift_disable();
    autocorrect_enable();
}
