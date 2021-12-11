;
; Copyright (c) 2021 DrunkFly Team
; Licensed under 3-clause BSD license
;

                PUBLIC  _MYX_IsKeyPressed
                PUBLIC  _MYX_IsGamepad1Pressed
                PUBLIC  _MYX_IsGamepad2Pressed

                PUBLIC  _MYXP_ReadInput
                PUBLIC  _MYXP_RawKeys
                PUBLIC  _MYXP_RawKempston

                SECTION MYX_INPUT

_MYXP_RawKeys:  db      0, 0, 0, 0, 0, 0, 0, 0
_MYXP_RawKempston:
                db      0, 0

_MYXP_ReadInput:; Read keyboard
                ld      bc, 0xfefe
                in      l, (c)          ; CAPS, Z, X, C, V
                ld      b, 0xfd
                in      h, (c)          ; A, S, D, F, G
                ld      (_MYXP_RawKeys + 0), hl
                ld      b, 0xfb
                in      l, (c)          ; Q, W, E, R, T
                ld      b, 0xf7
                in      h, (c)          ; 1, 2, 3, 4, 5
                ld      (_MYXP_RawKeys + 2), hl
                ld      bc, 0xeffe
                in      l, (c)          ; 0, 9, 8, 7, 6
                ld      b, 0xdf
                in      h, (c)          ; P, O, I, U, Y
                ld      (_MYXP_RawKeys + 4), hl
                ld      b, 0xbf
                in      l, (c)          ; ENTER, L, K, J, H
                ld      b, 0x7f
                in      h, (c)          ; SPACE, SYM, M, N, B
                ld      (_MYXP_RawKeys + 6), hl
                ; Read kempston
                ld      c, 0x1f         ; Kempston 1
                in      l, (c)
                ld      c, 0x37         ; Kempston 2
                in      h, (c)
                ld      (_MYXP_RawKempston), hl
                ret

_MYX_IsKeyPressed:
                ; Calculate offset into _RawKeys
                ld      a, l
                rlca
                rlca
                rlca
                and     7
                ld      b, 0                ; BC => offset into _RawKeys
                ld      c, a
                ; Calculate bit mask
                ld      a, l
                and     0x1f
                ; Read port value
                ld      hl, _MYXP_RawKeys
                add     hl, bc
                and     (hl)
                ld      l, b                ; L = 0
                ret     nz                  ; not pressed
                inc     l
                ret

_MYX_IsGamepad1Pressed:
                ld      a, (_MYXP_RawKempston)
CheckGamepadPress:
                and     l
                ld      l, 1
                ret     nz                  ; return if pressed
                dec     l
                ret

_MYX_IsGamepad2Pressed:
                ld      a, (_MYXP_RawKempston+1)
                jr      CheckGamepadPress

_MYX_IsAnyKeyPressed:
                ld      hl, _MYXP_RawKeys
                ld      b, 8
_MYX_IsAnyKeyPressed_1:
                ld      a, (hl)
                inc     hl
                and     0x1f
                cp      0x1f
                jr      nz, _MYX_IsAnyKeyPressed_2
                djnz    _MYX_IsAnyKeyPressed_1
                ld      a, (_MYXP_RawKempston)
                or      a
                ld      l, a
                ret     z
_MYX_IsAnyKeyPressed_2:
                ld      l, 1
                ret                
