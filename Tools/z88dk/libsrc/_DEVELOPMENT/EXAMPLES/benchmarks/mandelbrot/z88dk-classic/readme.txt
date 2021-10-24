CHANGES TO SOURCE CODE
======================

For the sccz80 compile, variable "limit" in main() cannot be made static.

COMPILATION
===========

Compilation:

classic/sccz80
zcc +test -vn -DSTATIC -DTIMER -D__Z88DK -O2 mandelbrot.c -o mandelbrot.bin -lm -lndos -m

classic/sccz80/math32
zcc +test -vn -DSTATIC -DTIMER -D__Z88DK -O2 mandelbrot.c -o mandelbrot.bin --math32 -lndos -m

classic/zsdcc
zcc +test -vn -DSTATIC -DTIMER -D__Z88DK -compiler=sdcc -SO3 --max-allocs-per-node200000 mandelbrot.c -o mandelbrot.bin -lmath48 -lndos -m

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

z88dk-ticks mandelbrot.bin -start 00cd -end 0364 -counter 999999999999 -output verify.bin

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
zsdcc #11566 / classic
2356 bytes less page zero

cycle count  = 3783223422
time @ 4MHz  = 3783223422 / 4*10^6 = 15 min 45 sec


Z88DK April 20, 2020
sccz80 / classic
2108 bytes less page zero

cycle count  = 3591216622
time @ 4MHz  = 3591216622 / 4*10^6 = 14 min 57 sec


Z88DK April 20, 2020
sccz80 / classic / math32
3859 bytes less page zero

cycle count  = 1519179081
time @ 4MHz  = 1519179081 / 4*10^6 =  6 min 20 sec
