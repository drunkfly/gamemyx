
SECTION code_fp_am9511

PUBLIC cam32_sdcc_fmul2

EXTERN cam32_sdcc_read1, asm_am9511_fmul2_fastcall

.cam32_sdcc_fmul2
    call cam32_sdcc_read1
    jp asm_am9511_fmul2_fastcall
