
    SECTION code_fp_math16
    PUBLIC  mul10f16
    EXTERN asm_f16_mul10

    defc mul10f16 = asm_f16_mul10


; SDCC bridge for Classic
IF __CLASSIC
PUBLIC _mul10f16
EXTERN cm16_sdcc_mul10
defc _mul10f16 = cm16_sdcc_mul10
ENDIF

