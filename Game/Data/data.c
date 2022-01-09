#include "data.h"
#include "Data/ForestMaps.h"
#include "Data/InsideMaps.h"
#include "Data/Fonts.h"

const byte SpritePalette[] = {
#include "Data/Palettes/SwordsmanPalette.h"
#include "Data/Palettes/SwordsmanDeathPalette.h"
};

void GAME_LoadData()
{
    MYX_SetFont(&font_BitPotionExt);
    MYX_SetSpritePalette(0, SpritePalette, SPRITE_PALETTE_COUNT * 16);
}
