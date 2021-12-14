/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "importer.h"

#define MAX_TRACKS  32

void loadPT3(const char* file, const char* symbol)
{
    FILE* f = fopen(file, "rb");
    if (!f) {
        fprintf(stderr, "error: unable to open file \"%s\": %s.\n", file, strerror(errno));
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (ferror(f)) {
        fprintf(stderr, "error: can't determine size of file \"%s\": %s.\n", file, strerror(errno));
        fclose(f);
        exit(1);
    }

    byte* data = (byte*)malloc(size);
    if (!data) {
        fprintf(stderr, "error: out of memory reading file \"%s\".\n", file);
        fclose(f);
        exit(1);
    }

    size_t bytesRead = fread(data, 1, size, f);
    if (ferror(f) || bytesRead != (size_t)size) {
        fprintf(stderr, "error: error reading \"%s\": %s.\n", file, strerror(errno));
        fclose(f);
        exit(1);
    }

    fclose(f);

    if (size < 100) {
        fprintf(stderr, "error: file \"%s\" is too small.\n", file);
        exit(1);
    }

    byte version = data[13];
    if (version != 0x37) {
        fprintf(stderr, "error: file \"%s\" has unsupported version.\n", file);
        exit(1);
    }

    byte freqTable = data[99];
    if (freqTable != 2) { // ASM or PSC
        fprintf(stderr, "error: file \"%s\" has unsupported freq table.\n", file);
        exit(1);
    }

    size -= 100;

    byte bank;
    byte* bankData = produceOutput(symbol, size, &bank);
    memcpy(bankData, &data[100], size);
    addSymbolInBank(symbol, bank);

    free(data);
}
