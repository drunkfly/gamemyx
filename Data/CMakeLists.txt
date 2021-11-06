
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
