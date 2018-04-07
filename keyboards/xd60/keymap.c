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
#include "xd60.h"

#define _BASE 0
#define _FUNC 1
#define _STEN 2

#ifdef STENO_ENABLE
  #include "keymap_steno.h"
  #define TGL_STN TG(_STEN)
#else
  #define TGL_STN KC_RGUI
#endif

#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // 0: Base Layer
  [_BASE] = LAYOUT_ALL(
    KC_ESC,    KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,    KC_BSLS, KC_GRV,  \
    KC_TAB,    KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,            KC_BSPC, \
    KC_LSFT,   KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, XXXXXXX,            KC_ENT,  \
    MO(_FUNC), XXXXXXX, KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TGL_STN,   KC_UP,   KC_DEL,  \
    KC_LCTL,   KC_LALT, KC_LGUI,                             KC_SPC,                             KC_RGUI, KC_RALT, KC_LEFT,   KC_DOWN, KC_RIGHT),

  // 1: Function Layer
  [_FUNC] = LAYOUT_ALL(
    _______,   KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,    KC_F14, \
    KC_CAPS,   KC_MPRV, KC_UP,   KC_MNXT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            KC_DEL, \
    KC_LSFT,   KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            KC_ENT, \
    _______,   XXXXXXX, KC_VOLD, KC_MUTE,  KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP,   KC_INS, \
    _______,   _______, _______,                             KC_MPLY,                            _______, _______, KC_HOME, KC_PGDOWN, KC_END),

  // 1: Plover GeminiPR Stenography
  #ifdef STENO_ENABLE
  [_STEN] = LAYOUT_ALL(
    TGL_STN,   STN_N1,  STN_N2,  STN_N3,   STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC,  XXXXXXX,  XXXXXXX, \
    STN_FN,    STN_S1,  STN_TL,  STN_PL,   STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,  XXXXXXX,           XXXXXXX, \
    XXXXXXX,   STN_S2,  STN_KL,  STN_WL,   STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,  XXXXXXX,           XXXXXXX, \
    XXXXXXX,   XXXXXXX, XXXXXXX, STN_A,    STN_O,   XXXXXXX, XXXXXXX, STN_E,   STN_U,   STN_PWR, STN_RE1, STN_RE2, XXXXXXX, KC_UP,    XXXXXXX, \
    XXXXXXX,   XXXXXXX, XXXXXXX,                             KC_SPC,                             XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,  KC_RIGHT),
  #endif
};

void matrix_init_user() {
  #ifdef STENO_ENABLE
    steno_set_mode(STENO_MODE_GEMINI);
  #endif
}
