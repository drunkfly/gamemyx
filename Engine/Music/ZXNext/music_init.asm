
                PUBLIC      _MYXP_InitMusicPlayer

                EXTERN      _MYXP_CurrentUpperBank
                EXTERN      _MYXP_SetUpperMemoryBank
                EXTERN      MusicPlayer_T1_
                EXTERN      MusicPlayer_T_NEW_2
                EXTERN      MusicPlayer_TCNEW_2
                EXTERN      MusicPlayer_NT_
                EXTERN      MusicPlayer_VT_

                SECTION     MYX_MUSIC

_MYXP_InitMusicPlayer:
                ld          a, (_MYXP_CurrentUpperBank)
                push        af
                ld          l, 3
                call        _MYXP_SetUpperMemoryBank
                call        DoInitMusic
                pop         af
                ld          l, a
                jp          _MYXP_SetUpperMemoryBank

                SECTION     BANK_3

DoInitMusic:    ;note table data depacker
                ld          de, InitMusicPlayer_packedNoteTable
                ld          bc, MusicPlayer_T1_ + (2 * 49) - 1
InitMusicPlayer_TP_0:
                ld          a, (de)
                inc         de
                cp          15*2
                jr          nc, InitMusicPlayer_TP_1
                ld          h, a
                ld          a, (de)
                ld          l, a
                inc         de
                jr          InitMusicPlayer_TP_2
InitMusicPlayer_TP_1:
                push        de
                ld          d, 0
                ld          e, a
                add         hl, de
                add         hl, de
                pop         de
InitMusicPlayer_TP_2:
                ld          a, h
                ld          (bc), a
                dec         bc
                ld          a, l
                ld          (bc), a
                dec         bc
                sub         0xff & (0xf8 * 2)
                jr          nz, InitMusicPlayer_TP_0
                ; NoteTableCreator (c) Ivan Roshin
                ld          hl, MusicPlayer_T_NEW_2
                ld          bc, MusicPlayer_TCNEW_2
                push        bc
                ld          de, MusicPlayer_NT_
                push        de
                ;
                ld          b, 12
InitMusicPlayer_L1:
                push        bc
                ld          c, (hl)
                inc         hl
                push        hl
                ld          b, (hl)
                ;
                push        de
                ex          de, hl
                ld          de, 23
                ld          ixh, 8
                ;
InitMusicPlayer_L2:
                srl         b
                rr          c
                ld          a, c
                adc         a, d                            ; = ADC 0
                ld          (hl), a
                inc         hl
                ld          a, b
                adc         a, d
                ld          (hl), a
                add         hl, de
                dec         ixh
                jr          nz, InitMusicPlayer_L2
                ;
                pop         de
                inc         de
                inc         de
                pop         hl
                inc         hl
                pop         bc
                djnz        InitMusicPlayer_L1
                ;
                pop         hl
                pop         de
InitMusicPlayer_CORR_1:
                ld          a, (de)
                and         a
                jr          z, InitMusicPlayer_TC_EXIT
                rra
                push        af
                add         a, a
                ld          c, a
                add         hl, bc
                pop         af
                jr          nc, InitMusicPlayer_CORR_2
                dec         (hl)
                dec         (hl)
InitMusicPlayer_CORR_2:
                inc         (hl)
                and         a
                sbc         hl, bc
                inc         de
                jr          InitMusicPlayer_CORR_1
InitMusicPlayer_TC_EXIT:      ; VolTableCreator (c) Ivan Roshin
                ld          hl, 0x11
                ld          d, h
                ld          e, h
                ;
                ld          ix, MusicPlayer_VT_ + 16
                ld          c, 0x10
                ;
InitMusicPlayer_INITV2:
                push        hl
                ;
                add         hl, de
                ex          de, hl
                sbc         hl, hl
                ;
InitMusicPlayer_INITV1:
                ld          a, l
                db          0x17
                ld          a, h
                adc         a, 0
                ld          (ix), a
                inc         ix
                add         hl, de
                inc         c
                ld          a, c
                and         15
                jr          nz, InitMusicPlayer_INITV1
                ;
                pop         hl
                ld          a, e
                cp          0x77
                jr          nz, InitMusicPlayer_M3
                inc         e
InitMusicPlayer_M3:
                ld          a, c
                and         a
                jr          nz, InitMusicPlayer_INITV2
                ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                ; first 12 values of tone tables (packed)

InitMusicPlayer_packedNoteTable:
                db          0xff & (0x06EC * 2 / 256), 0xff & (0x06EC * 2)
                db          0x0755 - 0x06EC
                db          0x07C5 - 0x0755
                db          0x083B - 0x07C5
                db          0x08B8 - 0x083B
                db          0x093D - 0x08B8
                db          0x09CA - 0x093D
                db          0x0A5F - 0x09CA
                db          0x0AFC - 0x0A5F
                db          0x0BA4 - 0x0AFC
                db          0x0C55 - 0x0BA4
                db          0x0D10 - 0x0C55
                db          0xff & (0x066D * 2 / 256), 0xff & (0x066D * 2)
                db          0x06CF - 0x066D
                db          0x0737 - 0x06CF
                db          0x07A4 - 0x0737
                db          0x0819 - 0x07A4
                db          0x0894 - 0x0819
                db          0x0917 - 0x0894
                db          0x09A1 - 0x0917
                db          0x0A33 - 0x09A1
                db          0x0ACF - 0x0A33
                db          0x0B73 - 0x0ACF
                db          0x0C22 - 0x0B73
                db          0x0CDA - 0x0C22
                db          0xff & (0x0704 * 2 / 256), 0xff & (0x0704 * 2)
                db          0x076E - 0x0704
                db          0x07E0 - 0x076E
                db          0x0858 - 0x07E0
                db          0x08D6 - 0x0858
                db          0x095C - 0x08D6
                db          0x09EC - 0x095C
                db          0x0A82 - 0x09EC
                db          0x0B22 - 0x0A82
                db          0x0BCC - 0x0B22
                db          0x0C80 - 0x0BCC
                db          0x0D3E - 0x0C80
                db          0xff & (0x07E0 * 2 / 256), 0xff & (0x07E0 * 2)
                db          0x0858 - 0x07E0
                db          0x08E0 - 0x0858
                db          0x0960 - 0x08E0
                db          0x09F0 - 0x0960
                db          0x0A88 - 0x09F0
                db          0x0B28 - 0x0A88
                db          0x0BD8 - 0x0B28
                db          0x0C80 - 0x0BD8
                db          0x0D60 - 0x0C80
                db          0x0E10 - 0x0D60
                db          0x0EF8 - 0x0E10
