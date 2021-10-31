
HDRS=\
    $(wildcard *.h) \
    $(wildcard Platform/ZXNext/*.h) \
    $(wildcard $(ROOTDIR)/Engine/*.h)

SRCS=\
    $(wildcard *.c) \
    $(wildcard Platform/ZXNext/*.c)

ASMS=\
    $(wildcard Platform/ZXNext/*.asm)

OBJS=\
    $(SRCS:%.c=$(OUTDIR)/%.c.o) \
    $(ASMS:%.asm=$(OUTDIR)/%.asm.o)

MKFIL=\
    Makefile \
    $(ROOTDIR)/Build/common.mk \
    $(ROOTDIR)/Build/rules.mk

all: $(ROOTDIR)/Build/Lib/$(NAME).lib
.PHONY: all clean

$(OUTDIR):
	@$(MKDIR) "$(OUTDIR)"

$(ROOTDIR)/Build/Lib/$(NAME).lib: $(OBJS) $(OUTDIR)
	@echo $(NAME).lib
	@$(AS) -x$(ROOTDIR)/Build/Lib/$(NAME).lib $(OBJS)

$(OUTDIR)/%.c.o: %.c $(HDRS) $(OUTDIR) $(MKFIL)
	@echo $(NAME)/$<
	@$(CC) $(CFLAGS) -c -o "$@" "$<"
	@$(CC) $(CFLAGS) -S -o "$@.asm" "$<"

$(OUTDIR)/%.asm.o: %.asm $(OUTDIR) $(MKFIL)
	@echo $(NAME)/$<
	@$(CC) $(CFLAGS) -c -o "$@" "$<"

clean:
	@-$(RM) "$(ROOTDIR)/Build/Lib/$(NAME).lib"
	@-$(RMDIR) "$(OUTDIR)"
