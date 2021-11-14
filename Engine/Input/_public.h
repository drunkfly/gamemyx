/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_INPUT_PUBLIC_H
#define ENGINE_INPUT_PUBLIC_H

#ifdef ZXNEXT
#include "ZXNext/keys.h"
#endif

bool MYX_IsKeyPressed(byte key)
    Z88DK_FASTCALL Z88DK_PRESERVES((d, e, iyl, iyh));

bool MYX_IsGamepad1Pressed(byte key)
    Z88DK_FASTCALL Z88DK_PRESERVES((b, c, d, e, h, iyl, iyh));

bool MYX_IsGamepad2Pressed(byte key)
    Z88DK_FASTCALL Z88DK_PRESERVES((b, c, d, e, h, iyl, iyh));

#endif
