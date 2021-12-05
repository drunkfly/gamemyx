
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

    -area16x16 0 3
    -outsprite4 "${bin}/Sprites/SwordsmanIdleLeft.h"
    -area16x16 1 3
    -outsprite4 "${bin}/Sprites/SwordsmanWalkLeft1.h"
    -area16x16 2 3
    -outsprite4 "${bin}/Sprites/SwordsmanWalkLeft2.h"
    -area16x16 3 3
    -outsprite4 "${bin}/Sprites/SwordsmanWalkLeft3.h"
    -area16x16 4 3
    -outsprite4 "${bin}/Sprites/SwordsmanWalkLeft4.h"

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
    -loadimage "${src}/MiniWorldSprites/RedDemon.png"
    -histogram
    -palette4

    -area16x16 0 0
    -outsprite4 "${bin}/Sprites/RedDemonIdleFront.h"
    -area16x16 1 0
    -outsprite4 "${bin}/Sprites/RedDemonWalkFront1.h"
    -area16x16 2 0
    -outsprite4 "${bin}/Sprites/RedDemonWalkFront2.h"
    -area16x16 3 0
    -outsprite4 "${bin}/Sprites/RedDemonWalkFront3.h"
    -area16x16 4 0
    -outsprite4 "${bin}/Sprites/RedDemonWalkFront4.h"

    -area16x16 0 1
    -outsprite4 "${bin}/Sprites/RedDemonIdleBack.h"
    -area16x16 1 1
    -outsprite4 "${bin}/Sprites/RedDemonWalkBack1.h"
    -area16x16 2 1
    -outsprite4 "${bin}/Sprites/RedDemonWalkBack2.h"
    -area16x16 3 1
    -outsprite4 "${bin}/Sprites/RedDemonWalkBack3.h"
    -area16x16 4 1
    -outsprite4 "${bin}/Sprites/RedDemonWalkBack4.h"

    -area16x16 0 2
    -outsprite4 "${bin}/Sprites/RedDemonIdleRight.h"
    -area16x16 1 2
    -outsprite4 "${bin}/Sprites/RedDemonWalkRight1.h"
    -area16x16 2 2
    -outsprite4 "${bin}/Sprites/RedDemonWalkRight2.h"
    -area16x16 3 2
    -outsprite4 "${bin}/Sprites/RedDemonWalkRight3.h"
    -area16x16 4 2
    -outsprite4 "${bin}/Sprites/RedDemonWalkRight4.h"

    -area16x16 0 3
    -outsprite4 "${bin}/Sprites/RedDemonIdleLeft.h"
    -area16x16 1 3
    -outsprite4 "${bin}/Sprites/RedDemonWalkLeft1.h"
    -area16x16 2 3
    -outsprite4 "${bin}/Sprites/RedDemonWalkLeft2.h"
    -area16x16 3 3
    -outsprite4 "${bin}/Sprites/RedDemonWalkLeft3.h"
    -area16x16 4 3
    -outsprite4 "${bin}/Sprites/RedDemonWalkLeft4.h"

    -outpalette4 "${bin}/Palettes/RedDemonPalette.h"
    )

IMPORTER(
    -loadtsx "${src}/tiles_new.tsx"
    -loadtsx "${src}/control.tsx"

    -startbank 7

    -loadtmx "${src}/park.tmx"
    #-loadtmx "${src}/stone.tmx"
    -outtiles4 "${bin}/Map/Tileset.h"
    -outmaps "${bin}/Maps.h"

    -loadfnt "${src}/BitPotion/BitPotionExt.fnt"
    -loadfnt "${src}/BitPotion/BitPotionExt_Black.fnt"
    -outfontlist "${bin}/Fonts.h"
    )
