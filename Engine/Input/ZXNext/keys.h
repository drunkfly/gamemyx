/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef MYX_ZXNEXT_KEYS_H
#define MYX_ZXNEXT_KEYS_H

enum
{
    KEY_CAPS_SHIFT      = (0 << 5) | 0x01,
    KEY_Z               = (0 << 5) | 0x02,
    KEY_X               = (0 << 5) | 0x04,
    KEY_C               = (0 << 5) | 0x08,
    KEY_V               = (0 << 5) | 0x10,
    KEY_A               = (1 << 5) | 0x01,
    KEY_S               = (1 << 5) | 0x02,
    KEY_D               = (1 << 5) | 0x04,
    KEY_F               = (1 << 5) | 0x08,
    KEY_G               = (1 << 5) | 0x10,
    KEY_Q               = (2 << 5) | 0x01,
    KEY_W               = (2 << 5) | 0x02,
    KEY_E               = (2 << 5) | 0x04,
    KEY_R               = (2 << 5) | 0x08,
    KEY_T               = (2 << 5) | 0x10,
    KEY_1               = (3 << 5) | 0x01,
    KEY_2               = (3 << 5) | 0x02,
    KEY_3               = (3 << 5) | 0x04,
    KEY_4               = (3 << 5) | 0x08,
    KEY_5               = (3 << 5) | 0x10,
    KEY_0               = (4 << 5) | 0x01,
    KEY_9               = (4 << 5) | 0x02,
    KEY_8               = (4 << 5) | 0x04,
    KEY_7               = (4 << 5) | 0x08,
    KEY_6               = (4 << 5) | 0x10,
    KEY_P               = (5 << 5) | 0x01,
    KEY_O               = (5 << 5) | 0x02,
    KEY_I               = (5 << 5) | 0x04,
    KEY_U               = (5 << 5) | 0x08,
    KEY_Y               = (5 << 5) | 0x10,
    KEY_ENTER           = (6 << 5) | 0x01,
    KEY_L               = (6 << 5) | 0x02,
    KEY_K               = (6 << 5) | 0x04,
    KEY_J               = (6 << 5) | 0x08,
    KEY_H               = (6 << 5) | 0x10,
    KEY_SPACE           = (7 << 5) | 0x01,
    KEY_SYMB_SHIFT      = (7 << 5) | 0x02,
    KEY_M               = (7 << 5) | 0x04,
    KEY_N               = (7 << 5) | 0x08,
    KEY_B               = (7 << 5) | 0x10,
};

enum
{
    GAMEPAD_LEFT        = 0x01,
    GAMEPAD_RIGHT       = 0x02,
    GAMEPAD_UP          = 0x08,
    GAMEPAD_DOWN        = 0x04,
    GAMEPAD_A           = 0x40,
    GAMEPAD_B           = 0x10,
    GAMEPAD_C           = 0x20,
    GAMEPAD_START       = 0x80,
};

#endif
