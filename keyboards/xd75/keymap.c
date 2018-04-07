/* Copyright 2017 Max Riveiro
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
#include "xd75.h"

extern rgblight_config_t rgblight_config;

uint8_t old_layer = 255;
bool has_layer_changed = false;

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define _QW 0
#define _CM 1
#define _DV 2
#define _LW 3
#define _RS 4
#define _FN 5
#define _MI 6

#define RAISE MO(_RS)
#define LOWER MO(_LW)
#define QWERTY M(_QW)
#define COLEMAK M(_CM)
#define DVORAK M(_DV)

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,
  RGB_RST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QWERTY - MIT ENHANCED / GRID COMPATIBLE
  * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
  * | `      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | XXXXXX . BACKSP |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
  * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | \      | DEL    |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
  * | ESC    | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | XXXXXX . ENTER  | PG UP  |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
  * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | XXXXXX . RSHIFT | UP     | PG DN  |
  * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
  * | RSHIFT | LCTRL  | LALT   | LGUI   | RAISE  | XXXXXX . SPACE  | LOWER  | RGUI   | RALT   | RCTRL  | FN     | LEFT   | DOWN   | RIGHT  |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */

  [_QW] = LAYOUT_ortho_5x15( /* QWERTY */
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC ,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL  ,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_ENT,  KC_PGUP ,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT, KC_UP,   KC_PGDN ,
    KC_RSFT, KC_LCTL, KC_LALT, KC_LGUI, RAISE,   KC_SPC,  KC_SPC,  LOWER,   KC_RGUI, KC_RALT, KC_RCTL, MO(_FN), KC_LEFT, KC_DOWN, KC_RGHT),

  /* COLEMAK - MIT ENHANCED / GRID COMPATIBLE
  * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
  * | `      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | XXXXXX . BACKSP |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
  * | TAB    | Q      | W      | F      | P      | G      | J      | L      | U      | Y      | ;      | [      | ]      | \      | DEL    |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
  * | ESC    | A      | R      | S      | T      | D      | H      | N      | E      | I      | O      | '      | XXXXXX . ENTER  | PG UP  |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
  * | LSHIFT | Z      | X      | C      | V      | B      | K      | M      | ,      | .      | /      | XXXXXX . RSHIFT | UP     | PG DN  |
  * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
  * | RSHIFT | LCTRL  | LALT   | LGUI   | RAISE  | XXXXXX . SPACE  | LOWER  | RGUI   | RALT   | RCTRL  | FN     | LEFT   | DOWN   | RIGHT  |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */

  [_CM] = LAYOUT_ortho_5x15( /* COLEMAK */
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC ,
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL  ,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_ENT,  KC_ENT,  KC_PGUP ,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT, KC_UP,   KC_PGDN ,
    KC_RSFT, KC_LCTL, KC_LALT, KC_LGUI, RAISE,   KC_SPC,  KC_SPC,  LOWER,   KC_RGUI, KC_RALT, KC_RCTL, MO(_FN), KC_LEFT, KC_DOWN, KC_RGHT),

  /* DVORAK - MIT ENHANCED / GRID COMPATIBLE
  * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
  * | `      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | XXXXXX . BACKSP |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
  * | TAB    | '      | ,      | .      | P      | Y      | F      | G      | C      | R      | L      | [      | ]      | \      | DEL    |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
  * | ESC    | A      | O      | E      | U      | I      | D      | H      | T      | N      | S      | /      | XXXXXX . ENTER  | PG UP  |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
  * | LSHIFT | ;      | Q      | J      | K      | X      | B      | M      | W      | V      | Z      | XXXXXX . RSHIFT | UP     | PG DN  |
  * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
  * | RSHIFT | LCTRL  | LALT   | LGUI   | RAISE  | XXXXXX . SPACE  | LOWER  | RGUI   | RALT   | RCTRL  | FN     | LEFT   | DOWN   | RIGHT  |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */

  [_DV] = LAYOUT_ortho_5x15( /* DVORAK */
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC ,
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL  ,
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, KC_ENT,  KC_ENT,  KC_PGUP ,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, KC_RSFT, KC_UP,   KC_PGDN ,
    KC_RSFT, KC_LCTL, KC_LALT, KC_LGUI, RAISE,   KC_SPC,  KC_SPC,  LOWER,   KC_RGUI, KC_RALT, KC_RCTL, MO(_FN), KC_LEFT, KC_DOWN, KC_RGHT),

  /* LOWERED
  * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
  * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | XXXXXX .        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
  * |        | !      | @      | #      | $      | %      | ^      | &      | *      | (      | )      |        |        |        | INS    |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
  * |        | F1     | F2     | F3     | F4     | F5     | F6     | _      | +      | {      | }      | |      | XXXXXX .        |        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
  * |        | F7     | F8     | F9     | F10    | F11    | F12    |        |        |        |        | XXXXXX .        |        |        |
  * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
  * |        |        |        |        |        | XXXXXX .        |        |        |        |        |        |        |        |        |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */

  [_LW] = LAYOUT_ortho_5x15( /* LOWERED */
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______ ,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______, _______, KC_INS  ,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, _______, _______, _______ ,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______ ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

  /* RAISED
  * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
  * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | XXXXXX .        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
  * |        | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |        |        |        | INS    |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
  * |        | F1     | F2     | F3     | F4     | F5     | F6     | -      | =      | [      | ]      | \      | XXXXXX .        |        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
  * |        | F7     | F8     | F9     | F10    | F11    | F12    |        |        |        |        | XXXXXX .        |        |        |
  * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
  * |        |        |        |        |        | XXXXXX .        |        |        |        |        |        |        |        |        |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */

  [_RS] = LAYOUT_ortho_5x15( /* RAISED */
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______ ,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, _______, KC_INS  ,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, _______, _______, _______ ,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______ ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

  /* FUNCTION
  * .---------------------------------------------------------------------------------------------------------------------------------------.
  * | NUM LK | F1      | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | XXXXXX |  MIDI  |
  * |--------+---------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
  * | SCR LK | F13     | F14    | F15    | F16    | F17    | F18    | F19    | F20    | F21    | F22    | F23    | F24    | PAUSE  | PR SCR |
  * |--------+---------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
  * | CAP LK | MS BT5  | MS BT4 | MS BT3 | MS BT2 | SLOW M | FAST M | NEXT   | VOL+   | VOL-   | PLAY   |        | XXXXXX .        | WHEEL+ |
  * |--------+---------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
  * | RGB TG | RGB MD  | RGB HI | RGB HD | RGB SI | RGB SD | RGB VI | RGB VD | BL TOG | BL INC | BL DEC | XXXXXX .        | MOUS U | WHEEL- |
  * |--------+---------+--------+--------+--------+-- 2u -----------+--------+--------+--------+--------+-----------------+--------+--------|
  * | RESET  | RGB RST | QWERTY | COLEMK | DVORAK | XXXXXX . MS BT1 |        |        |        |        |        | MOUS L | MOUS D | MOUS R |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */

  [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
    KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, TG(_MI) ,
    KC_SLCK, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_PAUS, KC_PSCR ,
    KC_CAPS, KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, KC_ACL0, KC_ACL2, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______, _______, _______, KC_WH_U ,
    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, BL_TOGG, BL_INC,  BL_DEC,  _______, _______, KC_MS_U, KC_WH_D ,
    RESET  , RGB_RST, QWERTY,  COLEMAK, DVORAK,  KC_BTN1, KC_BTN1, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R),

  /* MIDI
  * .---------------------------------------------------------------------------------------------------------------------------------------.
  * |        |         |        |        |        |        |        |        |        |        |        |        |        |        |        |
  * |--------+---------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * |        |         |        |        |        |        |        |        |        |        |        |        |        |        |        |
  * |--------+---------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * |        |         |        |        |        |        |        |        |        |        |        |        |        |        |        |
  * |--------+---------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * |        |         |        |        |        |        |        |        |        |        |        |        |        |        |        |
  * |--------+---------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * |        |         |        |        |        |        |        |        |        |        |        |        |        |        |        |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */

  [_MI] = LAYOUT_ortho_5x15( /* MIDI */
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   _______ ,
    MI_CHU,  XXXXXXX, MI_Cs,   MI_Ds,    XXXXXXX,  MI_Fs,     MI_Gs,     MI_As,     XXXXXXX,   MI_Cs_1,   MI_Ds_1, XXXXXXX,  MI_Fs_1,  MI_Gs_1,   MI_As_1 ,
    MI_MOD,  MI_C,    MI_D,    MI_E,     MI_F,     MI_G,      MI_A,      MI_B,      MI_C_1,    MI_D_1,    MI_E_1,  MI_F_1,   MI_G_1,   MI_A_1,    MI_B_1  ,
    MI_SUS,  MI_OCTD, MI_OCTU, MI_MODSD, MI_MODSU, XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, MI_TRNSD, MI_TRNSU, MI_TRNS_0, MI_SUS  ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  MI_ALLOFF, MI_ALLOFF, MI_ALLOFF, MI_ALLOFF, MI_ALLOFF, XXXXXXX, _______,  XXXXXXX,  XXXXXXX,   XXXXXXX),
};

// User Functions
void rgb_color_set(uint8_t layer) {
  switch (layer) {
    case _QW:
      rgblight_sethsv(0, 0, 255);
      break;
    case _CM:
      rgblight_sethsv(0, 255, 255);
      break;
    case _DV:
      rgblight_sethsv(255,255,255);
      break;
  }
}

void default_layer_color_set(void) {
  uint8_t default_layer = eeconfig_read_default_layer();
  rgb_color_set(default_layer);
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
  default_layer_color_set();
}

// QMK Handlers
void matrix_init_user(void) {
  rgblight_enable();
  default_layer_color_set();
};

const macro_t* action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case _QW:
      if (record->event.pressed) {
        persistent_default_layer_set(_QW);
      }
      break;
    case _CM:
      if (record->event.pressed) {
        persistent_default_layer_set(_CM);
      }
      break;
    case _DV:
      if (record->event.pressed) {
        persistent_default_layer_set(_DV);
      }
      break;
  }

  return MACRO_NONE;
};

void matrix_scan_user(void) {
  if (rgblight_config.mode > 1) {
    return;
  }

  uint8_t layer = biton32(layer_state);
  if (old_layer != layer) {
      has_layer_changed = true;
      old_layer = layer;
  }

  if (has_layer_changed) {
      switch (layer) {
        case _RS:
            rgblight_setrgb(0xFF, 0xFF, 0x00);
            break;
        case _LW:
            rgblight_setrgb(0x00, 0xFF, 0xFF);
            break;
        case _FN:
            rgblight_setrgb(0xFF, 0x00, 0xFF);
            break;
        case _MI:
            rgblight_setrgb(0x00, 0xFF, 0x00);
            break;
        default:
          default_layer_color_set();
          break;
      }

      has_layer_changed = false;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_RST:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;
  }

  return true;
}
