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

enum preonic_layers {
    L_BASE = 0,
    L_LOWER,
    L_RAISE,
    L_MOUSE,
    L_PARA,
};

enum preonic_keycodes {
    LOWER = SAFE_RANGE,
    RAISE,
};

#define OS_LSFT OSM(MOD_LSFT)
#define OS_LALT OSM(MOD_LALT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LGUI OSM(MOD_LGUI)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_RALT OSM(MOD_RALT)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RGUI OSM(MOD_RGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [L_BASE] = LAYOUT_preonic_grid(
        KC_NO,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,
     // KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        RAISE,   KC_ESC,  KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RALT, KC_RGUI, KC_RCTL, LOWER
    ),

    [L_LOWER] = LAYOUT_preonic_grid(
        KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
     // KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        OS_LCTL, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
        OS_LSFT, KC_GRV,  KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,  KC_NO,   KC_QUOT, KC_MINS, KC_EQL,  KC_BSLS, OS_RSFT,
        _______, KC_NO,   OS_LGUI, OS_LALT, _______, KC_NO,   KC_NO,   _______, OS_RALT, OS_RGUI, OS_RCTL, _______
    ),

    [L_RAISE] = LAYOUT_preonic_grid(
        KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
     // KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_DEL,
        OS_LCTL, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_F12,
        OS_LSFT, KC_TILD, KC_LCBR, KC_RCBR, KC_F11,  KC_F12,  KC_NO,   KC_DQT,  KC_UNDS, KC_PLUS, KC_PIPE, OS_RSFT,
        _______, KC_NO,   OS_LGUI, OS_LALT, _______, KC_NO,   KC_NO,   _______, OS_RALT, OS_RGUI, OS_RCTL, _______
    ),

    [L_MOUSE] = LAYOUT_preonic_grid(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_NO,   KC_NO,   KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, KC_NO,
        _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,   KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_NO,
        _______, KC_NO,   KC_BTN3, KC_BTN2, KC_BTN1, KC_NO,   KC_NO,   KC_BTN1, KC_BTN2, KC_BTN3, KC_NO,   _______,
        _______, KC_NO,   _______, _______, _______, KC_NO,   KC_NO,   _______, _______, _______, _______, _______
    ),

    [L_PARA] = LAYOUT_preonic_grid(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_VOLU, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_VOLD, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______,
        _______, QK_BOOT, _______, _______, _______, KC_NO,   KC_NO,   _______, _______, _______, _______, _______
    ),

};

static int layer_lock_count = 0;

static uint16_t pressed_keycode = KC_NO;
static uint16_t pressed_time = 0;
static uint16_t last_pressed_keycode = KC_NO;
static uint16_t last_pressed_time = 0;

static void clean_up_oneshot(void) {
    uint8_t mods;
    if ((mods = get_oneshot_mods())) {
        clear_oneshot_mods();
        unregister_mods(mods);
    }
}

static void layer_lock(int layer) {
    ++layer_lock_count;
    if (layer_lock_count == 1) {
        clean_up_oneshot();
        layer_on(layer);
    } else {
        layer_on(L_PARA);
    }
}

static void layer_unlock(void) {
    --layer_lock_count;
    if (layer_lock_count == 0) {
        layer_off(L_LOWER);
        layer_off(L_RAISE);
        layer_off(L_MOUSE);
    } else {
        layer_off(L_PARA);
    }
}

static __attribute__((unused)) void switch_layer_lock(void) {
    if (layer_lock_count != 1) return;
    if (layer_state_is(L_LOWER)) {
        layer_off(L_LOWER);
        layer_on(L_RAISE);
    } else if (layer_state_is(L_RAISE)) {
        layer_off(L_RAISE);
        layer_on(L_LOWER);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint16_t llast_pressed_keycode = last_pressed_keycode;
    last_pressed_keycode = pressed_keycode;
    last_pressed_time = pressed_time;
    if (record->event.pressed) {
        pressed_keycode = keycode;
        pressed_time = timer_read();
    } else {
        pressed_keycode = KC_NO;
    }

#define IS_TAPPING() (last_pressed_keycode == keycode && timer_elapsed(last_pressed_time) < 300)
    switch (keycode) {
    case LOWER:
        if (record->event.pressed) {
            layer_lock(L_LOWER);
        } else {
            layer_unlock();
        }
        break;
    case RAISE:
        if (record->event.pressed) {
            layer_lock(L_RAISE);
        } else {
            layer_unlock();
        }
        break;
    case KC_LSFT:
    case KC_RSFT:
        if (!record->event.pressed && llast_pressed_keycode == keycode && (last_pressed_keycode == LOWER || last_pressed_keycode == RAISE)) {
            layer_unlock();
            layer_lock(L_MOUSE);
        }
        break;
    }
    return true;
#undef IS_TAPPING
}
