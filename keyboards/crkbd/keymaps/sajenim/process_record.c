#include "process_record.h"
#include "layers.h"
#include "features/sentence_case.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_sentence_case(keycode, record)) { return false; }

        case SC_TOGG:
            if (record->event.pressed) {
                sentence_case_toggle();
            }
            return false;
  }
  return true;
};
