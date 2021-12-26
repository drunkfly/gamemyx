/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine.h"
#include "character.h"
#include "Data/HeartBitmaps.h"
#include "Data/Fonts.h"
#include "Data/Maps.h"
#include "Data/Music.h"

static const byte SpritePalette[] = {
#include "Data/Palettes/SwordsmanPalette.h"
#include "Data/Palettes/SwordsmanDeathPalette.h"
#include "Data/Palettes/RedDemonPalette.h"
#include "Data/Palettes/FarmerPurplePalette.h"
};

static const byte TilesetData[] = {
#include "Data/Map/Tileset.h"
};

#include "Data/swordsman.h"
#include "Data/reddemon.h"
#include "Data/farmerpurple.h"

static void CheckQuest1(Quest* quest);

static MYXSprite RedDemonIdleFrontSprite;

static Character player;
static Character enemies[MAX_ENEMIES];
static Character npcs[MAX_NPCS];
static const Character* firstRedDemon;
static const Character* firstFarmer;
static byte enemyCount;
static byte npcCount;

static byte playerMaxLives;
static byte playerCurLives;

static byte playerInvincible;

static Quest quest1 = { "Quest 1", CheckQuest1 };

void MYXP_WaitVSync(); // FIXME

static void Npc1Dialog(Character* c)
{
    MYX_ClearLayer2(MYX_TRANSPARENT_COLOR_INDEX8);
    MYX_DrawHUD();

    switch (quest1.state) {
        case QUEST_NOT_STARTED: {
            MYX_DrawDialogBubble(c->x, c->y, 16, "Do you want quest?");

            static const DialogChoice choices[] = {
                    { "Yes", NULL, 1 },
                    { "No", NULL, 1 },
                    { NULL, NULL, 0 },
                };

            int r = MYX_DialogChoice(player.x, player.y, 16, choices);

            MYX_ClearLayer2(MYX_TRANSPARENT_COLOR_INDEX8);
            MYX_DrawHUD();

            if (r == 0)
                MYX_StartQuest(&quest1);

            break;
        }

        case QUEST_ACTIVE:
            while (MYX_IsAnyKeyPressed())
                MYXP_WaitVSync();

            MYX_DrawDialogBubble(c->x, c->y,
                16, "Return when you're done.");

            while (!MYX_IsAnyKeyPressed())
                MYXP_WaitVSync();

            MYX_ClearLayer2(MYX_TRANSPARENT_COLOR_INDEX8);
            MYX_DrawHUD();

            break;

        case QUEST_COMPLETED:
            while (MYX_IsAnyKeyPressed())
                MYXP_WaitVSync();

            MYX_DrawDialogBubble(c->x, c->y,
                16, "Congratulations!");

            while (!MYX_IsAnyKeyPressed())
                MYXP_WaitVSync();

            MYX_ClearLayer2(MYX_TRANSPARENT_COLOR_INDEX8);
            MYX_DrawHUD();

            break;
    }
}

static void CheckQuest1(Quest* quest)
{
    for (byte i = 0; i < enemyCount; i++) {
        if (enemies[i].state != CHAR_DEAD)
            return;
    }

    MYX_CompleteQuest(&quest1);
}

static bool npcCollided; // FIXME
static bool npcCollidedThisFrame;

void DrawLives()
{
    const int y = -20;
    byte x = 0;

    byte n = playerCurLives >> 2;
    for (byte i = 0; i < n; i++) {
        MYX_DrawLayer2Bitmap(x, y, Heart4, HEART4_BANK);
        x += 18;
    }

    byte nn = playerCurLives & 3;
    if (nn != 0) {
        n++;
        switch (nn) {
            case 1: MYX_DrawLayer2Bitmap(x, y, Heart1, HEART1_BANK); break;
            case 2: MYX_DrawLayer2Bitmap(x, y, Heart2, HEART2_BANK); break;
            case 3: MYX_DrawLayer2Bitmap(x, y, Heart3, HEART3_BANK); break;
        }
        x += 18;
    }

    byte max = (playerMaxLives + 3) >> 2;
    for (; n < max; n++) {
        MYX_DrawLayer2Bitmap(x, y, Heart0, HEART0_BANK);
        x += 18;
    }
}

static void OnPlayerCollision(byte tag)
{
    if (tag >= TAG_ENEMY && tag < TAG_NPC) {
        if (playerInvincible == 0) {
            if (playerCurLives != 0) {
                playerCurLives--;
                DrawLives();
            }

            if (playerCurLives == 0)
                Character_Kill(&player);
            else
                playerInvincible = 2 * 50;
        }
    } else if (tag >= TAG_NPC) {
        npcCollidedThisFrame = true;
        if (!npcCollided) {
            Npc1Dialog(&npcs[tag - TAG_NPC]);
            npcCollided = true;
        }
    }
}

static void OnPlayerAttackCollision(byte tag)
{
    if (tag >= TAG_ENEMY && tag < TAG_NPC)
        Character_Kill(&enemies[tag - TAG_ENEMY]);
}

void MapObjectHandler(const MapObject* obj)
{
    ASSERT(enemyCount < MAX_ENEMIES);

    switch (obj->func) {
        case FUNC_ENEMY1:
            if (firstRedDemon) {
                Character_Copy(&enemies[enemyCount], firstRedDemon, obj->x, obj->y);
                enemies[enemyCount].tag = TAG_ENEMY + enemyCount;
                enemies[enemyCount].attackTag = enemies[enemyCount].tag;
            } else {
                Character_Init(&enemies[enemyCount], obj->x, obj->y, TAG_ENEMY + enemyCount, RedDemonData);
                firstRedDemon = &enemies[enemyCount];
            }
            enemies[enemyCount].direction = obj->dir;
            ++enemyCount;
            break;        

        case FUNC_NPC1:
            if (firstFarmer) {
                Character_Copy(&npcs[npcCount], firstFarmer, obj->x, obj->y);
                npcs[npcCount].tag = TAG_NPC + npcCount;
                npcs[npcCount].attackTag = npcs[npcCount].tag;
            } else {
                Character_Init(&npcs[npcCount], obj->x, obj->y, TAG_NPC + npcCount, FarmerPurpleData);
                firstFarmer = &npcs[npcCount];
            }
            npcs[npcCount].direction = obj->dir;
            ++npcCount;
            break;        

        default:
            ASSERT(false);
    }
}

void RunLevel()
{
    firstFarmer = NULL;
    firstRedDemon = NULL;
    npcCount = 0;
    enemyCount = 0;
    MYX_LoadTileset(TilesetData);
    MYX_LoadMap(&map_park_tmx, &MapObjectHandler);

    int px = MYX_PlayerX * MYX_TILE_WIDTH;
    int py = MYX_PlayerY * MYX_TILE_HEIGHT;
    Character_Init(&player, px, py, TAG_PLAYER, SwordsmanData);
    player.attackTag = TAG_PLAYER_ATTACK;

    MYX_SetCollisionCallback(TAG_PLAYER, OnPlayerCollision);
    MYX_SetCollisionCallback(TAG_PLAYER_ATTACK, OnPlayerAttackCollision);

    playerMaxLives = 2 * 4;
    playerCurLives = playerMaxLives;
    playerInvincible = 0;

    MYX_ResetHUD();
    MYX_RegisterHUD(DrawLives);

    MYX_ClearLayer2(MYX_TRANSPARENT_COLOR_INDEX8);
    MYX_DrawHUD();

    while (playerCurLives != 0 || !Character_FinishedDying(&player)) {
        MYX_BeginFrame();

        for (byte i = 0; i < enemyCount; i++) {
            Character_Draw(&enemies[i]);
            Character_ForwardBackwardMove(&enemies[i]);
        }

        for (byte i = 0; i < npcCount; i++)
            Character_Draw(&npcs[i]);

        if (playerInvincible == 0)
            Character_Draw(&player);
        else {
            --playerInvincible;
            if ((playerInvincible & 15) < 8)
                Character_Draw(&player);
        }

        Character_HandleInput(&player);

        MYX_SetMapVisibleCenter(player.x, player.y);

        npcCollidedThisFrame = false;
        MYX_EndFrame();
        if (!npcCollidedThisFrame)
            npcCollided = false;
    }

    MYX_ResetQuests();
    MYX_DisplayNotification("You Died!");
}

void GameMain()
{
    /*
    MYX_SetMusic(0, music_ingame, MUSIC_INGAME_BANK);
    MYX_PlayMusic(MYX_AY_CHIP1);
    */

    /*
    MYX_SetMusic(0, music_ingame_1, MUSIC_INGAME_1_BANK);
    MYX_SetMusic(1, music_ingame_2, MUSIC_INGAME_2_BANK);
    MYX_SetMusic(2, music_ingame_3, MUSIC_INGAME_3_BANK);
    MYX_PlayMusic(MYX_AY_ALL);
    */

    MYX_SetFont(&font_BitPotionExt);
    MYX_SetSpritePalette(0, SpritePalette, 4*16);

    for (;;)
        RunLevel();
}
