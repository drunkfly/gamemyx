
SECTION code_fp_am9511

PUBLIC cam32_sdcc_sinh

EXTERN cam32_sdcc_read1, _am9511_sinh

.cam32_sdcc_sinh
    call cam32_sdcc_read1
    jp _am9511_sinh
