#pragma once

// #define USE_I2C

/* Select hand configuration */
// #define MASTER_RIGHT
#define EE_HANDS

// Always use NKRO
#define FORCE_NKRO

// Better polling
#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 4

#define ONESHOT_TAP_TOGGLE 5
#define ONESHOT_TIMEOUT 1000

#define PERMISSIVE_HOLD
// #define TAPPING_FORCE_HOLD
