;
;       Z88dk Generic Floating Point Math Library
;
;	
;
;       $Id: ddiv.asm,v 1.3 2016-06-21 21:16:49 dom Exp $:


        SECTION code_fp
	PUBLIC	ddiv

	EXTERN	fdiv

.ddiv
	pop	hl	;ret address 
	pop	de
	pop	ix
	pop	bc	
	push	hl
	jp	fdiv
