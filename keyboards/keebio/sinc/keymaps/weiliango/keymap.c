#include QMK_KEYBOARD_H

// TAP DANCE
enum {
    satk,
    tumor,
    reset,
    inject2,
    inject4,
    inject8
};

void dance_satk_finished(qk_tap_dance_state_t *state, void *user_data) {
	if (!state->interrupted || state->pressed) {
		register_code16(KC_RSFT);
		register_code16(KC_U);
		wait_ms(50);
		unregister_code16(KC_U);
		unregister_code16(KC_RSFT);
	}
}

void dance_satk_prepare(qk_tap_dance_state_t *state, void *user_data) {
	tap_code(KC_U); 
}

void dance_satk_reset(qk_tap_dance_state_t *state, void *user_data) {
	tap_code(KC_BSPC); 
}

void dance_tumor_reset(qk_tap_dance_state_t *state, void *user_data) {
	tap_code(KC_BSPC); 
}

void dance_tumor_prepare(qk_tap_dance_state_t *state, void *user_data) {
	tap_code(KC_SLSH);
	tap_code(KC_L);
}

void dance_tumor_finished(qk_tap_dance_state_t *state, void *user_data) {
	if (!state->interrupted || state->pressed) {
		register_code16(KC_RSFT);
		register_code16(KC_L);
		wait_ms(50);
		unregister_code16(KC_L);
		unregister_code16(KC_RSFT);
	}
}

int cnt1 = 0;
int cnt2 = 0;
int cnt3 = 0;

void inject2_finished(qk_tap_dance_state_t *state, void *user_data) {
	cnt1++;
	tap_code(KC_CAPS);
	cnt1%=2;
}
void inject4_finished(qk_tap_dance_state_t *state, void *user_data) {
	cnt2++;
	tap_code(KC_SLCK);
	cnt2%=2;
}
void inject8_finished(qk_tap_dance_state_t *state, void *user_data) {
	cnt3++;
	tap_code(KC_NLCK);
	cnt3%=2;
}
void reset_finished(qk_tap_dance_state_t *state, void *user_data) {
	if (cnt1 != 0) tap_code(KC_CAPS);
	if (cnt2 != 0) tap_code(KC_SLCK);
	if (cnt3 != 0) tap_code(KC_NLCK);
	
	cnt1 = 0;
	cnt2 = 0;
	cnt3 = 0;
}

// All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
	[satk]= ACTION_TAP_DANCE_FN_ADVANCED(dance_satk_prepare, dance_satk_finished, dance_satk_reset),
	[tumor]= ACTION_TAP_DANCE_FN_ADVANCED(dance_tumor_prepare, dance_tumor_finished, dance_tumor_reset),
	[inject2]= ACTION_TAP_DANCE_FN_ADVANCED(NULL, inject2_finished, NULL),
	[inject4]= ACTION_TAP_DANCE_FN_ADVANCED(NULL, inject4_finished, NULL),
	[inject8]= ACTION_TAP_DANCE_FN_ADVANCED(NULL, inject8_finished, NULL),
	[reset]= ACTION_TAP_DANCE_FN_ADVANCED(NULL, reset_finished, NULL),
};

// TAP DANCE END

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_80_with_macro(
    KC_MUTE,          KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_ESC,  KC_INS,
    KC_F1,   KC_F2,   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,  KC_BSPC, TD(inject2),
    KC_F3,   KC_F4,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, TD(inject4),
    KC_F5,   KC_F6,   KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  TD(inject8),
    KC_F7,   KC_F8,   KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   TD(reset),
    KC_F9,   KC_F10,  KC_LCTL, KC_LALT, KC_LGUI, MO(1),   KC_SPC,  KC_SPC,           MO(1),   KC_SPC,  KC_RALT, MO(1) ,  KC_RCTL, KC_RSFT, KC_DOWN, TD(tumor)
  ),
  [1] = LAYOUT_80_with_macro(
		  _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    RGB_HUI, RGB_HUD, KC_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,  _______, _______, _______,
    RGB_SAI, RGB_SAD, RGB_TOG, RGB_MOD, _______, KC_UP,   _______, _______, _______, _______, KC_F1  , KC_F2  , KC_F3 , KC_1  , KC_2  , _______, _______, 
    RGB_VAI, RGB_VAD, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_F4  , KC_F5  , KC_F6  , KC_3  , KC_4  ,         KC_F7  , _______,
    _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, KC_5  , KC_6  , _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [2] = LAYOUT_80_with_macro(
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    RGB_HUI, RGB_HUD, KC_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,
    RGB_SAI, RGB_SAD, RGB_TOG, RGB_MOD, _______, KC_UP,   _______, _______, _______, _______, SFT_T(KC_I), _______, _______, KC_MS_BTN4, KC_MS_BTN5, _______, _______,
    RGB_VAI, RGB_VAD, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______
  ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
}
