#include <stdio.h>

__sfr __at 0xfe ZX_Control;

__sfr __banked __at 0x243b Next_RegisterNumber;
__sfr __banked __at 0x253b Next_RegisterValue;

__sfr __banked __at 0x123b Next_Layer2AccessPort;

#define NEXT_PALETTEINDEX       0x40
#define NEXT_PALETTEVALUE8      0x41
#define NEXT_PALETTECONTROL     0x43

#define NEXT_SETREG(reg, value) \
    do { \
        Next_RegisterNumber = (reg); \
        Next_RegisterValue = (value); \
    } while (0)

int main()
{
    // Enabling layer 2

    Next_Layer2AccessPort = 3; // 00000011

    // Loading layer2 palette

    /*
    NEXT_SETREG(NEXT_PALETTECONTROL, 0x10); // 00010000
    NEXT_SETREG(NEXT_PALETTEINDEX, 0);
    for (int i = 0; i < 256; i++)
        NEXT_SETREG(NEXT_PALETTEVALUE8, (unsigned char)i);
    */

    // Drawing to layer2

    __asm
    di
    __endasm;

    int offset = 0;
    for (;;) {
        int i = offset;

        ZX_Control = (offset & 7);

        for (int bank = 0; bank < 3; bank++) {
            Next_Layer2AccessPort = (bank << 6) | 3; // xx000011
            unsigned char* p = (unsigned char*)0;
            unsigned char* end = (unsigned char*)0x4000;
            for (; p < end; p++, i++)
                *p = (i & 0xff);
        }

        offset++;
    }
}
