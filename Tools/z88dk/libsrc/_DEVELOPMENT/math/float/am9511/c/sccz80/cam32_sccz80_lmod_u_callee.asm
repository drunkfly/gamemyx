
; long __lmod_u_callee (long left, long right)

SECTION code_clib
SECTION code_fp_am9511

PUBLIC cam32_sccz80_lmod_u_callee

EXTERN asm_am9511_lmod_callee

    ; modulus of sccz80 unsigned long by sccz80 unsigned long
    ;
    ; enter : stack = sccz80_long left, ret
    ;          DEHL = sccz80_long right
    ;
    ; exit  :  DEHL = sccz80_long(left+right)
    ;
    ; uses  : af, bc, de, hl, af', bc', de', hl'

.cam32_sccz80_lmod_u_callee
    res 7,d                 ; unsigned divisor
    jp asm_am9511_lmod_callee
                            ; enter stack = sccz80_long left, ret
                            ;        DEHL = sccz80_long right
                            ; return DEHL = sccz80_long
