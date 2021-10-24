#!/usr/bin/perl

# Z88DK Z80 Macro Assembler
#
# Copyright (C) Paulo Custodio, 2011-2020
# License: The Artistic License 2.0, http://www.perlfoundation.org/artistic_license_2_0
# Repository: https://github.com/z88dk/z88dk/
#
# Test -h

use Modern::Perl;
use Test::More;
require './t/testlib.pl';

my $config = slurp("../config.h");
my($version) = $config =~ /Z88DK_VERSION\s*"(.*)"/;
ok $version, "version $version";

run("z80asm -h", 0, <<"END", "");
Z80 Module Assembler $version
(c) InterLogic 1993-2009, Paulo Custodio 2011-2020

Usage:
  z80asm [options] { \@<modulefile> | <filename> }

  [] = optional, {} = may be repeated, | = OR clause.

  To assemble 'fred.asm' use 'fred' or 'fred.asm'

  <modulefile> contains list of file names of all modules to be linked,
  one module per line.

  File types recognized or created by z80asm:
    .asm   = source file
    .o     = object file
    .lis   = list file
    .bin   = Z80 binary file
    .sym   = symbols file
    .map   = map file
    .reloc = reloc file
    .def   = global address definition file
    .err   = error file

Help Options:
  -h                     Show help options
  -v                     Be verbose

Code Generation Options:
  -mz80n                 Assemble for the Z80 variant of ZX Next
  -mz80                  Assemble for the Z80
  -mgbz80                Assemble for the GameBoy Z80
  -m8080                 Assemble for the 8080 (with Zilog or Intel mnemonics)
  -m8085                 Assemble for the 8085 (with Zilog or Intel mnemonics)
  -mz180                 Assemble for the Z180
  -mr2k                  Assemble for the Rabbit 2000
  -mr3k                  Assemble for the Rabbit 3000
  -mti83plus             Assemble for the TI83Plus
  -mti83                 Assemble for the TI83
  -IXIY                  Swap IX and IY registers
  -opt-speed             Optimize for speed
  -debug                 Add debug info to map file

Environment:
  -IPATH                 Add directory to include search path
  -LPATH                 Add directory to library search path
  -DSYMBOL[=VALUE]       Define a static symbol

Libraries:
  -xFILE                 Create a library file.lib
  -lFILE                 Use library file.lib

Binary Output:
  -ODIR                  Output directory
  -oFILE                 Output binary file
  -b                     Assemble and link/relocate to file.bin
  -split-bin             Create one binary file per section
  -d                     Assemble only updated files
  -rADDR                 Relocate binary file to given address (decimal or hex)
  -R                     Create relocatable code
  -reloc-info            Geneate binary file relocation information
  -fBYTE                 Default value to fill in DEFS (decimal or hex)

Output File Options:
  -s                     Create symbol table file.sym
  -l                     Create listing file.lis
  -m                     Create address map file.map
  -g                     Create global definition file.def

Appmake Options:
  +zx81                  Generate ZX81 .P file, origin at 16514
  +zx                    Generate ZX Spectrum .tap file, origin defaults to
                         23760 (in a REM), but can be set with -rORG >= 24000
                         for above RAMTOP
END

run("z80asm -h=x", 1, "", <<END);
Error: illegal option: -h=x
END

# make sure help fist in 80 columns
ok open(my $fh, "<", __FILE__), "open ".__FILE__;
while (<$fh>) {
	next if /^\s*\#/;
	chomp;
	if (length($_) > 80) {
		ok 0, "line $. longer than 80 chars";
	}
}

unlink_testfiles();
done_testing();
