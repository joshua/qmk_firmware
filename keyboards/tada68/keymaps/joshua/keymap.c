#include "tada68.h"

#ifdef LEADER_TIMEOUT
#undef LEADER_TIMEOUT
#endif
#define LEADER_TIMEOUT 2000

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

#define _______ KC_TRNS
#define SHRUG LT(_FL, KC_ESC)

// predefined cords
#define C_LOCK_SCREEN LCTL(LGUI(KC_Q))
#define C_UNDO LGUI(KC_Z)
#define C_CTLGRV LCTL(KC_GRV)
#define C_MUTIFY LSFT(LGUI(KC_0))

// #define DIAMOND_BL KC_GRV
// #define DIAMOND_FL KC_INS
//
// enum custom_keycodes {
//     CKC_SSS = SAFE_RANGE
// };

enum tap_dances
{
  TD_MUTE_LOCK = 0,
  TD_Z_UNDO
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |~ ` | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |Esc    |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Alt |Cmd |        Space          |Cmd| Alt| FN|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
    [_BL] = KEYMAP_ANSI(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, TD(TD_MUTE_LOCK),
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        SHRUG, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN,
        KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_UP, C_CTLGRV,
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RALT, MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT),

    /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Ins |
   * |----------------------------------------------------------------|
   * |     |   |Up |   |   |   |   |   |   |   |   |   |   |     |Hme |
   * |----------------------------------------------------------------|
   * |      |<- |Dn | ->|   |   |   |   |   |   |   |   |        |End |
   * |----------------------------------------------------------------|
   * |        |   |   |Bl-|BL |BL+|   |VU-|VU+|MUT|   |   McL|MsU|McR |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |MsL|MsD|MsR |
   * `----------------------------------------------------------------'
   */
    [_FL] = KEYMAP_ANSI(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_INS,
        _______, _______, KC_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END,
        _______, _______, _______, BL_DEC, BL_TOGG, BL_INC, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_MRWD, KC_MPLY, KC_MFFD),
};

// Tap Dance Definitions
// void dance_undo_finished(qk_tap_dance_state_t *state, void *user_data)
// {
//   if (state->count == 1)
//   {
//     register_code(KC_Z);
//   }
//   else
//   {
//     register_code(KC_LGUI);
//     register_code(KC_Z);
//   }
// }

// void dance_undo_reset(qk_tap_dance_state_t *state, void *user_data)
// {
//   if (state->count == 1)
//   {
//     unregister_code(KC_Z);
//   }
//   else
//   {
//     unregister_code(KC_LGUI);
//     unregister_code(KC_Z);

//     register_code(KC_ESC);
//     unregister_code(KC_ESC);
//   }
// }

qk_tap_dance_action_t tap_dance_actions[] = {
    //Tap once for Esc, twice for Lock Screen
    [TD_MUTE_LOCK] = ACTION_TAP_DANCE_DOUBLE(C_MUTIFY, C_LOCK_SCREEN),
    // [TD_Z_UNDO] = ACTION_TAP_DANCE_DOUBLE(KC_Z, C_UNDO),
    // [TD_Z_UNDO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_undo_finished, dance_undo_reset)
};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     if (record->event.pressed) {
//         switch(keycode) {
//             case CKC_SSS:
//                 SEND_STRING(SS_LCTRL(SS_LALT(SS_LGUI("\\"))));
//                 return false;
//                 break;
//         }
//     }
//     return true;
// };
//
//
// LEADER_EXTERNS();
// void matrix_scan_user(void) {
//     LEADER_DICTIONARY() {
//         leading = false;
//         leader_end();
//
//         SEQ_ONE_KEY(DIAMOND_BL) {
//             register_code(KC_LCTL);
//             register_code(KC_LALT);
//             register_code(KC_LGUI);
//             register_code(KC_BSLS);
//             unregister_code(KC_BSLS);
//             unregister_code(KC_LGUI);
//             unregister_code(KC_LALT);
//             unregister_code(KC_LCTL);
//         }
//     }
// }
