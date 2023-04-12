#pragma once

#include "quantum.h"

// Our custom keycodes
enum custom_keycodes {
  CK_LOCK = SAFE_RANGE,
  BSPC_DW,
};

// Left-hand thumb key layers
#define GUI_EXT LT(L_EXTEND, KC_LGUI)
#define BAK_LWR LT(L_LOWER,  KC_BSPC)
#define SPC_EXT LT(L_EXTEND, KC_SPC)

// Right-hand thumb key layers
#define ENT_SFT MT(MOD_LSFT, KC_ENT)
#define DEL_RSE LT(L_RAISE,  KC_DEL)
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

// Default Layers
#define xQWERTY DF(L_QWERTY)
#define xCANARY DF(L_CANARY)

// Shortcuts
#define WZ_CMOD LCTL(LSFT(KC_X))
#define WZ_PSTE LCTL(LSFT(KC_V))

// Gaming
#define GM_TOGG TG(L_GAMING)
#define GAME_FN MO(L_GAMEFN)

// Misc
#define TABCTRL MT(MOD_LCTL, KC_TAB)
#define BSPC_DW MT(MOD_LCTL, KC_BSPC)

