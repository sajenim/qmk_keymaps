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

#include "process_record.h"

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
            SEND_STRING("~/");
        }
        break;

    case UPDIR:
        if (record->event.pressed) {
            SEND_STRING("../");
        }
        break;

    }
    return true;
};

