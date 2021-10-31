#include "importer.h"
#include "ezxml/ezxml.h"

#define MAX_TILESET_REFS 8
#define MAX_LAYERS 8

STRUCT(TilesetRef)
{
    Tileset* tileset;
    int first;
    int last;
};

STRUCT(TilesetLayer)
{
    Tile** data;
};

static TilesetRef tilesetRefs[MAX_TILESET_REFS];
static TilesetLayer tilemapLayers[MAX_LAYERS];
static int layerCount;
static int tilesetRefCount;

void unloadTilemap()
{
    for (int i = 0; i < layerCount; i++)
        free(tilemapLayers[i].data);
    layerCount = 0;
    tilesetRefCount = 0;
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
    ezxml_t xml = ezxml_parse_file(file);
    if (!xml) {
        fprintf(stderr, "error: unable to load \"%s\".\n", file);
        exit(1);
    }

    int width = atoi(ezxml_attr(xml, "width"));
    int height = atoi(ezxml_attr(xml, "height"));

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

        if (tilesetRefCount >= MAX_TILESET_REFS) {
            fprintf(stderr, "error: too many tilesets in \"%s\".\n", file);
            ezxml_free(xml);
            exit(1);
        }

        tilesetRefs[tilesetRefCount].tileset = tileset;
        tilesetRefs[tilesetRefCount].first = firstgid;
        ++tilesetRefCount;
    }

    if (tilesetRefCount == 0) {
        fprintf(stderr, "error: no tilesets in \"%s\".\n", file);
        ezxml_free(xml);
        exit(1);
    }

    qsort(tilesetRefs, tilesetRefCount, sizeof(TilesetRef), compareTilesetRefs);

    for (int i = 1; i < tilesetRefCount; i++) {
        int last1 = tilesetRefs[i].first - 1;
        int last2 = tilesetRefs[i].first + tilesetRefs[i].tileset->tileCount - 1;
        tilesetRefs[i - 1].last = (last1 < last2 ? last1 : last2);
    }
    tilesetRefs[tilesetRefCount - 1].last = INT_MAX;

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

        if (layerCount >= MAX_LAYERS) {
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
                for (int i = 0; i < tilesetRefCount; i++) {
                    if (value >= tilesetRefs[i].first && value <= tilesetRefs[i].last) {
                        tiles[off++] = &tilesetRefs[i].tileset->tiles[value - tilesetRefs[i].first];
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

        tilemapLayers[layerCount].data = tiles;
        ++layerCount;
    }

    if (layerCount == 0) {
        fprintf(stderr, "error: no layers in \"%s\".\n", file);
        ezxml_free(xml);
        exit(1);
    }

    ezxml_free(xml);
}
