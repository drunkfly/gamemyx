;       CRT0 (rom) stub for the SEGA SC-3000/SG-1000
;
;       Stefano Bodrato - Jun 2010
;
;	$Id: sc3000_crt0.asm,v 1.18 2016-07-13 22:12:25 dom Exp $
;

	; Constants for ROM mode (-startup=2)
	
	defc	ROM_Start  = $0000
	defc	RAM_Start  = $C000
	defc	RAM_Length = $0800
	defc	Stack_Top  = $c400

	defc    CRT_ORG_CODE  = ROM_Start
        defc    TAR__register_sp = Stack_Top
        defc    TAR__clib_exit_stack_size = 0
        defc    TAR__fgetc_cons_inkey = 1
	defc	__CPU_CLOCK = 3580000

	; VDP signals delivered to im1
	defc TAR__crt_enable_rst = $8080
	defc _z80_rst_38h = tms9918_interrupt

	; NMI is delivered by BREAK on the keyboard
IFNDEF CRT_ENABLE_NMI
	defc TAR__crt_enable_nmi = 1
	EXTERN asm_nmi_handler
	defc _z80_nmi = asm_nmi_handler
ENDIF
	INCLUDE	"crt/classic/crt_rules.inc"

	EXTERN	msx_set_mode
	EXTERN	im1_vectors
	EXTERN	asm_interrupt_handler

        org     CRT_ORG_CODE

if (ASMPC<>$0000)
        defs    CODE_ALIGNMENT_ERROR
endif
	di
        jp      program

	INCLUDE	"crt/classic/crt_z80_rsts.asm"

	; Interrupt routine, defines tms9918_interrupt
	INCLUDE	"crt/classic/tms9918/interrupt.asm"
	ei
	reti

int_VBL:
	ld	hl,im1_vectors
	call	asm_interrupt_handler
	pop	hl
	pop	af
	ei
	reti



program:
; Make room for the atexit() stack
	INCLUDE	"crt/classic/crt_init_sp.asm"
	INCLUDE	"crt/classic/crt_init_atexit.asm"

	call	crt0_init_bss
	ld      (exitsp),sp

; Optional definition for auto MALLOC init
; it assumes we have free space between the end of 
; the compiled program and the stack pointer
	IF DEFINED_USING_amalloc
		INCLUDE "crt/classic/crt_init_amalloc.asm"
	ENDIF


	; Initialise mode 2 by default
	ld	hl,2
	call	msx_set_mode
	
	im	1
;	ei

; Entry to the user code
	call    _main

cleanup:
;
;       Deallocate memory which has been allocated here!
;
	push	hl
	call    crt0_exit


endloop:
	jr	endloop


	defc	__crt_org_bss = RAM_Start
        ; If we were given a model then use it
        IF DEFINED_CRT_MODEL
            defc __crt_model = CRT_MODEL
        ELSE
            defc __crt_model = 1
        ENDIF
