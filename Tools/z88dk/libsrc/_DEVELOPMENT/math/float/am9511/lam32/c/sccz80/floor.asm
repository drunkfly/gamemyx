
	SECTION	code_fp_am9511
	PUBLIC	floor
	EXTERN	cam32_sccz80_floor

	defc	floor = cam32_sccz80_floor

; SDCC bridge for Classic
IF __CLASSIC
PUBLIC _floor
EXTERN cam32_sdcc_floor
defc _floor = cam32_sdcc_floor
ENDIF

