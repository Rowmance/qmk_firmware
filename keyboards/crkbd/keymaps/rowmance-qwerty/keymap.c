#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;
extern uint8_t is_master;

#define _BASE 0
#define _LOWER 1
#define _RAISE 2

enum custom_keycodes {
    BASE = SAFE_RANGE,
    LOWER,
    RAISE
};

const uint16_t PROGMEM
keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] =
LAYOUT( \
// ---------------------------------------------------------------------------------------------------------------------
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EJCT, \
// ---------------------------------------------------------------------------------------------------------------------
        KC_ESC, SFT_T(KC_A), ALT_T(KC_S), CTL_T(KC_D), CMD_T(KC_F), KC_G, KC_H, RCMD_T(KC_J), RCTL_T(KC_K),
        RALT_T(KC_L), RSFT_T(KC_SCLN), KC_ENT, \
// ---------------------------------------------------------------------------------------------------------------------
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, \
// ---------------------------------------------------------------------------------------------------------------------
        KC_DEL, MO(_LOWER), KC_BSPC,    KC_SPC, MO(_RAISE), KC_NO \
// ---------------------------------------------------------------------------------------------------------------------
),

[_RAISE] =
LAYOUT( \
// ---------------------------------------------------------------------------------------------------------------------
        KC_NO, KC_LSFT, KC_LALT, KC_LCTL, KC_LCMD, KC_NO, KC_MRWD, KC_MPLY, KC_MFFD, KC__VOLDOWN, KC__MUTE, KC__VOLUP, \
// ---------------------------------------------------------------------------------------------------------------------
        KC_F1, SFT_T(KC_F2), ALT_T(KC_F3), CTL_T(KC_F4), CMD_T(KC_F5), KC_F6, KC_BSLS, RCMD_T(KC_HOME),
        RCTL_T(KC_UP), RALT_T(KC_END), RSFT_T(KC_PGUP), KC_ENT, \
// ---------------------------------------------------------------------------------------------------------------------
        KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_GRV, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_RSFT, \
// ---------------------------------------------------------------------------------------------------------------------
        KC_DEL, KC_TRNS, KC_BSPC, KC_SPC, KC_TRNS, KC_NO \
// ---------------------------------------------------------------------------------------------------------------------
),

[_LOWER] =
LAYOUT( \
// ---------------------------------------------------------------------------------------------------------------------
        KC_LCTL, KC_BSLS, KC_TILD, KC_MINS, KC_EQL, KC_AT, KC_LBRC, KC_7, KC_8, KC_9, S(KC_RBRC), KC_RCTL, \
// ---------------------------------------------------------------------------------------------------------------------
        KC_CIRC, KC_EXLM, KC_LCBR, KC_LPRN, KC_RPRN, KC_HASH, S(KC_8), RCMD_T(KC_4), RCTL_T(KC_5), RALT_T(KC_6),
        RSFT_T(KC_QUOT), KC_RALT, \
// ---------------------------------------------------------------------------------------------------------------------
        KC_LSFT, KC_AMPR, KC_PIPE, S(KC_MINS), S(KC_EQL), S(KC_QUOT), KC_E, KC_1, KC_2, KC_3, KC_RBRC, KC_RSFT, \
// ---------------------------------------------------------------------------------------------------------------------
        KC_DEL, KC_TRNS, KC_BSPC, KC_SPC, KC_TRNS, KC_0 \
// ---------------------------------------------------------------------------------------------------------------------
)
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
    iota_gfx_init(!has_usb());   // turns on the display
#endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_host_led_state());
  } else {
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //    matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
//    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef SSD1306OLED
        set_keylog(keycode, record);
#endif
        // set_timelog();
    }

    switch (keycode) {
        case BASE:
            if (record->event.pressed) {
                persistent_default_layer_set(1UL << _BASE);
            }
            return false;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            return false;
    }
    return true;
}
