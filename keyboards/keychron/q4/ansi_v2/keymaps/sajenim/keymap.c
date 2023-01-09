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
    // layouts that enable extra functionality
    _SPACEFN,
    _FN1,
    _FN2,
};

/* Define our custom keycodes */
enum custom_keycodes {
    VI_SAVE = SAFE_RANGE,
    VI_EXIT,
    DC_MUTE,
    DC_DFEN,
    DELWORD,
    UPDIR,
};

/* Define our combo keycodes */
enum combos {
    NE_ESCAPE,
    REPEAT_SPACE,
    COMBO_LENGTH
};

// Programmatically declare the size of the Combo data structure
uint16_t COMBO_LEN = COMBO_LENGTH;

// Define key sequences
const uint16_t PROGMEM ne_combo[] = {HOME_N, HOME_E, COMBO_END};
const uint16_t PROGMEM repeat_space_combo[] = {OS_LALT, SPACEFN, COMBO_END};

// List the combination of keys and there resulting action
combo_t key_combos[] = {
  [NE_ESCAPE] = COMBO(ne_combo, KC_ESC),
  [REPEAT_SPACE] = COMBO_ACTION(repeat_space_combo),
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
     * │CTRL│GUI │ALT │         SPACEFN        │ALT │FN1 │FN2 │CTRL│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     */ 
    [_QWERTY] = LAYOUT_ansi_61(
        KC_GRV,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        CW_TOGG, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,
        OS_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            OS_RSFT,
        OS_LCTL, OS_LGUI,  OS_LALT,                            SPACEFN,                            OS_RALT,  MO(_FN1), MO(_FN2), OS_RCTL),

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
     * │CTRL│GUI │ALT │         SPACEFN        │ALT │FN1 │FN2 │CTRL│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     * Credit: https://precondition.github.io/home-row-mods
     *
     */
    [_CANARY] = LAYOUT_ansi_61(
      KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
      KC_TAB,   KC_W,    KC_L,    KC_Y,    KC_P,    KC_K,    KC_Z,    KC_X,    KC_O,    KC_U,    KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_BSLS,
      CW_TOGG,  HOME_C,  HOME_R,  HOME_S,  HOME_T,  KC_B,    KC_F,    HOME_N,  HOME_E,  HOME_I,  HOME_A,   KC_QUOT,            KC_ENT,
      OS_LSFT,           KC_J,    KC_V,    KC_D,    KC_G,    KC_Q,    KC_M,    KC_H,    KC_SLSH, KC_COMM,  KC_DOT,             OS_RSFT,
      OS_LCTL,  OS_LGUI, OS_LALT,                            SPACEFN,                            OS_RALT,  MO(_FN1), MO(_FN2), OS_RCTL),

    /**
     * SPACEFN
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │../│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│DELWORD│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │     │:w │:q!│PUP│PDN│   │   │HOM│END│   │   │   │   │     │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │GUI│ALT│SFT│CTL│   │   │LFT│DWN│UP │RGT│   │ INSERT │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │        │   │   │BAK│   │   │   │DEL│   │   │   │          │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │    │    │    │                        │    │    │    │    │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     *
     * Credit: https://geekhack.org/index.php?topic=51069.0
     *
     */
    [_SPACEFN] = LAYOUT_ansi_61(
      UPDIR,    KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   DELWORD,
      XXXXXXX,  VI_SAVE,  VI_EXIT, KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX, KC_HOME, KC_END,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  KC_LGUI,  KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, XXXXXXX,            KC_INS,
      XXXXXXX,            XXXXXXX, XXXXXXX, KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,                            XXXXXXX,                            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),

    /**
     * Function 1
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │   │MUT│DFN│VUP│VDN│HOM│BAK│FWD│REF│PLY│STP│PRV│NXT│ SLEEP │
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
      XXXXXXX,  DC_MUTE,  DC_DFEN, KC_VOLU, KC_VOLD, KC_WHOM, KC_WBAK, KC_WFWD, KC_WREF, KC_MPLY, KC_MSTP,  KC_MPRV,  KC_MNXT,  KC_SLEP,
      XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
      XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,                            XXXXXXX,                            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),

    /**
     * Function 2
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │   │X01│X02│X03│X04│X05│X06│X07│X08│X09│X10│X11│X12│BOOTLDR│
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
    [_FN2] = LAYOUT_ansi_61(
      XXXXXXX,  PB_1,     PB_2,    PB_3,    PB_4,    PB_5,    PB_6,    PB_7,    PB_8,    PB_9,    PB_10,    PB_11,    PB_12,    QK_BOOT,
      XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
      XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,                            XXXXXXX,                            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),
};

/* Define the behaviour of our custom keycodes */
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
    case DC_MUTE:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT("m"))); 
        }
        break;
    case DC_DFEN:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT("d"))); 
        }
        break;
    case DELWORD:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("w"));
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

/* Define the behaviour of our custom combos */ 
void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case REPEAT_SPACE:
      if (pressed) {
        register_code(KC_SPC);
      }
      break;
  }
}
