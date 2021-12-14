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

                PUBLIC  _MYX_PlayMusic
                PUBLIC  _MYX_StopMusic
                PUBLIC  _MYXP_UpdateMusicPlayer

                SECTION MYX_MUSIC

MusicBank:      db      0

_MYX_StopMusic: ld      a, (_MYXP_CurrentUpperBank)
                push    af
                ld      l, 3        ; BANK_3
                call    _MYXP_SetUpperMemoryBank
                ld      a, 0xc9     ; RET
                ld      (PT3_play), a
                call    PT3_mute
                pop     af
                ld      l, a
                jp      _MYXP_SetUpperMemoryBank

_MYX_PlayMusic: call    ___sdcc_enter_ix
                ; Stop the player
                call    _MYX_StopMusic
                ; Map proper memory banks
                ld      a, (_MYXP_CurrentUpperBank)
                push    af
                ld      a, (_MYXP_CurrentLowerBank)
                push    af
                ld      l, 3        ; BANK_3
                call    _MYXP_SetUpperMemoryBank
                ld      a, (ix+6)   ; A = bank
                ld      (MusicBank), a
                ld      l, a
                call    _MYXP_SetLowerMemoryBank
                ; Setup new music
                ld	    l, (ix+4)   ; HL = pointer
                ld	    h, (ix+5)
                ld      de, 0xc000-0x4000+100
                or      a
                sbc     hl, de
                call    PT3_init
                ; Enable playback
                xor     a           ; NOP
                ld      (PT3_play), a
                ; Restore memory banks
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
                ld      a, (MusicBank)
                ld      l, a
                call    _MYXP_SetLowerMemoryBank
                call    PT3_play
                pop     af
                ld      l, a
                call    _MYXP_SetLowerMemoryBank
                pop     af
                ld      l, a
                jp      _MYXP_SetUpperMemoryBank
