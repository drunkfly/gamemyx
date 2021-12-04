;
; Copyright (c) 2021 DrunkFly Team
; Licensed under 3-clause BSD license
;

                PUBLIC  _MYX_ByteToString

                EXTERN  ___sdcc_enter_ix

                SECTION MYX_CORE

_MYX_ByteToString:
                call	___sdcc_enter_ix
	            ld	    l, (ix+4)       ; HL <- buffer
	            ld	    h, (ix+5)
                ld      a, (ix+6)       ; A <- value
                pop	    ix
                push    hl
                ld      c, -100
                call    _MYX_ByteToString_l1
                ld      c, -10
                call    _MYX_ByteToString_l1
                ld      c, -1
                call    _MYX_ByteToString_l1
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
	            ret

_MYX_ByteToString_l1:
                ld      b, 47           ; '0' - 1
_MYX_ByteToString_l2:
                inc     b
                add     a, c
                jr      c, _MYX_ByteToString_l2
                sub     c
                ld      (hl), b
                inc     hl
                ret
