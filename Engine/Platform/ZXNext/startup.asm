;
; Copyright (c) 2021 DrunkFly Team
; Licensed under 3-clause BSD license
;

                PUBLIC  _main

                EXTERN  _MYXP_EngineMain
                EXTERN  _MYXP_IntVectors

                SECTION MYX_STARTUP

_main:          ld      sp, 0x8300
                di
                ld      a, 0x80 | (_MYXP_IntVectors & 0)
                ld      i, a
                im      2
                ei
                jp      _MYXP_EngineMain
