static const byte RedDemonData[] = {
// left idle
/*flags=*/ REF_SPRITE | MYX_FLIP_X,
/*source=*/ DIR_RIGHT,

// right idle
/*flags=*/ 0,
/*count=*/ 2, /* delay= */ 8, /* paletteIndex= */ 2,
#include "Data/Sprites/RedDemonIdleRight.h"
#include "Data/Sprites/RedDemonWalkRight1.h"

// up idle
/*flags=*/ 0,
/*count=*/ 2, /* delay= */ 8, /* paletteIndex= */ 2,
#include "Data/Sprites/RedDemonIdleBack.h"
#include "Data/Sprites/RedDemonWalkBack1.h"

// down idle
/*flags=*/ 0,
/*count=*/ 2, /* delay= */ 8, /* paletteIndex= */ 2,
#include "Data/Sprites/RedDemonIdleFront.h"
#include "Data/Sprites/RedDemonWalkFront1.h"

// left walk
/*flags=*/ REF_SPRITE | MYX_FLIP_X,
/*source=*/ DIR_RIGHT,

// right walk
/*flags=*/ 0,
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 2,
#include "Data/Sprites/RedDemonWalkRight1.h"
#include "Data/Sprites/RedDemonWalkRight2.h"
#include "Data/Sprites/RedDemonWalkRight3.h"
#include "Data/Sprites/RedDemonWalkRight4.h"

// up walk
/*flags=*/ 0,
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 2,
#include "Data/Sprites/RedDemonWalkBack1.h"
#include "Data/Sprites/RedDemonWalkBack2.h"
#include "Data/Sprites/RedDemonWalkBack3.h"
#include "Data/Sprites/RedDemonWalkBack4.h"

// down walk
/*flags=*/ 0,
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 2,
#include "Data/Sprites/RedDemonWalkFront1.h"
#include "Data/Sprites/RedDemonWalkFront2.h"
#include "Data/Sprites/RedDemonWalkFront3.h"
#include "Data/Sprites/RedDemonWalkFront4.h"

// left melee attack
/*flags=*/ NO_SPRITE,

// right melee attack
/*flags=*/ NO_SPRITE,

// up melee attack
/*flags=*/ NO_SPRITE,

// down melee attack
/*flags=*/ NO_SPRITE,

// left death
/*flags=*/ 0,
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 1,
#include "Data/Sprites/SwordsmanDeath1.h"
#include "Data/Sprites/SwordsmanDeath2.h"
#include "Data/Sprites/SwordsmanDeath3.h"
#include "Data/Sprites/SwordsmanDeath4.h"

// right death
/*flags=*/ REF_SPRITE,
/*source=*/ DIR_LEFT,

// up death
/*flags=*/ REF_SPRITE,
/*source=*/ DIR_LEFT,

// down death
/*flags=*/ REF_SPRITE,
/*source=*/ DIR_LEFT,
};
