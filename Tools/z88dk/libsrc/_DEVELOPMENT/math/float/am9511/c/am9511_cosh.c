
#include "am9511_math.h"

float am9511_cosh (const float x) __z88dk_fastcall
{
    float y;

    y = exp(x);
    return div2( y + 1/y );
}
