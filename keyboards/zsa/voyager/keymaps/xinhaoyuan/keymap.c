#include QMK_KEYBOARD_H

enum layers {
    L_BASE = 0,
    L_LOWER,
    L_RAISE,
    L_MOUSE,
    L_P_MOUSE,
    L_P_ARROW,
    L_PARA,
};

enum keycodes {
    LOWER = SAFE_RANGE,
    RAISE,
    MY_LGUI,
    MY_RCTL,
    LPSWCH,
    LPTOGG,
    AMTOGG,  // ALTMOD
};

static int layer_lock_count = 0;

static uint16_t pressed_keycode = KC_NO;
static uint16_t pressed_time = 0;
static uint16_t last_pressed_keycode = KC_NO;
static uint16_t last_pressed_time = 0;
static uint16_t last_tapped_keycode = KC_NO;
static uint16_t last_tapped_count = 0;
static bool    my_alt_mod_enabled = 0;
static uint8_t my_mod_mask = 0;
static uint8_t my_alt_mod_mask = 0;

static void clean_up_oneshot(void) {
    uint8_t mods;
    if ((mods = get_oneshot_mods())) {
        clear_oneshot_mods();
        unregister_mods(mods);
    }
}

#define ALWAYS_SET_LAYER 1
#define IN_MOD() (layer_state_is(L_LOWER) || layer_state_is(L_RAISE))

static void layer_lock(int layer) {
    ++layer_lock_count;
    if (ALWAYS_SET_LAYER || layer_lock_count == 1) {
        clean_up_oneshot();
        layer_on(layer);
    }
    if (layer_lock_count > 1) {
        layer_on(L_PARA);
    }
}

static void layer_unlock(int layer) {
    --layer_lock_count;
    if (ALWAYS_SET_LAYER && layer > 0) {
        layer_off(layer);
    }
    if (layer_lock_count == 0) {
        layer_off(L_LOWER);
        layer_off(L_RAISE);
        layer_off(L_MOUSE);
    }
    layer_off(L_PARA);
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

    if (!record->event.pressed) {
        if (last_pressed_keycode == keycode &&
            timer_elapsed(last_pressed_time) < 250) {
            if (last_tapped_keycode == keycode) {
                ++last_tapped_count;
            } else {
                last_tapped_keycode = keycode;
                last_tapped_count = 1;
            }
        } else {
            last_tapped_keycode = KC_NO;
            last_tapped_count = 0;
        }
    } else if (last_tapped_keycode != KC_NO && timer_elapsed(last_pressed_time) > 400) {
        last_tapped_keycode = KC_NO;
        last_tapped_count = 0;
    }

#define HANDLE_MOD(ALT_KEY)                                             \
    do {                                                                \
        if (record->event.pressed) {                                    \
            if (IN_MOD()) {                                             \
                if ((get_oneshot_mods() & MOD_BIT(keycode)) == 0) {     \
                    add_oneshot_mods(MOD_BIT(keycode));                 \
                    add_mods(MOD_BIT(keycode));                         \
                    my_mod_mask |= MOD_BIT(keycode);                    \
                } else {                                                \
                    del_oneshot_mods(MOD_BIT(keycode));                 \
                    del_mods(MOD_BIT(keycode));                         \
                    my_mod_mask ^= MOD_BIT(keycode);                    \
                    add_oneshot_mods(MOD_BIT(ALT_KEY));                 \
                    add_mods(MOD_BIT(ALT_KEY));                         \
                    my_alt_mod_mask |= MOD_BIT(keycode);                \
                }                                                       \
            } else {                                                    \
                if (my_alt_mod_enabled &&                               \
                    last_tapped_keycode == keycode &&                   \
                    timer_elapsed(last_pressed_time) < 300)  {          \
                    my_alt_mod_mask |= MOD_BIT(keycode);                \
                    register_mods(MOD_BIT(ALT_KEY));                    \
                } else {                                                \
                    register_mods(MOD_BIT(keycode));                    \
                    my_mod_mask |= MOD_BIT(keycode);                    \
                }                                                       \
            }                                                           \
        } else {                                                        \
            if ((my_alt_mod_mask & MOD_BIT(keycode))) {                 \
                my_alt_mod_mask ^= MOD_BIT(keycode);                    \
                unregister_mods(MOD_BIT(ALT_KEY));                      \
            }                                                           \
            if ((my_mod_mask & MOD_BIT(keycode))) {                     \
                my_mod_mask ^= MOD_BIT(keycode);                        \
                unregister_mods(MOD_BIT(keycode));                      \
            }                                                           \
        }                                                               \
        return false;                                                   \
    } while (0)

#define HANDLE_MOUSE_LAYER()                                            \
    do {                                                                \
        if (!record->event.pressed) {                                   \
            if (llast_pressed_keycode == keycode && (last_pressed_keycode == LOWER || last_pressed_keycode == RAISE)) { \
                layer_unlock(0);                                        \
                layer_lock(L_MOUSE);                                    \
            }                                                           \
        }                                                               \
    } while (0)

    switch (keycode) {
    case LOWER:
        if (record->event.pressed) {
            if (last_tapped_keycode == keycode)  {
                layer_lock(last_tapped_count == 1 ? L_RAISE : L_PARA);
            } else {
                layer_lock(L_LOWER);
            }
        } else {
                layer_unlock(L_LOWER);
        }
        return false;
    case RAISE:
        if (record->event.pressed) {
            if (last_tapped_keycode == keycode)  {
                layer_lock(last_tapped_count == 1 ? L_LOWER : L_PARA);
            } else {
                layer_lock(L_RAISE);
            }
        } else {
            layer_unlock(L_RAISE);
        }
        return false;
    case MY_LGUI:
        if (record->event.pressed) {
            register_mods(MOD_BIT(KC_LGUI));
        } else {
            unregister_mods(MOD_BIT(KC_LGUI));
        }
        return false;
    case MY_RCTL:
        if (record->event.pressed) {
            register_mods(MOD_BIT(KC_RCTL));
        } else {
            unregister_mods(MOD_BIT(KC_RCTL));
        }
        return false;
    case KC_LCTL:
        HANDLE_MOD(KC_LGUI);
        break;
    case KC_RCTL:
        HANDLE_MOD(KC_RGUI);
        break;
    case KC_LALT:
        HANDLE_MOD(KC_LSFT);
        break;
    case KC_RALT:
        HANDLE_MOUSE_LAYER();
        HANDLE_MOD(KC_RSFT);
        break;
    case KC_LGUI:
        HANDLE_MOD(KC_LCTL);
        break;
    case KC_RGUI:
        HANDLE_MOD(KC_RCTL);
        break;
    case KC_LSFT:
        HANDLE_MOUSE_LAYER();
        HANDLE_MOD(KC_LALT);
        break;
    case KC_RSFT:
        HANDLE_MOD(KC_RALT);
        break;
    case LPSWCH:
        if (record->event.pressed) {
            if (layer_state_is(L_P_MOUSE)) {
                layer_off(L_P_MOUSE);
                layer_on(L_P_ARROW);
            } else {
                layer_off(L_P_ARROW);
                layer_on(L_P_MOUSE);
            }
        }
        return false;
    case LPTOGG:
        if (record->event.pressed) {
            if (layer_state_is(L_P_ARROW) || layer_state_is(L_P_MOUSE)) {
                layer_off(L_P_ARROW);
                layer_off(L_P_MOUSE);
            } else {
                layer_on(L_P_ARROW);
            }
        }
        return false;
    case AMTOGG:
        if (record->event.pressed) my_alt_mod_enabled = !my_alt_mod_enabled;
        return false;
    }
    return true;
#undef IS_TAPPING
#undef HANDLE_MOD
#undef HANDLE_MOUSE_LAYER
}

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
        QK_BOOT, UG_HUEU, UG_SATU, UG_VALU, KC_NO,   KC_VOLU, LPTOGG,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        _______, UG_HUED, UG_SATD, UG_VALD, KC_NO,   KC_VOLD, LPSWCH,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______,
        _______, UG_TOGG, RGB_M_P, UG_NEXT, KC_CAPS, KC_MUTE, KC_NO,   AMTOGG,  KC_NO,   KC_NO,   KC_NO,   _______,
        _______, QK_BOOT, _______, _______, _______, KC_NO,   KC_NO,   _______, _______, _______, KC_NO,   _______,
                                            KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),
};

#undef _LAYOUT
