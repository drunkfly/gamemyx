/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

const int KEY_A         = SDL_SCANCODE_A;
const int KEY_I         = SDL_SCANCODE_I;
const int KEY_O         = SDL_SCANCODE_O;
const int KEY_P         = SDL_SCANCODE_P;
const int KEY_Q         = SDL_SCANCODE_Q;
const int KEY_SPACE     = SDL_SCANCODE_SPACE;

bool MYX_IsAnyKeyPressed()
{
    // FIXME
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    return keys[KEY_A] ||
           keys[KEY_I] ||
           keys[KEY_O] ||
           keys[KEY_P] ||
           keys[KEY_Q] ||
           keys[KEY_SPACE];
}

bool MYX_IsKeyPressed(byte key)
{
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    return keys[key] != 0;
}

bool MYX_IsGamepad1Pressed(byte key)
{
    // FIXME
    return false;
}

bool MYX_IsGamepad2Pressed(byte key)
{
    // FIXME
    return false;
}
