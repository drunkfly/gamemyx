
	SECTION	code_fp_am9511
	PUBLIC	sinh
	EXTERN	cam32_sccz80_sinh

	defc	sinh = cam32_sccz80_sinh

; SDCC bridge for Classic
IF __CLASSIC
PUBLIC _sinh
EXTERN cam32_sdcc_sinh
defc _sinh = cam32_sdcc_sinh
ENDIF

