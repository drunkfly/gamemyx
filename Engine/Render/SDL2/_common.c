/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

SDL_Renderer* MYXP_SDLRenderer;
SDL_Texture* MYXP_SDLScreenTexture;
SDL_Texture* MYXP_SDLLayer2Texture;
SDL_PixelFormat* MYXP_SDLPixelFormat;
Uint32 MYXP_ScreenBuffer[MYX_SDL2_CONTENT_WIDTH * MYX_SDL2_CONTENT_HEIGHT];
Uint32 MYXP_Layer2Buffer[MYX_SDL2_SCREEN_WIDTH * MYX_SDL2_SCREEN_HEIGHT];

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

    MYXP_SDLScreenTexture = SDL_CreateTexture(MYXP_SDLRenderer,
        format, SDL_TEXTUREACCESS_STREAMING,
        MYX_SDL2_CONTENT_WIDTH, MYX_SDL2_CONTENT_HEIGHT);
    if (!MYXP_SDLScreenTexture)
        MYXP_ErrorExit("Unable to create texture: %s", SDL_GetError());

    SDL_SetTextureBlendMode(MYXP_SDLScreenTexture, SDL_BLENDMODE_NONE);

    MYXP_SDLLayer2Texture = SDL_CreateTexture(MYXP_SDLRenderer,
        format, SDL_TEXTUREACCESS_STREAMING,
        MYX_SDL2_SCREEN_WIDTH, MYX_SDL2_SCREEN_HEIGHT);
    if (!MYXP_SDLLayer2Texture)
        MYXP_ErrorExit("Unable to create texture: %s", SDL_GetError());

    SDL_SetTextureBlendMode(MYXP_SDLLayer2Texture, SDL_BLENDMODE_BLEND);
}

void MYXP_TerminateRenderer()
{
    if (MYXP_SDLLayer2Texture) {
        SDL_DestroyTexture(MYXP_SDLLayer2Texture);
        MYXP_SDLLayer2Texture = NULL;
    }

    if (MYXP_SDLScreenTexture) {
        SDL_DestroyTexture(MYXP_SDLScreenTexture);
        MYXP_SDLScreenTexture = NULL;
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
    SDL_UpdateTexture(MYXP_SDLScreenTexture, NULL,
        MYXP_ScreenBuffer, MYX_SDL2_CONTENT_WIDTH * sizeof(Uint32));
    SDL_UpdateTexture(MYXP_SDLLayer2Texture, NULL,
        MYXP_Layer2Buffer, MYX_SDL2_SCREEN_WIDTH * sizeof(Uint32));

    SDL_Rect dstRect;
    dstRect.x = MYX_SDL2_BORDER_SIZE * MYX_SDL2_SCALE;
    dstRect.y = MYX_SDL2_BORDER_SIZE * MYX_SDL2_SCALE;
    dstRect.w = MYX_SDL2_CONTENT_WIDTH * MYX_SDL2_SCALE;
    dstRect.h = MYX_SDL2_CONTENT_HEIGHT * MYX_SDL2_SCALE;

    SDL_SetRenderDrawColor(MYXP_SDLRenderer, 0, 0, 0, 0);
    SDL_RenderClear(MYXP_SDLRenderer);
    SDL_RenderCopy(MYXP_SDLRenderer, MYXP_SDLScreenTexture, NULL, &dstRect);
    SDL_RenderCopy(MYXP_SDLRenderer, MYXP_SDLLayer2Texture, NULL, NULL);
    SDL_RenderPresent(MYXP_SDLRenderer);

    MYXP_HandleEvents();
}
