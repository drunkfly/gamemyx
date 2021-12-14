;
; Copyright (c) 2021 DrunkFly Team
; Licensed under 3-clause BSD license
;

                EXTERN  _MYXP_CurrentUpperBank
                EXTERN  _MYXP_CurrentLowerBank
                EXTERN  _MYXP_SetUpperMemoryBank
                EXTERN  _MYXP_SetLowerMemoryBank
                EXTERN  ___sdcc_enter_ix
                EXTERN  PT3_init
                EXTERN  PT3_play
                EXTERN  PT3_mute
                EXTERN  PT3_enabled

                PUBLIC  _MYX_PlayMusic
                PUBLIC  _MYX_StopMusic
                PUBLIC  _MYX_SetMusic
                PUBLIC  _MYXP_UpdateMusicPlayer

                SECTION MYX_MUSIC

MusicBank:      db      0, 0, 0
AYMask:         db      1, 2, 4

                ; H = enable/disable flag
                ; L = AY mask

_MYX_StopMusic: ld      h, 0
                jp      EnableDisable
_MYX_PlayMusic: ld      h, 1
EnableDisable:  ld      a, (_MYXP_CurrentUpperBank)
                push    af
                push    hl
                ld      l, 3        ; BANK_3
                call    _MYXP_SetUpperMemoryBank
                pop     hl
                di
                bit     0, l
                jr      z, SkipAY1
                ld      a, 3*2+1
                nextreg 0x57, a
                ld      a, h
                ld      (PT3_enabled), a
                or      a
                push    hl
                call    z, PT3_mute
                pop     hl
SkipAY1:        bit     1, l
                jr      z, SkipAY2
                ld      a, 3*2+2
                nextreg 0x57, a
                ld      a, h
                ld      (PT3_enabled), a
                or      a
                push    hl
                call    z, PT3_mute
                pop     hl
SkipAY2:        bit     2, l
                jr      z, SkipAY3
                ld      a, 3*2+3
                nextreg 0x57, a
                ld      a, h
                ld      (PT3_enabled), a
                or      a
                push    hl
                call    z, PT3_mute
                pop     hl
SkipAY3:        ei
                pop     af
                ld      l, a
                jp      _MYXP_SetUpperMemoryBank

_MYX_SetMusic:  call    ___sdcc_enter_ix
                ; Stop the player
                ld      e, (ix+4)   ; DE = AY chip
                ld      d, 0
                ld      hl, AYMask
                add     hl, de
                ld      l, (hl)
                call    _MYX_StopMusic
                ; Map proper memory banks
                ld      a, (_MYXP_CurrentUpperBank)
                push    af
                ld      a, (_MYXP_CurrentLowerBank)
                push    af
                ld      l, 3        ; BANK_3
                call    _MYXP_SetUpperMemoryBank
                ld      a, (ix+7)   ; A = bank
                ld      e, (ix+4)   ; DE = AY chip
                ld      d, 0
                ld      hl, MusicBank
                add     hl, de
                ld      (hl), a
                ld      l, a
                call    _MYXP_SetLowerMemoryBank
                di
                ld      a, (ix+4)   ; A = AY chip
                add     a, 3*2+1
                nextreg 0x57, a
                ; Setup new music
                ld	    l, (ix+5)   ; HL = pointer
                ld	    h, (ix+6)
                ld      de, 0xc000-0x4000+100
                or      a
                sbc     hl, de
                call    PT3_init
                ; Restore memory banks
                ei
                pop     af
                ld      l, a
                call    _MYXP_SetLowerMemoryBank
                pop     af
                ld      l, a
                call    _MYXP_SetUpperMemoryBank
	            pop     ix
                ret

_MYXP_UpdateMusicPlayer:
                ld      a, (_MYXP_CurrentUpperBank)
                push    af
                ld      a, (_MYXP_CurrentLowerBank)
                push    af
                ld      l, 3        ; BANK_3
                call    _MYXP_SetUpperMemoryBank

                ld      bc, 0xfffd
                ld      a, 0xff     ; chip 1
                out     (c), a
                ld      a, 3*2+1
                nextreg 0x57, a
                ld      a, (MusicBank+0)
                ld      l, a
                call    _MYXP_SetLowerMemoryBank
                call    PT3_play

                ld      bc, 0xfffd
                ld      a, 0xfe     ; chip 2
                out     (c), a
                ld      a, 3*2+2
                nextreg 0x57, a
                ld      a, (MusicBank+1)
                ld      l, a
                call    _MYXP_SetLowerMemoryBank
                call    PT3_play

                ld      bc, 0xfffd
                ld      a, 0xfd     ; chip 3
                out     (c), a
                ld      a, 3*2+3
                nextreg 0x57, a
                ld      a, (MusicBank+2)
                ld      l, a
                call    _MYXP_SetLowerMemoryBank
                call    PT3_play

                pop     af
                ld      l, a
                call    _MYXP_SetLowerMemoryBank
                pop     af
                ld      l, a
                jp      _MYXP_SetUpperMemoryBank
