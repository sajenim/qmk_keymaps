/* If you’re a Vim user, you probably know what a Leader key is. */
#include "quantum.h"

void leader_end_user(void) {
  /* Type some strings */

  // (E)mail (O)utlook
  if (leader_sequence_two_keys(KC_E, KC_O)) {
    SEND_STRING("jasmine.wilson@outlook.com.au");
  }
  // (E)mail (P)roton
  else if (leader_sequence_two_keys(KC_E, KC_P)) {
    SEND_STRING("its.jassy@pm.me");
  }
}

