CHANGES TO SOURCE CODE
======================

For the sccz80 compile, variable "limit" in main() cannot be made static.

COMPILATION
===========

Compilation:

new/sccz80
zcc +z80 -vn -DSTATIC -DTIMER -startup=0 -O2 -clib=new mandelbrot.c -o mandelbrot -lm -m -pragma-include:zpragma.inc -create-app

math32/new/sccz80
zcc +z80 -vn -DSTATIC -DTIMER -startup=0 -O2 -clib=new mandelbrot.c -o mandelbrot --math32 -m -pragma-include:zpragma.inc -create-app

math16/new/sccz80
zcc +z80 -vn -DSTATIC -DTIMER -startup=0 -O2 -clib=new mandelbrot.c -o mandelbrot --math16 -m -pragma-include:zpragma.inc -create-app

new/zsdcc
zcc +z80 -vn -DSTATIC -DTIMER -startup=0 -SO3 -clib=sdcc_iy --max-allocs-per-node200000 mandelbrot.c -o mandelbrot -lm -m -pragma-include:zpragma.inc -create-app

TIMING & VERIFICATION
=====================

With PRINTF undefined the program will write the 480-byte result into memory
at address 0xc000.  TICKS will be invoked such that it dumps the memory
contents of the 64k virtual machine at the end so that those 480 bytes
can be extracted and compared to the golden result.  The memory dump produced
consists of the current state of the 64k of memory followed by a block
holding current cpu state.

The map files generated from the compiles above were used to look up symbols
"TIMER_START" and "TIMER_STOP".  These address bounds were given to TICKS to
measure execution time.

A typical invocation of TICKS looked like this:

z88dk-ticks mandelbrot.bin -start 0495 -end 075d -counter 999999999999 -output verify.bin

start   = TIMER_START in hex
end     = TIMER_STOP in hex
counter = High value to ensure completion

If the result is close to the counter value, the program may have
prematurely terminated so rerun with a higher counter if that is the case.

To verify, extract the 480 bytes at address 0xc000 from "verify.bin":

appmake +extract -b verify.bin -s 0xc000 -l 480 -o image.bin

Compare the contents of "image.bin" to "image-golden.bin" in the same directory.
The pixels around the edge of the mandelbrot set can vary somewhat depending
on math library precision so if there are differences, the two images may have
to be compared visually.  This can be done on a zx spectrum emulator by loading
the images to address 16384 to see a visual representation.

RESULT
======

Z88DK April 20, 2020
zsdcc #11566 / new
1939 bytes less page zero

cycle count  = 3736280696
time @ 4MHz  = 3736280696 / 4*10^6 = 15 min 34 sec


Z88DK April 20, 2020
sccz80 / new
1826 bytes less page zero

cycle count  = 3265477446
time @ 4MHz  = 3265477446 / 4*10^6 = 13 min 36 sec


Z88DK June 13, 2020
sccz80 / new / math32
3663 bytes less page zero

cycle count  = 1517530881
time @ 4MHz  = 1517530881 / 4*10^6 =  6 min 20 sec


Z88DK June 13, 2020
sccz80 / new / math16-fast
1986 bytes less page zero

cycle count  =  965171871
time @ 4MHz  =  965171871 / 4*10^6 =  4 min 01 sec
