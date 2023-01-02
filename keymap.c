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
#include "config.h"
#include "keycodes.h"

/* Define our layers */
enum layers {
    // Our default layouts
    _QWERTY,
    _CANARY,
    // Optimized dead-key positioning + homerow mods and a few misc features
    _MODCANARY,
    // layouts that enable extra functionality
    _SPACEFN,
    _FN1,
    _FN2,
};

/* Define our custom keycodes */
enum custom_keycodes {
  MOD_TOG = SAFE_RANGE,
};

/* Define our combo keycodes */
enum combos {
    NE_ESCAPE,
    SE_CAPSWRD,
    COMBO_LENGTH
};

// Programmatically declare the size of the Combo data structure
uint16_t COMBO_LEN = COMBO_LENGTH;

// Define key sequences
const uint16_t PROGMEM esc_combo[]     = {HOME_N, HOME_E, COMBO_END};
const uint16_t PROGMEM capswrd_combo[] = {HOME_S, HOME_E, COMBO_END};

// List the combination of keys and there resulting action
combo_t key_combos[] = {
  [NE_ESCAPE]  = COMBO(esc_combo, KC_ESC),
  [SE_CAPSWRD] = COMBO(capswrd_combo, CAPSWRD),
};

/* Define our keymaps */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /**
     * Qwerty
     *
     * The QWERTY design is based on a layout created for the Sholes and Glidden typewriter and sold to E. Remington and Sons in 1873.
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ + │ BKSPC │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ TAB │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ CAPS │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ ENTER  │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │ LSHIFT │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │  RSHIFT  │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │CTRL│GUI │ALT │          SPACE         │ALT │FN1 │FN2 │CTRL│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     */ 
    [_QWERTY] = LAYOUT_ansi_61(
        KC_ESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            KC_RSFT,
        KC_LCTL, KC_LGUI,  KC_LALT,                            KC_SPC,                             KC_RALT,  MO(_FN1), MO(_FN2), KC_RCTL),

     /**
     * Canary
     *
     * This layout is the result of collaboration between many of the top layout creators from the AKL (Alternate Keyboard Layout) community
     * Reflects a lot of different ideas and optimization strategies combined together into one.
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ BKSPC │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ TAB │ W │ L │ Y │ P │ K │ Z │ X │ O │ U │ ; │ [ │ ] │  \  │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ CAPS │ C │ R │ S │ T │ B │ F │ N │ E │ I │ A │ ' │ ENTER  │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │ LSHIFT │ J │ V │ D │ G │ Q │ M │ H │ / │ , │ . │  RSHIFT  │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │CTRL│GUI │ALT │          SPACE         │ALT │FN1 │FN2 │CTRL│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     */
    [_CANARY] = LAYOUT_ansi_61(
      KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
      KC_TAB,   KC_W,    KC_L,    KC_Y,    KC_P,    KC_K,    KC_Z,    KC_X,    KC_O,    KC_U,    KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_BSLS,
      KC_CAPS,  KC_C,    KC_R,    KC_S,    KC_T,    KC_B,    KC_F,    KC_N,    KC_E,    KC_I,    KC_A,     KC_QUOT,            KC_ENT,
      KC_LSFT,           KC_J,    KC_V,    KC_D,    KC_G,    KC_Q,    KC_M,    KC_H,    KC_SLSH, KC_COMM,  KC_DOT,             KC_RSFT,
      KC_LCTL,  KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,  MO(_FN1), MO(_FN2), KC_RCTL),

    /**
     * MODIFIERS + MISC FEATURES
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │ ` │   │   │   │   │   │   │   │   │   │   │   │   │       │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │ 
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ MOD4 │GUI│ALT│SFT│CTL│   │   │CTL│SFT│ALT│GUI│   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │        │   │   │   │   │   │   │   │   │   │   │          │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │HYPR│MEH │LEAD│         SPACEFN        │    │    │    │    │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     * Credit: https://precondition.github.io/home-row-mods
     *
     */
    [_MODCANARY] = LAYOUT_ansi_61(
      KC_GRV,   _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,
      _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,
      DK_MOD4,  HOME_C,   HOME_R,  HOME_S,  HOME_T,  _______, _______, HOME_N,  HOME_E,  HOME_I,  HOME_A,   _______,            _______,
      XXXXXXX,            _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            XXXXXXX,
      DK_HYPR,  DK_MEH,   QK_LEAD,                            SPACEFN,                            XXXXXXX,  _______,  _______,  XXXXXXX),

    /**
     * SPACEFN
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│DELWORD│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │     │   │   │   │   │   │   │HOM│END│PUP│PDN│   │   │     │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │GUI│ALT│SFT│CTL│   │   │LFT│DWN│UP │RGT│DEL│        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │        │   │   │INS│   │   │   │BAK│   │   │   │          │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │    │    │    │                        │    │    │    │    │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     * Credit: https://geekhack.org/index.php?topic=51069.0
     *
     */
    [_SPACEFN] = LAYOUT_ansi_61(
      XXXXXXX,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   DELWORD,
      XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_END,  KC_PGUP, KC_PGDN,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  KC_LGUI,  KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_DEL,             XXXXXXX,
      XXXXXXX,            XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,                            XXXXXXX,                            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),

    /**
     * Function 1
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│       │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │     │   │UP │   │   │   │   │   │   │   │   │   │   │     │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │LFT│DWN│RGT│   │   │   │   │   │   │   │   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │        │   │   │   │   │   │   │   │   │   │   │          │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │    │    │    │                        │    │    │    │    │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     */
    [_FN1] = LAYOUT_ansi_61(
      XXXXXXX,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   XXXXXXX,
      XXXXXXX,  XXXXXXX,  KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  KC_LEFT,  KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
      XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,                            XXXXXXX,                            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),

    /**
     * Function 2
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │MOD│   │   │   │   │   │   │   │   │   │   │   │   │BOOTLDR│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ RGB │   │   │   │   │   │   │   │   │   │   │   │   │     │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │   │   │   │   │   │   │   │   │   │   │   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │        │   │   │   │   │   │   │   │   │   │   │          │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │    │    │    │                        │    │    │    │    │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     */
    [_FN2] = LAYOUT_ansi_61(
      MOD_TOG,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  QK_BOOT,
      RGB_TOG,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
      XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,                            XXXXXXX,                            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),
};

/* Define the behaviour of our custom keycodes */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MOD_TOG:
            if (record->event.pressed && layer_state_is(_CANARY)) {
                layer_invert(_MODCANARY);
            }
            return false;
        default:
            return true;
    }
}

/* Custom layer handling */
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _MODCANARY:
            autoshift_enable();
            combo_enable();
            break;
        default:
            autoshift_disable();
            combo_disable();
            break;
    }
    return state;
};

/* Configure which keys are auto-shifted */
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        // Left-hand home row mods
        case HOME_C:
        case HOME_R:
        case HOME_S:
        case HOME_T:
        
        // Right-hand home row mods
        case HOME_N:
        case HOME_E:
        case HOME_I:
        case HOME_A:
           return true;
        default:
            return false;
    }
};

/* Configure our dip switch */
bool dip_switch_update_mask_user(uint32_t state) { 
    if (state & (1UL<<0) && state & (1UL<<1)) {
        layer_on(_QWERTY);
    } else {
        layer_clear();
    }
    if (state & (1UL<<0)) {
       layer_on(_CANARY);
    } else {
        layer_clear();
    }
    return true;
}
