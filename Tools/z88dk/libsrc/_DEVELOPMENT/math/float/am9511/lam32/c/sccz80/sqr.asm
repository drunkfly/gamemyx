
    SECTION code_fp_am9511

    PUBLIC sqr
    EXTERN cam32_sccz80_sqr

    defc sqr = cam32_sccz80_sqr

; SDCC bridge for Classic
IF __CLASSIC
PUBLIC _sqr
EXTERN cam32_sdcc_sqr
defc _sqr = cam32_sdcc_sqr
ENDIF

