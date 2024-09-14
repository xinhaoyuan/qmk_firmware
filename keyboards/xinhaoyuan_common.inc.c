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

#define HANDLE_ZIG_LAYER(L)                                             \
    do {                                                                \
        if (!record->event.pressed) {                                   \
            if (llast_pressed_keycode == keycode &&                     \
                (last_pressed_keycode == LOWER ||                       \
                 last_pressed_keycode == RAISE)) {                      \
                layer_unlock(0);                                        \
                register_code(KC_F24);                                  \
                unregister_code(KC_F24);                                \
                layer_lock(L);                                          \
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
        HANDLE_ZIG_LAYER(L_MOUSE);
        HANDLE_MOD(KC_RSFT);
        break;
    case KC_LGUI:
        HANDLE_MOD(KC_LCTL);
        break;
    case KC_RGUI:
        HANDLE_MOD(KC_RCTL);
        break;
    case KC_LSFT:
        HANDLE_ZIG_LAYER(L_MOUSE);
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
