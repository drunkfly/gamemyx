
	SECTION	code_fp_math16
	PUBLIC	logf16
	EXTERN	_m16_logf

	defc	logf16 = _m16_logf


; SDCC bridge for Classic
IF __CLASSIC
PUBLIC _logf16
EXTERN cm16_sdcc_log
defc _logf16 = cm16_sdcc_log
ENDIF

