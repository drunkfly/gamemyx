;
; Copyright (c) 2021 DrunkFly Team
; Licensed under 3-clause BSD license
;
;
; Based on Vortex Tracker II v1.0 PT3 player for ZX Spectrum
; (c)2004,2007 S.V.Bulba <vorobey@mail.khstu.ru>
; http://bulba.untergrund.net (http://bulba.at.kz)
;

                PUBLIC  PT3_init
                PUBLIC  PT3_play
                PUBLIC  PT3_mute
                PUBLIC  PT3_enabled
                PUBLIC  PT3_WriteAY

                EXTERN  MYXP_NoteTable
                EXTERN  MYXP_VolumeTable

                SECTION BANK_3_LO

PT3_init:       ld      (PT3_MODADDR), hl
                ld      (PT3_MDADDR2), hl
                push    hl
                ld      de, 100
                add     hl, de
                ld      a, (hl)
                ld      (PT3_delayValue), a
                push    hl
                pop     ix
                add     hl, de
                ld      (PT3_currentPos), hl
                ld      e, (ix+102-100)
                add     hl, de
                inc     hl
                ld      (PT3_LPosPtr), hl
                pop     de
                ld      l, (ix+103-100)
                ld      h, (ix+104-100)
                add     hl, de
                ld      (PT3_PatsPtr), hl
                ld      hl, 169
                add     hl, de
                ld      (PT3_OrnPtrs), hl
                ld      hl, 105
                add     hl, de
                ld      (PT3_SamPtrs), hl
                xor     a
                ;
                ld      hl, PT3_VARS
                ld      (hl), a
                ld      de, PT3_VARS + 1
                ld      bc, PT3_VARSEND - PT3_VARS - 1
                ldir
                inc     a
                ld      (PT3_DelyCnt), a
                ld      hl, 0xf001  ; H - CHP.Volume, L - CHP.NtSkCn
                ld      (PT3_ChanA+PT3_CHP_NtSkCn), hl
                ld      (PT3_ChanB+PT3_CHP_NtSkCn), hl
                ld      (PT3_ChanC+PT3_CHP_NtSkCn), hl
                ;
                ld      hl, PT3_EMPTYSAMORN
                ld      (PT3_AdInPtA), hl               ; ptr to zero
                ld      (PT3_ChanA+PT3_CHP_OrnPtr), hl  ; ornament 0 is "0,1,0"
                ld      (PT3_ChanB+PT3_CHP_OrnPtr), hl  ; in all versions from
                ld      (PT3_ChanC+PT3_CHP_OrnPtr), hl  ; 3.xx to 3.6x and VTII
                ;
                ld      (PT3_ChanA+PT3_CHP_SamPtr), hl
                ld      (PT3_ChanB+PT3_CHP_SamPtr), hl
                ld      (PT3_ChanC+PT3_CHP_SamPtr), hl
                jp      PT3_ROUT_A0

PT3_mute:       xor     a
                ld      h, a
                ld      l, a
                ld      (PT3_AmplA), a
                ld      (PT3_AmplB), hl
                jp      PT3_ROUT_A0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                ; pattern decoder

PT3_PD_OrSm:    ld      (ix+PT3_CHP_Env_En-12), 0
                call    PT3_SETORN
                ld      a, (bc)
                inc     bc
                rrca
                ;
PT3_PD_SAM:     add     a, a
PT3_PD_SAM_:    ld      e, a
                ld      d, 0
                ld      hl, (PT3_SamPtrs)
                add     hl, de
                ld      e, (hl)
                inc     hl
                ld      d, (hl)
                ld      hl, (PT3_MODADDR)
                add     hl, de
                ld      (ix+PT3_CHP_SamPtr-12), l
                ld      (ix+PT3_CHP_SamPtr-12+1), h
                jr      PT3_PD_LOOP
                ;
PT3_PD_VOL:     rlca
                rlca
                rlca
                rlca
                ld      (ix+PT3_CHP_Volume-12), a
                jr      PT3_PD_LP2
                ;
PT3_PD_EOff:    ld      (ix+PT3_CHP_Env_En-12), a
                ld      (ix+PT3_CHP_PsInOr-12), a
                jr      PT3_PD_LP2
                ;
PT3_PD_SorE:    dec     a
                jr      nz, PT3_PD_ENV
                ld      a, (bc)
                inc     bc
                ld      (ix+PT3_CHP_NNtSkp-12), a
                jr      PT3_PD_LP2
                ;
PT3_PD_ENV:     call    PT3_SETENV
                jr      PT3_PD_LP2
                ;
PT3_PD_ORN:     call    PT3_SETORN
                jr      PT3_PD_LOOP
                ;
PT3_PD_ESAM:    ld      (ix+PT3_CHP_Env_En-12), a
                ld      (ix+PT3_CHP_PsInOr-12), a
                call    nz, PT3_SETENV
                ld      a, (bc)
                inc     bc
                jr      PT3_PD_SAM_
                ;
PT3_PTDECOD:    ld      a, (ix+PT3_CHP_Note-12)
                ld      (PT3_PrNote), a
                ld      l, (ix+PT3_CHP_CrTnSl-12)
                ld      h, (ix+PT3_CHP_CrTnSl-12+1)
                ld      (PT3_PrSlide), hl
                ;
PT3_PD_LOOP:    ld      de, 0x2010
PT3_PD_LP2:     ld      a, (bc)
                inc     bc
                add     a, e
                jr      c, PT3_PD_OrSm
                add     a, d
                jr      z, PT3_PD_FIN
                jr      c, PT3_PD_SAM
                add     a, e
                jr      z, PT3_PD_REL
                jr      c, PT3_PD_VOL
                add     a, e
                jr      z, PT3_PD_EOff
                jr      c, PT3_PD_SorE
                add     a, 96
                jr      c, PT3_PD_NOTE
                add     a, e
                jr      c, PT3_PD_ORN
                add     a, d
                jr      c, PT3_PD_NOIS
                add     a, e
                jr      c, PT3_PD_ESAM
                add     a, a
                ld      e, a
                ld      hl, 0xffff & (PT3_SPCCOMS+0xFF20-0x2000)
                add     hl, de
                ld      e, (hl)
                inc     hl
                ld      d, (hl)
                push    de
                jr      PT3_PD_LOOP
                ;
PT3_PD_NOIS:    ld      (PT3_Ns_Base), a
                jr      PT3_PD_LP2
                ;
PT3_PD_REL:     res     0, (ix+PT3_CHP_Flags-12)
                jr      PT3_PD_RES
                ;
PT3_PD_NOTE:    ld      (ix+PT3_CHP_Note-12), a
                set     0, (ix+PT3_CHP_Flags-12)
                xor     a
                ;
PT3_PD_RES:     ld      (PT3_PDSP), sp
                ld      sp, ix
                ld      h, a
                ld      l, a
                push    hl
                push    hl
                push    hl
                push    hl
                push    hl
                push    hl
                ld      sp, (PT3_PDSP)
                ;
PT3_PD_FIN:     ld      a, (ix+PT3_CHP_NNtSkp-12)
                ld      (ix+PT3_CHP_NtSkCn-12), a
                ret
                ;
PT3_C_PORTM:    res     2, (ix+PT3_CHP_Flags-12)
                ld      a, (bc)
                inc     bc
                ; SKIP PRECALCULATED TONE DELTA (BECAUSE CANNOT BE RIGHT AFTER PT3 COMPILATION)
                inc     bc
                inc     bc
                ld      (ix+PT3_CHP_TnSlDl-12), a
                ld      (ix+PT3_CHP_TSlCnt-12), a
                ld      de, MYXP_NoteTable
                ld      a, (ix+PT3_CHP_Note-12)
                ld      (ix+PT3_CHP_SlToNt-12), a
                add     a, a
                ld      l, a
                ld      h, 0
                add     hl, de
                ld      a, (hl)
                inc     hl
                ld      h, (hl)
                ld      l, a
                push    hl
                ld      a, (PT3_PrNote)
                ld      (ix+PT3_CHP_Note-12), a
                add     a, a
                ld      l, a
                ld      h, 0
                add     hl, de
                ld      e, (hl)
                inc     hl
                ld      d, (hl)
                pop     hl
                sbc     hl, de
                ld      (ix+PT3_CHP_TnDelt-12), l
                ld      (ix+PT3_CHP_TnDelt-12+1), h
                ld      e, (ix+PT3_CHP_CrTnSl-12)
                ld      d, (ix+PT3_CHP_CrTnSl-12+1)
                ld      de, (PT3_PrSlide)
                ld      (ix+PT3_CHP_CrTnSl-12), e
                ld      (ix+PT3_CHP_CrTnSl-12+1), d
PT3_OLDPRTM:    ld      a, (bc)     ; SIGNED TONE STEP
                inc     bc
                ex      af, af'
                ld      a, (bc)
                inc     bc
                and     a
                jr      z, PT3_NOSIG
                ex      de, hl
PT3_NOSIG:      sbc     hl, de
                jp      p, PT3_SET_STP
                cpl
                ex      af, af'
                neg
                ex      af, af'
PT3_SET_STP:    ld      (ix+PT3_CHP_TSlStp-12+1), a
                ex      af, af'
                ld      (ix+PT3_CHP_TSlStp-12), a
                ld      (ix+PT3_CHP_COnOff-12), 0
                ret

PT3_C_GLISS:    set     2, (ix+PT3_CHP_Flags-12)
                ld      a, (bc)
                inc     bc
                ld      (ix+PT3_CHP_TnSlDl-12), a
                and     a
                jr      nz, PT3_GL36
                inc     a
PT3_GL36:       ld      (ix+PT3_CHP_TSlCnt-12), a
                ld      a, (bc)
                inc     bc
                ex      af, af'
                ld      a, (bc)
                inc     bc
                jr      PT3_SET_STP

PT3_C_SMPOS:    ld      a, (bc)
                inc     bc
                ld      (ix+PT3_CHP_PsInSm-12), a
                ret

PT3_C_ORPOS:    ld      a, (bc)
                inc     bc
                ld      (ix+PT3_CHP_PsInOr-12), a
                ret

PT3_C_VIBRT:    ld      a, (bc)
                inc     bc
                ld      (ix+PT3_CHP_OnOffD-12), a
                ld      (ix+PT3_CHP_COnOff-12), a
                ld      a, (bc)
                inc     bc
                ld      (ix+PT3_CHP_OffOnD-12), a
                xor     a
                ld      (ix+PT3_CHP_TSlCnt-12), a
                ld      (ix+PT3_CHP_CrTnSl-12), a
                ld      (ix+PT3_CHP_CrTnSl-12+1), a
                ret

PT3_C_ENGLS:    ld      a, (bc)
                inc     bc
                ld      (PT3_Env_Del), a
                ld      (PT3_CurEDel), a
                ld      a, (bc)
                inc     bc
                ld      l, a
                ld      a, (bc)
                inc     bc
                ld      h, a
                ld      (PT3_ESldAdd), hl
                ret

PT3_C_DELAY:    ld      a, (bc)
                inc     bc
                ld      (PT3_delayValue), a
                ret

PT3_SETENV:     ld      (ix+PT3_CHP_Env_En-12), e
                ld      (PT3_EnvTp), a
                ld      a, (bc)
                inc     bc
                ld      h, a
                ld      a, (bc)
                inc     bc
                ld      l, a
                ld      (PT3_EnvBase), hl
                xor     a
                ld      (ix+PT3_CHP_PsInOr-12), a
                ld      (PT3_CurEDel), a
                ld      h, a
                ld      l, a
                ld      (PT3_CurESld), hl
PT3_C_NOP:      ret

PT3_SETORN:     add     a, a
                ld      e, a
                ld      d, 0
                ld      (ix+PT3_CHP_PsInOr-12), d
                ld      hl, (PT3_OrnPtrs)
                add     hl, de
                ld      e, (hl)
                inc     hl
                ld      d, (hl)
                ld      hl, (PT3_MDADDR2)
                add     hl, de
                ld      (ix+PT3_CHP_OrnPtr-12), l
                ld      (ix+PT3_CHP_OrnPtr-12+1), h
                ret

PT3_SPCCOMS:    dw      PT3_C_NOP
                dw      PT3_C_GLISS
                dw      PT3_C_PORTM
                dw      PT3_C_SMPOS
                dw      PT3_C_ORPOS
                dw      PT3_C_VIBRT
                dw      PT3_C_NOP
                dw      PT3_C_NOP
                dw      PT3_C_ENGLS
                dw      PT3_C_DELAY

PT3_CHREGS:     xor     a
                ld      (PT3_Ampl), a
                bit     0, (ix+PT3_CHP_Flags)
                push    hl
                jp      z, PT3_CH_EXIT
                ld      (PT3_CSP), sp
                ld      l, (ix+PT3_CHP_OrnPtr)
                ld      h, (ix+PT3_CHP_OrnPtr+1)
                ld      sp, hl
                pop     de
                ld      h, a
                ld      a, (ix+PT3_CHP_PsInOr)
                ld      l, a
                add     hl, sp
                inc     a
                cp      d
                jr      c, PT3_CH_ORPS
                ld      a, e
PT3_CH_ORPS:    ld      (ix+PT3_CHP_PsInOr), a
                ld      a, (ix+PT3_CHP_Note)
                add     a,(hl)
                jp      p, PT3_CH_NTP
                xor     a
PT3_CH_NTP:     cp      96
                jr      c, PT3_CH_NOK
                ld      a, 95
PT3_CH_NOK:     add     a, a
                ex      af, af'
                ld      l, (ix+PT3_CHP_SamPtr)
                ld      h, (ix+PT3_CHP_SamPtr+1)
                ld      sp, hl
                pop     de
                ld      h, 0
                ld      a, (ix+PT3_CHP_PsInSm)
                ld      b, a
                add     a, a
                add     a, a
                ld      l, a
                add     hl, sp
                ld      sp, hl
                ld      a, b
                inc     a
                cp      d
                jr      c, PT3_CH_SMPS
                ld      a, e
PT3_CH_SMPS:    ld      (ix+PT3_CHP_PsInSm), a
                pop     bc
                pop     hl
                ld      e, (ix+PT3_CHP_TnAcc)
                ld      d, (ix+PT3_CHP_TnAcc+1)
                add     hl, de
                bit     6, b
                jr      z, PT3_CH_NOAC
                ld      (ix+PT3_CHP_TnAcc), l
                ld      (ix+PT3_CHP_TnAcc+1), h
PT3_CH_NOAC:    ex      de, hl
                ex      af, af'
                ld      l, a
                ld      h, 0
                ld      sp, MYXP_NoteTable
                add     hl, sp
                ld      sp, hl
                pop     hl
                add     hl, de
                ld      e, (ix+PT3_CHP_CrTnSl)
                ld      d, (ix+PT3_CHP_CrTnSl+1)
                add     hl, de
                ld      sp, (PT3_CSP)
                ex      (sp), hl
                xor     a
                or      (ix+PT3_CHP_TSlCnt)
                jr      z, PT3_CH_AMP
                dec     (ix+PT3_CHP_TSlCnt)
                jr      nz, PT3_CH_AMP
                ld      a, (ix+PT3_CHP_TnSlDl)
                ld      (ix+PT3_CHP_TSlCnt), a
                ld      l, (ix+PT3_CHP_TSlStp)
                ld      h, (ix+PT3_CHP_TSlStp+1)
                ld      a, h
                add     hl, de
                ld      (ix+PT3_CHP_CrTnSl), l
                ld      (ix+PT3_CHP_CrTnSl+1), h
                bit     2, (ix+PT3_CHP_Flags)
                jr      nz, PT3_CH_AMP
                ld      e, (ix+PT3_CHP_TnDelt)
                ld      d, (ix+PT3_CHP_TnDelt+1)
                and     a
                jr      z, PT3_CH_STPP
                ex      de, hl
PT3_CH_STPP:    sbc     hl, de
                jp      m, PT3_CH_AMP
                ld      a, (ix+PT3_CHP_SlToNt)
                ld      (ix+PT3_CHP_Note), a
                xor     a
                ld      (ix+PT3_CHP_TSlCnt), a
                ld      (ix+PT3_CHP_CrTnSl), a
                ld      (ix+PT3_CHP_CrTnSl+1), a
PT3_CH_AMP:     ld      a, (ix+PT3_CHP_CrAmSl)
                bit     7, c
                jr      z, PT3_CH_NOAM
                bit     6, c
                jr      z, PT3_CH_AMIN
                cp      15
                jr      z, PT3_CH_NOAM
                inc     a
                jr      PT3_CH_SVAM
PT3_CH_AMIN:    cp      -15
                jr      z, PT3_CH_NOAM
                dec     a
PT3_CH_SVAM:    ld      (ix+PT3_CHP_CrAmSl), a
PT3_CH_NOAM:    ld      l, a
                ld      a, b
                and     15
                add     a, l
                jp      p, PT3_CH_APOS
                xor     a
PT3_CH_APOS:    cp      16
                jr      c, PT3_CH_VOL
                ld      a, 15
PT3_CH_VOL:     or      (ix+PT3_CHP_Volume)
                ld      l, a
                ld      h, 0
                ld      de, MYXP_VolumeTable
                add     hl, de
                ld      a, (hl)
PT3_CH_ENV:     bit     0, c
                jr      nz, PT3_CH_NOEN
                or      (ix+PT3_CHP_Env_En)
PT3_CH_NOEN:    ld      (PT3_Ampl), a
                bit     7, b
                ld      a, c
                jr      z, PT3_NO_ENSL
                rla
                rla
                sra     a
                sra     a
                sra     a
                add     a, (ix+PT3_CHP_CrEnSl)  ; SEE COMMENT BELOW
                bit     5, b
                jr      z, PT3_NO_ENAC
                ld      (ix+PT3_CHP_CrEnSl), a
PT3_NO_ENAC:    ld      hl, PT3_AddToEn
                add     a, (hl)                         ; BUG IN PT3 - NEED WORD HERE.
                ld      (hl), a                         ; FIX IT IN NEXT VERSION?
                jr      PT3_CH_MIX
PT3_NO_ENSL:    rra
                add     a, (ix+PT3_CHP_CrNsSl)
                ld      (PT3_AddToNs), a
                bit     5, b
                jr      z, PT3_CH_MIX
                ld      (ix+PT3_CHP_CrNsSl), a
PT3_CH_MIX:     ld      a, b
                rra
                and     0x48
PT3_CH_EXIT:    ld      hl, PT3_Mixer
                or      (hl)
                rrca
                ld      (hl), a
                pop     hl
                xor     a
                or      (ix+PT3_CHP_COnOff)
                ret     z
                dec     (ix+PT3_CHP_COnOff)
                ret     nz
                xor     (ix+PT3_CHP_Flags)
                ld      (ix+PT3_CHP_Flags), a
                rra
                ld      a, (ix+PT3_CHP_OnOffD)
                jr      c, PT3_CH_ONDL
                ld      a, (ix+PT3_CHP_OffOnD)
PT3_CH_ONDL:    ld      (ix+PT3_CHP_COnOff), a
                ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PT3_play:       ld      a, (PT3_enabled)
                or      a
                ret     z
                xor     a
                ld      (PT3_AddToEn), a
                ld      (PT3_Mixer), a
                dec     a
                ld      (PT3_EnvTp), a
                ld      hl, PT3_DelyCnt
                dec     (hl)
                jp      nz, PT3_PL2
                ld      hl, PT3_ChanA + PT3_CHP_NtSkCn
                dec     (hl)
                jr      nz, PT3_PL1B
                ld      bc, (PT3_AdInPtA)
                ld      a, (bc)
                and     a
                jr      nz, PT3_PL1A
                ld      d, a
                ld      (PT3_Ns_Base), a
                ld      hl, (PT3_currentPos)
                inc     hl
                ld      a, (hl)
                inc     a
                jr      nz, PT3_PLNLP
                ld      hl, (PT3_LPosPtr)
                ld      a, (hl)
                inc     a
PT3_PLNLP:      ld      (PT3_currentPos), hl
                dec     a
                add     a, a
                ld      e, a
                rl      d
                ld      hl, (PT3_PatsPtr)
                add     hl, de
                ld      de, (PT3_MODADDR)
                ld      (PT3_PSP), sp
                ld      sp, hl
                pop     hl
                add     hl, de
                ld      b, h
                ld      c, l
                pop     hl
                add     hl, de
                ld      (PT3_AdInPtB), hl
                pop     hl
                add     hl, de
                ld      (PT3_AdInPtC), hl
                ld      sp, (PT3_PSP)
PT3_PL1A:       ld      ix, PT3_ChanA + 12
                call    PT3_PTDECOD
                ld      (PT3_AdInPtA), bc
                ;
PT3_PL1B:       ld      hl, PT3_ChanB + PT3_CHP_NtSkCn
                dec     (hl)
                jr      nz, PT3_PL1C
                ld      ix, PT3_ChanB + 12
                ld      bc, (PT3_AdInPtB)
                call    PT3_PTDECOD
                ld      (PT3_AdInPtB),bc
                ;
PT3_PL1C:       ld      hl, PT3_ChanC + PT3_CHP_NtSkCn
                dec     (hl)
                jr      nz, PT3_delay
                ld      ix, PT3_ChanC + 12
                ld      bc, (PT3_AdInPtC)
                call    PT3_PTDECOD
                ld      (PT3_AdInPtC), bc
                ;
PT3_delay:      ld      a, (PT3_delayValue)
                ld      (PT3_DelyCnt), a
                ;
PT3_PL2:        ld      ix, PT3_ChanA
                ld      hl, (PT3_TonA)
                call    PT3_CHREGS
                ld      (PT3_TonA), hl
                ld      a, (PT3_Ampl)
                ld      (PT3_AmplA), a
                ld      ix ,PT3_ChanB
                ld      hl, (PT3_TonB)
                call    PT3_CHREGS
                ld      (PT3_TonB), hl
                ld      a, (PT3_Ampl)
                ld      (PT3_AmplB), a
                ld      ix, PT3_ChanC
                ld      hl, (PT3_TonC)
                call    PT3_CHREGS
                ld      (PT3_TonC), hl
                ;
                ld      hl, (PT3_Ns_Base_AddToNs)
                ld      a, h
                add     a, l
                ld      (PT3_Noise), a
                ld      a, (PT3_AddToEn)
                ld      e, a
                add     a, a
                sbc     a, a
                ld      d, a
                ld      hl, (PT3_EnvBase)
                add     hl, de
                ld      de, (PT3_CurESld)
                add     hl, de
                ld      (PT3_Env), hl
                ;
                xor     a
                ld      hl, PT3_CurEDel
                or      (hl)
                ret     z
                dec     (hl)
                ret     nz
                ld      a, (PT3_Env_Del)
                ld      (hl), a
                ld      hl, (PT3_ESldAdd)
                add     hl, de
                ld      (PT3_CurESld), hl
                ret

PT3_WriteAY:    xor     a
PT3_ROUT_A0:    ld      de, 0xffbf
                ld      bc, 0xfffd
                ld      hl, PT3_AYREGS
PT3_LOUT:       out     (c), a
                ld      b, e
                outi
                ld      b, d
                inc     a
                cp      13
                jr      nz, PT3_LOUT
                out     (c), a
                ld      a, (hl)
                and     a
                ret     m
                ld      b, e
                out     (c), a
                ret

PT3_EMPTYSAMORN:db      0, 1, 0, 0x90

                SECTION BANK_3_HI

PT3_enabled:    db      0
PT3_SamPtrs:    dw      0
PT3_MODADDR:    dw      0
PT3_PrNote:     db      0
PT3_PrSlide:    dw      0
PT3_PDSP:       dw      0
PT3_delayValue: db      0
PT3_OrnPtrs:    dw      0
PT3_MDADDR2:    dw      0
PT3_CSP:        dw      0
PT3_AddToEn:    db      0
PT3_currentPos: dw      0
PT3_LPosPtr:    dw      0
PT3_PatsPtr:    dw      0
PT3_PSP:        dw      0
PT3_AdInPtA:    dw      0
PT3_AdInPtB:    dw      0
PT3_AdInPtC:    dw      0
PT3_Ns_Base_AddToNs:
PT3_Ns_Base:    db      0
PT3_AddToNs:    db      0
PT3_CurESld:    dw      0
PT3_Env_Del:    db      0
PT3_ESldAdd:    dw      0

                PT3_CHP_PsInOr = 0
                PT3_CHP_PsInSm = 1
                PT3_CHP_CrAmSl = 2
                PT3_CHP_CrNsSl = 3
                PT3_CHP_CrEnSl = 4
                PT3_CHP_TSlCnt = 5
                PT3_CHP_CrTnSl = 6
                PT3_CHP_TnAcc  = 8
                PT3_CHP_COnOff = 10
                PT3_CHP_OnOffD = 11
                PT3_CHP_OffOnD = 12     ; IX for PTDECOD here (+12)
                PT3_CHP_OrnPtr = 13
                PT3_CHP_SamPtr = 15
                PT3_CHP_NNtSkp = 17
                PT3_CHP_Note   = 18
                PT3_CHP_SlToNt = 19
                PT3_CHP_Env_En = 20
                PT3_CHP_Flags  = 21
                PT3_CHP_TnSlDl = 22     ; Enabled - 0,SimpleGliss - 2
                PT3_CHP_TSlStp = 23
                PT3_CHP_TnDelt = 25
                PT3_CHP_NtSkCn = 27
                PT3_CHP_Volume = 28

PT3_VARS:
PT3_ChanA:      defs    29, 0
PT3_ChanB:      defs    29, 0
PT3_ChanC:      defs    29, 0
PT3_DelyCnt:    db      0
PT3_CurEDel:    db      0

PT3_AYREGS:
PT3_TonA:       dw      0
PT3_TonB:       dw      0
PT3_TonC:       dw      0
PT3_Noise:      db      0
PT3_Mixer:      db      0
PT3_AmplA:      db      0
PT3_AmplB:      db      0
PT3_Ampl:
PT3_AmplC:      db      0
PT3_Env:        dw      0
PT3_EnvTp:      db      0
PT3_EnvBase:    dw      0

PT3_VARSEND:
