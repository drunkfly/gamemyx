
SECTION code_fp_am9511

PUBLIC cam32_sdcc_round

EXTERN cam32_sdcc_read1, _am9511_round

.cam32_sdcc_round
    call cam32_sdcc_read1
    jp _am9511_round
