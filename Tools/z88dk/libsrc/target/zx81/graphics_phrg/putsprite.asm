;
;--------------------------------------------------------------
; ZX81 Pseudo - HRG library
; by Stefano Bodrato, Mar. 2020
;--------------------------------------------------------------
;
; Sprite Rendering Routine
; original code by Patrick Davidson (TI 85)
; modified by Stefano Bodrato - Jan 2009
;
;
; $Id: putsprite.asm $
;

	MODULE    __pseudohrg_putsprite

	SECTION smc_clib
	PUBLIC  putsprite
	PUBLIC  _putsprite

	EXTERN	base_graphics

	INCLUDE "graphics/grafix.inc"

        EXTERN  pixeladdress
        EXTERN  __pixeladdress_hl
        EXTERN	__pixelbyte
        EXTERN  __dfile_addr
		EXTERN	pix_return_pixelbyte


;	EXTERN  swapgfxbk
        EXTERN	__graphics_end



; __gfx_coords: d,e (vert-horz)
; sprite: (ix)


.putsprite
._putsprite
	push	ix		;save callers
        ld      hl,4
        add     hl,sp
        ld      e,(hl)
        inc     hl
        ld      d,(hl)  ; sprite address
	push	de
	pop	ix

        inc     hl
        ld      e,(hl)  
 	inc	hl
        inc     hl
        ld      d,(hl)	; x and y __gfx_coords

	inc	hl

        inc     hl
        ld      a,(hl)  ; and/or/xor mode
        ld	(ortype+1),a	; Self modifying code
        ld	(ortype2+1),a	; Self modifying code

        inc     hl
        ld      a,(hl)
        ld	(ortype),a	; Self modifying code
        ld	(ortype2),a	; Self modifying code


	ld	h,d
	ld	l,e

	ld	(actcoord),hl	; save current coordinates

	;call    swapgfxbk
	call	pixeladdress

         ld       hl,offsets_table
         ld       c,a
         ld       b,0
         add      hl,bc
         ld       a,(hl)
         ld       (wsmc1+1),a
         ld       (wsmc2+1),a
	 ld       (_smc1+1),a
	ld	h,d
	ld	l,e
	

	ld	a,(ix+0)
	;cp	9
	cp	5		; we have nibbles, not bytes !
	jr	nc,putspritew

         ld       d,(ix+0)
         ld       b,(ix+1)
._oloop  push     bc                ;Save # of rows
         ld       b,d               ;Load width
         ld       c,(ix+2)          ;Load one line of image
         inc      ix
._smc1   ld       a,1               ;Load pixel mask
._iloop
	 ;push     hl			;*
	 ld       hl,__pixelbyte		;*
         sla      c                 ;Test leftmost pixel
         jr       nc,_noplot        ;See if a plot is needed
         ld       e,a
.ortype
	nop	; changed into nop / cpl
         nop	; changed into and/or/xor (hl)
	;and @00001111
	 ld       (hl),a		; we work on "__pixelbyte"

         ld       a,e
._noplot rrca
         ;pop      hl			;*
         call     c,_edge        ;If edge of byte reached, go to next byte
         djnz     _iloop

	; ---------
         call     _row
	; ---------

         pop      bc                ;Restore data
         djnz     _oloop
.putsprite_exit
	 jp       __graphics_end


.putspritew
         ld       d,(ix+0)
         ld       b,(ix+1)
.woloop  push     bc                ;Save # of rows
         ld       b,d               ;Load width
         ld       c,(ix+2)          ;Load one line of image
         inc      ix
.wsmc1   ld       a,1               ;Load pixel mask
.wiloop
	 ;push     hl			;*
	 ld       hl,__pixelbyte		;*
         sla      c                 ;Test leftmost pixel
         jr       nc,wnoplot         ;See if a plot is needed
         ld       e,a

.ortype2
	nop	; changed into nop / cpl
         nop	; changed into and/or/xor (hl)
	;and @00001111
         ld       (hl),a
         ld       a,e
.wnoplot rrca
         ;pop      hl			;*
         call     c,_edge        ;If edge of byte reached, go to next byte
.wsmc2   cp       1
         jr       z,wover_1
         djnz     wiloop

	; ---------
         call     _row
	; ---------

         pop      bc                ;Restore data
         djnz     woloop
	 jr       putsprite_exit
	

.wover_1 ld       c,(ix+2)
         inc      ix
         djnz     wiloop
         dec      ix

	; ---------
         call     _row
	; ---------

         pop      bc
         djnz     woloop
	 jr       putsprite_exit



; Edge of byte reached, save its content,
; increment video ptr, and get new byte.
._edge
	push     af
	push     bc
;**************
	push de
	call pix_return_pixelbyte
	
	ld	hl,(__dfile_addr)
	inc hl
	call __pixeladdress_hl
	pop de
;**************
	pop      bc
	pop      af
	ret



._row
	push	af
;**************
	push de
	call pix_return_pixelbyte
;	pop de 
;**************
;	push	de
	ld	hl,(actcoord)
	inc	l
	ld	(actcoord),hl
	call	pixeladdress
	pop	de		; (hl=de=pixelbyte, we can trash de directly)
	pop	af
	ret


    
	SECTION	rodata_clib
.offsets_table
         defb	1,2,4,8
		 ;defb	16,32,64,128
		 ;defb	128,64,32,16


	SECTION bss_clib
.actcoord
	defw	0


