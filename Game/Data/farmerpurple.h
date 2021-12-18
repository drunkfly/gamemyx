static const byte FarmerPurpleData[] = {
// left idle
/*flags=*/ REF_SPRITE | MYX_FLIP_X,
/*source=*/ DIR_RIGHT,

// right idle
/*flags=*/ 0,
/*count=*/ 1, /* delay= */ 8, /* paletteIndex= */ 3,
#include "Data/Sprites/FarmerPurpleIdleRight.h"

// up idle
/*flags=*/ REF_SPRITE,
/*source=*/ DIR_LEFT,

// down idle
/*flags=*/ REF_SPRITE,
/*source=*/ DIR_RIGHT,

// left walk
/*flags=*/ NO_SPRITE,

// right walk
/*flags=*/ NO_SPRITE,

// up walk
/*flags=*/ NO_SPRITE,

// down walk
/*flags=*/ NO_SPRITE,

// left melee attack
/*flags=*/ NO_SPRITE,

// right melee attack
/*flags=*/ NO_SPRITE,

// up melee attack
/*flags=*/ NO_SPRITE,

// down melee attack
/*flags=*/ NO_SPRITE,

// left death
/*flags=*/ NO_SPRITE,

// right death
/*flags=*/ NO_SPRITE,

// up death
/*flags=*/ NO_SPRITE,

// down death
/*flags=*/ NO_SPRITE,
};
