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

#include "../../../xinhaoyuan_common.inc.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [L_BASE] = LAYOUT_planck_grid(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RGUI,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RALT,
        RAISE,   KC_ESC,  KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_ENT,  RAISE,   KC_RSFT, KC_RCTL, KC_ESC,  LOWER
    ),

    [L_LOWER] = LAYOUT_planck_grid(
        KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, KC_GRV,  KC_LBRC, KC_RBRC, KC_NO,   KC_NO,   CW_TOGG, KC_QUOT, KC_MINS, KC_EQL,  KC_BSLS, _______,
        _______, KC_NO,   _______, _______, _______, KC_SPC,  KC_ENT,  _______, _______, _______, KC_NO,   _______
    ),

    [L_RAISE] = LAYOUT_planck_grid(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_DEL,
        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
        _______, KC_TILD, KC_LCBR, KC_RCBR, KC_F11,  KC_F12,  KC_NO,   KC_DQT,  KC_UNDS, KC_PLUS, KC_PIPE, _______,
        _______, KC_NO,   _______, _______, _______, KC_SPC,  KC_ENT,  _______, _______, _______, KC_NO,   _______
    ),

    [L_MOUSE] = LAYOUT_planck_grid(
        KC_NO,   KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_NO,   KC_NO,   KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, KC_NO,
        _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,
        _______, KC_NO,   KC_BTN3, KC_BTN2, KC_BTN1, KC_NO,   KC_NO,   KC_BTN1, KC_BTN2, KC_BTN3, KC_NO,   _______,
        _______, KC_NO,   _______, _______, _______, KC_NO,   KC_NO,   _______, _______, _______, KC_NO,   _______
    ),

    [L_P1] = LAYOUT_planck_grid(
        LPTOGG,  KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_NO,   KC_NO,   KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, LPTOGG,
        _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,
        _______, KC_NO,   KC_BTN3, KC_BTN2, KC_BTN1, KC_NO,   KC_NO,   KC_BTN1, KC_BTN2, KC_BTN3, KC_NO,   _______,
        _______, LPTOGG,  _______, _______, _______, KC_NO,   KC_NO,   _______, _______, _______, LPTOGG,  _______
    ),

    [L_PARA] = LAYOUT_planck_grid(
        KC_NO,   UG_HUEU, UG_NEXT, KC_NO,   KC_VOLU, AMTOGG,  AMTOGG,  KC_VOLU, KC_NO,   UG_NEXT, UG_HUEU, KC_NO,
        _______, UG_SATU, RGB_M_P, KC_NO,   KC_VOLD, OMTOGG,  OMTOGG,  KC_VOLD, KC_NO,   RGB_M_P, UG_SATU, _______,
        _______, UG_VALU, UG_TOGG, KC_NO,   KC_MUTE, LPTOGG,  LPTOGG,  KC_MUTE, KC_NO,   UG_TOGG, UG_VALU, _______,
        _______, QK_BOOT, _______, _______, _______, KC_NO,   KC_NO,   _______, _______, _______, QK_BOOT, _______
    ),

};
