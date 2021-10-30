
HDRS=$(wildcard *.h) $(wildcard $(ROOTDIR)/Engine/*.h)
SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=$(OUTDIR)/%.o)

MKFIL=\
    Makefile \
    $(ROOTDIR)/Build/common.mk \
    $(ROOTDIR)/Build/rules.mk

all: $(ROOTDIR)/Build/Lib/$(NAME).lib
.PHONY: all clean

$(OUTDIR):
	@$(MKDIR) "$(OUTDIR)"

$(ROOTDIR)/Build/Lib/$(NAME).lib: $(OBJS) $(OUTDIR)
	@echo $(NAME)
	@$(AS) -x$(ROOTDIR)/Build/Lib/$(NAME).lib $(OBJS)

$(OUTDIR)/%.o: %.c $(HDRS) $(OUTDIR) $(MKFIL)
	@echo $(NAME)/$<
	@$(CC) $(CFLAGS) -c -o "$@" "$<"

clean:
	@-$(RM) "$(ROOTDIR)/Build/Lib/$(NAME).lib"
	@-$(RMDIR) "$(OUTDIR)"
