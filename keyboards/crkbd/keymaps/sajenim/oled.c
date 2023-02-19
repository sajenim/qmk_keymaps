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
#include "oled.h"
#include "layers.h"

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

