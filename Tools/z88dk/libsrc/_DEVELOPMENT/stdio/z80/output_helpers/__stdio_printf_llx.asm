
SECTION code_clib
SECTION code_stdio

PUBLIC __stdio_printf_llx

EXTERN __stdio_printf_number_tail_ulonglong

__stdio_printf_llx:

   ; %llx, %llX converter called from vfprintf()
   ;
   ; enter : ix = FILE *
   ;         hl = void *stack_param
   ;         de = void *buffer_digits
   ;         stack = buffer_digits, width, precision
   ;
   ; exit  : carry set if stream error
   ;
   ; NOTE: (buffer_digits - 3) points at buffer space of three free bytes

   ld bc,16                    ; base 16 conversion
   jp __stdio_printf_number_tail_ulonglong
