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

SECTION code_clib
SECTION code_fp_am9511

EXTERN __IO_APU_CONTROL
EXTERN __IO_APU_OP_FLTS
EXTERN __IO_APU_OP_FLTD

EXTERN asm_am9511_pushi_fastcall
EXTERN asm_am9511_pushl_fastcall
EXTERN asm_am9511_popf

PUBLIC asm_am9511_float8
PUBLIC asm_am9511_float16
PUBLIC asm_am9511_float32

PUBLIC asm_am9511_float8u
PUBLIC asm_am9511_float16u
PUBLIC asm_am9511_float32u

EXTERN asm_am9511_normalize

; convert signed char in l to float in dehl
.asm_am9511_float8
    ld a,l
    rla                         ; sign bit of a into C
    sbc a,a
    ld h,a                      ; now hl is sign extended

; convert integer in hl to float in dehl
.asm_am9511_float16
    call asm_am9511_pushi_fastcall

    ld a,__IO_APU_OP_FLTS
    out (__IO_APU_CONTROL),a    ; convert to float 

    jp asm_am9511_popf

; now convert long in dehl to float in dehl
.asm_am9511_float32
    call asm_am9511_pushl_fastcall

    ld a,__IO_APU_OP_FLTD
    out (__IO_APU_CONTROL),a    ; convert to float 

    jp asm_am9511_popf


; convert character in l to float in dehl
.asm_am9511_float8u
    ld h,0

; convert unsigned in hl to float in dehl
.asm_am9511_float16u                  
    res 7,h                     ; ensure unsigned int's "sign" bit is reset
                                ; continue, with unsigned int number in hl
    call asm_am9511_pushi_fastcall

    ld a,__IO_APU_OP_FLTS
    out (__IO_APU_CONTROL),a    ; convert to float 

    jp asm_am9511_popf

; convert unsigned long in dehl to float in dehl
.asm_am9511_float32u                  
    res 7,d                     ; ensure unsigned long's "sign" bit is reset
                                ; continue, with unsigned long number in dehl

    call asm_am9511_pushl_fastcall

    ld a,__IO_APU_OP_FLTD
    out (__IO_APU_CONTROL),a    ; convert to float 

    jp asm_am9511_popf

