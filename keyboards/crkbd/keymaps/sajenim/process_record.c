#include "process_record.h"
#include "layers.h"
#include "features/sentence_case.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_sentence_case(keycode, record)) { return false; }
    
    switch (keycode) {
        case BSPC_DW:
            if (record->tap.count && record->event.pressed) {
                tap_code(KC_BSPC);
            } else if (record->event.pressed) {
                tap_code16(C(KC_W));
            }
            return false;

        case SC_TOGG:
            if (record->event.pressed) {
                sentence_case_toggle();
            }
            return false;
  }
  return true;
};
