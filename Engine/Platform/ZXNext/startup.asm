;
; Copyright (c) 2021 DrunkFly Team
; Licensed under 3-clause BSD license
;

                PUBLIC  _main

                EXTERN  _EngineMain
                EXTERN  _IntVectors

                SECTION ENGINE_INIT

_main:          ld      sp, 0x8300
                di
                ld      a, 0x80 | (_IntVectors & 0)
                ld      i, a
                im      2
                ei
                jp      _EngineMain
