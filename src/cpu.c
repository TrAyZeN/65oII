#include "cpu.h"
#include "instructions.h"

#include "stdlib.h"
#include "stdio.h"

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

byte read_8()
{
    return mem[regs.PC++];
}

word read_16()
{
    return mem[regs.PC++] | (mem[regs.PC++] << 8);
}

void push(byte b)
{
    mem[STACK_OFFSET + regs.SP++] = b;
}

void push_word(word w)
{
    push(w & 0xFF);
    push(w >> 8);
}

byte pull()
{
    return mem[STACK_OFFSET + regs.SP--];
}

void update_flag(byte val, byte flag)
{
    if (val)
        regs.SR |= flag;
    else
        regs.SR &= ~flag;
}

byte is_flag_set(byte flag)
{
    return regs.SR & flag;
}

byte *read_operand()
{
    switch (addrmode_table[opcode])
    {
        case  ACC:
            return &regs.A;
        case  ABS:
            return &mem[read_16()];
        case ABSX:
            return &mem[read_16() + regs.X];
        case ABSY:
            return &mem[read_16() + regs.Y];
        case  IMM:
            return &mem[regs.PC++];
        case  IND:
            return &mem[mem[read_16()]];
        case XIND:
            return &mem[mem[read_8() + regs.X]];
        case INDY:
            return &mem[mem[read_8()] + regs.Y];
        case  REL:
            return &mem[regs.PC++];
        case  ZPG:
            return &mem[read_8()];
        case ZPGX:
            return &mem[read_8() + regs.X];
        case ZPGY:
            return &mem[read_8() + regs.Y];
    default:
        printf("Error : invalid addressing mode\n");
        exit(EXIT_FAILURE);
    }
}

void reset()
{
    int i;

    regs.PC = RAM_OFFSET;
    regs.SP = 0;
    regs.SR = 0b00100000;
    counter = 0;

    for (i = 0; i < 64000; i++) {
        mem[i] = 0;
    }
}

void load_ROM(const char *filename)
{
    FILE *f;
    int op;

    regs.PC = RAM_OFFSET;

    f = fopen(filename, "rb");
    if (f == NULL)
    {
        printf("Error : Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    while ((op = fgetc(f)) != EOF) {
        mem[regs.PC++] = op;
    }

    fclose(f);

    regs.PC = RAM_OFFSET;
}

void run()
{
    for (;;)
    {
        opcode = mem[regs.PC++];
        operand = read_operand();
        instructions_table[opcode]();

        //sleep(1.0 / CLOCK_SPEED);
    }
}
