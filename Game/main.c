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

    #define MAX 32
    int x[MAX], y[MAX], dx[MAX], dy[MAX];
    for (int i = 0; i < MAX; i++) {
        x[i] = i * 2 + 2;
        y[i] = i * 2 + 2;
        dx[i] = (i & 1) ? -1 : 1;
        dy[i] = (i & 2) ? -1 : 1;
    }

    for (;;) {
        BeginFrame();

        for (int i = 0; i < MAX; i++) {
            x[i] += dx[i];
            y[i] += dy[i];
            if (x[i] == 0) dx[i] = 1;
            if (x[i] == 255-16) dx[i] = -1;
            if (y[i] == 0) dy[i] = 1;
            if (y[i] == 192-16) dy[i] = -1;
            PutSprite(x[i], y[i], IdleFrontSprite);
        }

        EndFrame();
    }
}
