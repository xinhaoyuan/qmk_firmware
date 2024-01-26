// Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum tap_dance_keys {
  L2_THEN_L1 = 0
};

enum layers {
    BASE = 0,
    FN1 = 1,
    FN2 = 2,
    ARR = 3,
    SYS = 4,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Bsp│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab│ Q │ W │ E | R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \ │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Cap│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │   |Ent│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │   |Sft|   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│GUI│Alt│   │Spc│Mut│   │   |Spc|Alt│App│Ctl│   │Mo1|
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [BASE] = LAYOUT_all(
         KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,     KC_7,       KC_8,     KC_9,        KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,
         KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,     KC_U,       KC_I,     KC_O,        KC_P,     KC_LBRC,  KC_RBRC,   KC_BSLS,
        KC_LCTL,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,     KC_J,       KC_K,     KC_L,     KC_SCLN,     KC_QUOT,              KC_ENT,
        KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,     KC_M,    KC_COMM,   KC_DOT,     KC_SLSH,               KC_RSFT,
        MO(FN1),  KC_LGUI,  KC_LALT,             KC_SPC,   KC_SPC,     KC_MUTE,        TD(L2_THEN_L1),  KC_RALT,     KC_APP,     KC_RCTL,             MO(SYS)
    ),

    [FN1] = LAYOUT_all(
        _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,       KC_F6,    KC_F7,      KC_F8,    KC_F9,      KC_F10,      KC_F11,   KC_F12,    KC_DEL,
          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,  KC_WH_L,    KC_MS_U,  KC_WH_R,     KC_WH_U,       KC_NO,    KC_NO,     KC_NO,
        _______,    KC_NO,  KC_BTN3,  KC_BTN2,  KC_BTN1,    KC_NO,       KC_NO,  KC_MS_L,    KC_MS_D,  KC_MS_R,     KC_WH_D,      KC_GRV,             _______,
        _______,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,  KC_BTN1,    KC_BTN2,  KC_BTN3,       KC_NO,               _______,
        _______,  _______,  _______,            _______,  _______,     _______,              MO(SYS),  _______,     _______,     _______,             _______
    ),

    [FN2] = LAYOUT_all(
        _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,       KC_F6,    KC_F7,      KC_F8,    KC_F9,      KC_F10,      KC_F11,   KC_F12,    KC_DEL,
          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,  KC_HOME,      KC_UP,   KC_END,     KC_PGUP,       KC_NO,    KC_NO,     KC_NO,
        _______,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,  KC_LEFT,    KC_DOWN, KC_RIGHT,     KC_PGDN,      KC_GRV,             _______,
        _______,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,      KC_NO,    KC_NO,       KC_NO,               _______,
        MO(SYS),  _______,  _______,            _______,  _______,     _______,              _______,  _______,     _______,     _______,             _______
    ),

    [ARR] = LAYOUT_all(
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,    _______,  _______,     _______,     _______,  _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,    _______,  _______,     _______,     _______,  _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,    _______,  _______,     _______,     _______,             _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,    _______,  _______,       KC_UP,               _______,
        _______,  _______,  _______,            _______,  _______,     _______,              _______,  KC_LEFT,     KC_DOWN,    KC_RIGHT,             MO(SYS)
    ),

    [SYS] = LAYOUT_all(
        QK_BOOT,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,      KC_NO,    KC_NO,       KC_NO,       KC_NO,    KC_NO,     KC_NO,
        RGB_TOG,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,      KC_NO,    KC_NO,       KC_NO,       KC_NO,    KC_NO,     KC_NO,
        KC_CAPS,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,      KC_NO,    KC_NO,       KC_NO,       KC_NO,               KC_NO,
          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,      KC_NO,    KC_NO,     KC_PGUP,                 KC_NO,
          KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,     RGB_M_P,              TG(ARR),  KC_HOME,     KC_PGDN,      KC_END,               KC_NO
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [FN1]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [FN2]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [ARR]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [SYS]  = { ENCODER_CCW_CW(RGB_VAI, RGB_HUI) },
};
#endif

void L2_THEN_L1_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
      layer_on(FN2);
  } else {
      layer_on(FN1);
  }
}

void L2_THEN_L1_reset(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
      layer_off(FN2);
  } else {
      layer_off(FN1);
  }
}

tap_dance_action_t tap_dance_actions[] = {
  [L2_THEN_L1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, L2_THEN_L1_finished, L2_THEN_L1_reset),
};
