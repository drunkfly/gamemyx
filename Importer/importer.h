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

STRUCT(Tileset);

STRUCT(Properties)
{
    enum Func func;
    Direction dir;
};

STRUCT(Tile)
{
    int id;
    Tileset* tileset;
    bool blocking;
    Properties props;
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

extern char outputPath[1024];
extern int currentBank;
extern int currentBankSize;

void unloadImage(void);
void loadImage(const char* file);
void buildImageHistogram();
void makeImagePalette4();
void outputImagePalette4(const char* file);
void output4BitSprite(const char* file);
void output8BitSprite(const char* file);
void output8BitBitmap(const char* symbol);
int histogramSort(const void* p1, const void* p2);
void setTransparentColor(int color);

void unloadFont();
void loadFnt(const char* file);
void outputFontList(const char* file);

void unloadTilemap(void);
void loadTilemap(const char* file);
void outputTilemapList(const char* file);

void unloadTilesets(void);
void loadTileset(const char* file);
Tileset* findTileset(const char* file);
void outputTileset4Bit(const char* symbol);

void unloadPT3();
void loadPT3(const char* file, const char* symbol);
void writeMusicList(const char* file);

void clearTileCache();
int addTile(const unsigned char* pixels);

void unloadOutputs(void);
byte requestBank(const char* symbol, int size, char* outPath, size_t max);
byte* produceOutput(const char* symbol, int size, byte* bank);
void addSymbolInBank(const char* symbol, byte bank);
void writeOutputFiles();
void writeSymbolList(const char* file);

void createDirectories(const char* file);
void calculateNextBank(int size, const char* file);

bool decodeFunc(Func *func, const char* value);
void decodeProperty(const char* file, Properties* props, const char* name, const char* value);

#endif
