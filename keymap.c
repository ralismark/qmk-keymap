#include QMK_KEYBOARD_H
#include "flatmap.c"

enum layers
{
	_BASE = 0,
	_HI,
	_LO,
};

enum custom_keycodes
{
	_LA_START = SAFE_RANGE,
	_LA_END = SAFE_RANGE + 15,
#define LA(layer) (_LA_START + (layer))
	_LD_START,
	_LD_END = SAFE_RANGE + 31,
#define LD(layer) (_LD_START + (layer))

	REPDOWN, REPUP,
	REPFAST, REPSLOW,

	RANDOM,
	GESC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT( \
		KC_BSLS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            /**/ KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,   \
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            /**/ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,  \
		GESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            /**/ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  \
		KC_LBRC, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            /**/ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RBRC,  \
		KC_LCTL, KC_GRV,  KC_LGUI, KC_LALT, KC_SPC,  LT(_HI, KC_ENT), /**/ KC_RSFT, KC_BSPC, KC_RGUI, REPDOWN, REPUP,   KC_RCTL   \
	),

	[_HI] = LAYOUT( \
		KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           /**/ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
		XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLU, KC_VOLD, LCA(KC_C),       /**/ KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, XXXXXXX, \
		KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, S(KC_INS),       /**/ KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_PSCR, \
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LCA(KC_V),       /**/ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
		_______, _______, _______, _______, _______, _______,         /**/ _______, KC_DEL,  _______, REPSLOW, REPFAST, _______  \
	),

};

void matrix_scan_user()
{
	rep_tick();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
	static uint8_t gesc_mods = 0; // mods when GESC pressed

	switch (keycode) {
	case _LA_START ... _LA_END:
		if (record->event.pressed && keycode != _LA_START) layer_on(keycode - _LA_START);
		return false;
	case _LD_START ... _LD_END:
		if (record->event.pressed && keycode != _LD_START) layer_off(keycode - _LD_START);
		return false;
	case RANDOM:
		if (record->event.pressed) tap_random_base64();
		return false;
	case REPDOWN:
		rep_change(KC_DOWN, record->event.pressed);
		return false;
	case REPUP:
		rep_change(KC_UP, record->event.pressed);
		return false;
	case REPFAST:
		rep_interval -= rep_interval > 10 ? 10 : 0;
		return false;
	case REPSLOW:
		rep_interval += 10;
		return false;
	case GESC:
		if (record->event.pressed) {
			gesc_mods = get_mods();

			if(gesc_mods & MOD_MASK_SG) {
				register_code(KC_GRAVE);
			} else {
				register_code(KC_ESCAPE);
			}
		} else {
			if(gesc_mods & MOD_MASK_SG) {
				unregister_code(KC_GRAVE);
			} else {
				unregister_code(KC_ESCAPE);
			}
		}
		return false;
	}
	return true;
}
