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
;  asm_am9511_0_popi - am9511 APU pop integer
;-------------------------------------------------------------------------
; 
;  Load integer from Am9511 APU stack
;
;-------------------------------------------------------------------------

SECTION code_fp_am9511

EXTERN __IO_APU0_STATUS, __IO_APU0_DATA

PUBLIC asm_am9511_0_popi_hl
PUBLIC asm_am9511_0_popi

.am9511_0_popi_hl_wait
    ex (sp),hl
    ex (sp),hl
    
.asm_am9511_0_popi_hl

    ; float primitive
    ; pop an integer from the Am9511 stack.
    ;
    ; enter : stack = ret1, ret0
    ;       :    hl = pointer to integer
    ;
    ; exit  : stack = long, ret1
    ; 
    ; uses  : af, bc, hl

    in a,(__IO_APU0_STATUS)     ; read the APU status register
    rlca                        ; busy? __IO_APU_STATUS_BUSY
    jr C,am9511_0_popi_hl_wait

    ld bc,__IO_APU0_DATA        ; the address of the APU data port in bc
    inc hl
    ind                         ; load LSW into APU
    inc b
    ind
    ret

.am9511_0_popi_wait
    ex (sp),hl
    ex (sp),hl

.asm_am9511_0_popi

    ; float primitive
    ; pop an integer from the Am9511 stack.
    ;
    ; enter : stack = ret0
    ;
    ; exit  :  dehl = integer
    ; 
    ; uses  : af, bc, hl

    in a,(__IO_APU0_STATUS)     ; read the APU status register
    rlca                        ; busy? and __IO_APU_STATUS_BUSY
    jr C,am9511_0_popi_wait

    ld bc,__IO_APU0_DATA        ; the address of the APU data port in bc
    in h,(c)                    ; load LSW from APU
    in l,(c)
    ret

