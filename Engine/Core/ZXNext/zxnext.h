/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_ZXNEXT_H
#define ENGINE_ZXNEXT_H

#define MYX_NEXT_BORDER_SIZE                32

#define NEXT_MAX_SPRITES                    64

#define NEXT_SPRITESIZE4                    (16*16/2)
#define NEXT_SPRITESIZE8                    (16*16)

/**********************************************************************/

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
 * Peripheral 3 register
 */

#define NEXT_PERIPHERALCONTROL3             0x08

#define NEXT_UNLOCK_PORT_7FFD               0x80
#define NEXT_DISABLE_RAM_CONTENTION         0x40
#define NEXT_AY_STEREO_ABC                  0x00
#define NEXT_AY_STEREO_ACB                  0x20
#define NEXT_ENABLE_INTERNAL_SPEAKER        0x10
#define NEXT_ENABLE_8BIT_DACS               0x08
#define NEXT_ENABLE_PORT_FF_READ            0x04
#define NEXT_ENABLE_TURBOSOUND              0x02
#define NEXT_ENABLE_ISSUE2_KEYBOARD         0x01

/*
 * Layer 2 RAM Bank
 */

#define NEXT_LAYER2BANK                     0x12

/*
 * Layer 2 RAM Shadow Bank
 */

#define NEXT_LAYER2SHADOWBANK               0x13

/*
 * Global transparency color
 */

#define NEXT_GLOBALTRANSPARENCYCOLOR        0x14

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
 * Layer2 Offset X
 */

#define NEXT_LAYER2_X_OFFSET                0x16

/*
 * Layer2 Offset Y
 */

#define NEXT_LAYER2_Y_OFFSET                0x17

/*
 * Clip Window Layer 2
 */

#define NEXT_CLIP_WINDOW_LAYER2             0x18

/*
 * Clip Window Tilemap
 */

#define NEXT_CLIP_WINDOW_TILEMAP            0x1B

/*
 * Clip Window Control
 */

#define NEXT_CLIP_WINDOW_CONTROL            0x1C

#define NEXT_RESET_TILEMAP_CLIP_INDEX       0x80
#define NEXT_RESET_ULA_CLIP_INDEX           0x40
#define NEXT_RESET_SPRITE_CLIP_INDEX        0x20
#define NEXT_RESET_LAYER2_CLIP_INDEX        0x10

/*
 * Tilemap Offset X MSB
 */

#define NEXT_TILEMAP_X_OFFSET_MSB           0x2F

/*
 * Tilemap Offset X LSB
 */

#define NEXT_TILEMAP_X_OFFSET_LSB           0x30

/*
 * Tilemap Offset Y
 */

#define NEXT_TILEMAP_Y_OFFSET               0x31

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

#define NEXT_PALETTEINDEX                   0x40

/*
 * Palette value (8-bit colour)
 */

#define NEXT_PALETTEVALUE8                  0x41

/*
 * Transparency index for sprites
 */

#define NEXT_SPRITETRANSPARENCY             0x4b

/*
 * MMU slot 0
 */

#define NEXT_MMUSLOT0                       0x50

/*
 * MMU slot 1
 */

#define NEXT_MMUSLOT1                       0x51

/*
 * MMU slot 2
 */

#define NEXT_MMUSLOT2                       0x52

/*
 * MMU slot 3
 */

#define NEXT_MMUSLOT3                       0x53

/*
 * MMU slot 4
 */

#define NEXT_MMUSLOT4                       0x54

/*
 * MMU slot 5
 */

#define NEXT_MMUSLOT5                       0x55

/*
 * MMU slot 6
 */

#define NEXT_MMUSLOT6                       0x56

/*
 * MMU slot 7
 */

#define NEXT_MMUSLOT7                       0x57

/*
 * Tilemap control
 */

#define NEXT_TILEMAPCONTROL                 0x6b

#define NEXT_TILEMAP_ENABLED                0x80
#define NEXT_TILEMAP_80X32                  0x40
#define NEXT_TILEMAP_40X32                  0x00
#define NEXT_TILEMAP_NO_ATTRIBUTES          0x20
#define NEXT_TILEMAP_HAS_ATTRIBUTES         0x00
#define NEXT_TILEMAP_USE_SECONDARY_PALETTE  0x10
#define NEXT_TILEMAP_USE_PRIMARY_PALETTE    0x00
#define NEXT_TILEMAP_TEXT_MODE              0x04
#define NEXT_TILEMAP_256_TILES              0x00
#define NEXT_TILEMAP_512_TILES              0x02
#define NEXT_TILEMAP_OVER_ULA               0x01

/*
 * Tilemap base address
 */

#define NEXT_TILEMAPBASE                    0x6e

/*
 * Tile definitions base address
 */

#define NEXT_TILEDEFINITIONSBASE            0x6f

/*
 * Layer 2 Control Register
 */

#define NEXT_LAYER2CONTROLREGISTER          0x70

#define NEXT_LAYER2_256X192_8BPP            0x00
#define NEXT_LAYER2_320X256_8BPP            0x10
#define NEXT_LAYER2_640X256_4BPP            0x20

/**********************************************************************/

// NEXT_Layer2AccessPort

#define NEXT_LAYER2_BANK0                   0x00
#define NEXT_LAYER2_BANK1                   0x40
#define NEXT_LAYER2_BANK2                   0x80
#define NEXT_LAYER2_BANK3                   0xC0
#define NEXT_USE_SHADOW_LAYER2              0x08
#define NEXT_ENABLE_LAYER2_READONLY         0x04
#define NEXT_LAYER2_VISIBLE                 0x02
#define NEXT_ENABLE_LAYER2_WRITEONLY        0x01

// NEXT_TurboSoundControl

#define NEXT_TURBOSOUNDCONTROL_MASK         0x9c
#define NEXT_TURBOSOUNDCONTROL_ENABLE_LEFT  0x40
#define NEXT_TURBOSOUNDCONTROL_ENABLE_RIGHT 0x20
#define NEXT_TURBOSOUNDCONTROL_CHIP3        0x01
#define NEXT_TURBOSOUNDCONTROL_CHIP2        0x02
#define NEXT_TURBOSOUNDCONTROL_CHIP1        0x03

/**********************************************************************/

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

__sfr __banked __at 0xfffd NEXT_TurboSoundControl;
__sfr __banked __at 0xbffd NEXT_SoundChipRegister;

#endif
