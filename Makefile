CPPFLAGS := -I include
CFLAGS := -Wall -Wextra 
LDFLAGS :=

BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
BINDIR := $(BUILDDIR)/bin

EMU_SRCS := src/cpu.c \
			src/instructions.c \
			src/main.c \
			src/table.c \
			src/utils.c \
			src/debug.c

EMU_OBJS := $(EMU_SRCS:%.c=$(OBJDIR)/%.o)

.PHONY: all
all: $(BINDIR)/emulator $(BINDIR)/disassembler

$(BINDIR)/emulator: $(EMU_OBJS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $(EMU_OBJS) -o $@

$(BINDIR)/disassembler:
	@mkdir -p $(@D)
	$(CC) disassembler/disassembler.c -o $@ -I disassembler

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJDIR)

.PHONY: mrproper
mrproper:
	rm -rf $(BUILDDIR)

.PHONY: fmt
fmt:
	clang-format --style=file -i src/**.[ch] include/**.h disassembler/**.[ch]
