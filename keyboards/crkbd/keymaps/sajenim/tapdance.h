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

#pragma once

// Our tapdance keycodes
enum td_keycodes {
  TD_YANK,
  TD_PSTE,
  TD_BAKWORD,
  TD_DELWORD,
  TD_FNPFX,
  TD_FNLDR
};

// Define a type containing as many tapdance states as we need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Declare our tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void yank_finished(qk_tap_dance_state_t *state, void *user_data);
void yank_reset(qk_tap_dance_state_t *state, void *user_data);

void pste_finished(qk_tap_dance_state_t *state, void *user_data);
void pste_reset(qk_tap_dance_state_t *state, void *user_data);

void delword_finished(qk_tap_dance_state_t *state, void *user_data);
void delword_reset(qk_tap_dance_state_t *state, void *user_data);

void bakword_finished(qk_tap_dance_state_t *state, void *user_data);
void bakword_reset(qk_tap_dance_state_t *state, void *user_data);

void fnpfx_finished(qk_tap_dance_state_t *state, void *user_data);
void fnpfx_reset(qk_tap_dance_state_t *state, void *user_data);

void fnldr_finished(qk_tap_dance_state_t *state, void *user_data);
void fnldr_reset(qk_tap_dance_state_t *state, void *user_data);

