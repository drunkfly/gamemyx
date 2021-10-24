
; long __lmod (long left, long right)

SECTION code_clib
SECTION code_fp_am9511

PUBLIC cam32_sdcc_lmods, cam32_sdcc_lmodu

EXTERN cam32_sdcc_readr, asm_am9511_lmod

.cam32_sdcc_lmods

    ; modulus sdcc long by sdcc long
    ;
    ; enter : stack = sdcc_long right, sdcc_long left, ret
    ;
    ; exit  : DEHL = sdcc_long(left/right)
    ;
    ; uses  : af, bc, de, hl, af', bc', de', hl'

    call cam32_sdcc_readr
    jp asm_am9511_lmod      ; enter stack = sdcc_long right, sdcc_long left, ret
                            ;        DEHL = sdcc_long right
                            ; return DEHL = sdcc_long

.cam32_sdcc_lmodu

    ; modulus sdcc long by sdcc long
    ;
    ; enter : stack = sdcc_long right, sdcc_long left, ret
    ;
    ; exit  : DEHL = sdcc_long(left/right)
    ;
    ; uses  : af, bc, de, hl, af', bc', de', hl'

    call cam32_sdcc_readr
    res 7,d                 ; unsigned divisor
    jp asm_am9511_lmod      ; enter stack = sdcc_long right, sdcc_long left, ret
                            ;        DEHL = sdcc_long right
                            ; return DEHL = sdcc_long
