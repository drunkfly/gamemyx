/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

static bool MYXP_SDLInitialized = false;
static SDL_Window* MYXP_SDLWindow;
static SDL_Renderer* MYXP_SDLRenderer;

static void MYXP_Cleanup(void)
{
    if (MYXP_SDLRenderer) {
        SDL_DestroyRenderer(MYXP_SDLRenderer);
        MYXP_SDLRenderer = NULL;
    }

    if (MYXP_SDLWindow) {
        SDL_DestroyWindow(MYXP_SDLWindow);
        MYXP_SDLWindow = NULL;
    }

    if (MYXP_SDLInitialized) {
        MYXP_SDLInitialized = false;
        SDL_Quit();
    }
}

void MYXP_ErrorExit(const char* fmt, ...)
{
    char buf[2048];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    MYXP_Cleanup();

    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", buf);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", buf, NULL);

    exit(1);
}

void MYXP_PlatformInit()
{
    int r = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (r != 0)
        MYXP_ErrorExit("Unable to initialize SDL: %s", SDL_GetError());

    SDL_ClearError();
    MYXP_SDLWindow = SDL_CreateWindow("",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        MYX_SDL2_SCREEN_WIDTH * MYX_SDL2_SCALE,
        MYX_SDL2_SCREEN_HEIGHT * MYX_SDL2_SCALE,
        0);
    if (!MYXP_SDLWindow)
        MYXP_ErrorExit("Unable to initialize video mode: %s", SDL_GetError());
        
    MYXP_SDLRenderer = SDL_CreateRenderer(MYXP_SDLWindow, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!MYXP_SDLRenderer)
        MYXP_ErrorExit("Unable to initialize renderer: %s", SDL_GetError());
   
}

int main(int argc, char** argv)
{
    atexit(MYXP_Cleanup);
    MYXP_EngineMain();
    return 0;
}
