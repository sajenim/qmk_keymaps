#include QMK_KEYBOARD_H
#include "features/sentence_case.h"
#include "layers.h"
#include <stdio.h>

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
  case L_CANARY:
    oled_write(" BAS ", false);
    break;
  case L_LOWER:
    oled_write(" LWR ", false);
    break;
  case L_RAISE:
    oled_write(" RSE ", false);
    break;
  case L_ADJUST:
    oled_write(" ADJ ", false);
    break;
  case L_EXTEND:
    oled_write(" EXT ", false);
    break;
  case L_MACRO:
    oled_write(" MAC ", false);
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
