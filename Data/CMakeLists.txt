
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
    -outpalette4 Palettes/RedDemonPalette.h
    )

IMPORTER(
    -loadtsx "${src}/tiles.tsx"
    -loadtsx "${src}/control.tsx"
    -loadtmx "${src}/map.tmx"
    -outmapinfo Map/Info.h
    -outmap Map/Tilemap.h
    -outtiles4 Map/Tileset.h
    )
