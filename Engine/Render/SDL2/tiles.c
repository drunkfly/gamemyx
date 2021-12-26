/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#define MYX_MAX_TILES 256
#define MYX_TILE_BYTES (8 * 8 / 2)

STRUCT(Tile)
{
    word index;
    byte paletteIndex;
};

static byte MYXP_Tileset[MYX_MAX_TILES * MYX_TILE_BYTES];
static Tile MYXP_Tilemap[(MYX_TILEMAP_VISIBLE_WIDTH + 1) * (MYX_TILEMAP_VISIBLE_HEIGHT + 1)];
static byte MYXP_TilemapOffsetX;
static byte MYXP_TilemapOffsetY;

void MYX_LoadTileset(const byte* tileset, byte bank)
{
    (void)bank;

    byte paletteCount = *tileset++;
    byte n = (paletteCount << 4);
    MYX_SetTilemapPalette(0, tileset, n);
    tileset += paletteCount * 16;

    byte tileCount = *tileset++;
    memcpy(MYXP_Tileset, tileset, tileCount * MYX_TILE_BYTES);
}

void MYX_UploadVisibleTilemap(const byte* tilemap, byte x, byte y, byte w)
{
    const byte BytesPerTile = 2;

    Tile* dst = MYXP_Tilemap;
    const byte* p = tilemap + (y * w + x) * BytesPerTile;

    for (int y = 0; y <= MYX_TILEMAP_VISIBLE_HEIGHT; y++) {
        for (int x = 0; x <= MYX_TILEMAP_VISIBLE_WIDTH; x++) {
            byte indexLow = *p++;
            byte attrib = *p++;

            dst->index = indexLow | ((attrib << 8) & 0x100);
            dst->paletteIndex = (attrib >> 4) & 0xF;
            dst++;
        }

        p += (w - MYX_TILEMAP_VISIBLE_WIDTH - 1) * BytesPerTile;
    }
}

void MYX_SetTilemapOffset(byte x, byte y)
{
    MYXP_TilemapOffsetX = x;
    MYXP_TilemapOffsetY = y;
}

void MYXP_RenderTilemap()
{
    const Tile* tile = MYXP_Tilemap;

    for (int y = 0; y <= MYX_TILEMAP_VISIBLE_HEIGHT; y++) {
        for (int x = 0; x <= MYX_TILEMAP_VISIBLE_WIDTH; x++) {
            const byte* s = &MYXP_Tileset[tile->index * MYX_TILE_BYTES];
            bool first = true;

            for (int yy = 0; yy < MYX_TILE_SMALL_HEIGHT; yy++) {
                int dstX = x * MYX_TILE_SMALL_WIDTH - MYXP_TilemapOffsetX;
                int dstY = y * MYX_TILE_SMALL_HEIGHT - MYXP_TilemapOffsetY + yy;

                if (dstY >= MYX_SDL2_CONTENT_HEIGHT)
                    break;

                Uint32* p = &MYXP_ScreenBuffer[dstY * MYX_SDL2_CONTENT_WIDTH + dstX];
                for (int xx = 0; xx < MYX_TILE_SMALL_WIDTH; xx++, dstX++) {
                    byte index;
                    if (first)
                        index = (*s >> 4) & 0xF;
                    else
                        index = ((*s++) & 0xF);

                    first = !first;

                    if (dstY < 0 || dstX < 0 || dstX >= MYX_SDL2_CONTENT_WIDTH) {
                        p++;
                        continue;
                    }

                    index += tile->paletteIndex * 16;
                    *p++ = MYXP_TilemapPalette[index];
                }
            }

            tile++;
        }
    }
}
