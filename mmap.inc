
SECTION MYX_INTVECTORS
org 0x8000

SECTION MYX_INTENTRY
org 0x8181

SECTION MYX_STARTUP
org 0xc000
SECTION MYX_INPUT

SECTION CODE
org __crt_org_code
SECTION code_crt_init
SECTION code_crt_main
SECTION code_crt_exit
SECTION code_crt_return
SECTION code_crt_common
SECTION code_driver
SECTION code_font
SECTION code_clib
include "../../clib_code.inc"
SECTION code_lib
SECTION code_compiler
SECTION code_user
SECTION rodata_driver
SECTION rodata_font
SECTION rodata_clib
include "../../clib_rodata.inc"
SECTION rodata_lib
SECTION rodata_compiler
SECTION rodata_user
SECTION CODE_END

SECTION DATA
IF __crt_org_data
    org __crt_org_data
ELSE
    IF __crt_model
        "DATA section address must be specified for ROM models"
    ENDIF
ENDIF
defb 0
SECTION smc_driver
SECTION smc_font
SECTION smc_clib
include "../../clib_smc.inc"
SECTION smc_lib
SECTION smc_compiler
SECTION smc_user
SECTION data_driver
SECTION data_font
SECTION data_clib
include "../../clib_data.inc"
SECTION data_lib
SECTION data_compiler
SECTION data_user
SECTION DATA_END

SECTION BSS
IF __crt_org_bss
    org __crt_org_bss
ELSE
    IF __crt_model
        org -1
    ENDIF
ENDIF
defb 0
SECTION BSS_UNINITIALIZED
SECTION bss_driver
SECTION bss_font
SECTION bss_clib
include "../../clib_bss.inc"
SECTION bss_lib
SECTION bss_compiler
SECTION bss_user
SECTION BSS_END
