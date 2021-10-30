;
; Copyright (c) 2021 DrunkFly Team
; Licensed under 3-clause BSD license
;

                PUBLIC  _IntVectors
                PUBLIC  _IntEntry

                EXTERN  _InterruptHandler

                SECTION INT_ENTRY

_IntEntry:      push    af
                push    bc
                push    de
                push    hl
                ex      af, af'
                exx
                push    af
                push    bc
                push    de
                push    hl
                push    ix
                push    iy
                call    _InterruptHandler
                pop     iy
                pop     ix
                pop     hl
                pop     de
                pop     bc
                pop     af
                exx
                ex      af, af'
                pop     hl
                pop     de
                pop     bc
                pop     af
                ei
                ret

                SECTION INT_VECTORS

_IntVectors:    dw      _IntEntry
                defs    255, 0x81
