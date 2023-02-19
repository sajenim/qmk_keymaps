/* Copyright 2022 @ sajenim (https://github.com/sajenim)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "layers.h"
#include "tapdance.h"

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}


/* Yank:
 *
 *  Sends <ctrl> + <c> on single tap
 *  Sends <ctrl> + <shft> + <c> on double tap (Commonly used in UNIX terminals)
 *
 */

static td_tap_t yank_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void yank_finished(qk_tap_dance_state_t *state, void *user_data) {
    yank_tap_state.state = cur_dance(state);
    switch (yank_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_C);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_C);
            break;
        default:
            break;
    }
}

void yank_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (yank_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_LCTL);
            unregister_code(KC_C);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            unregister_code(KC_C);
            break;
        default:
            break;
    }
    yank_tap_state.state = TD_NONE;
}


/* Paste: 
 *
 *  Sends <ctrl> + <v> on single tap
 *  Sends <ctrl> + <shft> + <v> on double tap (Commonly used in UNIX terminals)
 *
 */

static td_tap_t pste_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void pste_finished(qk_tap_dance_state_t *state, void *user_data) {
    pste_tap_state.state = cur_dance(state);
    switch (pste_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_V);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_V);
            break;
        default:
            break;
    }
}

void pste_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (pste_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_LCTL);
            unregister_code(KC_V);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            unregister_code(KC_V);
            break;
        default:
            break;
    }
    pste_tap_state.state = TD_NONE;
}


/* Delete word:
 *
 *  Sends delete on single tap or hold
 *  Sends <esc> + "daw" on double tap (Vim: delete the word under the cursor)
 *
 */

static td_tap_t delword_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void delword_finished(qk_tap_dance_state_t *state, void *user_data) {
     delword_tap_state.state = cur_dance(state);
     switch (delword_tap_state.state) {
         case TD_SINGLE_TAP:
             register_code(KC_DEL);
             break;
         case TD_SINGLE_HOLD:
             register_code(KC_DEL);
             break;
         case TD_DOUBLE_TAP:
             tap_code(KC_ESC);
             SEND_STRING("daw");
             break;
         default:
             break;
    }
}

void delword_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (delword_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_DEL);
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_DEL);
            break;
        default:
            break;
    }
    delword_tap_state.state = TD_NONE;
}


/* Back word:
 *
 *  Sends bacspace on single tap or hold
 *  Sends <ctrl> + <w> on double tap (Bash: remove the command/argument before the cursor)
 *
 */

static td_tap_t backword_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void bakword_finished(qk_tap_dance_state_t *state, void *user_data) {
    backword_tap_state.state = cur_dance(state);
    switch (backword_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_BSPC);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_BSPC);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_W);
            break;
        default:
            break;
    }
}

void bakword_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (backword_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_BSPC);
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_BSPC);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_LCTL);
            unregister_code(KC_W);
            break;
        default:
            break;
    }
    backword_tap_state.state = TD_NONE;
}


/* Function prefix:
 *
 *  Send tmux prefix on tap <ctrl> + <b>.
 *  Enable function layer on hold.
 *
 */

static td_tap_t fnpfx_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void fnpfx_finished(qk_tap_dance_state_t *state, void *user_data) {
    fnpfx_tap_state.state = cur_dance(state);
    switch (fnpfx_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_B);
            break;
        case TD_SINGLE_HOLD:
            layer_on(L_NUMBERS);
            break;
        default:
            break;
    }
}

void fnpfx_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (fnpfx_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_LCTL);
            unregister_code(KC_B);
            break;
        case TD_SINGLE_HOLD:
            layer_off(L_NUMBERS);
            break;
        default:
            break;
    }
    fnpfx_tap_state.state = TD_NONE;
}


/* Function leader:
 *
 *  Send leader key on tap.
 *  Enable function layer on hold.
 *
 */

static td_tap_t fnldr_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void fnldr_finished(qk_tap_dance_state_t *state, void *user_data) {
    fnldr_tap_state.state = cur_dance(state);
    switch (fnldr_tap_state.state) {
        case TD_SINGLE_TAP:
            qk_leader_start();
            break;
        case TD_SINGLE_HOLD:
            layer_on(L_SYMBOLS);
            break;
        default:
            break;
    }
}

void fnldr_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (fnldr_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_off(L_SYMBOLS);
            break;
        default:
            break;
    }
    fnldr_tap_state.state = TD_NONE;
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_YANK]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, yank_finished, yank_reset),
    [TD_PSTE]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pste_finished, pste_reset),
    [TD_DELWORD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, delword_finished, delword_reset),
    [TD_BAKWORD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bakword_finished, bakword_reset),
    [TD_FNPFX]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fnpfx_finished, fnpfx_reset),
    [TD_FNLDR]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fnldr_finished, fnldr_reset)
};

