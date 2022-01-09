#ifndef DATA_H
#define DATA_H

#include "engine.h"
#include "../character.h"
#include "swordsman.h"
#include "Data/InsideTilesets.h"
#include "Data/ForestTilesets.h"

#define SPRITE_PALETTE_COUNT 2
extern const byte SpritePalette[];

extern const MapInfo map_New_Year_Home_tmx;
extern const MapInfo map_New_Year_Forest_tmx;

void GAME_LoadData(void);

#endif
