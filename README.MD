#	MiSTer Input Tester

## Overview

A custom mini-system running an input test utility.  There are 4 test screens available:
 - Digital - shows joypad buttons for first two input devices
 - Analog - shows analog axes for selected input device (cycle with a/b)
 - Advanced - shows all standard HPS sourced inputs (joystick, analog, paddle, spinner, ps2 keyboard and mouse) simultaneously
 - Button test - guided button test to help detect bounce / missed inputs and test man+machine lag

To access the menu:
- Hold (select) on the first joypad
- Press Escape on a keyboard
- Press the USER button
- Use the OSD option

There are two secrets to find...

## Analog triggers

This fork accepts independent L2/R2 values through proposed UIO command `0x46`,
paired with the Main_MiSTer joymap_v4 sender. The packet is four zero-extended
byte-valued words: command, player (0–5), L2 (0–255), R2 (0–255). Both triggers
update together after the complete packet; invalid players and incomplete packets
do not alter the displayed values. `0x45` is not a trigger command: it is reserved
upstream for force feedback. The command allocation still needs upstream agreement.

Receiver regression coverage is shared with the Template_MiSTer analog-trigger
branch. From that checkout, with Python 3 and Verilator 5:

```
python3 tools/test_analog_triggers.py --hps-io PATH/TO/InputTest_MiSTer/sys/hps_io.sv --output NEW_OUTPUT_DIRECTORY
```

## Acknowledgements

Created by JimmyStones (http://github.com/jimmystones), with thanks to:
- alanswx (https://github.com/alanswx) for ideas, cross-platform simulation support, and the tutorial this core was based on
- Jotego (https://github.com/jotego) for his very tidy JTFRAME modules
- Darrin Cardani for the quality YM music
- Porkchop Express (https://misteraddons.com/) for testing a bunch of devices I couldn't
- M. Walrus (@WalrusFPGA) for more testing
- Sorgelig (https://github.com/sorgelig) for testing, finding bugs and suggesting new features.  Oh, and the MiSTer project :)

## Hardware

The InputTest core is based on my Aznable 'custom hardware' project.  See the main repo for hardware and software details, build instruction, etc 
https://github.com/JimmyStones/Aznable 

## License
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
