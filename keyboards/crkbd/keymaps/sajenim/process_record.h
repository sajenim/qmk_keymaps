#pragma once

#include "quantum.h"

// Our custom keycodes
enum custom_keycodes {
  // Additional, distinct "Alternate Repeat"-like keys.
  ALTREP2 = SAFE_RANGE,
  ALTREP3,
  SC_TOGG,
};

// Dual role keys
#define SPACEFN LT(L_EXTEND, KC_SPC)
#define ENTERFN LT(L_MACRO, KC_ENT)
#define TABCTRL MT(MOD_LCTL, KC_TAB)
#define BAK_LWR LT(L_LOWER, KC_BSPC)
#define DEL_RSE LT(L_RAISE, KC_DEL)

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
#define DELWORD LCTL(KC_W)
#define WZ_CMOD LCTL(LSFT(KC_X))
#define WZ_COPY LCTL(LSFT(KC_C))
#define WZ_PSTE LCTL(LSFT(KC_V))

