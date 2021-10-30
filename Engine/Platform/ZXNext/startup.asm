;
; Copyright (c) 2021 DrunkFly Team
; Licensed under 3-clause BSD license
;

                SECTION ENGINE_INIT

                EXTERN  _EngineMain

                PUBLIC  _main

_main:          
                jp      _EngineMain
