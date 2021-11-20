/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

SDL_Renderer* MYXP_SDLRenderer;
SDL_Texture* MYXP_SDLTexture;
SDL_PixelFormat* MYXP_SDLPixelFormat;
Uint32 MYXP_ScreenBuffer[MYX_SDL2_CONTENT_WIDTH * MYX_SDL2_CONTENT_HEIGHT];

void MYXP_InitRenderer()
{
    MYXP_SDLRenderer = SDL_CreateRenderer(MYXP_SDLWindow, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!MYXP_SDLRenderer)
        MYXP_ErrorExit("Unable to initialize renderer: %s", SDL_GetError());

    unsigned format = SDL_PIXELFORMAT_BGRA32;

    MYXP_SDLPixelFormat = SDL_AllocFormat(format);
    if (!MYXP_SDLPixelFormat)
        MYXP_ErrorExit("Unable to allocate pixel format: %s", SDL_GetError());

    MYXP_SDLTexture = SDL_CreateTexture(MYXP_SDLRenderer,
        format, SDL_TEXTUREACCESS_STREAMING,
        MYX_SDL2_CONTENT_WIDTH, MYX_SDL2_CONTENT_HEIGHT);
    if (!MYXP_SDLTexture)
        MYXP_ErrorExit("Unable to create texture: %s", SDL_GetError());
}

void MYXP_TerminateRenderer()
{
    if (MYXP_SDLTexture) {
        SDL_DestroyTexture(MYXP_SDLTexture);
        MYXP_SDLTexture = NULL;
    }

    if (MYXP_SDLPixelFormat) {
        SDL_FreeFormat(MYXP_SDLPixelFormat);
        MYXP_SDLPixelFormat = NULL;
    }

    if (MYXP_SDLRenderer) {
        SDL_DestroyRenderer(MYXP_SDLRenderer);
        MYXP_SDLRenderer = NULL;
    }
}

void MYXP_WaitVSync()
{
    SDL_UpdateTexture(MYXP_SDLTexture, NULL,
        MYXP_ScreenBuffer, MYX_SDL2_CONTENT_WIDTH * sizeof(Uint32));

    SDL_Rect dstRect;
    dstRect.x = MYX_SDL2_BORDER_SIZE * MYX_SDL2_SCALE;
    dstRect.y = MYX_SDL2_BORDER_SIZE * MYX_SDL2_SCALE;
    dstRect.w = MYX_SDL2_CONTENT_WIDTH * MYX_SDL2_SCALE;
    dstRect.h = MYX_SDL2_CONTENT_HEIGHT * MYX_SDL2_SCALE;

    SDL_SetRenderDrawColor(MYXP_SDLRenderer, 0, 0, 0, 0);
    SDL_RenderClear(MYXP_SDLRenderer);
    SDL_RenderCopy(MYXP_SDLRenderer, MYXP_SDLTexture, NULL, &dstRect);
    SDL_RenderPresent(MYXP_SDLRenderer);

    MYXP_HandleEvents();
}
