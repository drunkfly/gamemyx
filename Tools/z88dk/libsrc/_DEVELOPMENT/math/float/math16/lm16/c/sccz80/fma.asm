
	SECTION	code_fp_math16
	PUBLIC	fmaf16
	EXTERN	cm16_sccz80_fma

	defc	fmaf16 = cm16_sccz80_fma


; SDCC bridge for Classic
IF __CLASSIC
PUBLIC _fmaf16
EXTERN cm16_sdcc_fma
defc _fmaf16 = cm16_sdcc_fma
ENDIF

