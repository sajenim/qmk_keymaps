// This file contains user defined aliases

// Default layouts
#define QWERTY  DF(_QWERTY)
#define COLEMAK DF(_COLEMAK)
#define DVORAK  DF(_DVORAK)

// Extra layers
#define SPACEFN LT(_SPACEFN, KC_SPC)

// Left-hand home row mods
#define HOME_A  LGUI_T(KC_A)
#define HOME_R  LALT_T(KC_R)
#define HOME_S  LSFT_T(KC_S)
#define HOME_T  LCTL_T(KC_T)

// Right-hand home row mods
#define HOME_N  RCTL_T(KC_N)
#define HOME_E  RSFT_T(KC_E)
#define HOME_I  RALT_T(KC_I)
#define HOME_O  RGUI_T(KC_O)

// Dead keys
#define DK_MOD4 OSM(MOD_LGUI)
#define DK_HYPR OSM(MOD_HYPR)
#define DK_MEH  OSM(MOD_MEH)

// Shortcuts
#define DELWORD LCTL(KC_W)
