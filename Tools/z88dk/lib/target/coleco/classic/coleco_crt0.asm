;
;	Startup for Colecovision
;
;	1k of memory 

	module	coleco_crt0 


;--------
; Include zcc_opt.def to find out some info
;--------

        defc    crt0 = 1
        INCLUDE "zcc_opt.def"

;--------
; Some scope definitions
;--------

        EXTERN    _main           ;main() is always external to crt0 code

        PUBLIC    cleanup         ;jp'd to by exit()
        PUBLIC    l_dcal          ;jp(hl)
	PUBLIC	  msxbios
	EXTERN	  msx_set_mode
	EXTERN    asm_im1_handler
	EXTERN    nmi_vectors
        EXTERN    asm_interrupt_handler
	EXTERN    __vdp_enable_status
	EXTERN    VDP_STATUS

	defc	CONSOLE_COLUMNS = 32
	defc	CONSOLE_ROWS = 24

	defc	CRT_ORG_BSS = 0x7000	
	defc	CRT_ORG_CODE = 0x8000

        defc    TAR__fputc_cons_generic = 1
        defc    TAR__no_ansifont = 1
        defc    TAR__clib_exit_stack_size = 0
        defc    TAR__register_sp = 0x7400
	defc	CRT_KEY_DEL = 127
	defc	__CPU_CLOCK = 3579545
        INCLUDE "crt/classic/crt_rules.inc"

	org	  CRT_ORG_CODE

	defb	0x55, 0xaa	;Title screen + 12 second delay, swap to not skip it
	defw	0		;Sprite name table for BIOS
	defw	0		;Sprite order table for BIOS
	defw	0		;Buffer for BIOS
	defw	0		;Controller map for bios
	defw	program		;Where to start execution from
IF ((__crt_enable_rst & $0202) = $0002)
        EXTERN  _z80_rst_08h
        jp      _z80_rst_08h
ELSE
	jp	restart_ret
ENDIF
IF ((__crt_enable_rst & $0404) = $0004)
        EXTERN  _z80_rst_10h
        jp      _z80_rst_10h
ELSE
	jp	restart_ret
ENDIF
IF ((__crt_enable_rst & $0808) = $0008)
        EXTERN  _z80_rst_18h
        jp      _z80_rst_18h
ELSE
	jp	restart_ret
ENDIF
IF ((__crt_enable_rst & $1010) = $0010)
        EXTERN  _z80_rst_20h
        jp      _z80_rst_20h
ELSE
	jp	restart_ret
ENDIF
IF ((__crt_enable_rst & $2020) = $0020)
        EXTERN  _z80_rst_28h
        jp      _z80_rst_28h
ELSE
	jp	restart_ret
ENDIF
IF ((__crt_enable_rst & $4040) = $0040)
        EXTERN  _z80_rst_30h
        jp      _z80_rst_30h
ELSE
	jp	restart_ret
ENDIF
IF ((__crt_enable_rst & $8080) = $0080)
	EXTERN	_z80_rst_38h
        jp      _z80_rst_38h
ELSE
	jp	asm_im1_handler	;Maskable interrupt
ENDIF
IF (__crt_enable_nmi > 1)
	EXTERN	_z80_nmi
	jp	_z80_nmi
ELSE
	jp	nmi_int		;NMI
ENDIF
	defm	" / / "		;TODO: Make it customisable
	

; Restart routines, nothing sorted yet
restart_ret:
	ret

program:
        INCLUDE "crt/classic/crt_init_sp.asm"
        INCLUDE "crt/classic/crt_init_atexit.asm"
	call    crt0_init_bss
	ld	(exitsp),sp
	ld	hl,2
	call	msx_set_mode
	im	1
    	ei
; Optional definition for auto MALLOC init
; it assumes we have free space between the end of
; the compiled program and the stack pointer
IF DEFINED_USING_amalloc
    INCLUDE "crt/classic/crt_init_amalloc.asm"
ENDIF
	call	_main
cleanup:
	rst	0		;Restart when main finishes



IF (__crt_enable_nmi <= 1)
nmi_int:
	push	af
	push	hl
	ld	a,(__vdp_enable_status)
	rlca
	jr	c,no_vbl
	in	a,(VDP_STATUS)
no_vbl:
	ld	hl,nmi_vectors
	call	asm_interrupt_handler
	pop	hl
	pop	af
	retn
ENDIF


; Safe BIOS call
msxbios:
        push    ix
        ret


l_dcal: jp      (hl)            ;Used for function pointer calls

	INCLUDE "crt/classic/crt_runtime_selection.asm" 
	
	defc	__crt_org_bss = CRT_ORG_BSS
        IF DEFINED_CRT_MODEL
            defc __crt_model = CRT_MODEL
        ELSE
            defc __crt_model = 1
        ENDIF
	INCLUDE	"crt/classic/crt_section.asm"

