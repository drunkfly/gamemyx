
CC:=$(ROOTDIR)/tools/z88dk/bin/zcc
AS:=$(ROOTDIR)/tools/z88dk/bin/z80asm
LD:=$(ROOTDIR)/tools/z88dk/bin/zcc

CFLAGS:=+zxn -I$(ROOTDIR)/Engine -clib=sdcc_iy -startup=4 --opt-code-size
LDFLAGS:=$(CFLAGS) -m -create-app -subtype=nex

ifeq ($(OS),Windows_NT)
CP:=copy /b
RM:=del /F/Q
MKDIR:=mkdir
RMDIR:=rmdir /S/Q
else
CP:=cp
RM:=rm -f
MKDIR:=mkdir -p
RMDIR:=rm -rf
endif
