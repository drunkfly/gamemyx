#include "importer.h"
#include "ezxml/ezxml.h"
#include "stb_image.h"

#define MAX_TILESETS 8

Tileset tilesets[MAX_TILESETS];
int tilesetCount;

void unloadTilesets()
{
    for (int i = 0; i < tilesetCount; i++) {
        free(tilesets[i].tiles);
        stbi_image_free(tilesets[i].tiles);
    }
    tilesetCount = 0;
}

void loadTileset(const char* file)
{
    ezxml_t xml = ezxml_parse_file(file);
    if (!xml) {
        fprintf(stderr, "error: unable to load \"%s\".\n", file);
        exit(1);
    }

    int tileWidth = atoi(ezxml_attr(xml, "tilewidth"));
    int tileHeight = atoi(ezxml_attr(xml, "tileheight"));
    if (tileWidth != MYX_TILE_WIDTH || tileHeight != MYX_TILE_HEIGHT) {
        fprintf(stderr, "error: invalid tile set \"%s\".\n", file);
        ezxml_free(xml);
        exit(1);
    }

    int tileCount = atoi(ezxml_attr(xml, "tilecount"));
    int columnCount = atoi(ezxml_attr(xml, "columns"));

    ezxml_t image = ezxml_child(xml, "image");
    if (!image) {
        fprintf(stderr, "error: missing image in \"%s\".\n", file);
        ezxml_free(xml);
        exit(1);
    }

    const char* source = ezxml_attr(image, "source");
    if (!source) {
        fprintf(stderr, "error: missing image source in \"%s\".\n", file);
        ezxml_free(xml);
        exit(1);
    }

    const char* fileEnd = strrchr(file, '/');
    const char* fileEnd2 = strrchr(file, '\\');
    if (fileEnd2 && (!fileEnd || fileEnd < fileEnd2))
        fileEnd = fileEnd2;

    const char* fileName;
    char sourcePath[1024];
    if (!fileEnd) {
        fileName = file;
        strcpy(sourcePath, source);
    } else {
        fileName = fileEnd + 1;
        memcpy(sourcePath, file, fileName - file);
        strcpy(sourcePath + (fileName - file), source);
    }

    Tile* tiles = (Tile*)calloc(tileCount, sizeof(Tile));
    if (!tiles) {
        fprintf(stderr, "error: out of memory parsing \"%s\".\n", file);
        ezxml_free(xml);
        exit(1);
    }

    for (ezxml_t tile = ezxml_child(xml, "tile"); tile; tile = tile->next) {
        int id = atoi(ezxml_attr(tile, "id"));
        if (id < 0 || id >= tileCount) {
            fprintf(stderr, "error: id %d is out of range in \"%s\".\n", id, file);
            free(tiles);
            ezxml_free(xml);
            exit(1);
        }
        
        ezxml_t properties = ezxml_child(tile, "properties");
        if (properties) {
            for (ezxml_t prop = ezxml_child(properties, "property"); prop; prop = prop->next) {
                const char* name = ezxml_attr(prop, "name");
                const char* value = ezxml_attr(prop, "value");

                if (!strcmp(name, "blocking"))
                    tiles[id].blocking = !strcmp(value, "true");
                else if (!strcmp(name, "func")) {
                    if (!strcmp(value, "none"))
                        tiles[id].func = FUNC_NONE;
                    else if (!strcmp(value, "player_start"))
                        tiles[id].func = FUNC_PLAYERSTART;
                    else
                        fprintf(stderr, "warning: unknown func \"%s\" in \"%s\".\n", name, value);
                } else
                    fprintf(stderr, "warning: unknown propery \"%s\" in \"%s\".\n", name, file);
            }
        }
    }

    if (tilesetCount >= MAX_TILESETS) {
        fprintf(stderr, "error: too many tilesets.\n");
        free(tiles);
        ezxml_free(xml);
        exit(1);
    }

    if (strlen(fileName) > MAX_TILESET_NAME-1) {
        fprintf(stderr, "error: tileset filename is too long.\n");
        free(tiles);
        ezxml_free(xml);
        exit(1);
    }

    int w, h;
    stbi_uc* pixels = stbi_load(sourcePath, &w, &h, NULL, 4);
    if (!pixels) {
        fprintf(stderr, "error: can't load \"%s\": %s\n", sourcePath, stbi_failure_reason());
        free(tiles);
        ezxml_free(xml);
        exit(1);
    }

    for (int i = 0; i < tileCount; i++) {
        tiles[i].id = i;
        tiles[i].tileset = &tilesets[tilesetCount];
    }

    strcpy(tilesets[tilesetCount].name, fileName);
    tilesets[tilesetCount].tileCount = tileCount;
    tilesets[tilesetCount].columnCount = columnCount;
    tilesets[tilesetCount].tiles = tiles;
    tilesets[tilesetCount].imageWidth = w;
    tilesets[tilesetCount].imageHeight = h;
    tilesets[tilesetCount].imagePixels = pixels;
    tilesetCount++;

    ezxml_free(xml);
}

Tileset* findTileset(const char* file)
{
    const char* fileEnd = strrchr(file, '/');
    const char* fileEnd2 = strrchr(file, '\\');
    if (fileEnd2 && (!fileEnd || fileEnd < fileEnd2))
        fileEnd = fileEnd2;

    const char* fileName = (fileEnd ? fileEnd + 1 : file);

    for (int i = 0; i < tilesetCount; i++) {
        if (!strcmp(tilesets[i].name, fileName))
            return &tilesets[i];
    }

    return NULL;
}
