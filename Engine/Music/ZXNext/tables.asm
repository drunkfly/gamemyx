;
; Copyright (c) 2021 DrunkFly Team
; Licensed under 3-clause BSD license
;
;
; Based on Vortex Tracker II v1.0 PT3 player for ZX Spectrum
; (c)2004,2007 S.V.Bulba <vorobey@mail.khstu.ru>
; http://bulba.untergrund.net (http://bulba.at.kz)
;

                PUBLIC  MYXP_NoteTable
                PUBLIC  MYXP_VolumeTable

                SECTION BANK_3

MYXP_VolumeTable:
                db      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                db      0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1
                db      0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2
                db      0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3
                db      0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4
                db      0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5
                db      0, 0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 6
                db      0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7
                db      0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8
                db      0, 1, 1, 2, 2, 3, 4, 4, 5, 5, 6, 7, 7, 8, 8, 9
                db      0, 1, 1, 2, 3, 3, 4, 5, 5, 6, 7, 7, 8, 9, 9,10
                db      0, 1, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 9,10,10,11
                db      0, 1, 2, 2, 3, 4, 5, 6, 6, 7, 8, 9,10,10,11,12
                db      0, 1, 2, 3, 3, 4, 5, 6, 7, 8, 9,10,10,11,12,13
                db      0, 1, 2, 3, 4, 5, 6, 7, 7, 8, 9,10,11,12,13,14
                db      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15

MYXP_NoteTable:
                dw      0xd10,0xc55,0xba4,0xafc,0xa5f,0x9ca,0x93d,0x8b8,0x83b,0x7c5,0x755,0x6ec
                dw      0x688,0x62a,0x5d2,0x57e,0x52f,0x4e5,0x49e,0x45c,0x41d,0x3e2,0x3ab,0x376
                dw      0x344,0x315,0x2e9,0x2bf,0x298,0x272,0x24f,0x22e,0x20f,0x1f1,0x1d5,0x1bb
                dw      0x1a2,0x18b,0x174,0x160,0x14c,0x139,0x128,0x117,0x107,0x0f9,0x0eb,0x0dd
                dw      0x0d1,0x0c5,0x0ba,0x0b0,0x0a6,0x09d,0x094,0x08c,0x084,0x07c,0x075,0x06f
                dw      0x069,0x063,0x05d,0x058,0x053,0x04e,0x04a,0x046,0x042,0x03e,0x03b,0x037
                dw      0x034,0x031,0x02f,0x02c,0x029,0x027,0x025,0x023,0x021,0x01f,0x01d,0x01c
                dw      0x01a,0x019,0x017,0x016,0x015,0x014,0x012,0x011,0x010,0x00f,0x00e,0x00d
