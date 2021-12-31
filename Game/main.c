/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine.h"
#include "character.h"
#include "Data/Fonts.h"

#define SPRITE_PALETTE_COUNT 2
static const byte SpritePalette[] = {
#include "Data/Palettes/SwordsmanPalette.h"
#include "Data/Palettes/SwordsmanDeathPalette.h"
};

#include "Data/swordsman.h"

void RunLevel()
{
    MYX_ResetQuests();
    MYX_DestroyAllAnimSprites();
    MYX_DestroyAllSprites();
    MYX_ClearInventory();
}

void GameMain()
{
    MYX_SetFont(&font_BitPotionExt);
    MYX_SetSpritePalette(0, SpritePalette, SPRITE_PALETTE_COUNT * 16);

    for (;;)
        RunLevel();
}
