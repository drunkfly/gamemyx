;
; Copyright (c) 2021 DrunkFly Team
; Licensed under 3-clause BSD license
;

                PUBLIC  _MYX_WordToString

                EXTERN  ___sdcc_enter_ix

                SECTION MYX_CORE

_MYX_WordToString:
                call	___sdcc_enter_ix
	            ld	    e, (ix+4)       ; DE <- buffer
	            ld	    d, (ix+5)
                ld      l, (ix+6)       ; HL <- value
                ld      h, (ix+7)
                pop	    ix
                push    de
                ld      bc, -10000
                call    _MYX_WordToString_l1
                ld      bc, -1000
                call    _MYX_WordToString_l1
                ld      bc, -100
                call    _MYX_WordToString_l1
                ld      c, -10
                call    _MYX_WordToString_l1
                ld      c, -1
                call    _MYX_WordToString_l1
                pop     hl
                ; strip leading '0'
                ld      a, (hl)
                cp      48              ; '0'
                ret     nz
                inc     hl
                ld      a, (hl)
                cp      48              ; '0'
                ret     nz
                inc     hl
                ld      a, (hl)
                cp      48              ; '0'
                ret     nz
                inc     hl
                ld      a, (hl)
                cp      48              ; '0'
                ret     nz
                inc     hl
                ret

_MYX_WordToString_l1:
                ld      a, 47           ; '0' - 1
_MYX_WordToString_l2:
                inc     a
                add     hl, bc
                jr      c, _MYX_WordToString_l2
                sbc     hl, bc
                ld      (de), a
                inc     de
                ret
