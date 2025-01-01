// Copyright 2024 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "oled.h"

uint16_t last_repos_time = 0;
uint8_t repos_lines = 0;

__attribute__((weak)) void get_feature_chars(char* output, size_t output_size);

void render_layer_state(void) {
    #define TOTAL_LINES 15
    const int lines = 3 + 3 + (get_feature_chars ? 2 : 0);
    if (last_repos_time == 0 || timer_elapsed(last_repos_time) > 10000) {
        last_repos_time = timer_read();
        repos_lines = rand() % (TOTAL_LINES - lines + 1);
        oled_clear();
    }
    for (uint8_t i = 0; i < repos_lines; ++i) {
        oled_advance_page(false);
    }
    oled_write_P(PSTR("Layer"), true);
    static const char layer_chars[8] = "BLRMamP ";
    for (uint8_t l = 0; l < 4; ++l) {
        oled_write_char(layer_chars[l], IS_LAYER_ON(l));
    }
    oled_advance_page(false);
    for (uint8_t l = 4; l < 8; ++l) {
        oled_write_char(layer_chars[l], IS_LAYER_ON(l));
    }
    oled_advance_page(false);
    oled_write_P(PSTR("Mod  "), true);
    static const uint8_t mod_masks[] = {
        MOD_BIT(KC_LCTL),
        MOD_BIT(KC_LGUI),
        MOD_BIT(KC_LALT),
        MOD_BIT(KC_LSFT),
        MOD_BIT(KC_RCTL),
        MOD_BIT(KC_RGUI),
        MOD_BIT(KC_RALT),
        MOD_BIT(KC_RSFT),
    };
    static const char mod_chars[8] = "CGASCGAS";
    uint8_t mods = get_mods();
    oled_write_char('L', false);
    for (uint8_t l = 0; l < 4; ++l) {
        oled_write_char(mod_chars[l], mods & mod_masks[l]);
    }
    oled_write_char('R', false);
    for (uint8_t l = 4; l < 8; ++l) {
        oled_write_char(mod_chars[l], mods & mod_masks[l]);
    }
    if (get_feature_chars) {
        oled_write_P(PSTR("Feat "), true);
        char feats[6];
        get_feature_chars(feats, 5);
        feats[5] = 0;
        oled_write(feats, false);
    }
}
