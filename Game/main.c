/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

static const unsigned char SpritePalette[] = {
#include "Data/Palettes/SwordsmanPalette.h"
};

static const unsigned char SpriteData[] = {
#include "Data/Sprites/SwordsmanIdleFront.h"
};

static HSprite IdleFrontSprite;

void GameMain()
{
    SetSpritePalette(0, SpritePalette, 16);
    IdleFrontSprite = CreateSprite(SpriteData, 0);

    int x = 100, y = 100, dx = 1, dy = 1;

    for (;;) {
        BeginFrame();
        PutSprite(x, y, IdleFrontSprite);
        EndFrame();

        x += dx;
        y += dy;
        if (x == 0) dx = 1;
        if (x == 255-16) dx = -1;
        if (y == 0) dy = 1;
        if (y == 192-16) dy = -1;
    }
}
