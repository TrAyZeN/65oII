#include "cpu.h"
#include "instructions.h"
#include "stdio.h"
#include "stdlib.h"

#ifdef _WIN32
#include "Windows.h"
#else
#include "unistd.h"
#endif

struct registers regs;
byte mem[0x10000];
byte opcode;
byte *operand;

byte counter;

byte read_8() {
    return mem[regs.pc++];
}

word read_16() {
    return mem[regs.pc++] | (mem[regs.pc++] << 8);
}

void push(byte b) {
    mem[STACK_OFFSET + regs.sp++] = b;
}

void push_word(word w) {
    push(w & 0xFF);
    push(w >> 8);
}

byte pull() {
    return mem[STACK_OFFSET + regs.sp--];
}

void update_flag(byte val, byte flag) {
    if (val)
        regs.sr |= flag;
    else
        regs.sr &= ~flag;
}

byte is_flag_set(byte flag) {
    return regs.sr & flag;
}

byte *read_operand() {
    switch (addrmode_table[opcode]) {
    case ACC:
        return &regs.a;
    case ABS:
        return &mem[read_16()];
    case ABSX:
        return &mem[read_16() + regs.x];
    case ABSY:
        return &mem[read_16() + regs.y];
    case IMM:
        return &mem[regs.pc++];
    case IND:
        return &mem[mem[read_16()]];
    case XIND:
        return &mem[mem[read_8() + regs.x]];
    case INDY:
        return &mem[mem[read_8()] + regs.y];
    case REL:
        return &mem[regs.pc++];
    case ZPG:
        return &mem[read_8()];
    case ZPGX:
        return &mem[read_8() + regs.x];
    case ZPGY:
        return &mem[read_8() + regs.y];
    default:
        printf("Error : invalid addressing mode\n");
        exit(EXIT_FAILURE);
    }
}

void reset() {
    int i;

    regs.pc = RAM_OFFSET;
    regs.sp = 0;
    regs.sr = 0b00100000;
    counter = 0;

    for (i = 0; i < 64000; i++) {
        mem[i] = 0;
    }
}

void load_rom(const char *filename) {
    FILE *f;
    int op;

    regs.pc = RAM_OFFSET;

    f = fopen(filename, "rb");
    if (f == NULL) {
        printf("Error : Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    while ((op = fgetc(f)) != EOF) {
        mem[regs.pc++] = op;
    }

    fclose(f);

    regs.pc = RAM_OFFSET;
}

void run() {
    for (;;) {
        opcode = mem[regs.pc++];
        operand = read_operand();
        instructions_table[opcode]();

        // sleep(1.0 / CLOCK_SPEED);
    }
}
