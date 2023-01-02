# QMK Keymap

This is the keymap definition for my Nyquist V2.
You can read about some aspects of it [in this blogpost](https://www.ralismark.xyz/posts/keyboard).

<img src="https://www.ralismark.xyz/assets/keyboard:own.png" width="600" />

# Building & Flashing w/ Nix

If you have Nix, you can easily build and flash the keyboard without needing any extra setup:

- `nix build` to compile and produce the firmware .hex file.
- `nix run` to flash the firmware.

The keymap is currently configured to use [`EE_HANDS`](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom).
If handedness is incorrect, follow the instructions there to flash the EEPROM.

# Old Setup Instructions

1. Install the QMK CLI.
2. Clone https://github.com/qmk/qmk_firmware/, and run `qmk doctor` from the root directory to check your environment.
You can also do `qmk setup`, which should be equivalent.
3. Symlink this folder to `keyboards/keebio/nyquist/keymaps/custom`.

You can then build the firmware with either `qmk compile -kb keebio/nyquist/v2 -km custom` or `make keebio/nyquist/v2:custom`.
To flash, run `qmk flash -kb keebio/nyquist/v2 -km custom`.
See [Handedness by EEPROM](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom) for how to set up `EE_HANDS` on the keyboard.
