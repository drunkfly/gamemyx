
	SECTION	code_fp_am9511
	PUBLIC	round
	EXTERN	cam32_sccz80_round

	defc	round = cam32_sccz80_round

; SDCC bridge for Classic
IF __CLASSIC
PUBLIC _round
EXTERN	cam32_sdcc_round
defc _round = cam32_sdcc_round
ENDIF

