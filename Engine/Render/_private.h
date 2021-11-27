/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_RENDER_PRIVATE_H
#define ENGINE_RENDER_PRIVATE_H

#ifdef TARGET_ZXNEXT

    STRUCT(MYXPSprite)
    {
        byte attr2;
        byte attr3;
        byte attr4;
    };

#elif defined(TARGET_SDL2)

    STRUCT(MYXPSprite)
    {
        int w;
        int h;
        bool is256Color;
        byte paletteIndex;
        byte data[16*16];   // FIXME
    };

    extern SDL_Renderer* MYXP_SDLRenderer;
    extern SDL_PixelFormat* MYXP_SDLPixelFormat;

    extern Uint32 MYXP_ScreenBuffer[];
    extern Uint32 MYXP_Layer2Buffer[];
    extern Uint32 MYXP_TilemapPalette[];
    extern Uint32 MYXP_SpritePalette[];

    void MYXP_InitRenderer();
    void MYXP_TerminateRenderer();

    void MYXP_RenderTilemap();

    Uint32 MYXP_MapColor(byte c);

#endif

void MYXP_BeginSprites();
void MYXP_EndSprites();

void MYXP_AdvanceSprite(const void** data, byte count);

#endif
