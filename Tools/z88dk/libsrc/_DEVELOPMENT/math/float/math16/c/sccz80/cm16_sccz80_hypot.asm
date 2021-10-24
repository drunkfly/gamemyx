
; half __hypot (half left, half right)

SECTION code_fp_math16

PUBLIC cm16_sccz80_hypot

EXTERN asm_f24_f16
EXTERN asm_f16_f24

EXTERN asm_f24_mul_f24
EXTERN asm_f24_add_f24

EXTERN asm_f24_sqrt

.cm16_sccz80_hypot

    ; hypotenuse of two sccz80 halfs
    ;
    ; enter : stack = sccz80_half left, sccz80_half right, ret
    ;
    ; exit  :    HL = sccz80_half(left+right)
    ;
    ; uses  : af, bc, de, hl, af', bc', de', hl'

    pop bc                      ; pop return address
    pop hl                      ; get right operand off of the stack
    pop de                      ; get left operand off the stack
    push de                     ; left operand on the stack
    push hl                     ; right operand on of the stack
    push bc                     ; push return
    push de                     ; left operand on the stack

    call asm_f24_f16            ; expand y to dehl
    push de                     ; y      d  = eeeeeeee e  = s-------
    push hl                     ;        hl = 1mmmmmmm mmmmmmmm
    exx

    pop hl
    pop de
    call asm_f24_mul_f24        ; y * y

    ex (sp),hl                  ; get left operand off of the stack
    push de                     ; y^2 on stack (backwards)
    call asm_f24_f16            ; expand x to dehl
    push de                     ; x      d  = eeeeeeee e  = s-------
    push hl                     ;        hl = 1mmmmmmm mmmmmmmm
    exx

    pop hl
    pop de
    call asm_f24_mul_f24        ; x * x
    exx

    pop de                      ; y^2
    pop hl
    call asm_f24_add_f24
    call asm_f24_sqrt
    jp asm_f16_f24              ; return HL = sccz80_half

