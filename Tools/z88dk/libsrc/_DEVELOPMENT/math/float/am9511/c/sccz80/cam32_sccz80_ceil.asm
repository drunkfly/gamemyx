

SECTION code_fp_am9511
PUBLIC cam32_sccz80_ceil

EXTERN cam32_sccz80_read1, asm_am9511_ceil_fastcall

.cam32_sccz80_ceil
    call cam32_sccz80_read1
    jp asm_am9511_ceil_fastcall
