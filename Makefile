CC ?= gcc

CPPFLAGS += -MMD -I src
CFLAGS += -std=gnu99 -Wall -Wextra -Wshadow -Wdouble-promotion -Wundef \
	 -Wconversion -Wsign-conversion -Wformat=2 -funsigned-char
LDFLAGS +=

ifeq ($(ASAN),1)
	CFLAGS += -fsanitize=address
	LDFLAGS += -fsanitize=address
endif
ifeq ($(UBSAN),1)
	CFLAGS += -fsanitize=undefined
	LDFLAGS += -fsanitize=undefined
endif

BUILDDIR ?= build
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
	$(CC) -I disassembler $(CFLAGS) disassembler/disassembler.c -o $@

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
	clang-format --style=file -i src/**.[ch] disassembler/**.[ch]

-include $(DEPS)
