#include "level.h"
#include "character.h"
#include "Data/data.h"

void MapObjectHandler(const MapObject* obj)
{
    /*
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

        case FUNC_ITEM1:
            cogOnMap[cogOnMapCount].present = true;
            cogOnMap[cogOnMapCount].x = obj->x;
            cogOnMap[cogOnMapCount].y = obj->y;
            ++cogOnMapCount;
            break;

        default:
            ASSERT(false);
    }
    */
}

void GAME_LoadLevel(const MapInfo* map)
{
    MYX_ResetQuests();
    MYX_DestroyAllAnimSprites();
    MYX_DestroyAllSprites();
    MYX_ClearInventory();

    MYX_LoadMap(map, &MapObjectHandler);

    int px = MYX_PlayerX * MYX_TILE_WIDTH;
    int py = MYX_PlayerY * MYX_TILE_HEIGHT;
    GAME_InitPlayer(px, py);
}

void GAME_RunLevel(void)
{
    while (GAME_IsPlayerAlive()) {
        MYX_BeginFrame();

        /*
        for (byte i = 0; i < cogOnMapCount; i++) {
            if (cogOnMap[i].present) {
                MYX_PutSprite(cogOnMap[i].x, cogOnMap[i].y, cogImage);
                MYX_AddCollision(cogOnMap[i].x, cogOnMap[i].y, 16, 16, TAG_COG + i);
            }
        }

        for (byte i = 0; i < enemyCount; i++) {
            Character_Draw(&enemies[i]);
            Character_ForwardBackwardMove(&enemies[i]);
        }

        for (byte i = 0; i < npcCount; i++)
            Character_Draw(&npcs[i]);
        */

        GAME_UpdatePlayer();

        /*
        npcCollidedThisFrame = false;
        */
        MYX_EndFrame();
        /*
        if (!npcCollidedThisFrame)
            npcCollided = false;

        if (MYX_IsKeyPressed(KEY_I))
            DrawInventory();
        */
    }

    MYX_DisplayNotification("You Died!");
}
