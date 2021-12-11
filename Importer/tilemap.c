#include "importer.h"
#include "ezxml/ezxml.h"

#define MAX_TILEMAPS 256
#define MAX_TILESET_REFS 8
#define MAX_OBJECTS 256
#define MAX_LAYERS 8

STRUCT(TilesetRef)
{
    Tileset* tileset;
    int first;
    int last;
};

STRUCT(TilemapLayer)
{
    Tile** data;
};

STRUCT(TilemapObject)
{
    int id;
    int x;
    int y;
    Properties props;
};

STRUCT(TilemapListEntry)
{
    char name[256];
    byte tilemapBank;
    byte collisionBank;
    byte infoBank;
    int layerCount;
    int tilesetRefCount;
    char tilemapName[256];
    int* tilemap;
    unsigned char* collision;
    int tilemapWidth;
    int tilemapHeight;
    int playerStartX;
    int playerStartY;
    int objectCount;
    TilesetRef tilesetRefs[MAX_TILESET_REFS];
    TilemapLayer tilemapLayers[MAX_LAYERS];
    TilemapObject tilemapObjects[MAX_OBJECTS];
};

static TilemapListEntry tilemapList[MAX_TILEMAPS];
int tilemapCount;

void unloadTilemap()
{
    /*
    for (int i = 0; i < layerCount; i++)
        free(tilemapLayers[i].data);
    layerCount = 0;
    tilesetRefCount = 0;
    free(tilemap);
    free(collision);
    tilemap = NULL;
    collision = NULL;
    */
}

static int compareTilesetRefs(const void* a, const void* b)
{
    TilesetRef* r1 = (TilesetRef*)a;
    TilesetRef* r2 = (TilesetRef*)b;

    if (r1->first > r2->first)
        return 1;
    else if (r1->first < r2->first)
        return -1;
    else
        return 0;
}

void loadTilemap(const char* file)
{
    unloadTilemap();

    if (tilemapCount >= MAX_TILEMAPS) {
        fprintf(stderr, "error: too many tilemaps.\n");
        exit(1);
    }

    ezxml_t xml = ezxml_parse_file(file);
    if (!xml) {
        fprintf(stderr, "error: unable to load \"%s\".\n", file);
        exit(1);
    }

    TilemapListEntry* tle = &tilemapList[tilemapCount++];

    char* slash = strrchr(file, '/');
    strcpy(tle->tilemapName, (slash ? slash + 1 : file));
    for (char* p = tle->tilemapName; *p; p++) {
        if (*p == '.')
            *p = '_';
    }

    strcpy(tle->name, tle->tilemapName);

    tle->playerStartX = 0;
    tle->playerStartY = 0;

    int width = atoi(ezxml_attr(xml, "width"));
    int height = atoi(ezxml_attr(xml, "height"));

    int tileWidth = atoi(ezxml_attr(xml, "tilewidth"));
    int tileHeight = atoi(ezxml_attr(xml, "tileheight"));
    if (tileWidth != MYX_TILE_WIDTH || tileHeight != MYX_TILE_HEIGHT) {
        fprintf(stderr, "error: invalid tile set \"%s\".\n", file);
        ezxml_free(xml);
        exit(1);
    }

    for (ezxml_t tileset = ezxml_child(xml, "tileset"); tileset; tileset = tileset->next) {
        int firstgid = atoi(ezxml_attr(tileset, "firstgid"));

        const char* source = ezxml_attr(tileset, "source");
        if (!source) {
            fprintf(stderr, "error: missing tileset source in \"%s\".\n", file);
            ezxml_free(xml);
            exit(1);
        }

        Tileset* tileset = findTileset(source);
        if (!tileset) {
            fprintf(stderr, "error: tileset \"%s\" not found in \"%s\".\n", source, file);
            ezxml_free(xml);
            exit(1);
        }

        if (tle->tilesetRefCount >= MAX_TILESET_REFS) {
            fprintf(stderr, "error: too many tilesets in \"%s\".\n", file);
            ezxml_free(xml);
            exit(1);
        }

        tle->tilesetRefs[tle->tilesetRefCount].tileset = tileset;
        tle->tilesetRefs[tle->tilesetRefCount].first = firstgid;
        ++tle->tilesetRefCount;
    }

    if (tle->tilesetRefCount == 0) {
        fprintf(stderr, "error: no tilesets in \"%s\".\n", file);
        ezxml_free(xml);
        exit(1);
    }

    qsort(tle->tilesetRefs, tle->tilesetRefCount, sizeof(TilesetRef), compareTilesetRefs);

    for (int i = 1; i < tle->tilesetRefCount; i++) {
        int last1 = tle->tilesetRefs[i].first - 1;
        int last2 = tle->tilesetRefs[i].first + tle->tilesetRefs[i].tileset->tileCount - 1;
        tle->tilesetRefs[i - 1].last = (last1 < last2 ? last1 : last2);
    }
    tle->tilesetRefs[tle->tilesetRefCount - 1].last = INT_MAX;

    for (ezxml_t layer = ezxml_child(xml, "layer"); layer; layer = layer->next) {
        int layerWidth = atoi(ezxml_attr(layer, "width"));
        int layerHeight = atoi(ezxml_attr(layer, "height"));
        if (layerWidth != width || layerHeight != height) {
            fprintf(stderr, "error: invalid layer size in \"%s\".\n", file);
            ezxml_free(xml);
            exit(1);
        }

        ezxml_t data = ezxml_child(layer, "data");
        if (!data) {
            fprintf(stderr, "error: missing layer data in \"%s\".\n", file);
            ezxml_free(xml);
            exit(1);
        }

        const char* encoding = ezxml_attr(data, "encoding");
        if (!encoding || strcmp(encoding, "csv") != 0) {
            fprintf(stderr, "error: layer encoding in \"%s\" is not CSV.\n", file);
            ezxml_free(xml);
            exit(1);
        }

        if (tle->layerCount >= MAX_LAYERS) {
            fprintf(stderr, "error: too many layers in \"%s\".\n", file);
            ezxml_free(xml);
            exit(1);
        }

        Tile** tiles = (Tile**)malloc(width * height * sizeof(Tile*));
        if (!tiles) {
            fprintf(stderr, "error: out of memory parsing \"%s\".\n", file);
            ezxml_free(xml);
            exit(1);
        }

        char* p = data->txt;
        if (!p) {
            fprintf(stderr, "error: empty layer data in \"%s\".\n", file);
            free(tiles);
            ezxml_free(xml);
            exit(1);
        }

        int off = 0;
        while (*p) {
            bool last = false;
            char* end = strchr(p, ',');
            if (!end) {
                end = p + strlen(p);
                last = true;
            }

            *end = 0;
            int value = atoi(p);
            if (value == 0)
                tiles[off++] = NULL;
            else {
                bool found = false;
                for (int i = 0; i < tle->tilesetRefCount; i++) {
                    if (value >= tle->tilesetRefs[i].first && value <= tle->tilesetRefs[i].last) {
                        tiles[off++] = &tle->tilesetRefs[i].tileset->tiles[value - tle->tilesetRefs[i].first];
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    fprintf(stderr, "error: invalid tile %d in \"%s\".\n", value, file);
                    free(tiles);
                    ezxml_free(xml);
                    exit(1);
                }
            }

            if (last)
                break;

            p = end + 1;
        }

        tle->tilemapLayers[tle->layerCount].data = tiles;
        ++tle->layerCount;
    }

    if (tle->layerCount == 0) {
        fprintf(stderr, "error: no layers in \"%s\".\n", file);
        ezxml_free(xml);
        exit(1);
    }

    tle->tilemap = (int*)malloc(width * 2 * height * 2 * sizeof(int));
    if (!tle->tilemap) {
        fprintf(stderr, "error: out of memory parsing \"%s\".\n", file);
        ezxml_free(xml);
        exit(1);
    }

    tle->collision = (unsigned char*)calloc(width * 2 * height * 2, sizeof(unsigned char));
    if (!tle->collision) {
        fprintf(stderr, "error: out of memory parsing \"%s\".\n", file);
        ezxml_free(xml);
        exit(1);
    }

    tle->tilemapWidth = width * 2;
    tle->tilemapHeight = height * 2;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int yy = 0; yy < 2; yy++) {
                for (int xx = 0; xx < 2; xx++) {
                    unsigned char pixels[MYX_TILE_SMALL_WIDTH * MYX_TILE_SMALL_HEIGHT * 4];
                    memset(pixels, 0, sizeof(pixels));
                    for (int i = 0; i < tle->layerCount; i++) {
                        Tile* tile = tle->tilemapLayers[i].data[y * width + x];
                        if (!tile)
                            continue;

                        if (tile->blocking) {
                            tle->collision[(y * 2 + 0) * tle->tilemapWidth + x * 2 + 0] = 1;
                            tle->collision[(y * 2 + 0) * tle->tilemapWidth + x * 2 + 1] = 1;
                            tle->collision[(y * 2 + 1) * tle->tilemapWidth + x * 2 + 0] = 1;
                            tle->collision[(y * 2 + 1) * tle->tilemapWidth + x * 2 + 1] = 1;
                        }

                        if (tile->props.func != FUNC_NONE) {
                            switch (tile->props.func) {
                                case FUNC_PLAYERSTART:
                                    tle->playerStartX = x;
                                    tle->playerStartY = y;
                                    break;
                            }
                            continue;
                        }

                        int id = tile->id;
                        int ix = (id % tile->tileset->columnCount) * MYX_TILE_WIDTH  + xx * MYX_TILE_SMALL_WIDTH;
                        int iy = (id / tile->tileset->columnCount) * MYX_TILE_HEIGHT + yy * MYX_TILE_SMALL_HEIGHT;

                        const unsigned char* src = tile->tileset->imagePixels;
                        for (int cy = 0; cy < MYX_TILE_SMALL_WIDTH; cy++) {
                            for (int cx = 0; cx < MYX_TILE_SMALL_HEIGHT; cx++) {
                                int off1 = ((iy + cy) * tile->tileset->imageWidth + (ix + cx)) * 4;
                                unsigned char r1 = src[off1 + 0];
                                unsigned char g1 = src[off1 + 1];
                                unsigned char b1 = src[off1 + 2];
                                unsigned char a1 = src[off1 + 3];

                                int off2 = (cy * MYX_TILE_SMALL_WIDTH + cx) * 4;
                                unsigned char* r2 = &pixels[off2 + 0];
                                unsigned char* g2 = &pixels[off2 + 1];
                                unsigned char* b2 = &pixels[off2 + 2];
                                unsigned char* a2 = &pixels[off2 + 3];

                                if (a1 == 255) {
                                    *r2 = r1;
                                    *g2 = g1;
                                    *b2 = b1;
                                } else if (a1 != 0) {
                                    *r2 = ((r1 * a1) + (*r2 * (255 - a1))) / 255;
                                    *g2 = ((g1 * a1) + (*g2 * (255 - a1))) / 255;
                                    *b2 = ((b1 * a1) + (*b2 * (255 - a1))) / 255;
                                }
                                *a2 = 255;
                            }
                        }
                    }

                    int tileIndex = addTile(pixels);
                    if (tileIndex < 0) {
                        fprintf(stderr, "error: too many tiles in \"%s\".\n", file);
                        ezxml_free(xml);
                        exit(1);
                    }

                    tle->tilemap[(y * 2 + yy) * width * 2 + (x * 2 + xx)] = tileIndex;
                }
            }
        }
    }

    for (ezxml_t grp = ezxml_child(xml, "objectgroup"); grp; grp = grp->next) {
        for (ezxml_t obj = ezxml_child(grp, "object"); obj; obj = obj->next) {
            TilemapObject* object = &tle->tilemapObjects[tle->objectCount];
            tle->objectCount++;

            object->id = atoi(ezxml_attr(obj, "id"));
            object->x = atoi(ezxml_attr(obj, "x"));
            object->y = atoi(ezxml_attr(obj, "y"));

            ezxml_t properties = ezxml_child(obj, "properties");
            if (properties) {
                for (ezxml_t prop = ezxml_child(properties, "property"); prop; prop = prop->next) {
                    const char* name = ezxml_attr(prop, "name");
                    const char* value = ezxml_attr(prop, "value");
                    decodeProperty(file, &object->props, name, value);
                }
            }
        }
    }

    ezxml_free(xml);
}

static void outputTilemapData(TilemapListEntry* tle)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "map_%s_data", tle->tilemapName);

    int size = 2 + tle->tilemapWidth * tle->tilemapHeight * 2;

    byte* data = produceOutput(buf, size, &tle->tilemapBank);

    *data++ = tle->tilemapWidth;
    *data++ = tle->tilemapHeight;
    for (int y = 0; y < tle->tilemapHeight; y++) {
        for (int x = 0; x < tle->tilemapWidth; x++) {
            unsigned tileIndex = tle->tilemap[y * tle->tilemapWidth + x];
            byte paletteIndex = cachedTiles[tileIndex].paletteIndex;
            *data++ = tileIndex;
            *data++ = (paletteIndex << 4) | ((tileIndex >> 8) & 1);
        }
    }
}

static void outputTilemapCollisions(TilemapListEntry* tle)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "map_%s_collisions", tle->tilemapName);

    int size = ((tle->tilemapWidth + 7) / 8) * tle->tilemapHeight;
    byte* data = produceOutput(buf, size, &tle->collisionBank);

    for (int y = 0; y < tle->tilemapHeight; y++) {
        unsigned char byte = 0;
        for (int x = 0; x < tle->tilemapWidth; x++) {
            byte >>= 1;
            if (tle->collision[y * tle->tilemapWidth + x])
                byte |= 0x80;

            if ((x & 7) == 7) {
                *data++ = byte;
                byte = 0;
            }
        }

        if ((tle->tilemapWidth & 7) != 0) {
            byte >>= 8 - (tle->tilemapWidth & 7);
            *data++ = byte;
        }
    }
}

static void outputTilemapInfo(TilemapListEntry* tle)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "map_%s_info", tle->tilemapName);

    int size = 3 + tle->objectCount * sizeof(MapObject);
    byte* data = produceOutput(buf, size, &tle->infoBank);

    *data++ = tle->playerStartX;
    *data++ = tle->playerStartY;
    *data++ = (byte)tle->objectCount;

    for (int i = 0; i < tle->objectCount; i++) {
        MapObject* obj = (MapObject*)data;
        data += sizeof(MapObject);

        obj->x = tle->tilemapObjects[i].x;
        obj->y = tle->tilemapObjects[i].y;
        obj->func = tle->tilemapObjects[i].props.func;
        obj->dir = tle->tilemapObjects[i].props.dir;
    }
}

void outputTilemapList(const char* file)
{
    createDirectories(file);
    FILE* f = fopen(file, "w");
    if (!f) {
        fprintf(stderr, "error: can't write file \"%s\": %s\n", file, strerror(errno));
        exit(1);
    }

    for (int i = 0; i < tilemapCount; i++) {
        outputTilemapData(&tilemapList[i]);
        outputTilemapCollisions(&tilemapList[i]);
        outputTilemapInfo(&tilemapList[i]);

        fprintf(f, "\n");
        fprintf(f, "extern const byte map_%s_data[];\n", tilemapList[i].name);
        fprintf(f, "extern const byte map_%s_collisions[];\n", tilemapList[i].name);
        fprintf(f, "extern const byte map_%s_info[];\n", tilemapList[i].name);
        fprintf(f, "\n");
        fprintf(f, "const MapInfo map_%s = {\n", tilemapList[i].name);
        fprintf(f, "    map_%s_data,\n", tilemapList[i].name);
        fprintf(f, "    map_%s_collisions,\n", tilemapList[i].name);
        fprintf(f, "    map_%s_info,\n", tilemapList[i].name);
        fprintf(f, "    %d,\n", tilemapList[i].tilemapBank);
        fprintf(f, "    %d,\n", tilemapList[i].collisionBank);
        fprintf(f, "    %d,\n", tilemapList[i].infoBank);
        fprintf(f, "};\n");
    }

    fclose(f);
}
