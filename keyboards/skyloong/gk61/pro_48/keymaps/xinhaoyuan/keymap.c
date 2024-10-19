// Copyright 2024 Xinhao Yuan (derived from the default keymap).
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "../../../../../xinhaoyuan_common.inc.c"

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
    [L_BASE] = LAYOUT_all(
         KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,     KC_7,       KC_8,     KC_9,        KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,
         KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,     KC_U,       KC_I,     KC_O,        KC_P,     KC_LBRC,  KC_RBRC,   KC_BSLS,
        KC_LCTL,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,     KC_J,       KC_K,     KC_L,     KC_SCLN,     KC_QUOT,              KC_ENT,
        KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,     KC_M,    KC_COMM,   KC_DOT,     KC_SLSH,               KC_RSFT,
          LOWER,  KC_LGUI,  KC_LALT,             KC_SPC,   KC_SPC,     KC_MUTE,                LOWER,  KC_RALT,     KC_RGUI,     KC_RCTL,               LOWER
    ),

    [L_LOWER] = LAYOUT_all(
        _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,       KC_F6,    KC_F7,      KC_F8,    KC_F9,      KC_F10,      KC_F11,   KC_F12,    KC_DEL,
          KC_NO,  KC_PGUP,  KC_HOME,    KC_UP,   KC_END,    KC_NO,       KC_NO,  KC_HOME,      KC_UP,   KC_END,     KC_PGUP,       KC_NO,    KC_NO,     KC_NO,
        _______,  KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,    KC_NO,       KC_NO,  KC_LEFT,    KC_DOWN, KC_RIGHT,     KC_PGDN,      KC_GRV,             _______,
        _______,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,      KC_NO,    KC_NO,       KC_NO,               _______,
        _______,  _______,  _______,            _______,  _______,     _______,              _______,  _______,     _______,     _______,             _______
    ),

    [L_MOUSE] = LAYOUT_all(
          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,      KC_NO,    KC_NO,       KC_NO,       KC_NO,    KC_NO,     KC_NO,
          KC_NO,  KC_WH_U,  KC_WH_L,  KC_MS_U,  KC_WH_R,    KC_NO,       KC_NO,  KC_WH_L,    KC_MS_U,  KC_WH_R,     KC_WH_U,       KC_NO,    KC_NO,     KC_NO,
        _______,  KC_WH_D,  KC_MS_L,  KC_MS_D,  KC_MS_R,    KC_NO,       KC_NO,  KC_MS_L,    KC_MS_D,  KC_MS_R,     KC_WH_D,       KC_NO,             _______,
        _______,    KC_NO,  KC_BTN3,  KC_BTN2,  KC_BTN1,    KC_NO,       KC_NO,  KC_BTN1,    KC_BTN2,  KC_BTN3,       KC_NO,               _______,
        _______,  _______,  _______,            _______,  _______,     _______,              _______,  _______,     _______,     _______,             _______
    ),

    [L_PARA] = LAYOUT_all(
        QK_BOOT,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,      KC_NO,    KC_NO,       KC_NO,       KC_NO,    KC_NO,     KC_NO,
        RGB_TOG,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,      KC_NO,    KC_NO,       KC_NO,       KC_NO,    KC_NO,     KC_NO,
        KC_CAPS,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,      KC_NO,    KC_NO,       KC_NO,       KC_NO,               KC_NO,
          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,      KC_NO,    KC_NO,       KC_NO,                 KC_NO,
          KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,     RGB_M_P,                KC_NO,    KC_NO,       KC_NO,       KC_NO,               KC_NO
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [L_BASE]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [L_LOWER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [L_MOUSE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [L_PARA]  = { ENCODER_CCW_CW(RGB_VAI, RGB_HUI) },
};
#endif
