
SECTION code_fp_am9511

PUBLIC cam32_sdcc_floor

EXTERN cam32_sdcc_read1, asm_am9511_floor_fastcall

.cam32_sdcc_floor
    call cam32_sdcc_read1
    jp asm_am9511_floor_fastcall
