
	SECTION	code_fp_am9511
	PUBLIC	fmin
	EXTERN	cam32_sccz80_fmin

	defc	fmin = cam32_sccz80_fmin

; SDCC bridge for Classic
IF __CLASSIC
PUBLIC _fmin
EXTERN cam32_sdcc_fmin
defc _fmin = cam32_sdcc_fmin
ENDIF

