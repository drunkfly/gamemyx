/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#include <stdio.h>

void gotoxy(byte x, byte y)
{
	#ifndef __WIN32__
	printf("\26%c%c", x, y);
	#endif
}

static const unsigned char SpritePalette[] = {
#include "Data/Palettes/SwordsmanPalette.h"
};

static const unsigned char SpriteData[] = {
#include "Data/Sprites/SwordsmanIdleFront.h"
};

static HSprite IdleFrontSprite;

extern byte RawKeys[8];

void GameMain()
{
    SetSpritePalette(0, SpritePalette, 16);
    IdleFrontSprite = CreateSprite(SpriteData, 0);

    #define MAX 32
    int x = 0, y = 0;

    for (;;) {
        gotoxy(1, 1);
        printf("%02X\n", RawKeys[0]);
        printf("%02X\n", RawKeys[1]);
        printf("%02X\n", RawKeys[2]);
        printf("%02X\n", RawKeys[3]);
        printf("%02X\n", RawKeys[4]);
        printf("%02X\n", RawKeys[5]);
        printf("%02X\n", RawKeys[6]);
        printf("%02X\n", RawKeys[7]);

        printf("%d %d %d\n", IsKeyPressed(KEY_O), IsGamepad1Pressed(GAMEPAD_LEFT) , IsGamepad2Pressed(GAMEPAD_LEFT) );
        printf("%d %d %d\n", IsKeyPressed(KEY_P), IsGamepad1Pressed(GAMEPAD_RIGHT), IsGamepad2Pressed(GAMEPAD_RIGHT));

        BeginFrame();

        if (IsKeyPressed(KEY_O) || IsGamepad1Pressed(GAMEPAD_LEFT)) {
            if (x > 0)
                --x;
        }
        if (IsKeyPressed(KEY_P) || IsGamepad1Pressed(GAMEPAD_RIGHT)) {
            if (x < 255-16)
                ++x;
        }
        if (IsKeyPressed(KEY_Q) || IsGamepad1Pressed(GAMEPAD_UP)) {
            if (y > 0)
                --y;
        }
        if (IsKeyPressed(KEY_A) || IsGamepad1Pressed(GAMEPAD_DOWN)) {
            if (y < 192-16)
                ++y;
        }
        PutSprite(x, y, IdleFrontSprite);

        EndFrame();
    }
}
