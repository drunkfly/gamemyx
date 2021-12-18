static const byte SwordsmanData[] = {
// left idle
/*flags=*/ REF_SPRITE | MYX_FLIP_X,
/*source=*/ DIR_RIGHT,

// right idle
/*flags=*/ 0,
/*count=*/ 2, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanIdleRight.h"
#include "Data/Sprites/SwordsmanWalkRight1.h"

// up idle
/*flags=*/ 0,
/*count=*/ 2, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanIdleBack.h"
#include "Data/Sprites/SwordsmanWalkBack1.h"

// down idle
/*flags=*/ 0,
/*count=*/ 2, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanIdleFront.h"
#include "Data/Sprites/SwordsmanWalkFront1.h"

// left walk
/*flags=*/ REF_SPRITE | MYX_FLIP_X,
/*source=*/ DIR_RIGHT,

// right walk
/*flags=*/ 0,
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanWalkRight1.h"
#include "Data/Sprites/SwordsmanWalkRight2.h"
#include "Data/Sprites/SwordsmanWalkRight3.h"
#include "Data/Sprites/SwordsmanWalkRight4.h"

// up walk
/*flags=*/ 0,
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanWalkBack1.h"
#include "Data/Sprites/SwordsmanWalkBack2.h"
#include "Data/Sprites/SwordsmanWalkBack3.h"
#include "Data/Sprites/SwordsmanWalkBack4.h"

// down walk
/*flags=*/ 0,
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanWalkFront1.h"
#include "Data/Sprites/SwordsmanWalkFront2.h"
#include "Data/Sprites/SwordsmanWalkFront3.h"
#include "Data/Sprites/SwordsmanWalkFront4.h"

// left melee attack
/*flags=*/ REF_SPRITE | MYX_FLIP_X,
/*source=*/ DIR_RIGHT,

// right melee attack
/*flags=*/ 0,
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanMeleeRight1.h"
#include "Data/Sprites/SwordsmanMeleeRight2.h"
#include "Data/Sprites/SwordsmanMeleeRight3.h"
#include "Data/Sprites/SwordsmanMeleeRight4.h"

// up melee attack
/*flags=*/ 0,
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanMeleeUp1.h"
#include "Data/Sprites/SwordsmanMeleeUp2.h"
#include "Data/Sprites/SwordsmanMeleeUp3.h"
#include "Data/Sprites/SwordsmanMeleeUp4.h"

// down melee attack
/*flags=*/ 0,
/*count=*/ 4, /* delay= */ 8, /* paletteIndex= */ 0,
#include "Data/Sprites/SwordsmanMeleeDown1.h"
#include "Data/Sprites/SwordsmanMeleeDown2.h"
#include "Data/Sprites/SwordsmanMeleeDown3.h"
#include "Data/Sprites/SwordsmanMeleeDown4.h"

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
