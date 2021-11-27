
set(src "${CMAKE_CURRENT_SOURCE_DIR}")

IMPORTER(
    -loadimage "${src}/MiniWorldSprites/SwordsmanTemplate.png"
    -histogram
    -palette4

    -area16x16 0 0
    -outsprite4 Sprites/SwordsmanIdleFront.h
    -area16x16 1 0
    -outsprite4 Sprites/SwordsmanWalkFront1.h
    -area16x16 2 0
    -outsprite4 Sprites/SwordsmanWalkFront2.h
    -area16x16 3 0
    -outsprite4 Sprites/SwordsmanWalkFront3.h
    -area16x16 4 0
    -outsprite4 Sprites/SwordsmanWalkFront4.h

    -area16x16 0 1
    -outsprite4 Sprites/SwordsmanIdleBack.h
    -area16x16 1 1
    -outsprite4 Sprites/SwordsmanWalkBack1.h
    -area16x16 2 1
    -outsprite4 Sprites/SwordsmanWalkBack2.h
    -area16x16 3 1
    -outsprite4 Sprites/SwordsmanWalkBack3.h
    -area16x16 4 1
    -outsprite4 Sprites/SwordsmanWalkBack4.h

    -area16x16 0 2
    -outsprite4 Sprites/SwordsmanIdleRight.h
    -area16x16 1 2
    -outsprite4 Sprites/SwordsmanWalkRight1.h
    -area16x16 2 2
    -outsprite4 Sprites/SwordsmanWalkRight2.h
    -area16x16 3 2
    -outsprite4 Sprites/SwordsmanWalkRight3.h
    -area16x16 4 2
    -outsprite4 Sprites/SwordsmanWalkRight4.h

    -area16x16 0 3
    -outsprite4 Sprites/SwordsmanIdleLeft.h
    -area16x16 1 3
    -outsprite4 Sprites/SwordsmanWalkLeft1.h
    -area16x16 2 3
    -outsprite4 Sprites/SwordsmanWalkLeft2.h
    -area16x16 3 3
    -outsprite4 Sprites/SwordsmanWalkLeft3.h
    -area16x16 4 3
    -outsprite4 Sprites/SwordsmanWalkLeft4.h

    -outpalette4 Palettes/SwordsmanPalette.h
    )

IMPORTER(
    -loadimage "${src}/death.png"
    -transparent 0xffffff
    -histogram
    -palette4

    -area16x16 0 0
    -outsprite4 Sprites/SwordsmanDeath1.h
    -area16x16 1 0
    -outsprite4 Sprites/SwordsmanDeath2.h
    -area16x16 2 0
    -outsprite4 Sprites/SwordsmanDeath3.h
    -area16x16 3 0
    -outsprite4 Sprites/SwordsmanDeath4.h

    -outpalette4 Palettes/SwordsmanDeathPalette.h
    )

IMPORTER(
    -loadimage "${src}/MiniWorldSprites/RedDemon.png"
    -histogram
    -palette4

    -area16x16 0 0
    -outsprite4 Sprites/RedDemonIdleFront.h
    -area16x16 1 0
    -outsprite4 Sprites/RedDemonWalkFront1.h
    -area16x16 2 0
    -outsprite4 Sprites/RedDemonWalkFront2.h
    -area16x16 3 0
    -outsprite4 Sprites/RedDemonWalkFront3.h
    -area16x16 4 0
    -outsprite4 Sprites/RedDemonWalkFront4.h

    -area16x16 0 1
    -outsprite4 Sprites/RedDemonIdleBack.h
    -area16x16 1 1
    -outsprite4 Sprites/RedDemonWalkBack1.h
    -area16x16 2 1
    -outsprite4 Sprites/RedDemonWalkBack2.h
    -area16x16 3 1
    -outsprite4 Sprites/RedDemonWalkBack3.h
    -area16x16 4 1
    -outsprite4 Sprites/RedDemonWalkBack4.h

    -area16x16 0 2
    -outsprite4 Sprites/RedDemonIdleRight.h
    -area16x16 1 2
    -outsprite4 Sprites/RedDemonWalkRight1.h
    -area16x16 2 2
    -outsprite4 Sprites/RedDemonWalkRight2.h
    -area16x16 3 2
    -outsprite4 Sprites/RedDemonWalkRight3.h
    -area16x16 4 2
    -outsprite4 Sprites/RedDemonWalkRight4.h

    -area16x16 0 3
    -outsprite4 Sprites/RedDemonIdleLeft.h
    -area16x16 1 3
    -outsprite4 Sprites/RedDemonWalkLeft1.h
    -area16x16 2 3
    -outsprite4 Sprites/RedDemonWalkLeft2.h
    -area16x16 3 3
    -outsprite4 Sprites/RedDemonWalkLeft3.h
    -area16x16 4 3
    -outsprite4 Sprites/RedDemonWalkLeft4.h

    -outpalette4 Palettes/RedDemonPalette.h
    )

IMPORTER(
    -loadtsx "${src}/tiles_new.tsx"
    -loadtsx "${src}/control.tsx"

    -startbank 6

    -loadtmx "${src}/park.tmx"
    #-loadtmx "${src}/stone.tmx"
    -outtiles4 Map/Tileset.h
    -outmaps Maps.h
    )

IMPORTER(
    -loadfnt "${src}/BitPotion/BitPotionExt.fnt"
    -outfontdef BitPotionDef.h
    -outfontbytes BitPotionBytes.h
    )

IMPORTER(
    -loadfnt "${src}/BitPotion/BitPotionExt_Black.fnt"
    -outfontdef BitPotionBlackDef.h
    -outfontbytes BitPotionBlackBytes.h
    )
