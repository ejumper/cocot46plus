/*
Copyright 2022 aki27

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "process_key_override.h"

enum layer_number {
    HOMEWIN,
    HOMEMAC,
    HOMELIN,
    NUMBERWIN,
    NUMBERMAC,
    NUMBERLIN,
    NUMBER2,
    FUNCTIONWIN,
    FUNCTIONMAC,
    FUNCTIONLIN,
    FUNCTION2,
};

#ifdef DYNAMIC_MACRO_ENABLE
// Declare variables to track dynamic macro state and LED blink timing.
static bool recording_macro = false;
static uint16_t last_blink_time = 0;
static bool blink_on = false;

// Correct function definitions matching QMK's expected signature.
bool dynamic_macro_record_start_user(int8_t direction) {
    recording_macro = true;
    last_blink_time = timer_read();
    return true;
}

bool dynamic_macro_record_end_user(int8_t direction) {
    recording_macro = false;
    #ifdef RGB_MATRIX_ENABLE
      rgb_matrix_set_color(1, 0, 0, 0);
    #elif defined(RGBLIGHT_ENABLE)
      rgblight_setrgb_range(0, 0, 0, 0, 2);
    #endif
    return true;
}

bool dynamic_macro_play_user(int8_t direction) {
    clear_keyboard();             
    layer_move(HOMEWIN); 
    return true;
}

#endif



bool alt_tab_active = false;

enum {
    TD_LSFT_CAPS,
};


void td_lsft_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 || state->count == 2) {
        // One or two taps: act as Left Shift
        register_code(KC_LSFT);
    } else if (state->count >= 3) {
        // Three (or more) taps: send Caps Lock
        tap_code(KC_CAPS);
    }
}

void td_lsft_caps_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 || state->count == 2) {
        unregister_code(KC_LSFT);
    }
    // No need to unregister for KC_CAPS since tap_code() handles that.
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lsft_caps_finished, td_lsft_caps_reset),
};

const uint16_t PROGMEM ms_btn_combo[] = { MS_BTN1, MS_BTN2, COMBO_END };

enum combo_events {
    MS_BTN1_BTN2_COMBO,
};

combo_t key_combos[] = {
    [MS_BTN1_BTN2_COMBO] = COMBO(ms_btn_combo, MS_BTN3)
};

enum custom_keycodes {
    TO_HOMEWIN_R = SAFE_RANGE,
};

//navigation
const key_override_t backpage = ko_make_basic(MOD_MASK_SHIFT, A(KC_LEFT), A(KC_RGHT));
const key_override_t refresh = ko_make_basic(MOD_MASK_ALT, A(KC_LEFT), C(KC_R));
const key_override_t searchbox = ko_make_basic(MOD_MASK_SHIFT, A(KC_D), C(KC_E));
//app switching
const key_override_t taskbar = ko_make_basic(MOD_MASK_SHIFT, A(KC_TAB), G(KC_T));
const key_override_t desktopswitcher = ko_make_basic(MOD_MASK_GUI, A(KC_TAB), G(KC_TAB));
//media &brightness
const key_override_t next = ko_make_basic(MOD_MASK_SHIFT, CTL_T(KC_MPLY), KC_MNXT);
const key_override_t previous = ko_make_basic(MOD_MASK_ALT, CTL_T(KC_MPLY), KC_MPRV);
const key_override_t brightnessup = ko_make_basic(MOD_MASK_CTRL, CTL_T(KC_MPLY), KC_BRIU);
const key_override_t brightnessdown = ko_make_basic(MOD_MASK_GUI, CTL_T(KC_MPLY), KC_BRID);
//zoom
const key_override_t ctrlzero = ko_make_basic(MOD_MASK_SHIFT, SCRL_MO, C(KC_0));
//delete
const key_override_t shiftdel = ko_make_basic(MOD_MASK_SHIFT, KC_DEL, KC_BSPC);
//window arranging
const key_override_t appmenu = ko_make_basic(MOD_MASK_CTRL, G(KC_DOWN), A(KC_SPC));
const key_override_t maximize = ko_make_basic(MOD_MASK_ALT, G(KC_DOWN), G(KC_UP));
const key_override_t close = ko_make_basic(MOD_MASK_SHIFT, G(KC_DOWN), A(KC_F4));
//apps
const key_override_t printscreen = ko_make_basic(MOD_MASK_SHIFT, LSG(KC_S), KC_PSCR);
const key_override_t ctrlpanel = ko_make_basic(MOD_MASK_SHIFT, G(KC_I), KC_CPNL);
const key_override_t quicksettings = ko_make_basic(MOD_MASK_ALT, G(KC_I), G(KC_A));
const key_override_t calculator = ko_make_basic(MOD_MASK_SHIFT, G(KC_E), KC_CALC);
const key_override_t mail = ko_make_basic(MOD_MASK_ALT, G(KC_E), KC_MAIL);
const key_override_t browser = ko_make_basic(MOD_MASK_GUI, G(KC_E), KC_WHOM);
//power
const key_override_t sleep = ko_make_basic(MOD_MASK_SHIFT, G(KC_L), KC_SLEP);
const key_override_t powerdown = ko_make_basic(MOD_MASK_ALT, G(KC_L), KC_PWR);
//character shift changes
const key_override_t questionmark = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_QUES);
const key_override_t exclamationpoint = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_EXLM);
const key_override_t lessthan = ko_make_basic(MOD_MASK_SHIFT, KC_COLN, KC_LT);
const key_override_t greaterthan = ko_make_basic(MOD_MASK_SHIFT, KC_SCLN, KC_GT);
//num layer shift cancels
const key_override_t zero = ko_make_basic(MOD_MASK_SHIFT, KC_0, KC_0);
const key_override_t one = ko_make_basic(MOD_MASK_SHIFT, KC_1, KC_1);
const key_override_t two = ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_2);
const key_override_t three = ko_make_basic(MOD_MASK_SHIFT, KC_3, KC_3);
const key_override_t four = ko_make_basic(MOD_MASK_SHIFT, KC_4, KC_4);
const key_override_t five = ko_make_basic(MOD_MASK_SHIFT, KC_5, KC_5);
const key_override_t six = ko_make_basic(MOD_MASK_SHIFT, KC_6, KC_6);
const key_override_t seven = ko_make_basic(MOD_MASK_SHIFT, KC_7, KC_7);
const key_override_t eight = ko_make_basic(MOD_MASK_SHIFT, KC_8, KC_8);
const key_override_t nine = ko_make_basic(MOD_MASK_SHIFT, KC_9, KC_9);
const key_override_t LBRC = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_LBRC);
const key_override_t RBRC = ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, KC_RBRC);
const key_override_t EQL = ko_make_basic(MOD_MASK_SHIFT, KC_EQL, KC_EQL);
const key_override_t BSLS = ko_make_basic(MOD_MASK_SHIFT, KC_BSLS, KC_BSLS);
const key_override_t SLSH = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_SLSH);

const key_override_t *key_overrides[] = {
    &backpage,
    &refresh,
    &searchbox,

    &taskbar,
    &desktopswitcher,

    &next,
    &previous,
    &brightnessup,
    &brightnessdown,

    &ctrlzero,

    &shiftdel,

    &appmenu, 
    &maximize,
    &close,

    &printscreen,
    &ctrlpanel,
    &quicksettings, 
    &calculator,
    &mail,
    &browser,
    
    &sleep,
    &powerdown,

    &questionmark,
    &exclamationpoint,
    &lessthan,
    &greaterthan,
    
    &zero,
    &one,
    &two,
    &three,
    &four,
    &five,
    &six,
    &seven,
    &eight,
    &nine,
    &LBRC,
    &RBRC,
    &EQL,
    &BSLS,
    &SLSH,
    NULL
};



#define LW_MHEN LT(1,KC_INT5)  // lower
#define RS_HENK LT(2,KC_INT4)  // raise
#define DEL_ALT ALT_T(KC_DEL)

// In the buttom row, KC_MS_BTN3 binds middle-click to the encoder's button press
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [HOMEWIN] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                                          KC_J,    KC_L,    KC_U,    KC_Y,   KC_QUOT,  KC_GRV,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_BSPC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                                          KC_H,   KC_N, KC_E,    KC_I, KC_O, CTL_T(KC_MINS),
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      GUI_T(KC_TAB),    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                          KC_K,    KC_M, S(KC_SCLN), KC_SCLN, KC_COMM, KC_DOT,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
        KC_LALT, GUI_T(KC_ESC),   TT(NUMBERWIN),  TD(TD_LSFT_CAPS),     KC_LCTL,         KC_RCTL,   TT(FUNCTIONWIN), LT(3, KC_SPC), GUI_T(KC_ENT),  KC_RALT,
                                                                 XXXXXXX, TO(FUNCTION2),  XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
  [HOMEMAC] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                                          KC_J,    KC_L,    KC_U,    KC_Y,   KC_QUOT,  KC_GRV,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_TRNS,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                                          KC_H,   KC_N, KC_E,    KC_I, KC_O, KC_TRNS,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_TRNS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                          KC_K,    KC_M, S(KC_SCLN), KC_SCLN, KC_COMM, KC_DOT,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
        KC_LALT, KC_LGUI,   TT(NUMBERMAC),  TD(TD_LSFT_CAPS),     KC_TRNS,           KC_TRNS,   TT(FUNCTIONMAC), LT(4, KC_SPC), GUI_T(KC_ENT),  KC_LALT,
                                                                 XXXXXXX, TO(FUNCTION2),  XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
  [HOMELIN] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                                          KC_J,    KC_L,    KC_U,    KC_Y,   KC_QUOT,  KC_GRV,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_TRNS,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                                          KC_H,   KC_N, KC_E,    KC_I, KC_O, KC_TRNS,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_TRNS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                          KC_K,    KC_M, S(KC_SCLN), KC_SCLN, KC_COMM, KC_DOT,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
        KC_LALT, KC_LGUI,   TT(NUMBERLIN),  TD(TD_LSFT_CAPS),     KC_TRNS,           KC_TRNS,   TT(FUNCTIONLIN), LT(5, KC_SPC), GUI_T(KC_ENT),  KC_LALT,
                                                                 XXXXXXX, TO(FUNCTION2),  XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
  [NUMBERWIN] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS,  S(KC_6), S(KC_4), S(KC_LBRC), S(KC_RBRC), S(KC_BSLS),                                          S(KC_8), KC_4, KC_5, KC_6, KC_EQL, S(KC_5),
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS,  S(KC_2),   S(KC_7), S(KC_9), S(KC_0), S(KC_3),                                          KC_0,    KC_1, KC_2, KC_3, S(KC_EQL), KC_TRNS,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS,  G(KC_DOT), KC_F24,  KC_LBRC, KC_RBRC, KC_BSLS,                                          KC_SLSH, KC_7, KC_8, KC_9, KC_COMM, KC_DOT,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
        KC_LALT, KC_LGUI,   TO_HOMEWIN_R,  TD(TD_LSFT_CAPS),     KC_TRNS,           KC_TRNS,   MO(NUMBER2), LT(3, KC_SPC), GUI_T(KC_ENT),  KC_LALT,
                                                                 XXXXXXX, C(KC_0),  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
[NUMBERMAC] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS,  S(KC_6), S(KC_4), S(KC_LBRC), S(KC_RBRC), S(KC_BSLS),                                          S(KC_8), KC_4, KC_5, KC_6, KC_EQL, S(KC_5),
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS,  S(KC_2),   S(KC_7), S(KC_9), S(KC_0), S(KC_3),                                          KC_0,    KC_1, KC_2, KC_3, S(KC_EQL), KC_TRNS,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS,  G(KC_DOT), KC_F24,  KC_LBRC, KC_RBRC, KC_BSLS,                                          KC_SLSH, KC_7, KC_8, KC_9, KC_COMM, KC_DOT,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
        KC_LALT, KC_LGUI,   TO(HOMEWIN),  TD(TD_LSFT_CAPS),     KC_TRNS,           KC_TRNS,   MO(NUMBER2), LT(3, KC_SPC), GUI_T(KC_ENT),  KC_LALT,
                                                                 XXXXXXX, C(KC_0),  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
[NUMBERLIN] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS,  S(KC_6), S(KC_4), S(KC_LBRC), S(KC_RBRC), S(KC_BSLS),                                          S(KC_8), KC_4, KC_5, KC_6, KC_EQL, S(KC_5),
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS,  S(KC_2),   S(KC_7), S(KC_9), S(KC_0), S(KC_3),                                          KC_0,    KC_1, KC_2, KC_3, S(KC_EQL), KC_TRNS,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS,  G(KC_DOT), KC_F24,  KC_LBRC, KC_RBRC, KC_BSLS,                                          KC_SLSH, KC_7, KC_8, KC_9, KC_COMM, KC_DOT,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
        KC_LALT, KC_LGUI,   TT(NUMBERWIN),  TD(TD_LSFT_CAPS),     KC_TRNS,           KC_TRNS,   MO(NUMBER2), LT(5, KC_SPC), GUI_T(KC_ENT),  KC_LALT,
                                                                 XXXXXXX, C(KC_0),  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
  [NUMBER2] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  G(KC_L),    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, DF(HOMEMAC),                          KC_F11, KC_F4, KC_F5, KC_F6, KC_TRNS,   DM_REC1,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, DF(HOMEWIN),                               KC_F10, KC_F1, KC_F2, KC_F3, KC_TRNS, KC_TRNS,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, DF(HOMELIN),                                KC_F12, KC_F7, KC_F8, KC_F9, KC_TRNS,   KC_TRNS,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_LALT, KC_LGUI,   TT(NUMBERWIN),  TD(TD_LSFT_CAPS),     KC_TRNS,           KC_TRNS,   TT(FUNCTIONWIN), LT(3, KC_SPC), GUI_T(KC_ENT),  KC_LALT,
                                                                 XXXXXXX, KC_MUTE,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
  [FUNCTIONWIN] = LAYOUT(
  //|------KC_LEFT-------------------------------------------------|                           |-------------------------------------------------------|
  KC_ESC, KC_INS, KC_PGDN, KC_UP, KC_PGUP, LSG(KC_S),                                           C(KC_T), C(KC_TAB), A(KC_D), A(KC_LEFT), C(KC_W), DM_PLY1,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_BSPC, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                                       KC_DEL, MS_BTN1, MS_BTN2, SCRL_MO, A(KC_TAB), CTL_T(KC_MPLY),
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS, G(KC_I), RCS(KC_ESC), G(KC_E), KC_APP, G(KC_DOWN),                                       C(KC_V), C(KC_C), C(KC_Z), C(KC_Y), C(KC_A), C(KC_F),
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
                        KC_RALT, KC_LGUI, KC_LALT,  KC_TRNS,      KC_TRNS,           KC_TRNS,      TO_HOMEWIN_R, KC_TRNS, KC_TRNS,  KC_TRNS,
                                                                 XXXXXXX, KC_MUTE,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
  [FUNCTIONMAC] = LAYOUT(
  //|------KC_LEFT-------------------------------------------------|                           |-------------------------------------------------------|
  KC_ESC, KC_INS, KC_PGDN, KC_UP, KC_PGUP, KC_HOME,                                           G(KC_T), C(KC_TAB), G(KC_L), A(KC_LEFT), C(KC_W), DM_PLY1,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS, KC_APP, KC_LEFT, KC_DOWN, KC_RGHT, G(KC_M),                                       KC_DEL, MS_BTN1, MS_BTN2, SCRL_MO, G(KC_TAB), CTL_T(KC_MPLY),
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS, G(KC_COMM), KC_MCTL, KC_MCTL, KC_PSCR, G(KC_Q),                                       G(KC_V), G(KC_C), G(KC_Z), LSG(KC_Z), G(KC_A), G(KC_F),
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
                        G(KC_B), KC_LGUI, KC_LALT,  KC_TRNS,      KC_TRNS,           KC_TRNS,      TO(HOMEMAC), KC_TRNS, KC_TRNS,  KC_TRNS,
                                                                 XXXXXXX, KC_MUTE,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
  [FUNCTIONLIN] = LAYOUT(
  //|------KC_LEFT-------------------------------------------------|                            |-------------------------------------------------------|
  KC_ESC, KC_INS, KC_PGDN, KC_UP, KC_PGUP, KC_HOME,                                           C(KC_T), C(KC_TAB), A(KC_D), A(KC_LEFT), C(KC_W), DM_PLY1,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS, KC_APP, KC_LEFT, KC_DOWN, KC_RGHT, G(KC_DOWN),                                       KC_DEL, MS_BTN1, MS_BTN2, SCRL_MO, G(KC_TAB), CTL_T(KC_MPLY),
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_TRNS, G(KC_I), RCS(KC_ESC), LSA(KC_T), KC_PSCR, A(KC_F4),                                   C(KC_V), C(KC_C), C(KC_Z), C(KC_Y), C(KC_A), C(KC_F),
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
                        G(KC_B), KC_LGUI, KC_LALT,  KC_TRNS,      KC_TRNS,           KC_TRNS,      TO(HOMELIN), KC_TRNS, KC_TRNS,  KC_TRNS,
                                                                 XXXXXXX, KC_MUTE,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
[FUNCTION2] = LAYOUT(
  //|------KC_LEFT-------------------------------------------------|                            |-------------------------------------------------------|
  KC_DEL, KC_PAUS, LAG(KC_TAB), KC_UP, MS_BTN2, MS_BTN1,                                        MS_BTN1, MS_BTN2, KC_UP, LAG(KC_TAB), KC_PAUS, KC_DEL,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  KC_BSPC, KC_LSFT, KC_LSFT,  KC_DOWN, KC_RGHT, SCRL_MO,                                       SCRL_MO, KC_LEFT, KC_DOWN, KC_RGHT, KC_LSFT, KC_BSPC,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
  C(KC_F), C(KC_A), C(KC_Y), C(KC_Z), KC_C, KC_V,                                                C(KC_V), C(KC_C), C(KC_Z), C(KC_Y), C(KC_A), C(KC_F),
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
                         KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,      KC_VOLD,           KC_VOLU,      KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
                                                                 XXXXXXX, TO(HOMEWIN),  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
};

// Same function on all layers for now.
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [1] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [2] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [3] = { ENCODER_CCW_CW(C(KC_MINS), C(KC_PLUS)) },
    [4] = { ENCODER_CCW_CW(C(KC_MINS), C(KC_PLUS)) },
    [5] = { ENCODER_CCW_CW(C(KC_MINS), C(KC_PLUS)) },
    [6] = { ENCODER_CCW_CW(C(KC_Z), C(KC_Y)) },
    [7] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [8] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [9] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [10] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TO_HOMEWIN_R: 
            if (!record->event.pressed) {
                layer_move(HOMEWIN);
            }
            return false;

        case LGUI_T(KC_2):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_AT); 
                return false; 
            }
            break;
            
    }
    return true;
}

void matrix_scan_user(void) {
    layer_state_set_user(layer_state);
    
    #ifdef DYNAMIC_MACRO_ENABLE

    uint16_t on_duration = 500;  
    uint16_t off_duration = 500;  

    if (recording_macro) {
        if (blink_on) {
            // LED is currently on; check if it should turn off.
            if (timer_elapsed(last_blink_time) > on_duration) {
                blink_on = false;
                last_blink_time = timer_read();
                #ifdef RGB_MATRIX_ENABLE
                  rgb_matrix_set_color(1, 0, 0, 0);
                #elif defined(RGBLIGHT_ENABLE)
                  rgblight_setrgb_range(0, 0, 0, 0, 2);
                #endif
            }
        } else {
            if (timer_elapsed(last_blink_time) > off_duration) {
                blink_on = true;
                last_blink_time = timer_read();
                #ifdef RGB_MATRIX_ENABLE
                  rgb_matrix_set_color(1, 255, 255, 255);
                #elif defined(RGBLIGHT_ENABLE)
                  rgblight_setrgb_range(255, 255, 255, 0, 2);
                #endif
            }
        }
    }
#endif

}


layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t current_layer = get_highest_layer(state);
#ifdef RGBLIGHT_ENABLE
    if (get_mods() || host_keyboard_led_state().caps_lock) {
        if (current_layer == FUNCTIONWIN || current_layer == NUMBERWIN || current_layer == NUMBER2) {
            rgblight_sethsv_at(156, 255, 255, 1); //mods
            switch (current_layer) {
                case FUNCTIONWIN:
                case FUNCTIONMAC:
                case FUNCTIONLIN:
                    rgblight_sethsv_at(72, 220, 255, 0);  // FUNCTIONWIN
                    break;
                case NUMBERWIN:
                case NUMBERMAC:
                case NUMBERLIN:
                    rgblight_sethsv_at(180, 200, 255, 0);    // NUMBERWIN
                    break;
                case NUMBER2:
                    rgblight_sethsv_at(180, 255, 255, 0);  // NUMBER2
                    break;
                default:
                    break;
            }
        } else {
            // For other layers, override all LEDs to green as before
            rgblight_sethsv_range(156, 255, 255, 0, 2); //mods
        }
        return state;
    }
    // No modifier: set full LED range based solely on the active layer.
    switch (current_layer) {
        case FUNCTIONWIN:
        case FUNCTIONMAC:
        case FUNCTIONLIN:
            rgblight_sethsv_range(72, 220, 255, 0, 2); //fn
            break;
        case NUMBERWIN:
        case NUMBERMAC:
        case NUMBERLIN:
            rgblight_sethsv_range(180, 200, 255, 0, 2);
            break;
        case NUMBER2:
            rgblight_sethsv_range(190, 255, 255, 0, 2); //num
            break;
        case FUNCTION2:
            rgblight_sethsv_range(82, 255, 255, 0, 2); //fn2
            break;
        default:
            rgblight_sethsv_range(0, 0, 0, 0, 12); //home
            break;
    }
#endif
    return state;
}

