;
;  Copyright (c) 2020 Phillip Stevens
;
;  This Source Code Form is subject to the terms of the Mozilla Public
;  License, v. 2.0. If a copy of the MPL was not distributed with this
;  file, You can obtain one at http://mozilla.org/MPL/2.0/.
;
;  feilipu, August 2020
;
;-------------------------------------------------------------------------
; asm_am9511_sqr - z80, z180, z80n floating point square
;-------------------------------------------------------------------------

SECTION code_clib
SECTION code_fp_am9511

EXTERN __IO_APU_CONTROL
EXTERN __IO_APU_OP_PTOF
EXTERN __IO_APU_OP_FMUL

EXTERN asm_am9511_pushf_hl
EXTERN asm_am9511_pushf_fastcall
EXTERN asm_am9511_popf


PUBLIC asm_am9511_sqr, asm_am9511_sqr_fastcall


.asm_am9511_sqr
    ld hl,2
    add hl,sp
    call asm_am9511_pushf_hl        ; x

    ld a,__IO_APU_OP_PTOF
    out (__IO_APU_CONTROL),a        ; x

    ld a,__IO_APU_OP_FMUL
    out (__IO_APU_CONTROL),a        ; x*x

    jp asm_am9511_popf


.asm_am9511_sqr_fastcall
    call asm_am9511_pushf_fastcall  ; x

    ld a,__IO_APU_OP_PTOF
    out (__IO_APU_CONTROL),a        ; x

    ld a,__IO_APU_OP_FMUL
    out (__IO_APU_CONTROL),a        ; x*x

    jp asm_am9511_popf

