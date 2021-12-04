#include "importer.h"
#include "md5/md5.h"

#define MAX_CACHED_TILES 256
#define MAX_TILE_PALETTES 16

STRUCT(Palette)
{
    unsigned char colors[16];
    int colorCount;
};

TileCacheEntry cachedTiles[MAX_CACHED_TILES];
int cachedCount;

Palette tilesetPalette[MAX_TILE_PALETTES];
int tilesetPaletteCount = 0;

void clearTileCache()
{
    cachedCount = 0;
}

int addTile(const unsigned char* pixels)
{
    unsigned char md5[16];

    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, pixels, MYX_TILE_SMALL_WIDTH * MYX_TILE_SMALL_HEIGHT * 4);
    MD5_Final(md5, &ctx);

    for (int i = 0; i < cachedCount; i++) {
        if (!memcmp(cachedTiles[i].md5, md5, 16))
            return i;
    }

    if (cachedCount >= MAX_CACHED_TILES)
        return -1;

    memcpy(cachedTiles[cachedCount].md5, md5, 16);
    memcpy(cachedTiles[cachedCount].pixels, pixels, MYX_TILE_SMALL_WIDTH * MYX_TILE_SMALL_HEIGHT * 4);
    return cachedCount++;
}

static bool paletteCanFitColors(Palette* palette, unsigned char* pixels)
{
    int colorCount = palette->colorCount;
    for (int y = 0; y < MYX_TILE_SMALL_WIDTH; y++) {
        for (int x = 0; x < MYX_TILE_SMALL_HEIGHT; x++) {
            unsigned char r = pixels[(y * MYX_TILE_SMALL_WIDTH + x) * 4 + 0];
            unsigned char g = pixels[(y * MYX_TILE_SMALL_WIDTH + x) * 4 + 1];
            unsigned char b = pixels[(y * MYX_TILE_SMALL_WIDTH + x) * 4 + 2];
            //unsigned char a = pixels[(y * MYX_TILE_SMALL_WIDTH + x) * 4 + 3];

            unsigned char c = (b >> 6) | ((g >> 3) & 0x1c) | (r & 0xe0);

            signed char colorIndex = -1;
            for (int j = 0; j < 16; j++) {
                if (palette->colors[j] == c) {
                    colorIndex = j;
                    break;
                }
            }

            if (colorIndex < 0) {
                if (colorCount < 16)
                    palette->colors[colorCount++] = c;
                else
                    return false;
            }
        }
    }
    palette->colorCount = colorCount;
    return true;
}

void outputTileset4Bit(const char* file)
{
    for (int i = 0; i < cachedCount; i++) {
        HistogramEntry histogram[256];

        for (int j = 0; j < 256; j++) {
            histogram[j].index = j;
            histogram[j].count = 0;
        }

        for (int y = 0; y < MYX_TILE_SMALL_WIDTH; y++) {
            for (int x = 0; x < MYX_TILE_SMALL_HEIGHT; x++) {
                unsigned char r = cachedTiles[i].pixels[(y * MYX_TILE_SMALL_WIDTH + x) * 4 + 0];
                unsigned char g = cachedTiles[i].pixels[(y * MYX_TILE_SMALL_WIDTH + x) * 4 + 1];
                unsigned char b = cachedTiles[i].pixels[(y * MYX_TILE_SMALL_WIDTH + x) * 4 + 2];
                //unsigned char a = cachedTiles[i].pixels[(y * MYX_TILE_SMALL_WIDTH + x) * 4 + 3];
                unsigned char c = (b >> 6) | ((g >> 3) & 0x1c) | (r & 0xe0);
                histogram[c].count++;
            }
        }

        qsort(histogram, 256, sizeof(HistogramEntry), histogramSort);

        int paletteIndex = -1;
        for (int j = 0; j < tilesetPaletteCount; j++) {
            if (paletteCanFitColors(&tilesetPalette[j], cachedTiles[i].pixels)) {
                paletteIndex = j;
                break;
            }
        }

        if (paletteIndex < 0) {
            if (tilesetPaletteCount >= MAX_TILE_PALETTES) {
                fprintf(stderr, "error: too many palettes.\n");
                exit(1);
            }

            paletteIndex = tilesetPaletteCount++;

            for (int j = 0; j < 15; j++) {
                if (histogram[j].count == 0)
                    break;
                int k = tilesetPalette[paletteIndex].colorCount++;
                tilesetPalette[paletteIndex].colors[k] = histogram[j].index;
            }
        }

        cachedTiles[i].paletteIndex = paletteIndex;
    }

    createDirectories(file);
    FILE* f = fopen(file, "w");
    if (!f) {
        fprintf(stderr, "error: can't write file \"%s\": %s\n", file, strerror(errno));
        exit(1);
    }

    fprintf(f, "%d,\n", tilesetPaletteCount);

    for (int i = 0; i < tilesetPaletteCount; i++) {
        fprintf(f, "\n");
        for (int j = 0; j < 16; j++)
            fprintf(f, "0x%02X,\n", tilesetPalette[i].colors[j]);
    }

    fprintf(f, "\n%d,\n", cachedCount);

    for (int i = 0; i < cachedCount; i++) {
        fprintf(f, "\n");
        for (int y = 0; y < MYX_TILE_SMALL_WIDTH; y++) {
            unsigned char pixel = 0;
            for (int x = 0; x < MYX_TILE_SMALL_HEIGHT; x++) {
                unsigned char r = cachedTiles[i].pixels[(y * MYX_TILE_SMALL_WIDTH + x) * 4 + 0];
                unsigned char g = cachedTiles[i].pixels[(y * MYX_TILE_SMALL_WIDTH + x) * 4 + 1];
                unsigned char b = cachedTiles[i].pixels[(y * MYX_TILE_SMALL_WIDTH + x) * 4 + 2];
                //unsigned char a = cachedTiles[i].pixels[(y * MYX_TILE_SMALL_WIDTH + x) * 4 + 3];

                unsigned char c = (b >> 6) | ((g >> 3) & 0x1c) | (r & 0xe0);

                signed char colorIndex = -1;
                for (int j = 0; j < 16; j++) {
                    if (tilesetPalette[cachedTiles[i].paletteIndex].colors[j] == c) {
                        colorIndex = j;
                        break;
                    }
                }

                if (colorIndex < 0) {
                    r >>= 5;
                    g >>= 5;
                    b >>= 6;

                    int nearestDistance;
                    for (int j = 0; j < 16; j++) {
                        unsigned char pR = c >> 5;
                        unsigned char pG = (c >> 2) & 7;
                        unsigned char pB = c & 3;

                        int x = r - pR;
                        int y = g - pG;
                        int z = b - pB;
                        int distance = x * x + y * y + z * z;

                        if (colorIndex < 0 || distance < nearestDistance) {
                            nearestDistance = distance;
                            colorIndex = j;
                        }
                    }
                }

                if (x % 2 == 0)
                    pixel = (colorIndex << 4);
                else {
                    pixel |= colorIndex;
                    fprintf(f, "0x%02X,", pixel);
                }
            }
            fprintf(f, "\n");
        }
    }

    fclose(f);
}
