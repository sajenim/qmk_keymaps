#include "process_record.h"
#include "features/sentence_case.h"

// Use ALTREP2 and ALTREP3 in our layout...
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
  switch (keycode) {
    case ALTREP2:
    case ALTREP3:
      return false; // ignore ALTREP keys.
  }
  return true; // other keys can be repeated.
}

static void process_altrep2(uint16_t keycode, uint8_t mods) {
  switch (keycode) {
    // Expand and centre cursor
    case KC_LPRN: SEND_STRING(")"SS_TAP(X_LEFT)); break;                // ()
    case KC_LBRC: SEND_STRING("]"SS_TAP(X_LEFT)); break;                // []
    case KC_LCBR: SEND_STRING("}"SS_TAP(X_LEFT)); break;                // {}
    case KC_DQUO: SEND_STRING("\""); break;                             // ""
    // Complete
    case KC_LABK: SEND_STRING("-"); break;                              // <-
    case KC_RABK: SEND_STRING(SS_TAP(X_LEFT)"-"SS_TAP(X_RIGHT)); break; // ->
    case KC_DOT: SEND_STRING("|."); break;                              // .|.
    case KC_PIPE: SEND_STRING("||"); break;                             // |||
    case KC_COLN: SEND_STRING(":"); break;                              // ::
  }
}

// Define the behaviour of our custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_sentence_case(keycode, record)) { return false; }

  switch (keycode) {
    case ALTREP2:
      if (record->event.pressed) {
        process_altrep2(get_last_keycode(), get_last_mods());
      }
      return false;
    case SC_TOGG:
      if (record->event.pressed) {
        sentence_case_toggle();
      }
      return false; // Skip all further processing of this key
  } 
  return true;
};
