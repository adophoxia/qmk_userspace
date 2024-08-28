/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

/*
    * ┌───┬───┬───┬───┐
    * │TG1│Esc│Bsp│Tab│
    * ├───┼───┼───┼───┤
    * │Num│ / │ * │ - │
    * ├───┼───┼───┼───┤
    * │ 7 │ 8 │ 9 │   │
    * ├───┼───┼───┤ + │
    * │ 4 │ 5 │ 6 │   │
    * ├───┼───┼───┼───┤
    * │ 1 │ 2 │ 3 │   │
    * ├───┴───┼───┤Ent│
    * │ 0     │ . │   │
    * └───────┴───┴───┘
*/

enum layers { _BASE, _FN1, _FN2};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_numpad_6x4(
        TG(_FN1),   KC_ESC,  KC_BSPC,   KC_TAB,
        KC_NUM,     KC_PSLS, KC_PAST,   KC_PMNS,
        KC_P7,      KC_P8,   KC_P9,
        KC_P4,      KC_P5,   KC_P6,     KC_PPLS,
        KC_P1,      KC_P2,   KC_P3,
        KC_P0,               KC_PDOT,   KC_PENT
    ),

    [_FN1] = LAYOUT_numpad_6x4(
        TG(_FN2),   KC_LCTL, KC_LGUI,   KC_LALT,
        KC_F10,     KC_F11,  KC_F12,    _______,
        KC_F7,      KC_F8,   KC_F9,
        KC_F4,      KC_F5,   KC_F6,     _______,
        KC_F1,      KC_F2,   KC_F3,
        _______,             _______,   _______
    ),

    [_FN2] = LAYOUT_numpad_6x4(
        TO(_BASE),  KC_MUTE, KC_VOLD,   KC_VOLU,
        RGB_MOD,    RGB_VAI, RGB_HUI,   KC_DEL,
        RGB_RMOD,   RGB_VAD, RGB_HUD,
        RGB_SAI,    RGB_SPI, KC_MPRV,   _______,
        RGB_SAD,    RGB_SPD, KC_MPLY,
        RGB_TOG,             KC_MNXT,   _______
    )
};