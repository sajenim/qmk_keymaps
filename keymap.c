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
    _COLEMAK,
    _DVORAK,
    _CANARY,
    // Optimized dead-key positioning + homerow mods and a few misc features
    // Requires a layer per default layout for homerow mod combatiability
    _MODQWERTY,
    _MODCOLEMAK,
    _MODDVORAK,
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
     * Colemak-DH
     *
     * Designed to make typing more efficient and comfortable by placing the most frequently used letters of the English language on the home row.
     * Created on 1 January 2006, it is named after its inventor, Shai Coleman.
     *  
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ BKSPC │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ TAB │ Q │ W │ F │ P │ B │ J │ L │ U │ Y │ ; │ [ │ ] │  \  │ 
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ CAPS │ A │ R │ S │ T │ G │ M │ N │ E │ I │ O │ ' │ ENTER  │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │ LSHIFT │ X │ C │ D │ V │ Z │ K │ H │ , │ . │ / │  RSHIFT  │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │CTRL│GUI │ALT │          SPACE         │ALT │FN1 │FN2 │CTRL│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     */
    [_COLEMAK] = LAYOUT_ansi_61(
      KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
      KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_BSLS,
      KC_CAPS,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,     KC_QUOT,            KC_ENT,
      KC_LSFT,           KC_X,    KC_C,    KC_D,    KC_V,    KC_Z,    KC_K,    KC_H,    KC_COMM, KC_DOT,   KC_SLSH,            KC_RSFT,
      KC_LCTL,  KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,  MO(_FN1), MO(_FN2), KC_RCTL), 

    /**
     * Dvorak
     * 
     * Patented in 1936 by August Dvorak and his brother-in-law, William Dealey, as a faster and more ergonomic alternative to the QWERTY layout.
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ [ │ ] │ BKSPC │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ TAB │ ' │ , │ . │ P │ Y │ F │ G │ C │ R │ L │ / │ = │  \  │ 
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ CAPS │ A │ O │ E │ U │ I │ D │ H │ T │ N │ S │ - │ ENTER  │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │ LSHIFT │ ; │ Q │ J │ K │ X │ B │ M │ W │ V │ / │  RSHIFT  │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │CTRL│GUI │ALT │          SPACE         │ALT │FN1 │FN2 │CTRL│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     */
    [_DVORAK] = LAYOUT_ansi_61(
      KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_LBRC,  KC_RBRC,  KC_BSPC,
      KC_TAB,   KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,     KC_SLSH,  KC_EQL,   KC_BSLS,
      KC_CAPS,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,     KC_MINS,            KC_ENT,
      KC_LSFT,           KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,     KC_Z,               KC_RSFT,
      KC_LCTL,  KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,  MO(_FN1), MO(_FN2), KC_RCTL),

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
     * Currently only compatiable with colemak-dh
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
     * │HYPR│MEH │LEAD│                        │    │    │    │    │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     * Credit: https://precondition.github.io/home-row-mods
     *
     */
    [_MODCOLEMAK] = LAYOUT_ansi_61(
      KC_GRV,   _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,
      _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,
      DK_MOD4,  HOME_A,   HOME_R,  HOME_S,  HOME_T,  _______, _______, HOME_N,  HOME_E,  HOME_I,  HOME_O,   _______,            _______,
      XXXXXXX,            _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            XXXXXXX,
      DK_HYPR,  DK_MEH,   QK_LEAD,                            SPACEFN,                            XXXXXXX,  _______,  _______,  XXXXXXX),

    /**
     * SPACEFN
     *
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
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │   │   │   │   │   │   │   │   │   │   │   │        │
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
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │BOOTLDR│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ RGB │QTY│CAK│DAK│CRY│   │   │   │   │   │   │   │   │     │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │   │   │   │   │   │   │   │   │   │   │   │  MODS  │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │        │   │   │   │   │   │   │   │   │   │   │          │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │    │    │    │                        │    │    │    │    │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     */
    [_FN2] = LAYOUT_ansi_61(
      MOD_TOG,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  QK_BOOT,
      RGB_TOG,  QWERTY,   COLEMAK, DVORAK,  CANARY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
      XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,                            XXXXXXX,                            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),
};

/* Define the behaviour of our custom keycodes */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MOD_TOG:
        if (record->event.pressed) {
            // toggle our software features
            autoshift_toggle();
            combo_toggle();
            // toggle our mod layer
            layer_invert(_MODCOLEMAK);
        }
        break;
    }
    return true;
};

/* Configure which keys are auto-shifted */
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        // Left-hand home row mods
        case HOME_A:
        case HOME_R:
        case HOME_S:
        case HOME_T:
        
        // Right-hand home row mods
        case HOME_N:
        case HOME_E:
        case HOME_I:
        case HOME_O:
           return true;
        default:
            return false;
    }
}

/* Keyboard Post Initialization */
void keyboard_post_init_user(void) {
    autoshift_disable();
    combo_disable();
}
