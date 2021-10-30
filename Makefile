
NAME:=MyxDemo

MAKEFILE:=$(abspath $(lastword $(MAKEFILE_LIST)))
ROOTDIR:=$(patsubst %/,%,$(dir $(MAKEFILE)))
OUTDIR:=$(ROOTDIR)/Build

include Build/common.mk
.PHONY: all engine game tools clean

all: $(OUTDIR)/Sync/Build/$(NAME).nex

$(OUTDIR)/Bin:
	@$(MKDIR) "$(OUTDIR)/Bin"

$(OUTDIR)/Lib:
	@$(MKDIR) "$(OUTDIR)/Lib"

$(OUTDIR)/Bin/$(NAME).nex: $(OUTDIR)/Bin engine game tools
	@echo $(NAME).nex
	@$(LD) $(LDFLAGS) -o "$(OUTDIR)/Bin/$(NAME)" "-L$(OUTDIR)/Lib" -lgame -lengine Engine/main.c

$(OUTDIR)/Sync/Build/$(NAME).nex: $(OUTDIR)/Bin/$(NAME).nex
	@rem FIXME slashes on POSIX
	@$(CP) $(subst /,\\,$<) $(subst /,\\,$@)

engine: $(OUTDIR)/Lib
	@$(MAKE) -s -C Engine "ROOTDIR=$(ROOTDIR)"

game: $(OUTDIR)/Lib
	@$(MAKE) -s -C Game "ROOTDIR=$(ROOTDIR)"

tools: $(OUTDIR)/Lib
	@$(MAKE) -s -C Tools "ROOTDIR=$(ROOTDIR)"

clean:
	@-$(RM) "$(OUTDIR)/Sync/Build/$(NAME).nex"
	@-$(RMDIR) "$(OUTDIR)/Bin"
	@-$(RMDIR) "$(OUTDIR)/Lib"
	@-$(MAKE) -s -C Engine "ROOTDIR=$(ROOTDIR)" clean
	@-$(MAKE) -s -C Game "ROOTDIR=$(ROOTDIR)" clean
	@-$(MAKE) -s -C Tools "ROOTDIR=$(ROOTDIR)" clean
