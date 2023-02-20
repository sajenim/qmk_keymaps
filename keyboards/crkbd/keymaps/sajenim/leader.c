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
#include "leader.h"
#include "secrets.h"

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    
    /* Emerge */
    SEQ_TWO_KEYS(KC_E, KC_S) { 
      SEND_STRING(SEARCH);
    }
    SEQ_TWO_KEYS(KC_E, KC_I) {
      SEND_STRING(INSTALL);
    }
    SEQ_TWO_KEYS(KC_E, KC_R) {
      SEND_STRING(REMOVE);
    }
    SEQ_TWO_KEYS(KC_E, KC_U) {
      SEND_STRING(UPDATE);
    }
    SEQ_TWO_KEYS(KC_E, KC_D) {
      SEND_STRING(DEPCLEAN);
    }
    SEQ_THREE_KEYS(KC_E, KC_U, KC_U) {
      SEND_STRING(UPGRADE);
    }
   
    /* Expansion */
    SEQ_TWO_KEYS(KC_G, KC_M) {
      SEND_STRING(GM);
    }
    SEQ_TWO_KEYS(KC_G, KC_N) {
      SEND_STRING(GN);
    }
    SEQ_FOUR_KEYS(KC_R, KC_T, KC_F, KC_M) {
      SEND_STRING(RTFM);
    }

    /* Secrets */
    SEQ_TWO_KEYS(KC_A, KC_H) {
      SEND_STRING(ADDRESS);
    }
    SEQ_TWO_KEYS(KC_P, KC_M) {
      SEND_STRING(PHONE);
    }
    SEQ_TWO_KEYS(KC_E, KC_O) {
      SEND_STRING(OUTLOOK);
    }
    SEQ_TWO_KEYS(KC_E, KC_P) {
      SEND_STRING(PROTON);
    }
  }
}
