static const byte SwordsmanData[] = {
// left idle
/*flags=*/ MYX_FLIP_X,
/*source=*/ DIR_RIGHT,

// left walk
/*flags=*/ MYX_FLIP_X,
/*source=*/ DIR_RIGHT,

// right idle
/*flags=*/ 0,
/*count=*/ 2, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanIdleRight.h"
#include "Data/Sprites/SwordsmanWalkRight1.h"

// right walk
/*flags=*/ 0,
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanWalkRight1.h"
#include "Data/Sprites/SwordsmanWalkRight2.h"
#include "Data/Sprites/SwordsmanWalkRight3.h"
#include "Data/Sprites/SwordsmanWalkRight4.h"

// up idle
/*flags=*/ 0,
/*count=*/ 2, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanIdleBack.h"
#include "Data/Sprites/SwordsmanWalkBack1.h"

// up walk
/*flags=*/ 0,
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanWalkBack1.h"
#include "Data/Sprites/SwordsmanWalkBack2.h"
#include "Data/Sprites/SwordsmanWalkBack3.h"
#include "Data/Sprites/SwordsmanWalkBack4.h"

// down idle
/*flags=*/ 0,
/*count=*/ 2, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanIdleFront.h"
#include "Data/Sprites/SwordsmanWalkFront1.h"

// down walk
/*flags=*/ 0,
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanWalkFront1.h"
#include "Data/Sprites/SwordsmanWalkFront2.h"
#include "Data/Sprites/SwordsmanWalkFront3.h"
#include "Data/Sprites/SwordsmanWalkFront4.h"

// death
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 1,
#include "Data/Sprites/SwordsmanDeath1.h"
#include "Data/Sprites/SwordsmanDeath2.h"
#include "Data/Sprites/SwordsmanDeath3.h"
#include "Data/Sprites/SwordsmanDeath4.h"
};
