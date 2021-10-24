
    SECTION code_fp_math16

    PUBLIC  l_f16_fabs
    
    PUBLIC  fabsf16

    EXTERN  asm_f16_fabs

    defc l_f16_fabs = asm_f16_fabs

    defc fabsf16 = asm_f16_fabs


; SDCC bridge for Classic
IF __CLASSIC
PUBLIC _fabsf16
EXTERN cm16_sdcc_fabs
defc _fabsf16 = cm16_sdcc_fabs
ENDIF

