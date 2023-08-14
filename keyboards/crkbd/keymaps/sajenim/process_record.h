#pragma once

#include "quantum.h"

// Our custom keycodes
enum custom_keycodes {
  BSPC_DW = SAFE_RANGE,
  SC_TOGG,
};

// Left-hand thumb key layers
#define GUI_EXT LT(L_EXTEND, KC_LGUI)
#define BAK_LWR LT(L_LOWER,  KC_BSPC)
#define SPC_EXT LT(L_EXTEND, KC_SPC)

// Right-hand thumb key layers
#define ENT_SFT MT(MOD_LSFT, KC_ENT)
#define DEL_UPR LT(L_UPPER,  KC_DEL)
#define ALT_EXT LT(L_EXTEND, KC_LALT)

// One Shot Keys
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)

#define OS_RCTL OSM(MOD_RCTL)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_RALT OSM(MOD_RALT)
#define OS_RGUI OSM(MOD_RGUI)

// Shortcuts
#define WZ_CMOD LCTL(LSFT(KC_X))
#define WZ_COPY LCTL(LSFT(KC_C))
#define WZ_PSTE LCTL(LSFT(KC_V))

// Misc
#define TABCTRL MT(MOD_LCTL, KC_TAB)
#define BSPC_DW MT(MOD_LCTL, KC_BSPC)

