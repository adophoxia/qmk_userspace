/* Copyright 2024 @Adophoxia

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include "indicators.h"
#include "lib/lib8tion/lib8tion.h"

#define ARRAYSIZE(arr) sizeof(arr)/sizeof(arr[0])

//Reference LED Indexes
/*
__attribute__ ((weak)) led_config_t g_led_config = {
    {
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
        { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 },
        { 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 65, 42, 43 },
        { 44, NO_LED, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, NO_LED, 55, 56 },
        { 57, 58, 59, NO_LED, NO_LED, NO_LED, 60, NO_LED, NO_LED, NO_LED, 61, 62, 63, 64, 66 },
    },
    {
        // LED Index to Physical Position
        {0,0},  {15,0},  {29,0},  {44,0},  {59,0},  {73,0},  {88,0},  {103,0},  {118,0},  {132,0},  {147,0},  {162,0},  {176,0},  {198,0},            {224,0},
        {4,15}, {22,15}, {37,15}, {51,15}, {66,15}, {81,15}, {95,15}, {110,15}, {125,15}, {140,15}, {154,15}, {169,15}, {184,15}, {202,15},           {224,15},
        {6,30}, {26,30}, {40,30}, {55,30}, {70,30}, {84,30}, {99,30}, {114,30}, {129,30}, {143,30}, {158,30}, {173,30},           {196,30},           {224,30},
        {9,45},          {33,45}, {48,45}, {62,45}, {77,45}, {92,45}, {106,45}, {121,45}, {136,45}, {151,45}, {165,45},           {185,45}, {209,49},
        {2,60}, {20,60}, {39,60},                            {94,60},                               {147,60}, {162,60}, {176,60}, {195,64}, {209,64}, {224,64}
    },
    {
        // RGB LED Index to Flag
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,    1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 1,
        1, 1, 1,          4,          1, 1, 1, 1, 1, 1
    }
};
*/

/*
    {  0,  1,  2,  3 },
    {  4,  5,  6,  7 },
    {  8,  9, 10, 14 },
    { 11, 12, 13, __ },
    { 15, 16, 17, 20 },
    { 18, __, 19, __ }
*/

uint8_t alphabets[] = {
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    31, 32, 33, 34, 35, 36, 37, 38, 39,
    45, 46, 47, 48, 49, 50, 51,
};

uint8_t alphas[] = {
    26, 27, 28,
    40, 41,
    52, 53, 54,
};

uint8_t multimedia_f_row[] = {
    1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
};

uint8_t numlock_arrows[] = {
    9, 11, 13, 16
};

uint8_t fn_keys[] = {
    4, 5, 6,
    8, 9, 10,
    11, 12, 13,
    15, 16, 17
};

uint8_t fn2_modifiers_keys[] = {
    1, 2, 3
};

void numlock_arrows_indicators() {
    if (!host_keyboard_led_state().num_lock) {
        for (uint8_t i = 0; i < ARRAYSIZE(numlock_arrows); i++) {
            rgb_matrix_set_color(numlock_arrows[i], RGB_BLUE);
        }
        rgb_matrix_set_color(NUM_LOCK_LED_INDEX, RGB_WHITE);
    } else {
        if (!rgb_matrix_get_flags()) {
            rgb_matrix_set_color(NUM_LOCK_LED_INDEX, RGB_BLACK);
        }
    }
}

void fn_keys_indicators() {
    for (uint8_t i = 0; i < ARRAYSIZE(fn_keys); i++) {
        rgb_matrix_set_color(fn_keys[i], RGB_PURPLE);
    }
}

void fn2_modifiers() {
    for (uint8_t i = 0; i < ARRAYSIZE(fn2_modifiers_keys); i++) {
        rgb_matrix_set_color(fn2_modifiers_keys[i], RGB_PINK);    
    }
}

bool rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            numlock_arrows_indicators();
            rgb_matrix_set_color(0, RGB_RED);
        break;
        case _FN1:
            fn_keys_indicators();
            fn2_modifiers();
            rgb_matrix_set_color(0, RGB_GREEN);
        break;
        case _FN2:
            rgb_matrix_set_color(0, RGB_BLUE);
        break;
    }
    return false;
}

void f_row_leds() {
    for (uint8_t i = 0; i < ARRAYSIZE(multimedia_f_row); i++) {
        rgb_matrix_set_color(multimedia_f_row[0], RGB_RED);
        rgb_matrix_set_color(multimedia_f_row[1], RGB_RED);

        rgb_matrix_set_color(multimedia_f_row[2], RGB_ORANGE);
        rgb_matrix_set_color(multimedia_f_row[3], RGB_ORANGE);

        rgb_matrix_set_color(multimedia_f_row[4], RGB_YELLOW);
        rgb_matrix_set_color(multimedia_f_row[5], RGB_YELLOW);

        rgb_matrix_set_color(multimedia_f_row[6], RGB_GREEN);
        rgb_matrix_set_color(multimedia_f_row[7], RGB_GREEN);
        rgb_matrix_set_color(multimedia_f_row[8], RGB_GREEN);

        rgb_matrix_set_color(multimedia_f_row[9], RGB_BLUE);
        rgb_matrix_set_color(multimedia_f_row[10], RGB_BLUE);
        rgb_matrix_set_color(multimedia_f_row[11], RGB_BLUE);
    }
}

// Lights up certain areas of the keyboard when L_SFT/R_SFT is held
void shift_indicators(){
    if (get_mods() & MOD_BIT(KC_LSFT)){
        uint8_t i;
        for (i = 0; i < ARRAYSIZE(alphabets); i++){ // Lights up KC_A - KC_Z as PINK
            rgb_matrix_set_color(alphabets[i], RGB_PINK);
        }
        for (i = 0; i < ARRAYSIZE(multimedia_f_row); i++){ // Lights up KC_1 - KC_EQL as CYAN
            if (get_highest_layer(layer_state) == WIN_FN){ // Switches CYAN to RED if either SFT is press while in _FN3 
                rgb_matrix_set_color(multimedia_f_row[i], RGB_RED);
            } else { // "break;" for color switch
            rgb_matrix_set_color(multimedia_f_row[i], RGB_CYAN);
            }
        }
        for (uint8_t i = 0; i < ARRAYSIZE(alphas); i++){ // Lights up keys like [], ;, ', etc., as GREEN
            rgb_matrix_set_color(alphas[i], RGB_GREEN);
        } 
    }
};

void caps_lock_alphabets() {
    if (host_keyboard_led_state().caps_lock) { // Sets a breathing LED effect on caps locks and KC_A - KC_Z
        //RGB const rgb = hsv_to_rgb_glow((HSV){HSV_WHITE});
        for (uint8_t i = 0; i < ARRAYSIZE(alphabets); i++) {
            //rgb_matrix_set_color(alphabets[i], rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(alphabets[i], 255, 255, 255);
        }
        rgb_matrix_set_color(30, RGB_WHITE);
    }
}

bool mediatrack_navpage_indicators(void) {
    if (get_mods() & MOD_BIT(KC_LALT)){
        rgb_matrix_set_color(64, RGB_WHITE);
        rgb_matrix_set_color(66, RGB_WHITE);
    } else if (get_mods() & MOD_BIT(KC_LSFT)) {
        rgb_matrix_set_color(56, RGB_RED);
        rgb_matrix_set_color(65, RGB_RED);
    }
    return false;
}

static inline RGB hsv_to_rgb_glow(HSV hsv) {
    hsv.v = scale8(abs8(sin8(scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8)) - 128) * 2, hsv.v);
    return hsv_to_rgb(hsv);
}

bool rgb_matrix_indicators_user(void) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case _BASE:
            numlock_arrows_indicators();
            rgb_matrix_set_color(0, RGB_RED);
        break;
        case _FN1:
            fn_keys_indicators();
            fn2_modifiers();
            rgb_matrix_set_color(0, RGB_GREEN);
        break;
        case _FN2:
            rgb_matrix_set_color(0, RGB_BLUE);
        break;
        case WIN_MM:
            f_row_leds();
            rgb_matrix_set_color(index, RGB_BLUE);
        break;
        case WIN_FN:
            if (keycode <= KC_1 && keycode >= KC_0 && keycode == KC_MINS && keycode == KC_EQL) {
                rgb_matrix_set_color(index, RGB_RED);
            }
            rgb_matrix_set_color(index, RGB_YELLOW);
        break;
        case WIN_BASE:
            if (keymap_config.no_gui){ // Sets a breathing LED effect on Win Key
                RGB const rgb = hsv_to_rgb_glow((HSV){HSV_RED});
                rgb_matrix_set_color(58, rgb.r, rgb.g, rgb.b);
            }
            //if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
                caps_lock_alphabets();
            //}
            shift_indicators();
            mediatrack_navpage_indicators();
        break;
        default:
            break;
        }
    }
    return false;
}