/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_SDL2_H
#define ENGINE_SDL2_H

#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>

enum
{
    MYX_SDL2_SCALE = 3,

    MYX_SDL2_CONTENT_WIDTH = 256,
    MYX_SDL2_CONTENT_HEIGHT = 192,
    MYX_SDL2_BORDER_SIZE = 64,

    MYX_SDL2_SCREEN_WIDTH = MYX_SDL2_CONTENT_WIDTH + MYX_SDL2_BORDER_SIZE * 2,
    MYX_SDL2_SCREEN_HEIGHT = MYX_SDL2_CONTENT_HEIGHT + MYX_SDL2_BORDER_SIZE * 2,
};

#endif
