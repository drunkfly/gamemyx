;
; Copyright (c) 2021 DrunkFly Team
; Licensed under 3-clause BSD license
;

                PUBLIC  _ReadInput
                PUBLIC  _IsKeyPressed
                PUBLIC  _IsGamepad1Pressed
                PUBLIC  _IsGamepad2Pressed
                PUBLIC  _RawKeys
                PUBLIC  _RawKempston

                SECTION engine_input

_RawKeys:       db      0, 0, 0, 0, 0, 0, 0, 0
_RawKempston:   db      0, 0

_ReadInput:     ; Read keyboard
                ld      bc, 0xfefe
                in      l, (c)          ; CAPS, Z, X, C, V
                ld      b, 0xfd
                in      h, (c)          ; A, S, D, F, G
                ld      (_RawKeys + 0), hl
                ld      b, 0xfb
                in      l, (c)          ; Q, W, E, R, T
                ld      b, 0xf7
                in      h, (c)          ; 1, 2, 3, 4, 5
                ld      (_RawKeys + 2), hl
                ld      bc, 0xeffe
                in      l, (c)          ; 0, 9, 8, 7, 6
                ld      b, 0xdf
                in      h, (c)          ; P, O, I, U, Y
                ld      (_RawKeys + 4), hl
                ld      b, 0xbf
                in      l, (c)          ; ENTER, L, K, J, H
                ld      b, 0x7f
                in      h, (c)          ; SPACE, SYM, M, N, B
                ld      (_RawKeys + 6), hl
                ; Read kempston
                ld      c, 0x1f         ; Kempston 1
                in      l, (c)
                ld      c, 0x37         ; Kempston 2
                in      h, (c)
                ld      (_RawKempston), hl
                ret

_IsKeyPressed:  ; Calculate offset into _RawKeys
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
                ld      hl, _RawKeys
                add     hl, bc
                and     (hl)
                ld      l, b                ; L = 0
                ret     nz                  ; not pressed
                inc     l
                ret

_IsGamepad1Pressed:
                ld      a, (_RawKempston)
CheckGamepadPress:
                and     l
                ld      l, 1
                ret     nz                  ; not pressed
                dec     l
                ret

_IsGamepad2Pressed:
                ld      a, (_RawKempston+1)
                jr      CheckGamepadPress
