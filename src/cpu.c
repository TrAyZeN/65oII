#include "cpu.h"
#include "instructions.h"

#include "stdlib.h"
#include "stdio.h"

#ifdef _WIN32
#include "Windows.h"
#else
#include "unistd.h"
#endif

byte read_8()
{
    return mem[PC++];
}

word read_16()
{
    return mem[PC++] | (mem[PC++] << 8);
}

void push(byte b)
{
    mem[STACK_OFFSET + SP++] = B;
}

void push_word(word w)
{
    push(w & 0xFF);
    push(w >> 8);
}

byte pull()
{
    return mem[STACK_OFFSET + SP--];
}

void update_flag(byte val, byte flag)
{
    if (val)
        SR |= flag;
    else
        SR &= ~flag;
}

byte is_flag_set(byte flag)
{
    return SR & flag;
}

byte *read_operand()
{
    switch (addrmode_table[opcode])
    {
        case  ACC:
            return &A;
        case  ABS:
            return &mem[read_16()];
        case ABSX:
            return &mem[read_16() + X];
        case ABSY:
            return &mem[read_16() + Y];
        case  IMM:
            return &mem[PC++];
        case  IND:
            return &mem[mem[read_16()]];
        case XIND:
            return &mem[mem[read_8() + X]];
        case INDY:
            return &mem[mem[read_8()] + Y];
        case  REL:
            return &mem[PC++];
        case  ZPG:
            return &mem[read_8()];
        case ZPGX:
            return &mem[read_8() + X];
        case ZPGY:
            return &mem[read_8() + Y];
    }
}

void reset()
{
    int i;

    PC = RAM_OFFSET;
    SP = 0;
    SR = 0b00100000;
    counter = 0;

    for (i = 0; i < 64000; i++)
        mem[i] = 0;
}

void load_ROM(const char *filename)
{
    FILE *f;
    char op;

    PC = RAM_OFFSET;

    f = fopen(filename, "rb");
    if (f == NULL)
    {
        printf("Error : Failed to open file");
        exit(EXIT_FAILURE);
    }

    while ((op = fgetc(f)) != EOF)
        mem[PC++] = op;

    fclose(f);

    PC = RAM_OFFSET;
}

void run()
{
    for (;;)
    {
        opcode = mem[PC++];
        operand = read_operand();
        instructions_table[opcode]();

        //sleep(1.0 / CLOCK_SPEED);
    }
}

