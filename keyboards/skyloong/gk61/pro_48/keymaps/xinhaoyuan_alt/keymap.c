// Copyright 2024 Xinhao Yuan (derived from the default keymap).
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    BASE = 0,
    FN1 = 1,
    FN2 = 2,
    ARR = 3,
    SYS = 4,
};

enum custom_keys {
    _NULLKEY = SAFE_RANGE,
    MY_FN1,
    MY_FN2,
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
         MY_FN1,  KC_LGUI,  KC_LALT,             KC_SPC,   KC_SPC,     KC_MUTE,               MY_FN2,  KC_RALT,     KC_APP,     KC_RCTL,              MO(SYS)
    ),

    [FN1] = LAYOUT_all(
        _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,       KC_F6,    KC_F7,      KC_F8,    KC_F9,      KC_F10,      KC_F11,   KC_F12,    KC_DEL,
          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,  KC_WH_L,    KC_MS_U,  KC_WH_R,     KC_WH_U,       KC_NO,    KC_NO,     KC_NO,
        _______,    KC_NO,  KC_BTN3,  KC_BTN2,  KC_BTN1,    KC_NO,       KC_NO,  KC_MS_L,    KC_MS_D,  KC_MS_R,     KC_WH_D,      KC_GRV,             _______,
        _______,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,  KC_BTN1,    KC_BTN2,  KC_BTN3,       KC_NO,               _______,
        _______,  _______,  _______,            _______,  _______,     _______,              _______,  _______,     _______,     _______,             _______
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

static int shift_press_count = 0;
static int space_press_count = 0;
static int space_hold = 0;

static int layer_lock_count = 0;
static int locked_layer = 0;

static uint16_t last_pressed_keycode = _NULLKEY;
static uint16_t last_pressed_time = 0;

static void lock_layer(int num) {
    space_hold = 0;
    locked_layer = num;
    layer_on(num == 1 ? FN1 : FN2);
}

static void switch_locked_layer(void) {
    if (locked_layer == 1) {
        layer_off(FN1);
        locked_layer = 2;
        layer_on(FN2);
    } else if (locked_layer == 2) {
        layer_off(FN2);
        locked_layer = 1;
        layer_on(FN1);
    }
}

static void unlock_layer(void) {
    if (locked_layer) {
        locked_layer = 0;
        layer_off(FN1);
        layer_off(FN2);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#define IS_TAPPING() (last_pressed_keycode == keycode && timer_elapsed(last_pressed_time) < 150)
    switch (keycode) {
    case KC_LSFT:
        if (record->event.pressed) {
            ++shift_press_count;
        } else {
            --shift_press_count;
            if (IS_TAPPING()) switch_locked_layer();
            if (layer_lock_count > 0 && !locked_layer) lock_layer(1);
        }
        return true;
    case KC_RSFT:
        if (record->event.pressed) {
            ++shift_press_count;
        } else {
            --shift_press_count;
            if (IS_TAPPING()) switch_locked_layer();
            if (layer_lock_count > 0 && !locked_layer) lock_layer(2);
        }
        return true;
    case KC_SPACE:
        if (record->event.pressed) {
            ++layer_lock_count;
            ++space_press_count;
            if (space_press_count == 1 && shift_press_count >= 1 && !space_hold) {
                space_hold = 1;
                return false;
            }
            if (locked_layer) return false;
        } else {
            --layer_lock_count;
            --space_press_count;
            if (layer_lock_count == 0) {
                unlock_layer();
                if (space_hold) {
                    space_hold = 0;
                    register_code(KC_SPACE);
                }
            }
            if (locked_layer) return false;
        }
        return true;
    case MY_FN1:
        if (record->event.pressed) {
            ++layer_lock_count;
            if (layer_lock_count == 1) lock_layer(1);
        } else {
            --layer_lock_count;
            if (layer_lock_count == 0) {
                unlock_layer();
            }
        }
        return false;
    case MY_FN2:
        if (record->event.pressed) {
            ++layer_lock_count;
            if (layer_lock_count == 1) lock_layer(2);
        } else {
            --layer_lock_count;
            if (layer_lock_count == 0) {
                unlock_layer();
            }
        }
        return false;
    default:
        return true; // Process all other keycodes normally
    }
#undef IS_TAPPING
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        last_pressed_keycode = keycode;
        last_pressed_time = timer_read();
    } else {
        last_pressed_keycode = _NULLKEY;
    }
}
