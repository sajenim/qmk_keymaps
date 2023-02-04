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
    L_QWERTY,
    L_CANARY,
    // Layouts that enable extra functionality
    L_EXTEND,
};

/* Customise our keymaps */
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
     * │EXTEND│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ ENTER  │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │ LSHIFT │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │  RSHIFT  │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │CTRL│GUI │ALT │          SPACE         │ALT │MEH │HYPR│CTRL│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     */ 
    [L_QWERTY] = LAYOUT_ansi_61(
        QK_GESC, KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        EXTEND,  KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,
        OS_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            OS_RSFT,
        OS_LCTL, OS_LGUI,  OS_LALT,                            KC_SPC,                             OS_RALT,  OS_MEH,   OS_HYPR,  OS_RCTL),

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
     * │EXTEND│ C │ R │ S │ T │ B │ F │ N │ E │ I │ A │ ' │ ENTER  │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │ LSHIFT │ J │ V │ D │ G │ Q │ M │ H │ / │ , │ . │  RSHIFT  │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │CTRL│GUI │ALT │          SPACE         │ALT │MEH │HYPR│CTRL│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     */
    [L_CANARY] = LAYOUT_ansi_61(
      QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
      KC_TAB,   KC_W,    KC_L,    KC_Y,    KC_P,    KC_K,    KC_Z,    KC_X,    KC_O,    KC_U,    KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_BSLS,
      EXTEND,   KC_C,    KC_R,    KC_S,    KC_T,    KC_B,    KC_F,    KC_N,    KC_E,    KC_I,    KC_A,     KC_QUOT,            KC_ENT,
      OS_LSFT,           KC_J,    KC_V,    KC_D,    KC_G,    KC_Q,    KC_M,    KC_H,    KC_SLSH, KC_COMM,  KC_DOT,             OS_RSFT,
      OS_LCTL,  OS_LGUI, OS_LALT,                            KC_SPC,                             OS_RALT,  OS_MEH,   OS_HYPR,  OS_RCTL),

     /**
     * Extend
     * 
     * The Extend Layer provides an additional set of mappings for your keys by defining a new "Extend" modifier key. 
     * Holding down this key activates "Extend" mode and provides navigation and editing functions.
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │LDR│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│ SLEEP │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │     │   │   │   │   │   │   │HOM│PDN│PUP│END│   │   │     │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │GUI│ALT│SFT│CTL│   │   │LFT│DWN│UP │RGT│DEL│        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │        │   │   │   │   │   │   │BAK│   │   │   │          │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │    │    │    │                        │    │    │    │    │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     */
    [L_EXTEND] = LAYOUT_ansi_61(
      QK_BOOT,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_SLEP,
      XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,   XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  OS_LGUI,  OS_LALT, OS_LSFT, OS_LCTL, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_DEL,             XXXXXXX,
      XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,                            XXXXXXX,                            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),
};

