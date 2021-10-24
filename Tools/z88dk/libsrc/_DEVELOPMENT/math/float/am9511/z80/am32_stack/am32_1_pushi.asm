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
;  asm_am9511_1_pushi - am9511 APU push integer
;-------------------------------------------------------------------------
; 
;  Load integer into Am9511 APU stack
;
;-------------------------------------------------------------------------

SECTION code_fp_am9511

EXTERN __IO_APU1_STATUS, __IO_APU1_DATA

PUBLIC asm_am9511_1_pushi_hl
PUBLIC asm_am9511_1_pushi_fastcall

.am9511_1_pushi_hl_wait
    ex (sp),hl
    ex (sp),hl

.asm_am9511_1_pushi_hl

    ; float primitive
    ; push an integer into Am9511 stack.
    ;
    ; enter : stack = integer, ret1, ret0
    ;       :    hl = pointer to integer
    ;
    ; exit  : stack = integer, ret1
    ; 
    ; uses  : af, bc, hl

    in a,(__IO_APU1_STATUS)     ; read the APU status register
    rlca                        ; busy? __IO_APU_STATUS_BUSY
    jr C,am9511_1_pushi_hl_wait

    ld bc,__IO_APU1_DATA        ; the address of the APU data port in bc
    outi                        ; load LSW into APU
    inc b
    outi
    ret

.am9511_1_pushi_fastcall_wait
    ex (sp),hl
    ex (sp),hl

.asm_am9511_1_pushi_fastcall

    ; float primitive
    ; push an integer into Am9511 stack.
    ;
    ; enter : stack = ret1, ret0
    ;       :    hl = integer
    ;
    ; exit  : stack = ret1
    ; 
    ; uses  : af, bc, hl

    in a,(__IO_APU1_STATUS)     ; read the APU status register
    rlca                        ; busy? __IO_APU_STATUS_BUSY
    jr C,am9511_1_pushi_fastcall_wait

    ld bc,__IO_APU1_DATA        ; the address of the APU data port in bc
    out (c),l                   ; load LSW into APU
    out (c),h
    ret

