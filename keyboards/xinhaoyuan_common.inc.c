enum layers {
    L_BASE = 0,
    L_LOWER,
    L_RAISE,
    L_MOUSE,
    L_P_MOUSE,
    L_P_ARROW,
    L_PARA,
    L__END,
};

enum keycodes {
    LOWER = SAFE_RANGE,
    RAISE,
    MY_LGUI,
    MY_RCTL,
    LPSWCH,
    LPTOGG,
    AMTOGG,  // Alternative Mod
    OMTOGG,  // Oneshot Mod
};

static uint16_t pressed_keycode = KC_NO;
static uint16_t pressed_time = 0;
static uint16_t last_pressed_keycode = KC_NO;
static uint16_t last_pressed_time = 0;
static uint16_t last_tapped_keycode = KC_NO;
static uint16_t last_tapped_count = 0;
static bool    my_alt_mod_enabled = 0;
static bool    my_oneshot_mod_enabled = 0;
static uint8_t my_mod_mask = 0;
static uint8_t my_alt_mod_mask = 0;
// MetaMod: lower and raise
static uint8_t mm_press_count[2] = {0};
static uint8_t mm_layer[2] = {0};
static uint8_t mm_layer_ref[L__END] = {0};

static void clean_up_oneshot(void) {
    uint8_t mods;
    if ((mods = get_oneshot_mods())) {
        clear_oneshot_mods();
        unregister_mods(mods);
    }
}

#define ALWAYS_SET_LAYER 1
#define IN_LOWER_OR_RAISE() (layer_state_is(L_LOWER) || layer_state_is(L_RAISE))

static void mm_register_layer(int layer) {
    if (++mm_layer_ref[layer] == 1) layer_on(layer);
}

static void mm_unregister_layer(int layer) {
    if (mm_layer_ref[layer] == 0) return;
    if (--mm_layer_ref[layer] == 0) layer_off(layer);
}

static void update_para_layer(void) {
    if (mm_layer_ref[L_PARA] > 0 || (mm_layer_ref[L_LOWER] > 0 && mm_layer_ref[L_RAISE] > 0 )) {
        clean_up_oneshot();
        layer_on(L_PARA);
    } else {
        layer_off(L_PARA);
    }
}

static void mm_register(int index, int layer) {
    if (++mm_press_count[index] == 1 || layer > 0) {
        if (mm_layer[index] > 0) mm_unregister_layer(mm_layer[index]);
        mm_layer[index] = layer;
        mm_register_layer(layer);
    }
    update_para_layer();
}

static void mm_register_weak(int index, int layer) {
    mm_register(index, mm_layer[index] == 0 ? layer : mm_layer[index]);
}

static void mm_unregister(int index) {
    if (mm_press_count[index] == 0) return;
    if (--mm_press_count[index] == 0 && mm_layer[index] > 0) {
        mm_unregister_layer(mm_layer[index]);
        mm_layer[index] = 0;
    }
    update_para_layer();
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
            if (my_oneshot_mod_enabled && IN_LOWER_OR_RAISE()) {        \
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
                mm_unregister(last_pressed_keycode == LOWER ? 0 : 1);   \
                register_code(KC_F24);                                  \
                unregister_code(KC_F24);                                \
                mm_register(last_pressed_keycode == LOWER ? 0 : 1, L);  \
            }                                                           \
        }                                                               \
    } while (0)

    switch (keycode) {
    case LOWER:
        if (record->event.pressed) {
            if (my_alt_mod_enabled && last_tapped_keycode == keycode)  {
                mm_register(0, L_RAISE);
            } else {
                mm_register_weak(0, L_LOWER);
            }
        } else {
            mm_unregister(0);
        }
        return false;
    case RAISE:
        if (record->event.pressed) {
            if (my_alt_mod_enabled && last_tapped_keycode == keycode)  {
                mm_register(1, L_LOWER);
            } else {
                mm_register_weak(1, L_RAISE);
            }
        } else {
            mm_unregister(1);
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
        HANDLE_ZIG_LAYER(L_MOUSE);
        HANDLE_MOD(KC_LGUI);
        break;
    case KC_LALT:
        HANDLE_MOD(KC_LSFT);
        break;
    case KC_LGUI:
        HANDLE_MOD(KC_LCTL);
        break;
    case KC_LSFT:
        HANDLE_ZIG_LAYER(L_PARA);
        HANDLE_MOD(KC_LALT);
        break;
    case KC_RCTL:
        HANDLE_MOD(KC_RGUI);
        break;
    case KC_RALT:
        HANDLE_ZIG_LAYER(L_PARA);
        HANDLE_MOD(KC_RSFT);
        break;
    case KC_RGUI:
        HANDLE_ZIG_LAYER(L_MOUSE);
        HANDLE_MOD(KC_RCTL);
        break;
    case KC_RSFT:
        HANDLE_ZIG_LAYER(L_MOUSE);
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
    case OMTOGG:
        if (record->event.pressed) my_oneshot_mod_enabled = !my_oneshot_mod_enabled;
        return false;
    }
    return true;
#undef IS_TAPPING
#undef HANDLE_MOD
#undef HANDLE_MOUSE_LAYER
}
