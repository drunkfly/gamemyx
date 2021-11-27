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
    MYX_SDL2_SCALE = 2,

    MYX_SDL2_CONTENT_WIDTH = 256,
    MYX_SDL2_CONTENT_HEIGHT = 192,
    MYX_SDL2_BORDER_SIZE = 32,

    MYX_SDL2_SCREEN_WIDTH = MYX_SDL2_CONTENT_WIDTH + MYX_SDL2_BORDER_SIZE * 2,
    MYX_SDL2_SCREEN_HEIGHT = MYX_SDL2_CONTENT_HEIGHT + MYX_SDL2_BORDER_SIZE * 2,
};

#define MYX_SDL2_MAX_SPRITES    128

#define MYX_SDL2_SPRITESIZE4    (16*16/2)
#define MYX_SDL2_SPRITESIZE8    (16*16)

extern SDL_Window* MYXP_SDLWindow;

void MYXP_ErrorExit(const char* fmt, ...);

void MYXP_HandleEvents();

#endif
