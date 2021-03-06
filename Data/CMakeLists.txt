
set(src "${CMAKE_CURRENT_SOURCE_DIR}")
set(bin "${CMAKE_CURRENT_BINARY_DIR}")

IMPORTER(
    -loadimage "${src}/MiniWorldSprites/SwordsmanTemplate.png"
    -histogram
    -palette4

    -area16x16 0 0
    -outsprite4 "${bin}/Sprites/SwordsmanIdleFront.h"
    -area16x16 1 0
    -outsprite4 "${bin}/Sprites/SwordsmanWalkFront1.h"
    -area16x16 2 0
    -outsprite4 "${bin}/Sprites/SwordsmanWalkFront2.h"
    -area16x16 3 0
    -outsprite4 "${bin}/Sprites/SwordsmanWalkFront3.h"
    -area16x16 4 0
    -outsprite4 "${bin}/Sprites/SwordsmanWalkFront4.h"

    -area16x16 0 1
    -outsprite4 "${bin}/Sprites/SwordsmanIdleBack.h"
    -area16x16 1 1
    -outsprite4 "${bin}/Sprites/SwordsmanWalkBack1.h"
    -area16x16 2 1
    -outsprite4 "${bin}/Sprites/SwordsmanWalkBack2.h"
    -area16x16 3 1
    -outsprite4 "${bin}/Sprites/SwordsmanWalkBack3.h"
    -area16x16 4 1
    -outsprite4 "${bin}/Sprites/SwordsmanWalkBack4.h"

    -area16x16 0 2
    -outsprite4 "${bin}/Sprites/SwordsmanIdleRight.h"
    -area16x16 1 2
    -outsprite4 "${bin}/Sprites/SwordsmanWalkRight1.h"
    -area16x16 2 2
    -outsprite4 "${bin}/Sprites/SwordsmanWalkRight2.h"
    -area16x16 3 2
    -outsprite4 "${bin}/Sprites/SwordsmanWalkRight3.h"
    -area16x16 4 2
    -outsprite4 "${bin}/Sprites/SwordsmanWalkRight4.h"

    -area16x16 0 4
    -outsprite4 "${bin}/Sprites/SwordsmanMeleeDown1.h"
    -area16x16 1 4
    -outsprite4 "${bin}/Sprites/SwordsmanMeleeDown2.h"
    -area16x16 2 4
    -outsprite4 "${bin}/Sprites/SwordsmanMeleeDown3.h"
    -area16x16 3 4
    -outsprite4 "${bin}/Sprites/SwordsmanMeleeDown4.h"

    -area16x16 0 5
    -outsprite4 "${bin}/Sprites/SwordsmanMeleeUp1.h"
    -area16x16 1 5
    -outsprite4 "${bin}/Sprites/SwordsmanMeleeUp2.h"
    -area16x16 2 5
    -outsprite4 "${bin}/Sprites/SwordsmanMeleeUp3.h"
    -area16x16 3 5
    -outsprite4 "${bin}/Sprites/SwordsmanMeleeUp4.h"

    -area16x16 0 6
    -outsprite4 "${bin}/Sprites/SwordsmanMeleeRight1.h"
    -area16x16 1 6
    -outsprite4 "${bin}/Sprites/SwordsmanMeleeRight2.h"
    -area16x16 2 6
    -outsprite4 "${bin}/Sprites/SwordsmanMeleeRight3.h"
    -area16x16 3 6
    -outsprite4 "${bin}/Sprites/SwordsmanMeleeRight4.h"

    -outpalette4 "${bin}/Palettes/SwordsmanPalette.h"
    )

IMPORTER(
    -loadimage "${src}/death.png"
    -transparent 0xffffff
    -histogram
    -palette4

    -area16x16 0 0
    -outsprite4 "${bin}/Sprites/SwordsmanDeath1.h"
    -area16x16 1 0
    -outsprite4 "${bin}/Sprites/SwordsmanDeath2.h"
    -area16x16 2 0
    -outsprite4 "${bin}/Sprites/SwordsmanDeath3.h"
    -area16x16 3 0
    -outsprite4 "${bin}/Sprites/SwordsmanDeath4.h"

    -outpalette4 "${bin}/Palettes/SwordsmanDeathPalette.h"
    )

IMPORTER(
    -loadimage "${src}/Hearts/heart_animated_1.png"
    -transparent 0xff00ff
    -startbank 15

    -area 0 0 17 17
    -outbitmap Heart4

    -area 17 0 17 17
    -outbitmap Heart3

    -area 34 0 17 17
    -outbitmap Heart2

    -area 51 0 17 17
    -outbitmap Heart1

    -area 68 0 17 17
    -outbitmap Heart0

    -outsymlist "${bin}/HeartBitmaps.h"
    )

IMPORTER(
    -loadtsx "${src}/Tiles/inside.tsx"
    -loadtsx "${src}/Tiles/village.tsx"
    -loadtsx "${src}/control.tsx"

    -startbank 7

    -loadtmx "${src}/New_Year_Home.tmx"
    -outtiles4 InsideTileset
    -outsymlist "${bin}/InsideTilesets.h"
    -outmaps "${bin}/InsideMaps.h"

    -loadfnt "${src}/BitPotion/BitPotionExt.fnt"
    -loadfnt "${src}/BitPotion/BitPotionExt_Black.fnt"
    -outfontlist "${bin}/Fonts.h"
    )

IMPORTER(
    -loadtsx "${src}/Tiles/inside.tsx"
    -loadtsx "${src}/Tiles/village.tsx"
    -loadtsx "${src}/control.tsx"

    -startbank 8

    -loadtmx "${src}/New_Year_Forest.tmx"
    -outtiles4 ForestTileset
    -outsymlist "${bin}/ForestTilesets.h"
    -outmaps "${bin}/ForestMaps.h"
    )

IMPORTER(
    -startbank 14
    -loadpt3 "${src}/Music/nq-MMA-ingame-28.pt3" "music_ingame"
    -outsymlist "${bin}/Music.h"
    )
