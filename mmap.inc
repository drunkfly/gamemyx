
SECTION UNASSIGNED

;-----------------------------------------------------------------------
; Shared

SECTION MYX_INTVECTORS
org 0x8000

SECTION MYX_INTENTRY
org 0x8181

SECTION CODE
org 0x8300

SECTION code_crt_main
SECTION code_error
SECTION code_l
SECTION code_l_sdcc
SECTION code_math
SECTION data_threads
SECTION data_stdio
SECTION MYX_ANIMSPRITES
SECTION MYX_INTERRUPT
SECTION MYX_INPUT
SECTION bss_compiler
SECTION bss_stdio
SECTION bss_stdlib

;-----------------------------------------------------------------------
; Banks

SECTION MYX_STARTUP
org 0xc000

SECTION code_compiler
