/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "importer.h"

#define MAX_OUTPUT_FILES 256
#define MAX_INCLUDE_FILES 256

STRUCT(OutputFile)
{
    byte* data;
    char symbol[256];
    int size;
    int bank;
};

STRUCT(IncludeFile)
{
    char path[1024];
    int bank;
};

char outputPath[1024];
OutputFile outputFiles[MAX_OUTPUT_FILES];
IncludeFile includeFiles[MAX_INCLUDE_FILES];
int numOutputFiles;
int numIncludeFiles;
int currentBank;
int currentBankSize;

void unloadOutputs()
{
    for (int i = 0; i < numOutputFiles; i++)
        free(outputFiles[i].data);
}

static void allocBank(const char* symbol, int size, byte* data)
{
    if (size > 16384) {
        fprintf(stderr, "error: symbol too large \"%s\".\n", symbol);
        exit(1);
    }

    if (currentBankSize + size <= 16384)
        currentBankSize += size;
    else {
        currentBank++;
        currentBankSize = size;
    }

    if (numOutputFiles >= MAX_OUTPUT_FILES) {
        fprintf(stderr, "error: too many output files.\n");
        exit(1);
    }

    int idx = numOutputFiles;
    strcpy(outputFiles[idx].symbol, symbol);
    outputFiles[idx].data = data;
    outputFiles[idx].size = size;
    outputFiles[idx].bank = currentBank;
    numOutputFiles++;
}

byte requestBank(const char* symbol, int size, char* outPath, size_t max)
{
    allocBank(symbol, size, NULL);

    snprintf(outPath, max,
        "%sbank%d_%s.h", outputPath, currentBank, symbol);

    if (numIncludeFiles >= MAX_INCLUDE_FILES) {
        fprintf(stderr, "error: too many output files.\n");
        exit(1);
    }

    strcpy(includeFiles[numIncludeFiles].path, outPath);
    includeFiles[numIncludeFiles].bank = currentBank;
    ++numIncludeFiles;

    return currentBank;
}

byte* produceOutput(const char* symbol, int size, byte* outBank)
{
    byte* data = (byte*)malloc(size);
    if (!data) {
        fprintf(stderr, "error: out of memory.\n");
        exit(1);
    }

    allocBank(symbol, size, data);

    if (outBank)
        *outBank = (byte)currentBank;

    return data;
}

void writeOutputFiles()
{
    FILE* f = NULL;

    int bank = -1;
    for (int i = 0; i < numOutputFiles; i++) {
        if (outputFiles[i].bank != bank) {
            if (f)
                fclose(f);

            char buf[256];
            snprintf(buf, sizeof(buf), "%sbank%d.c", outputPath, outputFiles[i].bank);
            createDirectories(buf);
            f = fopen(buf, "w");
            if (!f) {
                fprintf(stderr, "can't write file %s: %s\n", buf, strerror(errno));
                exit(1);
            }

            fprintf(f, "#ifdef __SDCC\n");
            fprintf(f, "#pragma codeseg BANK_%d\n", outputFiles[i].bank);
            fprintf(f, "#pragma constseg BANK_%d\n", outputFiles[i].bank);
            fprintf(f, "#endif\n");

            bank = outputFiles[i].bank;

            for (int i = 0; i < numIncludeFiles; i++) {
                if (includeFiles[i].bank == bank)
                    fprintf(f, "#include \"%s\"\n", includeFiles[i].path);
            }
        }

        if (outputFiles[i].data) {
            fprintf(f, "\nconst unsigned char %s[] = {", outputFiles[i].symbol);
            const byte* p = outputFiles[i].data;
            for (int j = 0; j < outputFiles[i].size; j++) {
                if (j % 30 == 0)
                    fprintf(f, "\n");
                fprintf(f, "0x%02X,", *p++);
            }
            fprintf(f, "\n};\n");
        }
    }

    if (f)
        fclose(f);
}
