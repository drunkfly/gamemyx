/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "importer.h"

#define CHECK_ARG \
    if (i == argc - 1) { \
        fprintf(stderr, "error: missing command line argument after \"%s\".\n", argv[i]); \
        return 1; \
    }

int main(int argc, char** argv)
{
    atexit(unloadImage);
    atexit(unloadTilesets);
    atexit(unloadTilemap);
    atexit(unloadOutputs);

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-outpath")) {
            CHECK_ARG
            strcpy(outputPath, argv[++i]);
        } else if (!strcmp(argv[i], "-startbank")) {
            CHECK_ARG
            currentBank = atoi(argv[++i]);
            currentBankSize = 0;
        } else if (!strcmp(argv[i], "-loadimage")) {
            CHECK_ARG
            loadImage(argv[++i]);
        } else if (!strcmp(argv[i], "-area16x16")) {
            CHECK_ARG
            int x = atoi(argv[++i]);
            CHECK_ARG
            int y = atoi(argv[++i]);
            imageAreaX = x * 16;
            imageAreaY = y * 16;
            imageAreaW = 16;
            imageAreaH = 16;
        } else if (!strcmp(argv[i], "-histogram")) {
            buildImageHistogram();
        } else if (!strcmp(argv[i], "-transparent")) {
            CHECK_ARG
            setTransparentColor(strtol(argv[++i], NULL, 0));
        } else if (!strcmp(argv[i], "-palette4")) {
            makeImagePalette4();
        } else if (!strcmp(argv[i], "-outpalette4")) {
            CHECK_ARG
            outputImagePalette4(argv[++i]);
        } else if (!strcmp(argv[i], "-outsprite4")) {
            CHECK_ARG
            output4BitImage(argv[++i]);
        } else if (!strcmp(argv[i], "-loadtsx")) {
            CHECK_ARG
            loadTileset(argv[++i]);
        } else if (!strcmp(argv[i], "-loadtmx")) {
            CHECK_ARG
            loadTilemap(argv[++i]);
            outputTilemap();
        } else if (!strcmp(argv[i], "-outmaps")) {
            CHECK_ARG
            outputTilemapList(argv[++i]);
        } else if (!strcmp(argv[i], "-outtiles4")) {
            CHECK_ARG
            outputTileset4Bit(argv[++i]);
        } else if (!strcmp(argv[i], "-loadfnt")) {
            CHECK_ARG
            loadFnt(argv[++i]);
        } else if (!strcmp(argv[i], "-outfontdef")) {
            CHECK_ARG
            writeFontDef(argv[++i]);
        } else if (!strcmp(argv[i], "-outfontbytes")) {
            CHECK_ARG
            writeFontBytes(argv[++i]);
        } else {
            fprintf(stderr, "error: unknown command line argument \"%s\".\n", argv[i]);
            return 1;
        }
    }

    writeOutputFiles();
    return 0;
}
