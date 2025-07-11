#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _LOW,
    _LOWER,
    _LOWEST,
    _MOUSE,
    _GAME,
};
enum tophactyl_keycodes {
    QW = SAFE_RANGE,
    AltTab,
};

enum tap_dance_keycodes {
    Q_TAB,
    M_QUOT,
    H_LEFT,
    J_DOWN,
    K_UP,
    L_RGHT,
    P_PSCR,
    BTN1_BTN2,
};

#define LOW      MO(_LOW)
#define LOWER      MO(_LOWER)
#define GAME	TG(_GAME)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
    TD(Q_TAB), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, TD(P_PSCR), 
    LGUI_T(KC_A), KC_S, KC_D, KC_F, RCTL_T(KC_G), TD(H_LEFT), TD(J_DOWN), TD(K_UP),TD(L_RGHT), KC_BSPC,
    RALT_T(KC_Z), KC_X, KC_C, KC_V, LSFT_T(KC_B), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, 
    LOWER, LSFT_T(KC_ENT), _______, KC_INS, LCTL_T(KC_SPC), LOW
    ),

    [_LOW] = LAYOUT(
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
    QW, _______, KC_LCBR, KC_RCBR, KC_COLN, KC_GRV, KC_MINS, KC_PLUS, KC_PIPE, KC_DEL,
    _______, _______, _______, _______, _______, _______, KC_QUOT, _______, _______, KC_BSLS,
    _______, _______, _______, GAME, _______, _______ 
    ),

    [_LOWER] = LAYOUT(
    KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, 
    KC_ESC, _______, KC_LBRC, KC_RBRC, KC_SCLN, _______, KC_UNDS, KC_EQL, _______, _______, 
    _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, 
    _______, _______, _______, _______, _______, _______ 
    ),

    [_LOWEST] = LAYOUT(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, 
    KC_F11, KC_F12, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______, QK_RBT, QK_BOOT, _______, _______, _______ 
    ),

    [_MOUSE] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______ 
    ),

    [_GAME] = LAYOUT(
    KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
    KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_BSPC,
    KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_RSFT, KC_TAB, KC_ESC, 
    		      KC_J, KC_K, KC_L, GAME, KC_SPC, KC_ENT
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case _LOW:
        case _LOWER:
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            break;
        default:
            set_auto_mouse_enable(true);
            break;
        
        return state;
    }
    return update_tri_layer_state(state, _LOW, _LOWER, _LOWEST);
}

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);
    set_auto_mouse_enable(true);
}

void pointing_device_init_kb(void) { 
#ifdef PMW33XX_CPI     
    pointing_device_set_cpi(PMW33XX_CPI); 
#endif 
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(H_LEFT): return 160;
        case TD(J_DOWN): return 150;
        case TD(K_UP): return 160;
        case TD(L_RGHT): return 115;
        case TD(M_QUOT): return 140;
        case TD(Q_TAB): return 210;
        case TD(P_PSCR): return 130;
        case LGUI_T(KC_A): return 300;  
        case LSFT_T(KC_ENT): return 150;
        case LALT(KC_SPC): return 210;
        default:
            return TAPPING_TERM;
    }
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    [_LOW] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    [_LOWER] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    [_LOWEST] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    [_MOUSE] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    [_GAME] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
};
#endif

tap_dance_action_t tap_dance_actions[] = {
    [Q_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_TAB),
    [H_LEFT] = ACTION_TAP_DANCE_DOUBLE(KC_H, KC_LEFT),
    [J_DOWN] = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_DOWN),
    [K_UP] = ACTION_TAP_DANCE_DOUBLE(KC_K, KC_UP),
    [L_RGHT] = ACTION_TAP_DANCE_DOUBLE(KC_L, KC_RGHT),
    [M_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_M, KC_QUOT),
    [P_PSCR] = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_PSCR),
    [BTN1_BTN2] = ACTION_TAP_DANCE_DOUBLE(KC_BTN1, KC_BTN2),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {         
        case QW:
        if (record->event.pressed)
        {
            register_code(KC_LGUI);
            register_code(KC_LSFT);
            tap_code(KC_Q);
            unregister_code(KC_LGUI);
            unregister_code(KC_LSFT);
        }
        break;      
        case AltTab:
        if (record->event.pressed)
        {
            register_code(KC_LALT);
            tap_code(KC_TAB);
            unregister_code(KC_LALT);
        }
        break;
        }
  return true;
  }
