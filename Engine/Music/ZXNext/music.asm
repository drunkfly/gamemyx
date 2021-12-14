;
; Copyright (c) 2021 DrunkFly Team
; Licensed under 3-clause BSD license
;

                EXTERN      _MYXP_CurrentUpperBank
                EXTERN      _MYXP_CurrentLowerBank
                EXTERN      _MYXP_SetUpperMemoryBank
                EXTERN      _MYXP_SetLowerMemoryBank
                EXTERN      ___sdcc_enter_ix

                PUBLIC      _MYXP_UpdateMusicPlayer
                PUBLIC      _MYX_PlayMusic
                PUBLIC      MusicPlayer_T1_
                PUBLIC      MusicPlayer_T_NEW_2
                PUBLIC      MusicPlayer_TCNEW_2
                PUBLIC      MusicPlayer_NT_
                PUBLIC      MusicPlayer_VT_

                SECTION     MYX_MUSIC

_CurrentMusic:  db          0xff
_MusicAddress:  dw          0
_MusicBank:     db          0

_MYXP_UpdateMusicPlayer:
                ld          a, (_MYXP_CurrentUpperBank)
                push        af

                ld          a, (_MYXP_CurrentLowerBank)
                push        af

                ld          l, 3        ; BANK_3
                call        _MYXP_SetUpperMemoryBank

                ld          a, (_MusicBank)
                ld          l, a
                call        _MYXP_SetLowerMemoryBank

                call        MusicPlayer_play

                pop         af
                ld          l, a
                call        _MYXP_SetLowerMemoryBank

                pop         af
                ld          l, a
                jp          _MYXP_SetUpperMemoryBank

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_MYX_PlayMusic: call	    ___sdcc_enter_ix

                ; Stop the player
                ld          a, 0xff
                ld          (_CurrentMusic), a
                halt

                ; Setup new music
                ;ld	        l, (ix+4)   ; HL = pointer
                ;ld	        h, (ix+5)
 EXTERN _music_ingame
 ld hl,_music_ingame
                ld          de, 0x8000;0xc000-0x4000
                or          a
                sbc         hl, de
                ;ld          a, (ix+6)   ; A = bank
 ld a,14
                ld          (_MusicAddress), hl
                ld          (_MusicBank), a

                ; Restart player
                xor         a
                ld          (_CurrentMusic), a

	            pop	ix
                ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                SECTION     BANK_3

                ; Vortex Tracker II v1.0 PT3 player for ZX Spectrum
                ; (c)2004,2007 S.V.Bulba <vorobey@mail.khstu.ru>
                ; http://bulba.untergrund.net (http://bulba.at.kz)
                ;
                ; Features
                ; --------
                ; * Can be compiled at any address (i.e. no need rounding ORG address).
                ; * Variables (VARS) can be located at any address (not only after code block).
                ; * INIT subroutine detects module version and rightly generates both note and
                ;   volume tables outside of code block (in VARS).
                ; * Two portamento (spc. command 3xxx) algorithms (depending of module version).
                ; * New 1.XX and 2.XX special command behaviour (only for PT v3.7 and higher).
                ; * Any Tempo value are accepted (including Tempo=1 and Tempo=2).
                ; * Fully compatible with Ay_Emul PT3 player codes.
                ;
                ; Limitations
                ; -----------
                ; * Can run in RAM only (self-modified code is used).
                ;
                ;;Warning!!! PLAY subroutine can crash if no module are loaded into RAM or INIT
                ; subroutine was not called before.
                ;
                ; Call MUTE or INIT one more time to mute sound after stopping playing.
                ;
                ; Notes
                ; -----
                ;
                ; Tests in IMMATION TESTER V1.0 by Andy Man/POS (thanks to Himik's ZxZ for help):
                ; Module/author     Min tacts   Max tacts   Average
                ; Spleen/Nik-O      1720        9256        5500
                ; Chuta/Miguel      1720        9496        5500
                ; Zhara/Macros      4536        8744        5500
                ;
                ; Pro Tracker 3.4r can not be detected by header, so PT3.4r tone tables really
                ; used only for modules of 3.3 and older versions.

MYXP_MusicPlayer:

MusicPlayer_CurESld = MusicPlayer_CurESld_ + 1
MusicPlayer_Ns_Base_AddToNs = MusicPlayer_Ns_Base_AddToNS_ + 1
MusicPlayer_Ns_Base = MusicPlayer_Ns_Base_AddToNs
MusicPlayer_AddToNs = MusicPlayer_Ns_Base_AddToNs + 1

                MusicPlayer_TonA      = 0
                MusicPlayer_TonB      = 2
                MusicPlayer_TonC      = 4
                MusicPlayer_Noise     = 6
                MusicPlayer_Mixer     = 7
                MusicPlayer_AmplA     = 8
                MusicPlayer_AmplB     = 9
                MusicPlayer_AmplC     = 10
                MusicPlayer_Env       = 11
                MusicPlayer_EnvTp     = 13

;@@flags:        db          0       ; set bit0 to 1, if you want to play without looping
                                    ; bit7 is set each time, when loop point is passed
;@@currentPos:   dw          0
MusicPlayer_currentPos = MusicPlayer_currentPos_ + 1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;@@checkLoop:    ld          hl, @@flags
                ;set         7, (hl)
                ;bit         0, (hl)
                ;ret         z
                ;pop         hl
                ;ld          hl, @@DelyCnt
                ;inc         (hl)
                ;ld          hl, @@ChanA + @@CHP_NtSkCn
                ;inc         (hl)
MusicPlayer_mute:         xor         a
                ld          h, a
                ld          l, a
                ld          (MusicPlayer_AYREGS + MusicPlayer_AmplA), a
                ld          (MusicPlayer_AYREGS + MusicPlayer_AmplB), hl
                jp          MusicPlayer_ROUT_A0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                ; HL - AddressOfModule
MusicPlayer_init:
                ld          hl, _music_ingame-0x8000;(_MusicAddress) ;MusicBuffer - 100
                or          a                   ; clear carry flag
                ld          de, 100
                sbc         hl, de
                ld          (MusicPlayer_MODADDR + 1), hl
                ld          (MusicPlayer_MDADDR2 + 1), hl
                push        hl
                add         hl, de
                ld          a, (hl)
                ld          (MusicPlayer_delay + 1), a
                push        hl
                pop         ix
                add         hl, de
                ld          (MusicPlayer_currentPos), hl
ld (_DEBUG_currentPos),hl
                ld          e, (ix+102-100)
                add         hl, de
                inc         hl
                ld          (MusicPlayer_LPosPtr + 1), hl
                pop         de
                ld          l, (ix+103-100)
                ld          h, (ix+104-100)
                add         hl, de
                ld          (MusicPlayer_PatsPtr + 1), hl
                ld          hl, 169
                add         hl, de
                ld          (MusicPlayer_OrnPtrs + 1), hl
                ld          hl, 105
                add         hl, de
                ld          (MusicPlayer_SamPtrs + 1), hl
                ;ld          hl, @@flags
                ;res         7, (hl)
                ;note table data depacker
;                ld          de, @@packedNoteTable
;                ld          bc, @@T1_ + (2 * 49) - 1
;@@TP_0:         ld          a, (de)
;                inc         de
;                cp          15*2
;                jr          nc, @@TP_1
;                ld          h, a
;                ld          a, (de)
;                ld          l, a
;                inc         de
;                jr          @@TP_2
;@@TP_1:         push        de
;                ld          d, 0
;                ld          e, a
;                add         hl, de
;                add         hl, de
;                pop         de
;@@TP_2:         ld          a, h
;                ld          (bc), a
;                dec         bc
;                ld          a, l
;                ld          (bc), a
;                dec         bc
;                sub         0xff & (0xf8 * 2)
;                jr          nz, @@TP_0
              xor a
                ;
                ld          hl, MusicPlayer_VARS
                ld          (hl), a
                ld          de, MusicPlayer_VARS + 1
                ld          bc, MusicPlayer_VAR0END - MusicPlayer_VARS - 1
                ldir
                inc         a
                ld          (MusicPlayer_DelyCnt), a
                ld          hl, 0xf001                      ; H - CHP.Volume, L - CHP.NtSkCn
                ld          (MusicPlayer_ChanA + MusicPlayer_CHP_NtSkCn), hl
                ld          (MusicPlayer_ChanB + MusicPlayer_CHP_NtSkCn), hl
                ld          (MusicPlayer_ChanC + MusicPlayer_CHP_NtSkCn), hl
                ;
                ld          hl, MusicPlayer_EMPTYSAMORN
                ld          (MusicPlayer_AdInPtA + 1), hl             ; ptr to zero
                ld          (MusicPlayer_ChanA + MusicPlayer_CHP_OrnPtr), hl    ; ornament 0 is "0,1,0"
                ld          (MusicPlayer_ChanB + MusicPlayer_CHP_OrnPtr), hl    ; in all versions from
                ld          (MusicPlayer_ChanC + MusicPlayer_CHP_OrnPtr), hl    ; 3.xx to 3.6x and VTII
                ;
                ld          (MusicPlayer_ChanA + MusicPlayer_CHP_SamPtr), hl    ; S1 There is no default
                ld          (MusicPlayer_ChanB + MusicPlayer_CHP_SamPtr), hl    ; S2 sample in PT3, so, you
                ld          (MusicPlayer_ChanC + MusicPlayer_CHP_SamPtr), hl    ; S3 can comment S1,2,3; see
                                                            ; also EMPTYSAMORN comment
                ;ld          a, (ix + 13 - 100)              ; EXTRACT VERSION NUMBER
                ;sub         0x30
                ;jr          c, @@L20
                ;cp          10
                ;jr          c, @@L21
;@@L20:          ld          a, 6
;@@L21:          ld          (@@Version + 1), a
                ;push        af
                ;cp          4
                ;ld          a, (ix + 99 - 100)              ; TONE TABLE NUMBER
                ;rla
                ;and         7
                ; NoteTableCreator (c) Ivan Roshin
                ; A - NoteTableNumber * 2 + VersionForNoteTable
                ; (xx1b - 3.xx..3.4r, xx0b - 3.4x..3.6x..VTII1.0)
                ;ld          hl, @@NT_DATA
                ;push        de
                ;ld          d, b
                ;add         a, a
                ;ld          e, a
                ;add         hl, de
                ;ld          e, (hl)
                ;inc         hl
                ;srl         e
                ;sbc         a, a
                ;and         0xa7                            ; #00 (NOP) or #A7 (AND A)
                ;ld          (@@L3), a
                ;ex          de, hl
                ;pop         bc                              ; BC=T1_
                ;add         hl, bc
                ;
                ;ld          a, (de)
                ;add         a, @@T_ & 0xff
                ;ld          c, a
                ;adc         a, @@T_ / 256
                ;sub         c
                ;ld          b, a
;                push        bc
;                ld          de, @@NT_
;                push        de
;                ;
;                ld          b, 12
;@@L1:           push        bc
;                ld          c, (hl)
;                inc         hl
;                push        hl
;                ld          b, (hl)
;                ;
;                push        de
;                ex          de, hl
;                ld          de, 23
;                ld          ixh, 8
;                ;
;@@L2:           srl         b
;                rr          c
;;@@L3:           db          0x19                            ; AND A or NOP
;                ld          a, c
;                adc         a, d                            ; = ADC 0
;                ld          (hl), a
;                inc         hl
;                ld          a, b
;                adc         a, d
;                ld          (hl), a
;                add         hl, de
;                dec         ixh
;                jr          nz, @@L2
;                ;
;                pop         de
;                inc         de
;                inc         de
;                pop         hl
;                inc         hl
;                pop         bc
;                djnz        @@L1
;                ;
;                pop         hl
;                pop         de
;                ;
                ;ld          a, e
                ;cp          @@TCOLD_1 & 0xff
                ;jr          nz, @@CORR_1
                ;ld          a, 0xfd
                ;ld          (@@NT_ + 0x2e), a
                ;
;@@CORR_1:       ld          a, (de)
;                and         a
;                jr          z, @@TC_EXIT
;                rra
;                push        af
;                add         a, a
;                ld          c, a
;                add         hl, bc
;                pop         af
;                jr          nc, @@CORR_2
;                dec         (hl)
;                dec         (hl)
;@@CORR_2:       inc         (hl)
;                and         a
;                sbc         hl, bc
;                inc         de
;                jr          @@CORR_1
;@@TC_EXIT:      ;pop         af                              ; pop version number
                ; VolTableCreator (c) Ivan Roshin
                ; A - VersionForVolumeTable (0..4 - 3.xx..3.4x;
                ; 5.. - 3.5x..3.6x..VTII1.0)
;                ;cp          5
;                ld          hl, 0x11
;                ld          d, h
;                ld          e, h
;                ;ld          a, 0x17
;                ;jr          nc, @@M1
;                ;dec         l
;                ;ld          e, l
;                ;xor         a
;;@@M1:           ld          (@@M2), a
;                ;
;                ld          ix, @@VT_ + 16
;                ld          c, 0x10
;                ;
;@@INITV2:       push        hl
;                ;
;                add         hl, de
;                ex          de, hl
;                sbc         hl, hl
;                ;
;@@INITV1:       ld          a, l
;@@M2:           db          0x17 ;0x7d
;                ld          a, h
;                adc         a, 0
;                ld          (ix), a
;                inc         ix
;                add         hl, de
;                inc         c
;                ld          a, c
;                and         15
;                jr          nz, @@INITV1
;                ;
;                pop         hl
;                ld          a, e
;                cp          0x77
;                jr          nz, @@M3
;                inc         e
;@@M3:           ld          a, c
;                and         a
;                jr          nz, @@INITV2
                jp          MusicPlayer_ROUT_A0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                ; pattern decoder

MusicPlayer_PD_OrSm:      ld          (ix + MusicPlayer_CHP_Env_En - 12), 0
                call        MusicPlayer_SETORN
                ld          a, (bc)
                inc         bc
                rrca
                ;
MusicPlayer_PD_SAM:       add         a, a
MusicPlayer_PD_SAM_:      ld          e, a
                ld          d, 0
MusicPlayer_SamPtrs:      ld          hl, 0x2121
                add         hl, de
                ld          e, (hl)
                inc         hl
                ld          d, (hl)
MusicPlayer_MODADDR:      ld          hl, 0x2121
                add         hl, de
                ld          (ix + MusicPlayer_CHP_SamPtr - 12), l
                ld          (ix + MusicPlayer_CHP_SamPtr + 1 - 12), h
                jr          MusicPlayer_PD_LOOP
                ;
MusicPlayer_PD_VOL:       rlca
                rlca
                rlca
                rlca
                ld          (ix + MusicPlayer_CHP_Volume - 12), a
                jr          MusicPlayer_PD_LP2
                ;
MusicPlayer_PD_EOff:      ld          (ix + MusicPlayer_CHP_Env_En - 12), a
                ld          (ix + MusicPlayer_CHP_PsInOr - 12), a
                jr          MusicPlayer_PD_LP2
                ;
MusicPlayer_PD_SorE:      dec         a
                jr          nz, MusicPlayer_PD_ENV
                ld          a, (bc)
                inc         bc
                ld          (ix + MusicPlayer_CHP_NNtSkp - 12), a
                jr          MusicPlayer_PD_LP2
                ;
MusicPlayer_PD_ENV:       call        MusicPlayer_SETENV
                jr          MusicPlayer_PD_LP2
                ;
MusicPlayer_PD_ORN:       call        MusicPlayer_SETORN
                jr          MusicPlayer_PD_LOOP
                ;
MusicPlayer_PD_ESAM:      ld          (ix + MusicPlayer_CHP_Env_En - 12), a
                ld          (ix + MusicPlayer_CHP_PsInOr - 12), a
                call        nz, MusicPlayer_SETENV
                ld          a, (bc)
                inc         bc
                jr          MusicPlayer_PD_SAM_
                ;
MusicPlayer_PTDECOD:      ld          a, (ix + MusicPlayer_CHP_Note - 12)
                ld          (MusicPlayer_PrNote + 1), a
                ld          l, (ix + MusicPlayer_CHP_CrTnSl - 12)
                ld          h, (ix + MusicPlayer_CHP_CrTnSl - 12 + 1)
                ld          (MusicPlayer_PrSlide + 1), hl
                ;
MusicPlayer_PD_LOOP:      ld          de, 0x2010
MusicPlayer_PD_LP2:       ld          a, (bc)
                inc         bc
                add         a, e
                jr          c, MusicPlayer_PD_OrSm
                add         a, d
                jr          z, MusicPlayer_PD_FIN
                jr          c, MusicPlayer_PD_SAM
                add         a, e
                jr          z, MusicPlayer_PD_REL
                jr          c, MusicPlayer_PD_VOL
                add         a, e
                jr          z, MusicPlayer_PD_EOff
                jr          c, MusicPlayer_PD_SorE
                add         a, 96
                jr          c, MusicPlayer_PD_NOTE
                add         a, e
                jr          c, MusicPlayer_PD_ORN
                add         a, d
                jr          c, MusicPlayer_PD_NOIS
                add         a, e
                jr          c, MusicPlayer_PD_ESAM
                add         a, a
                ld          e, a
                ld          hl, 0xffff & (MusicPlayer_SPCCOMS + 0xFF20 - 0x2000)
                add         hl, de
                ld          e, (hl)
                inc         hl
                ld          d, (hl)
                push        de
                jr          MusicPlayer_PD_LOOP
                ;
MusicPlayer_PD_NOIS:      ld          (MusicPlayer_Ns_Base), a
                jr          MusicPlayer_PD_LP2
                ;
MusicPlayer_PD_REL:       res         0, (ix + MusicPlayer_CHP_Flags - 12)
                jr          MusicPlayer_PD_RES
                ;
MusicPlayer_PD_NOTE:      ld          (ix + MusicPlayer_CHP_Note - 12), a
                set         0, (ix + MusicPlayer_CHP_Flags - 12)
                xor         a
                ;
MusicPlayer_PD_RES:       ld          (MusicPlayer_PDSP_+1), sp
                ld          sp, ix
                ld          h, a
                ld          l, a
                push        hl
                push        hl
                push        hl
                push        hl
                push        hl
                push        hl
MusicPlayer_PDSP_:        ld          sp, 0x3131
                ;
MusicPlayer_PD_FIN:       ld          a, (ix + MusicPlayer_CHP_NNtSkp - 12)
                ld          (ix + MusicPlayer_CHP_NtSkCn - 12), a
                ret
                ;
MusicPlayer_C_PORTM:      res         2, (ix + MusicPlayer_CHP_Flags - 12)
                ld          a, (bc)
                inc         bc
                ; SKIP PRECALCULATED TONE DELTA (BECAUSE CANNOT BE RIGHT AFTER PT3 COMPILATION)
                inc         bc
                inc         bc
                ld          (ix + MusicPlayer_CHP_TnSlDl - 12), a
                ld          (ix + MusicPlayer_CHP_TSlCnt - 12), a
                ld          de, MusicPlayer_NT_
                ld          a, (ix + MusicPlayer_CHP_Note - 12)
                ld          (ix + MusicPlayer_CHP_SlToNt - 12), a
                add         a, a
                ld          l, a
                ld          h, 0
                add         hl, de
                ld          a, (hl)
                inc         hl
                ld          h, (hl)
                ld          l, a
                push        hl
MusicPlayer_PrNote:       ld          a, 0x3e
                ld          (ix + MusicPlayer_CHP_Note - 12), a
                add         a, a
                ld          l, a
                ld          h, 0
                add         hl, de
                ld          e, (hl)
                inc         hl
                ld          d, (hl)
                pop         hl
                sbc         hl, de
                ld          (ix + MusicPlayer_CHP_TnDelt - 12), l
                ld          (ix + MusicPlayer_CHP_TnDelt - 12 + 1), h
                ld          e, (ix + MusicPlayer_CHP_CrTnSl - 12)
                ld          d, (ix + MusicPlayer_CHP_CrTnSl - 12 + 1)
;@@Version:      ld          a, 0x3e
;                cp          6
;                jr          c, @@OLDPRTM                    ; Old 3xxx for PT v3.5-
MusicPlayer_PrSlide:      ld          de, 0x1111
                ld          (ix + MusicPlayer_CHP_CrTnSl - 12), e
                ld          (ix + MusicPlayer_CHP_CrTnSl - 12 + 1), d
MusicPlayer_OLDPRTM:      ld          a, (bc)                         ; SIGNED TONE STEP
                inc         bc
                ex          af, af'
                ld          a, (bc)
                inc         bc
                and         a
                jr          z, MusicPlayer_NOSIG
                ex          de, hl
MusicPlayer_NOSIG:        sbc         hl, de
                jp          p, MusicPlayer_SET_STP
                cpl
                ex          af, af'
                neg
                ex          af, af'
MusicPlayer_SET_STP:      ld          (ix + MusicPlayer_CHP_TSlStp - 12 + 1), a
                ex          af, af'
                ld          (ix + MusicPlayer_CHP_TSlStp - 12), a
                ld          (ix + MusicPlayer_CHP_COnOff - 12), 0
                ret

MusicPlayer_C_GLISS:      set         2, (ix + MusicPlayer_CHP_Flags - 12)
                ld          a, (bc)
                inc         bc
                ld          (ix + MusicPlayer_CHP_TnSlDl - 12), a
                and         a
                jr          nz, MusicPlayer_GL36
                ;ld          a, (@@Version + 1)              ; AlCo PT3.7+
                ;cp          7
                ;sbc         a, a
                inc         a
MusicPlayer_GL36:         ld          (ix + MusicPlayer_CHP_TSlCnt - 12), a
                ld          a, (bc)
                inc         bc
                ex          af, af'
                ld          a, (bc)
                inc         bc
                jr          MusicPlayer_SET_STP

MusicPlayer_C_SMPOS:      ld          a, (bc)
                inc         bc
                ld          (ix + MusicPlayer_CHP_PsInSm - 12), a
                ret

MusicPlayer_C_ORPOS:      ld          a, (bc)
                inc         bc
                ld          (ix + MusicPlayer_CHP_PsInOr - 12), a
                ret

MusicPlayer_C_VIBRT:      ld          a, (bc)
                inc         bc
                ld          (ix + MusicPlayer_CHP_OnOffD - 12), a
                ld          (ix + MusicPlayer_CHP_COnOff - 12), a
                ld          a, (bc)
                inc         bc
                ld          (ix + MusicPlayer_CHP_OffOnD - 12), a
                xor         a
                ld          (ix + MusicPlayer_CHP_TSlCnt - 12), a
                ld          (ix + MusicPlayer_CHP_CrTnSl - 12), a
                ld          (ix + MusicPlayer_CHP_CrTnSl - 12 + 1), a
                ret

MusicPlayer_C_ENGLS:      ld          a, (bc)
                inc         bc
                ld          (MusicPlayer_Env_Del + 1), a
                ld          (MusicPlayer_CurEDel), a
                ld          a, (bc)
                inc         bc
                ld          l, a
                ld          a, (bc)
                inc         bc
                ld          h, a
                ld          (MusicPlayer_ESldAdd + 1), hl
                ret

MusicPlayer_C_DELAY:      ld          a, (bc)
                inc         bc
                ld          (MusicPlayer_delay + 1), a
                ret

MusicPlayer_SETENV:       ld          (ix + MusicPlayer_CHP_Env_En - 12), e
                ld          (MusicPlayer_AYREGS + MusicPlayer_EnvTp), a
                ld          a, (bc)
                inc         bc
                ld          h, a
                ld          a, (bc)
                inc         bc
                ld          l, a
                ld          (MusicPlayer_EnvBase), hl
                xor         a
                ld          (ix + MusicPlayer_CHP_PsInOr - 12), a
                ld          (MusicPlayer_CurEDel), a
                ld          h, a
                ld          l, a
                ld          (MusicPlayer_CurESld), hl
MusicPlayer_C_NOP:        ret

MusicPlayer_SETORN:       add         a, a
                ld          e, a
                ld          d, 0
                ld          (ix + MusicPlayer_CHP_PsInOr - 12), d
MusicPlayer_OrnPtrs:      ld          hl, 0x2121
                add         hl, de
                ld          e, (hl)
                inc         hl
                ld          d, (hl)
MusicPlayer_MDADDR2:      ld          hl, 0x2121
                add         hl, de
                ld          (ix + MusicPlayer_CHP_OrnPtr - 12), l
                ld          (ix + MusicPlayer_CHP_OrnPtr - 12 + 1), h
                ret

                ; ALL 16 ADDRESSES TO PROTECT FROM BROKEN PT3 MODULES
MusicPlayer_SPCCOMS:      dw          MusicPlayer_C_NOP
                dw          MusicPlayer_C_GLISS
                dw          MusicPlayer_C_PORTM
                dw          MusicPlayer_C_SMPOS
                dw          MusicPlayer_C_ORPOS
                dw          MusicPlayer_C_VIBRT
                dw          MusicPlayer_C_NOP
                dw          MusicPlayer_C_NOP
                dw          MusicPlayer_C_ENGLS
                dw          MusicPlayer_C_DELAY
                ;dw          @@C_NOP
                ;dw          @@C_NOP
                ;dw          @@C_NOP
                ;dw          @@C_NOP
                ;dw          @@C_NOP
                ;dw          @@C_NOP

MusicPlayer_CHREGS:       xor         a
                ld          (MusicPlayer_Ampl), a
                bit         0, (ix + MusicPlayer_CHP_Flags)
                push        hl
                jp          z, MusicPlayer_CH_EXIT
                ld          (MusicPlayer_CSP_ + 1), sp
                ld          l, (ix + MusicPlayer_CHP_OrnPtr)
                ld          h, (ix + MusicPlayer_CHP_OrnPtr + 1)
                ld          sp, hl
                pop         de
                ld          h, a
                ld          a, (ix + MusicPlayer_CHP_PsInOr)
                ld          l, a
                add         hl, sp
                inc         a
                cp          d
                jr          c, MusicPlayer_CH_ORPS
                ld          a, e
MusicPlayer_CH_ORPS:      ld          (ix + MusicPlayer_CHP_PsInOr), a
                ld          a, (ix + MusicPlayer_CHP_Note)
                add         a,(hl)
                jp          p, MusicPlayer_CH_NTP
                xor         a
MusicPlayer_CH_NTP:       cp          96
                jr          c, MusicPlayer_CH_NOK
                ld          a, 95
MusicPlayer_CH_NOK:       add         a, a
                ex          af, af'
                ld          l, (ix + MusicPlayer_CHP_SamPtr)
                ld          h, (ix + MusicPlayer_CHP_SamPtr + 1)
                ld          sp, hl
                pop         de
                ld          h, 0
                ld          a, (ix + MusicPlayer_CHP_PsInSm)
                ld          b, a
                add         a, a
                add         a, a
                ld          l, a
                add         hl, sp
                ld          sp, hl
                ld          a, b
                inc         a
                cp          d
                jr          c, MusicPlayer_CH_SMPS
                ld          a, e
MusicPlayer_CH_SMPS:      ld          (ix + MusicPlayer_CHP_PsInSm), a
                pop         bc
                pop         hl
                ld          e, (ix + MusicPlayer_CHP_TnAcc)
                ld          d, (ix + MusicPlayer_CHP_TnAcc + 1)
                add         hl, de
                bit         6, b
                jr          z, MusicPlayer_CH_NOAC
                ld          (ix + MusicPlayer_CHP_TnAcc), l
                ld          (ix + MusicPlayer_CHP_TnAcc + 1), h
MusicPlayer_CH_NOAC:      ex          de, hl
                ex          af, af'
                ld          l, a
                ld          h, 0
                ld          sp, MusicPlayer_NT_
                add         hl, sp
                ld          sp, hl
                pop         hl
                add         hl, de
                ld          e, (ix + MusicPlayer_CHP_CrTnSl)
                ld          d, (ix + MusicPlayer_CHP_CrTnSl + 1)
                add         hl, de
MusicPlayer_CSP_:         ld          sp, 0x3131
                ex          (sp), hl
                xor         a
                or          (ix + MusicPlayer_CHP_TSlCnt)
                jr          z, MusicPlayer_CH_AMP
                dec         (ix + MusicPlayer_CHP_TSlCnt)
                jr          nz, MusicPlayer_CH_AMP
                ld          a, (ix + MusicPlayer_CHP_TnSlDl)
                ld          (ix + MusicPlayer_CHP_TSlCnt), a
                ld          l, (ix + MusicPlayer_CHP_TSlStp)
                ld          h, (ix + MusicPlayer_CHP_TSlStp + 1)
                ld          a, h
                add         hl, de
                ld          (ix + MusicPlayer_CHP_CrTnSl), l
                ld          (ix + MusicPlayer_CHP_CrTnSl + 1), h
                bit         2, (ix + MusicPlayer_CHP_Flags)
                jr          nz, MusicPlayer_CH_AMP
                ld          e, (ix + MusicPlayer_CHP_TnDelt)
                ld          d, (ix + MusicPlayer_CHP_TnDelt + 1)
                and         a
                jr          z, MusicPlayer_CH_STPP
                ex          de, hl
MusicPlayer_CH_STPP:      sbc         hl, de
                jp          m, MusicPlayer_CH_AMP
                ld          a, (ix + MusicPlayer_CHP_SlToNt)
                ld          (ix + MusicPlayer_CHP_Note), a
                xor         a
                ld          (ix + MusicPlayer_CHP_TSlCnt), a
                ld          (ix + MusicPlayer_CHP_CrTnSl), a
                ld          (ix + MusicPlayer_CHP_CrTnSl + 1), a
MusicPlayer_CH_AMP:       ld          a, (ix + MusicPlayer_CHP_CrAmSl)
                bit         7, c
                jr          z, MusicPlayer_CH_NOAM
                bit         6, c
                jr          z, MusicPlayer_CH_AMIN
                cp          15
                jr          z, MusicPlayer_CH_NOAM
                inc         a
                jr          MusicPlayer_CH_SVAM
MusicPlayer_CH_AMIN:      cp          -15
                jr          z, MusicPlayer_CH_NOAM
                dec         a
MusicPlayer_CH_SVAM:      ld          (ix + MusicPlayer_CHP_CrAmSl), a
MusicPlayer_CH_NOAM:      ld          l, a
                ld          a, b
                and         15
                add         a, l
                jp          p, MusicPlayer_CH_APOS
                xor         a
MusicPlayer_CH_APOS:      cp          16
                jr          c, MusicPlayer_CH_VOL
                ld          a, 15
MusicPlayer_CH_VOL:       or          (ix + MusicPlayer_CHP_Volume)
                ld          l, a
                ld          h, 0
                ld          de, MusicPlayer_VT_
                add         hl, de
                ld          a, (hl)
MusicPlayer_CH_ENV:       bit         0, c
                jr          nz, MusicPlayer_CH_NOEN
                or          (ix + MusicPlayer_CHP_Env_En)
MusicPlayer_CH_NOEN:      ld          (MusicPlayer_Ampl), a
                bit         7, b
                ld          a, c
                jr          z, MusicPlayer_NO_ENSL
                rla
                rla
                sra         a
                sra         a
                sra         a
                add         a, (ix + MusicPlayer_CHP_CrEnSl)          ; SEE COMMENT BELOW
                bit         5, b
                jr          z, MusicPlayer_NO_ENAC
                ld          (ix + MusicPlayer_CHP_CrEnSl), a
MusicPlayer_NO_ENAC:      ld          hl, MusicPlayer_AddToEn + 1
                add         a, (hl)                         ; BUG IN PT3 - NEED WORD HERE.
                                                            ; FIX IT IN NEXT VERSION?
                ld          (hl), a
                jr          MusicPlayer_CH_MIX
MusicPlayer_NO_ENSL:      rra
                add         a, (ix + MusicPlayer_CHP_CrNsSl)
                ld          (MusicPlayer_AddToNs), a
                bit         5, b
                jr          z, MusicPlayer_CH_MIX
                ld          (ix + MusicPlayer_CHP_CrNsSl), a
MusicPlayer_CH_MIX:       ld          a, b
                rra
                and         0x48
MusicPlayer_CH_EXIT:      ld          hl, MusicPlayer_AYREGS + MusicPlayer_Mixer
                or          (hl)
                rrca
                ld          (hl), a
                pop         hl
                xor         a
                or          (ix + MusicPlayer_CHP_COnOff)
                ret         z
                dec         (ix + MusicPlayer_CHP_COnOff)
                ret         nz
                xor         (ix + MusicPlayer_CHP_Flags)
                ld          (ix + MusicPlayer_CHP_Flags), a
                rra
                ld          a, (ix + MusicPlayer_CHP_OnOffD)
                jr          c, MusicPlayer_CH_ONDL
                ld          a, (ix + MusicPlayer_CHP_OffOnD)
MusicPlayer_CH_ONDL:      ld          (ix + MusicPlayer_CHP_COnOff), a
                ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

MusicPlayer_play:         ld          a, (_CurrentMusic)
MusicPlayer_currentMusic: cp          0xff
                jr          z, MusicPlayer_doPlay
                ld          (MusicPlayer_currentMusic + 1), a
                cp          0xff
                jr          z, MusicPlayer_doPlay
                ;ld          hl, MusicTracks
                ;ld          e, a
                ;ld          d, 0
                ;add         hl, de
                ;ld          a, (hl)
                ;inc         hl
                ;ld          h, (hl)
                ;ld          l, a
                push        af
                call        MusicPlayer_init
                pop         af
MusicPlayer_doPlay:       cp          0xff
                jp          z, MusicPlayer_mute
                xor         a
                ld          (MusicPlayer_AddToEn + 1), a
                ld          (MusicPlayer_AYREGS + MusicPlayer_Mixer), a
                dec         a
                ld          (MusicPlayer_AYREGS + MusicPlayer_EnvTp), a
                ld          hl, MusicPlayer_DelyCnt
                dec         (hl)
                jr          nz, MusicPlayer_PL2
                ld          hl, MusicPlayer_ChanA + MusicPlayer_CHP_NtSkCn
                dec         (hl)
                jr          nz, MusicPlayer_PL1B
MusicPlayer_AdInPtA:      ld          bc, 0x0101
                ld          a, (bc)
                and         a
                jr          nz, MusicPlayer_PL1A
                ld          d, a
                ld          (MusicPlayer_Ns_Base), a
MusicPlayer_currentPos_:  ld          hl, 0xcafe
                inc         hl
                ld          a, (hl)
                inc         a
                jr          nz, MusicPlayer_PLNLP
                ;call        MusicPlayer_checkLoop
MusicPlayer_LPosPtr:      ld          hl, 0x2121
                ld          a, (hl)
                inc         a
MusicPlayer_PLNLP:        ld          (MusicPlayer_currentPos), hl
                dec         a
                add         a, a
                ld          e, a
                rl          d
MusicPlayer_PatsPtr:      ld          hl, 0x2121
                add         hl, de
                ld          de, (MusicPlayer_MODADDR + 1)
                ld          (MusicPlayer_PSP_ + 1), sp
                ld          sp, hl
                pop         hl
                add         hl, de
                ld          b, h
                ld          c, l
                pop         hl
                add         hl, de
                ld          (MusicPlayer_AdInPtB + 1), hl
                pop         hl
                add         hl, de
                ld          (MusicPlayer_AdInPtC + 1), hl
MusicPlayer_PSP_:         ld          sp, 0x3131
MusicPlayer_PL1A:         ld          ix, MusicPlayer_ChanA + 12
                call        MusicPlayer_PTDECOD
                ld          (MusicPlayer_AdInPtA + 1), bc
                ;
MusicPlayer_PL1B:         ld          hl, MusicPlayer_ChanB + MusicPlayer_CHP_NtSkCn
                dec         (hl)
                jr          nz, MusicPlayer_PL1C
                ld          ix, MusicPlayer_ChanB + 12
MusicPlayer_AdInPtB:      ld          bc, 0x0101
                call        MusicPlayer_PTDECOD
                ld          (MusicPlayer_AdInPtB + 1),bc
                ;
MusicPlayer_PL1C:         ld          hl, MusicPlayer_ChanC + MusicPlayer_CHP_NtSkCn
                dec         (hl)
                jr          nz, MusicPlayer_delay
                ld          ix, MusicPlayer_ChanC + 12
MusicPlayer_AdInPtC:      ld          bc, 0x0101
                call        MusicPlayer_PTDECOD
                ld          (MusicPlayer_AdInPtC + 1), bc
                ;
MusicPlayer_delay:        ld          a, 0x3e
                ld          (MusicPlayer_DelyCnt), a
                ;
MusicPlayer_PL2:          ld          ix, MusicPlayer_ChanA
                ld          hl, (MusicPlayer_AYREGS + MusicPlayer_TonA)
                call        MusicPlayer_CHREGS
                ld          (MusicPlayer_AYREGS + MusicPlayer_TonA), hl
                ld          a, (MusicPlayer_Ampl)
                ld          (MusicPlayer_AYREGS + MusicPlayer_AmplA), a
                ld          ix ,MusicPlayer_ChanB
                ld          hl, (MusicPlayer_AYREGS + MusicPlayer_TonB)
                call        MusicPlayer_CHREGS
                ld          (MusicPlayer_AYREGS + MusicPlayer_TonB), hl
                ld          a, (MusicPlayer_Ampl)
                ld          (MusicPlayer_AYREGS + MusicPlayer_AmplB), a
                ld          ix, MusicPlayer_ChanC
                ld          hl, (MusicPlayer_AYREGS + MusicPlayer_TonC)
                call        MusicPlayer_CHREGS
                ;ld         a, (Ampl)                       ; Ampl = AYREGS+AmplC
                ;ld         (AYREGS + AmplC), a
                ld          (MusicPlayer_AYREGS + MusicPlayer_TonC), hl
                ;
MusicPlayer_Ns_Base_AddToNS_:
                ld          hl, 0xc0de
                ld          a, h
                add         a, l
                ld          (MusicPlayer_AYREGS + MusicPlayer_Noise), a
MusicPlayer_AddToEn:      ld          a, 0x3e
                ld          e, a
                add         a, a
                sbc         a, a
                ld          d, a
                ld          hl, (MusicPlayer_EnvBase)
                add         hl, de
MusicPlayer_CurESld_:     ld          de, 0xbabe
                add         hl, de
                ld          (MusicPlayer_AYREGS + MusicPlayer_Env), hl
                ;
                xor         a
                ld          hl, MusicPlayer_CurEDel
                or          (hl)
                jr          z, MusicPlayer_ROUT_A0
                dec         (hl)
                jr          nz, MusicPlayer_ROUT
MusicPlayer_Env_Del:      ld          a, 0x3e
                ld          (hl), a
MusicPlayer_ESldAdd:      ld          hl, 0x2121
                add         hl, de
                ld          (MusicPlayer_CurESld), hl
MusicPlayer_ROUT:         xor         a
MusicPlayer_ROUT_A0:      ld          de, 0xffbf
                ld          bc, 0xfffd
                ld          hl, MusicPlayer_AYREGS
MusicPlayer_LOUT:         out         (c), a
                ld          b, e
             push af
             ld a,(hl)
             out (c), a
             inc hl
             dec b
             pop af
                ;outi
                ld          b, d
                inc         a
                cp          13
                jr          nz, MusicPlayer_LOUT
                out         (c), a
                ld          a, (hl)
                and         a
                ret         m
                ld          b, e
                out         (c), a
                ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;@@NT_DATA       db          (@@T_NEW_0 - @@T1_) * 2
                ;db          (@@TCNEW_0 - @@T_)
                ;db          (@@T_OLD_0 - @@T1_) * 2 + 1
                ;db          (@@TCOLD_0 - @@T_)
                ;db          (@@T_NEW_1 - @@T1_) * 2 + 1
                ;db          (@@TCNEW_1 - @@T_)
                ;db          (@@T_OLD_1 - @@T1_) * 2 + 1
                ;db          (@@TCOLD_1 - @@T_)
                ;db          (@@T_NEW_2 - @@T1_) * 2
                ;db          (@@TCNEW_2 - @@T_)
                ;db          (@@T_OLD_2 - @@T1_) * 2
                ;db          (@@TCOLD_2 - @@T_)
                ;db          (@@T_NEW_3 - @@T1_) * 2
                ;db          (@@TCNEW_3 - @@T_)
                ;db          (@@T_OLD_3 - @@T1_) * 2
                ;db          (@@TCOLD_3 - @@T_)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

MusicPlayer_T_:
;@@TCOLD_0       db          0x00+1, 0x04+1, 0x08+1, 0x0A+1, 0x0C+1, 0x0E+1, 0x12+1, 0x14+1, 0x18+1, 0x24+1, 0x3C+1, 0
;@@TCOLD_1       db          0x5C+1, 0
;@@TCOLD_2       db          0x30+1, 0x36+1, 0x4C+1, 0x52+1, 0x5E+1, 0x70+1
;                db          0x82, 0x8C, 0x9C, 0x9E, 0xA0, 0xA6, 0xA8, 0xAA, 0xAC, 0xAE, 0xAE, 0
;@@TCNEW_3       db          0x56+1
;@@TCOLD_3       db          0x1E+1, 0x22+1, 0x24+1, 0x28+1, 0x2C+1, 0x2E+1, 0x32+1, 0xBE+1, 0
;@@TCNEW_0       db          0x1C+1, 0x20+1, 0x22+1, 0x26+1, 0x2A+1, 0x2C+1, 0x30+1, 0x54+1, 0xBC+1, 0xBE+1,0
;@@TCNEW_1       = @@TCOLD_1
MusicPlayer_TCNEW_2:      db          0x1A+1, 0x20+1, 0x24+1, 0x28+1, 0x2A+1, 0x3A+1, 0x4C+1, 0x5E+1, 0xBA+1, 0xBC+1, 0xBE+1, 0

MusicPlayer_EMPTYSAMORN   = MusicPlayer_EMPTYSAMORN_1 - 1
MusicPlayer_EMPTYSAMORN_1:db          1, 0, 0x90                      ; delete #90 if you don't need default sample

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                SECTION     MYX_MUSIC

PUBLIC _DEBUG_currentPos
_DEBUG_currentPos: dw 0

                SECTION     BANK_3

                ; vars from here can be stripped
                ; you can move VARS to any other address

PUBLIC _MusicPlayer_VARS
_MusicPlayer_VARS:

MusicPlayer_VARS:

                ; ChannelsVars
                ;   STRUCT CHP
                ; reset group
MusicPlayer_CHP_PsInOr    = 0     ; db 0
MusicPlayer_CHP_PsInSm    = 1     ; db 0
MusicPlayer_CHP_CrAmSl    = 2     ; db 0
MusicPlayer_CHP_CrNsSl    = 3     ; db 0
MusicPlayer_CHP_CrEnSl    = 4     ; db 0
MusicPlayer_CHP_TSlCnt    = 5     ; db 0
MusicPlayer_CHP_CrTnSl    = 6     ; dw 0
MusicPlayer_CHP_TnAcc     = 8     ; dw 0
MusicPlayer_CHP_COnOff    = 10    ; db 0
                ; reset group
MusicPlayer_CHP_OnOffD    = 11    ; db 0
                ; IX for PTDECOD here (+12)
MusicPlayer_CHP_OffOnD    = 12    ; db 0
MusicPlayer_CHP_OrnPtr    = 13    ; dw 0
MusicPlayer_CHP_SamPtr    = 15    ; dw 0
MusicPlayer_CHP_NNtSkp    = 17    ; db 0
MusicPlayer_CHP_Note      = 18    ; db 0
MusicPlayer_CHP_SlToNt    = 19    ; db 0
MusicPlayer_CHP_Env_En    = 20    ; db 0
MusicPlayer_CHP_Flags     = 21    ; db 0
                 ; Enabled - 0,SimpleGliss - 2
MusicPlayer_CHP_TnSlDl    = 22    ; db 0
MusicPlayer_CHP_TSlStp    = 23    ; dw 0
MusicPlayer_CHP_TnDelt    = 25    ; dw 0
MusicPlayer_CHP_NtSkCn    = 27    ; db 0
MusicPlayer_CHP_Volume    = 28    ; db 0
                ; ENDS

MusicPlayer_ChanA:        defs        29, 0   ; DS CHP
MusicPlayer_ChanB:        defs        29, 0   ; DS CHP
MusicPlayer_ChanC:        defs        29, 0   ; DS CHP

                ; GlobalVars
MusicPlayer_DelyCnt:      db          0
MusicPlayer_CurEDel:      db          0

MusicPlayer_AYREGS:
MusicPlayer_VT_:          defs        256, 0  ; DS 256 ; CreatedVolumeTableAddress

MusicPlayer_EnvBase       = MusicPlayer_VT_ + 14
MusicPlayer_T1_           = MusicPlayer_VT_ + 16                                ; Tone tables data depacked here
MusicPlayer_T_OLD_1       = MusicPlayer_T1_
MusicPlayer_T_OLD_2       = MusicPlayer_T_OLD_1 + 24
MusicPlayer_T_OLD_3       = MusicPlayer_T_OLD_2 + 24
MusicPlayer_T_OLD_0       = MusicPlayer_T_OLD_3 + 2
MusicPlayer_T_NEW_0       = MusicPlayer_T_OLD_0
;@@T_NEW_1       = @@T_OLD_1
MusicPlayer_T_NEW_2       = MusicPlayer_T_NEW_0 + 24
;@@T_NEW_3       = @@T_OLD_3

MusicPlayer_NT_:          defs        192, 0  ; DS 192 ; CreatedNoteTableAddress

                ; local var
MusicPlayer_Ampl          = MusicPlayer_AYREGS + MusicPlayer_AmplC
MusicPlayer_VAR0END       = MusicPlayer_VT_ + 16                                ; INIT zeroes from VARS to VAR0END-1
MusicPlayer_VARSEND:
