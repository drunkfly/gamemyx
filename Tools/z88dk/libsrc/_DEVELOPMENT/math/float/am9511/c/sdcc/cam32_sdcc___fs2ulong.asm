
SECTION code_fp_am9511
PUBLIC cam32_sdcc___fs2ulong

EXTERN asm_am9511_f2ulong
EXTERN cam32_sdcc_read1

.cam32_sdcc___fs2ulong
    call cam32_sdcc_read1
    jp asm_am9511_f2ulong
