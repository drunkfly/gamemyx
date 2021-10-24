
; float __fsub (float left, float right)

SECTION code_clib
SECTION code_fp_am9511

PUBLIC cam32_sccz80_fsub

EXTERN cam32_sccz80_switch_arg, cam32_sccz80_readl
EXTERN asm_am9511_fsub

    ; subtract sccz80 float from sccz80 float
    ;
    ; enter : stack = sccz80_float left, sccz80_float right, ret
    ;
    ; exit  :  DEHL = sccz80_float(left-right)
    ;
    ; uses  : af, bc, de, hl, af', bc', de', hl'

.cam32_sccz80_fsub
    call cam32_sccz80_switch_arg
    call cam32_sccz80_readl
    jp asm_am9511_fsub      ; enter stack = sccz80_float right, sccz80_float left, ret
                            ;        DEHL = sccz80_float right
                            ; return DEHL = sccz80_float
