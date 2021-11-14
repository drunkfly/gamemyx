/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef IMPORTER_H
#define IMPORTER_H

#include "engine.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TILESET_NAME 64

enum Func
{
    FUNC_NONE = 0,
    FUNC_PLAYERSTART,
};

STRUCT(Tileset);

STRUCT(Tile)
{
    int id;
    Tileset* tileset;
    bool blocking;
    enum Func func;
};

struct Tileset
{
    char name[MAX_TILESET_NAME];
    int tileCount;
    int columnCount;
    Tile* tiles;
    int imageWidth;
    int imageHeight;
    void* imagePixels;
};

STRUCT(HistogramEntry)
{
    unsigned char index;
    unsigned char count;
};

STRUCT(TileCacheEntry)
{
    char md5[16];
    unsigned char pixels[MYX_TILE_SMALL_WIDTH * MYX_TILE_SMALL_HEIGHT * 4];
    int paletteIndex;
};

extern int imageWidth;
extern int imageHeight;
extern int imageAreaX;
extern int imageAreaY;
extern int imageAreaW;
extern int imageAreaH;

extern unsigned char palette4[16];
extern HistogramEntry histogram[256];

extern Tileset tilesets[];
extern int tilesetCount;

extern TileCacheEntry cachedTiles[];
extern int cachedCount;

extern int* tilemap;
extern int tilemapWidth;
extern int tilemapHeight;

extern char outputPath[1024];
extern int currentBank;
extern int currentBankSize;

void unloadImage();
void loadImage(const char* file);
void buildImageHistogram();
void makeImagePalette4();
void outputImagePalette4(const char* file);
void output4BitImage(const char* file);
int histogramSort(const void* p1, const void* p2);
void setTransparentColor(int color);

void unloadTilemap();
void loadTilemap(const char* file);
void outputTilemap();
void outputTilemapList(const char* file);

void unloadTilesets();
void loadTileset(const char* file);
Tileset* findTileset(const char* file);
void outputTileset4Bit(const char* file);

void clearTileCache();
int addTile(const unsigned char* pixels);

void unloadOutputs();
byte* produceOutput(const char* symbol, int size, byte* bank);
void writeOutputFiles();

void createDirectories(const char* file);
void calculateNextBank(int size, const char* file);

#endif
