/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine.h"
#include "character.h"
#include "Data/Fonts.h"
#include "Data/Maps.h"
#include "Data/Music.h"

enum
{
    TAG_PLAYER,
    TAG_ENEMY,
};

#define MAX_ENEMIES 16

static const byte SpritePalette[] = {
#include "Data/Palettes/SwordsmanPalette.h"
#include "Data/Palettes/SwordsmanDeathPalette.h"
#include "Data/Palettes/RedDemonPalette.h"
};

static const byte TilesetData[] = {
#include "Data/Map/Tileset.h"
};

#include "Data/swordsman.h"
#include "Data/reddemon.h"

static MYXSprite RedDemonIdleFrontSprite;

static Character player;
static Character enemies[MAX_ENEMIES];
static const Character* firstRedDemon;
static byte enemyCount;

static void OnPlayerCollision(byte tag)
{
    switch (tag) {
        case TAG_ENEMY:
            Character_Kill(&player);
            break;
    }
}

void MapObjectHandler(const MapObject* obj)
{
    ASSERT(enemyCount < MAX_ENEMIES);

    switch (obj->func) {
        case FUNC_ENEMY1:
            if (firstRedDemon)
                Character_Copy(&enemies[enemyCount], firstRedDemon, obj->x, obj->y);
            else {
                Character_Init(&enemies[enemyCount], obj->x, obj->y, RedDemonData);
                firstRedDemon = &enemies[enemyCount];
            }
            enemies[enemyCount].direction = obj->dir;
            ++enemyCount;
            break;        

        default:
            ASSERT(false);
    }
}

void GameMain()
{
    MYX_PlayMusic(music_ingame, MUSIC_INGAME_BANK);

    MYX_SetFont(&font_BitPotionExt);
    MYX_DrawString(0, -30, "Hello, world!", 0xff);

    MYX_SetSpritePalette(0, SpritePalette, 3*16);

    firstRedDemon = NULL;
    enemyCount = 0;
    MYX_LoadTileset(TilesetData);
    MYX_LoadMap(&map_park_tmx, &MapObjectHandler);

    int px = MYX_PlayerX * MYX_TILE_WIDTH;
    int py = MYX_PlayerY * MYX_TILE_HEIGHT;
    Character_Init(&player, px, py, SwordsmanData);

    /*
    int demonX = 14 * MYX_TILE_WIDTH;
    int demonY = 2 * MYX_TILE_HEIGHT;
    Character_Init(&demon, demonX, demonY, RedDemonData);
    demon.direction = DIR_LEFT;
    */

    MYX_SetCollisionCallback(TAG_PLAYER, OnPlayerCollision);

    for (;;) {
        MYX_BeginFrame();

        for (byte i = 0; i < enemyCount; i++) {
            Character_Draw(&enemies[i]);
            Character_ForwardBackwardMove(&enemies[i]);
            MYX_AddCollision(enemies[i].x, enemies[i].y, 16, 16, TAG_ENEMY);
        }

        Character_Draw(&player);
        if (Character_HandleInput(&player)) {
            /*
            MYX_ClearLayer2(MYX_TRANSPARENT_COLOR_INDEX8);

            MYX_DrawDialogBubble(demon.x, demon.y, 16,
                "Lorem Ipsum is simply dummy text of the printing "
                "and typesetting industry.");

            static const DialogChoice choices[] = {
                    { "Choice 1", NULL, 1 },
                    { "Another choice", NULL, 1 },
                    { "Bad choice", NULL, 0xe0 },
                    { NULL, NULL, 0 },
                };

            MYX_DialogChoice(player.x, player.y, 16, choices);
            */
        }

        MYX_AddCollision(player.x, player.y, 16, 16, TAG_PLAYER);

        MYX_SetMapVisibleCenter(player.x, player.y);

        MYX_EndFrame();
    }
}
