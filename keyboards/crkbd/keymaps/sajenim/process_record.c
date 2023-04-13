#include "process_record.h"
#include "layers.h"
#include "oled.h"
#include "features/layer_lock.h"
#include "features/sentence_case.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_layer_lock(keycode, record, CK_LOCK)) { return false; }
    if (!process_sentence_case(keycode, record)) { return false; }
    
    switch (keycode) {
        case GUI_EXT:
            if (record->tap.count && record->event.pressed) {
                set_oneshot_mods(MOD_BIT(KC_LGUI));
                return false;
            } else if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LGUI));
                layer_on(L_EXTEND);
            } else {
                unregister_mods(MOD_BIT(KC_LGUI));
                layer_off(L_EXTEND);
            }
            return false;

        case ALT_EXT:
            if (record->tap.count && record->event.pressed) {
                set_oneshot_mods(MOD_BIT(KC_LALT));
                return false;
            } else if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LALT));
                layer_on(L_EXTEND);
            } else {
                unregister_mods(MOD_BIT(KC_LALT));
                layer_off(L_EXTEND);
            }
            return false;

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

        /* KEYBOARD PET STATUS START */
        case TABCTRL:
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;

        case SPC_EXT:
        case KC_SPC:
            if (record->tap.count && record->event.pressed) {
                isJumping = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;
    /* KEYBOARD PET STATUS END */
  }
  return true;
};
