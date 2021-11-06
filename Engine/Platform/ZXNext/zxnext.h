/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ZXNEXT_H
#define ZXNEXT_H

#include "engine_p.h"

#define NEXT_MAX_SPRITES                    64

#define NEXT_SPRITESIZE4                    (16*16/2)
#define NEXT_SPRITESIZE8                    (16*16)

/*
 * Peripheral 1 setting
 */

#define NEXT_PERIPHERALCONTROL1             0x05

#define NEXT_JOY1_SINCLAIR2                 0x00
#define NEXT_JOY1_KEMPSTON1                 0x40
#define NEXT_JOY1_CURSOR                    0x80
#define NEXT_JOY1_SINCLAIR1                 0xC0
#define NEXT_JOY1_KEMPSTON2                 0x08
#define NEXT_JOY1_MEGADRIVE1                0x48
#define NEXT_JOY1_MEGADRIVE2                0x88

#define NEXT_JOY2_SINCLAIR2                 0x00
#define NEXT_JOY2_KEMPSTON1                 0x10
#define NEXT_JOY2_CURSOR                    0x20
#define NEXT_JOY2_SINCLAIR1                 0x30
#define NEXT_JOY2_KEMPSTON2                 0x02
#define NEXT_JOY2_MEGADRIVE1                0x12
#define NEXT_JOY2_MEGADRIVE2                0x22

#define NEXT_50HZ_MODE                      0x00
#define NEXT_60HZ_MODE                      0x04

#define NEXT_ENABLE_SCANDOUBLER             0x01

/*
 * Peripheral 2 setting
 */

#define NEXT_PERIPHERALCONTROL2             0x06

#define NEXT_ENABLE_TURBOMODE_KEY           0x80
#define NEXT_ENABLE_50HZ_KEY                0x20
#define NEXT_ENABLE_DIVMMC_NMI              0x10
#define NEXT_ENABLE_MULTIFACE_NMI           0x08

#define NEXT_PS2MODE_KEYBOARD               0x00
#define NEXT_PS2MODE_MOUSE                  0x04

#define NEXT_AUDIOCHIP_YAMAHA               0x00
#define NEXT_AUDIOCHIP_AY                   0x01

/*
 * Turbo mode
 */

#define NEXT_TURBOMODE                      0x07

#define NEXT_3_5MHZ                         0x00
#define NEXT_7MHZ                           0x01
#define NEXT_14MHZ                          0x02
#define NEXT_28MHZ                          0x03

/*
 * Sprite and Layers system
 */

#define NEXT_SPRITELAYERMODE                0x15

#define NEXT_LORES_MODE                     0x80
#define NEXT_SPRITE_0_ON_TOP                0x40
#define NEXT_SPRITE_127_ON_TOP              0x00
#define NEXT_SPRITE_CLIP_OVER_BORDER        0x20
#define NEXT_ORDER_SPRITES_LAYER2_ULA       0x00
#define NEXT_ORDER_LAYER2_SPRITES_ULA       0x04
#define NEXT_ORDER_SPRITES_ULA_LAYER2       0x08
#define NEXT_ORDER_LAYER2_ULA_SPRITES       0x0C
#define NEXT_ORDER_ULA_SPRITES_LAYER2       0x10
#define NEXT_ORDER_ULA_LAYER2_SPRITES       0x14
#define NEXT_ORDER_SPRITES_ULALAYER2_7      0x18 /* ULA+Layer2 combined */
#define NEXT_ORDER_SPRITES_ULALAYER2_0_7    0x1C
#define NEXT_DRAW_OVER_BORDER               0x02
#define NEXT_SPRITES_VISIBLE                0x01

/*
 * Palette control
 */

#define NEXT_PALETTECONTROL                 0x43

#define NEXT_DISABLE_PALETTE_AUTOINCREMENT  0x80
#define NEXT_IO_ULA_FIRST_PALETTE           0x00
#define NEXT_IO_ULA_SECOND_PALETTE          0x40
#define NEXT_IO_LAYER2_FIRST_PALETTE        0x10
#define NEXT_IO_LAYER2_SECOND_PALETTE       0x50
#define NEXT_IO_SPRITES_FIRST_PALETTE       0x20
#define NEXT_IO_SPRITES_SECOND_PALETTE      0x60
#define NEXT_IO_TILEMAP_FIRST_PALETTE       0x30
#define NEXT_IO_TILEMAP_SECOND_PALETTE      0x70
#define NEXT_IO_PALETTE_MASK                0x70
#define NEXT_DRAW_SPRITES_PALETTE0          0x00
#define NEXT_DRAW_SPRITES_PALETTE1          0x08
#define NEXT_DRAW_LAYER2_PALETTE0           0x00
#define NEXT_DRAW_LAYER2_PALETTE1           0x04
#define NEXT_DRAW_ULA_PALETTE0              0x00
#define NEXT_DRAW_ULA_PALETTE1              0x02
#define NEXT_ENABLE_ULANEXT                 0x01

/*
 * Palette index
 */

#define NEXT_PALETTEINDEX       0x40

/*
 * Palette value (8-bit colour)
 */

#define NEXT_PALETTEVALUE8      0x41

/*
 * Transparency index for sprites
 */

#define NEXT_SPRITETRANSPARENCY 0x4b

/*
 * Tilemap control
 */

#define NEXT_TILEMAPCONTROL                 0x6b

/*
 * Tilemap base address
 */

#define NEXT_TILEMAPBASE                    0x6e

/*
 * Tile definitions base address
 */

#define NEXT_TILEDEFINITIONSBASE            0x6f

/*****************/

#define NEXT_LAYER2_XOFFSET     0x16
#define NEXT_LAYER2_YOFFSET     0x17
#define NEXT_SPRITENUMBER       0x34
#define NEXT_SPRITEX            0x35
#define NEXT_SPRITEY            0x36
#define NEXT_SPRITEATTR2        0x37


#define NEXT_GETREG(reg) \
    (NEXT_RegisterNumber = (reg), NEXT_RegisterValue)

#define NEXT_SETREG(reg, value) \
    (NEXT_RegisterNumber = (reg), NEXT_RegisterValue = (value))

__sfr __at 0x57 NEXT_SpriteAttribute;
__sfr __at 0x5b NEXT_SpritePattern;

__sfr __banked __at 0x243b NEXT_RegisterNumber;
__sfr __banked __at 0x253b NEXT_RegisterValue;

__sfr __banked __at 0x123b NEXT_Layer2AccessPort;

__sfr __banked __at 0x303b NEXT_SpriteControl;

void MYXP_ReadInput() __preserves_regs(a, iyl, iyh);

#endif
