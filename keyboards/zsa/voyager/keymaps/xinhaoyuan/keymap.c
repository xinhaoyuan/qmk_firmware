#include QMK_KEYBOARD_H

#include "../../../../xinhaoyuan_common.inc.c"

#define _LAYOUT LAYOUT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = _LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RGUI,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RALT,
        RAISE,   KC_ESC,  KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_ENT,  RAISE,   KC_RSFT, KC_RCTL, KC_ESC,  LOWER,
                                            KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [L_LOWER] = _LAYOUT(
        KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, KC_GRV,  KC_LBRC, KC_RBRC, CW_TOGG, MY_LGUI, KC_NO,   KC_QUOT, KC_MINS, KC_EQL,  KC_BSLS, _______,
        _______, KC_NO,   _______, _______, _______, KC_SPC,  KC_ENT,  _______, _______, _______, KC_NO,   _______,
                                            KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [L_RAISE] = _LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_DEL,
        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
        _______, KC_TILD, KC_LCBR, KC_RCBR, KC_F11,  KC_F12,  MY_RCTL, KC_DQT,  KC_UNDS, KC_PLUS, KC_PIPE, _______,
        _______, KC_NO,   _______, _______, _______, KC_SPC,  KC_ENT,  _______, _______, _______, KC_NO,   _______,
                                            KC_NO,   KC_NO,   KC_NO,  KC_NO
    ),

    [L_MOUSE] = _LAYOUT(
        KC_NO,   KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_NO,   KC_NO,   KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, KC_NO,
        _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,   KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,
        _______, KC_NO,   KC_BTN3, KC_BTN2, KC_BTN1, KC_NO,   KC_NO,   KC_BTN1, KC_BTN2, KC_BTN3, KC_NO,   _______,
        _______, KC_NO,   _______, _______, _______, KC_NO,   KC_NO,   _______, _______, _______, KC_NO,   _______,
                                            KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [L_P_MOUSE] = _LAYOUT(
        LPSWCH,  KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_NO,   KC_NO,   KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, LPSWCH,
        _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,   KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,
        _______, KC_NO,   KC_BTN3, KC_BTN2, KC_BTN1, KC_NO,   KC_NO,   KC_BTN1, KC_BTN2, KC_BTN3, KC_NO,   _______,
        _______, LPTOGG,  _______, _______, _______, KC_NO,   KC_NO,   _______, _______, _______, LPTOGG,  _______,
                                            KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [L_P_ARROW] = _LAYOUT(
        LPSWCH,  KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_NO,   KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_PGUP, LPSWCH,
        _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
        _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______,
        _______, LPTOGG,  _______, _______, _______, KC_NO,   KC_NO,   _______, _______, _______, LPTOGG,  _______,
                                            KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [L_PARA] = _LAYOUT(
        KC_NO,   UG_HUEU, UG_SATU, UG_VALU, KC_NO,   KC_VOLU, LPTOGG,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        _______, UG_HUED, UG_SATD, UG_VALD, KC_NO,   KC_VOLD, LPSWCH,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______,
        _______, UG_TOGG, RGB_M_P, UG_NEXT, KC_CAPS, KC_MUTE, OMTOGG,  AMTOGG,  KC_NO,   KC_NO,   KC_NO,   _______,
        _______, KC_NO,   _______, _______, _______, KC_NO,   KC_NO,   _______, _______, _______, KC_NO,   _______,
                                            KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),
};

#undef _LAYOUT
