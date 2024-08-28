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


#include QMK_KEYBOARD_H

bool tab_pressed = false; // ADD this near the beginning of keymap.c
bool ctrl_pressed = false;
bool l_shift_pressed = false;
bool r_shift_pressed = false;
bool l_alt_pressed = false;
bool r_alt_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //uint8_t mods_state = get_mods() | get_weak_mods();
    switch (keycode) {
    /* Modifier callbacks */
        case KC_LCTL:
            ctrl_pressed = record->event.pressed;
            break;
        case KC_LSFT:
            l_shift_pressed = record->event.pressed;
            break;
        case KC_RSFT:
            r_shift_pressed = record->event.pressed;
            break;
        case KC_LALT:
            l_alt_pressed = record->event.pressed;
            break;
        case KC_RALT:
            r_alt_pressed = record->event.pressed;
            break;
        case KC_TAB:
            tab_pressed = record->event.pressed;
            break;
    /* Encoder Actions */
        case ENC_PRS:
            if (record->event.pressed) {
                switch(get_highest_layer(layer_state)) {
                    case WIN_BASE:
                        if (r_alt_pressed) { // If R_Alt is held, Mute
                            tap_code(KC_MUTE);
                        } else {    // Else, Play/Pause
                            tap_code(KC_MPLY);
                        }
                        break;
                    case WIN_FN: //Reset EEPROM
                        soft_reset_keyboard();
                        break;
                    case WIN_MM: //Enter bootloader; Also resets EEPROM if BOOTMAGIC is enabled
                        reset_keyboard();
                        break;
                    default:
                        break;
                }
            }
            return false;
        case ENC_LFT:
            if (record->event.pressed) {
                switch(get_highest_layer(layer_state)) {
                    case WIN_BASE:
                        if (l_alt_pressed) { // If you are holding L Alt, Page Dn
                            tap_code(KC_PGDN);
                        } else if (r_alt_pressed) { // if holding R Alt, Media Prev track
                            tap_code(KC_MPRV);
                        } else if (ctrl_pressed) { // If holding L Ctrl, move between words
                            if (tab_pressed) {
                                tap_code16(C(KC_LEFT));
                            }
                        } else {
                            tap_code16_delay(KC_VOLD, 2);   // Otherwise, decrease volume
                        }
                        break;
                    case WIN_MM: //RGB Control
                        if (l_shift_pressed) { // If you are holding L Shift, decrease speed
                            rgb_matrix_decrease_speed();
                        } else if (l_alt_pressed) { // if holding L Alt, cycle back effect
                            rgb_matrix_step_reverse_noeeprom();
                        } else if (ctrl_pressed){   // If holding L Ctrl, decrease hue of effect
                            rgb_matrix_decrease_hue_noeeprom(); 
                        } else if (ctrl_pressed && l_shift_pressed) {   //  If holding both, L Ctrl and L Shift, decrease saturation
                            rgb_matrix_decrease_sat_noeeprom();
                        } else {
                            rgb_matrix_decrease_val_noeeprom(); // Otherwise, decrease brightness of effect
                        }
                        break;
                    default:
                        break;
                }
            }
            return false;
        case ENC_RGT:
            if (record->event.pressed) {
                switch(get_highest_layer(layer_state)) {
                    case WIN_BASE: //Default Layer
                        if (l_alt_pressed) { // If you are holding L Alt, Page Up
                            tap_code(KC_PGUP);
                        } else if (r_alt_pressed) {  // if holding R Alt, Media Next track
                            tap_code(KC_MNXT);
                        } else if (ctrl_pressed) { // If holding L Ctrl, move between words
                            tap_code16(C(KC_RIGHT));
                        } else {
                            tap_code16_delay(KC_VOLU, 2);   // Otherwise, increase volume
                        }
                        break;
                    case WIN_MM: //RGB Control
                        if (l_shift_pressed) { // If you are holding L Shift, increase speed
                            rgb_matrix_increase_speed_noeeprom();
                        } else if (l_alt_pressed) {  // if holding L Alt, cycle forward effect
                            rgb_matrix_step_noeeprom();
                        } else if (ctrl_pressed){   // If holding L Ctrl, increase hue of effect
                            rgb_matrix_increase_hue_noeeprom();
                        } else if (ctrl_pressed && l_shift_pressed) {   //  If holding both, L Ctrl and L Shift, decrease saturation
                            rgb_matrix_increase_sat_noeeprom();
                        } else {
                            rgb_matrix_increase_val_noeeprom(); // Otherwise, decrease brightness of effect
                        }
                        break;
                    default:
                        break;
                }
            }
            return false;
    }
    return true;
}