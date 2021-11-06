;
; Copyright (c) 2021 DrunkFly Team
; Licensed under 3-clause BSD license
;

                PUBLIC  _MYXP_IntVectors
                PUBLIC  _MYXP_IntEntry

                EXTERN  _MYXP_InterruptHandler

                SECTION MYX_INTENTRY

_MYXP_IntEntry: push    af
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
                call    _MYXP_InterruptHandler
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

                SECTION MYX_INTVECTORS

_MYXP_IntVectors:
                dw      _MYXP_IntEntry
                defs    255, 0x81
