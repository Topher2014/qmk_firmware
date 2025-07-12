/* Copyright 2015-2021 Jack Humbert
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

enum planck_layers {
  _QWERTY,
  _LOW,
  _LOWER,
  _LOWEST,
  _GAME
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  QW,
  BACKLIT
};

enum tap_dance_keycodes {
    Q_TAB,
    M_QUOT,
    H_LEFT,
    J_DOWN,
    K_UP,
    L_RGHT,
    P_PSCR,
};

#define LOW MO(_LOW)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ortho_4x12(
    TD(Q_TAB), KC_W, KC_E, KC_R, KC_T, _______, _______, KC_Y, KC_U, KC_I, KC_O, TD(P_PSCR), 
    LGUI_T(KC_A), KC_S, KC_D, KC_F, RCTL_T(KC_G), _______, _______, TD(H_LEFT), TD(J_DOWN), TD(K_UP), TD(L_RGHT), KC_BSPC, 
    RALT_T(KC_Z), KC_X, KC_C, KC_V, LSFT_T(KC_B), _______, _______, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, 
    _______, _______, _______, LOWER, LSFT_T(KC_ENT), KC_INS, _______, LCTL_T(KC_SPC), LOW, _______, _______, _______
),

[_LOW] = LAYOUT_ortho_4x12(
    KC_1, KC_2, KC_3, KC_4, KC_5, _______, _______, KC_6, KC_7, KC_8, KC_9, KC_0, 
    QW, _______, KC_LCBR, KC_RCBR, KC_COLN, _______, _______, KC_GRV, KC_MINS, KC_PLUS, KC_PIPE, KC_DEL, 
    _______, _______, _______, _______, _______, _______,  _______, _______, KC_QUOT, _______, _______, KC_BSLS,
    _______, _______, _______, _______, _______, _______, _______, TG(_GAME), _______, _______, _______, _______
),

[_LOWER] = LAYOUT_ortho_4x12(
    KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, 
    KC_ESC, _______, KC_LBRC, KC_RBRC, KC_SCLN, _______, _______, _______, KC_UNDS, KC_EQL, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_LOWEST] = LAYOUT_ortho_4x12(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, _______, _______, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, 
    KC_F11, KC_F12, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, QK_RBT, QK_BOOT, _______, _______, _______, _______, _______

),

[_GAME] = LAYOUT_ortho_4x12(
    KC_Q, KC_W, KC_E, KC_R, KC_T, _______, _______, KC_Y, KC_U, KC_I, KC_O, KC_P, 
    KC_A, KC_S, KC_D, KC_F, KC_G, _______, _______, KC_H, KC_J, KC_K, KC_L, KC_BSPC, 
    KC_Z, KC_X, KC_C, KC_V, KC_B, _______, _______, KC_N, KC_M, KC_RSFT, KC_TAB, KC_ESC, 
    		      _______, _______, KC_J, KC_K, KC_L, _______, _______, TG(_GAME), KC_SPC, KC_ENT, _______, _______ 
),

};

tap_dance_action_t tap_dance_actions[] = {
    [Q_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_TAB),
    [H_LEFT] = ACTION_TAP_DANCE_DOUBLE(KC_H, KC_LEFT),
    [J_DOWN] = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_DOWN),
    [K_UP] = ACTION_TAP_DANCE_DOUBLE(KC_K, KC_UP),
    [L_RGHT] = ACTION_TAP_DANCE_DOUBLE(KC_L, KC_RGHT),
    [M_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_M, KC_QUOT),
    [P_PSCR] = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_PSCR),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(H_LEFT): return 160;
        case TD(J_DOWN): return 150;
        case TD(K_UP): return 160;
        case TD(L_RGHT): return 100;
        case TD(M_QUOT): return 140;
        case TD(Q_TAB): return 210;
        case TD(P_PSCR): return 130;
        case LGUI_T(KC_A): return 300;  
        case LSFT_T(KC_ENT): return 150;
        case LALT_T(KC_SPC): return 210;
        default:
            return TAPPING_TERM;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOW, _LOWER, _LOWEST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case QW:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_Q);
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
      }
      return false;
      break;
  }
  return true;
}

