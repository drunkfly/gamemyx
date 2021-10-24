;
;       Z88 Graphics Functions
;       Written around the Interlogic Standard Library
;
;       Wide resolution (int type parameters) and CALLEE conversion by Stefano Bodrato, 2018
;
; ----- void __CALLEE__ draw(int x, int y, int x2, int y2)
;
;
;	$Id: w_draw_callee.asm $
;

IF !__CPU_INTEL__
SECTION code_graphics
PUBLIC draw_callee
PUBLIC _draw_callee
PUBLIC ASMDISP_DRAW_CALLEE

	EXTERN     swapgfxbk
	EXTERN    swapgfxbk1
	;EXTERN    __gfx_color
	EXTERN     w_line_r
	EXTERN     w_plotpixel
	EXTERN     __graphics_end



.draw_callee
._draw_callee
		pop af
		pop	de	;y2
		pop	hl	;x2
		exx			; w_plotpixel and swapgfxbk must not use the alternate registers, no problem with w_line_r
		pop de		;y1
		pop hl		;x1
		push af		; ret addr
		
; de = x1, hl = y1, hl'=x2, de'=y2
.asmentry
		
		push ix
		push hl		;x1
		push de		;y1
		call    swapgfxbk
		call	w_plotpixel

		exx
		ex	de,hl
		pop	bc	;y1
		or	a
		sbc	hl,bc
		ex	de,hl
		
		pop	bc		;x1
		or	a
		sbc	hl,bc

		ld      ix,w_plotpixel
		call    w_line_r
		jp      __graphics_end


DEFC ASMDISP_DRAW_CALLEE = asmentry - draw_callee
ENDIF
