/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

//#define USE_MATRIX_I2C

/* Select hand configuration */

//#define MASTER_LEFT
#define MASTER_LEFT
// #define EE_HANDS

#define SSD1306OLED

#define USE_SERIAL_PD2

// Above 300ms becomes a hold
#define TAPPING_TERM 200
// tap after 300ms if there's no other key in between
// #define RETRO_TAPPING

// Will register taps if downs happen without ups (typing fast)
#define IGNORE_MOD_TAP_INTERRUPT

// allows repeating of key which has a hold function
#define TAPPING_FORCE_HOLD
