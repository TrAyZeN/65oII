#include "cpu.h"
#include "instructions.h"

#include "stdio.h"

#ifdef _WIN32
#include "Windows.h"
#else
#include "unistd.h"
#endif

void (* instructions_table[256])() =
{
//        00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F
/* 00 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* 10 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, CLC, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* 20 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* 30 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, SEC, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* 40 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* 50 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, CLI, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* 60 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* 70 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, SEI, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* 80 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* 90 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* A0 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* B0 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* C0 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* D0 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, CLD, NIP, NIP, NIP, NIP, NIP, NIP, NIP,
/* E0 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, NOP, NIP, NIP, NIP, NIP, NIP,
/* F0 */ NIP, NIP, NIP, NIP, NIP, NIP, NIP, NIP, SED, NIP, NIP, NIP, NIP, NIP, NIP, NIP
};

void reset()
{
    PC = RAM_OFFSET;
    SP = 0;
    SR = 0;
    counter = 0;
    // reset memory
}

void loadROM(const char *filename)
{
    FILE *f;
    char op;

    PC = RAM_OFFSET;

    f = fopen(filename, "rb");
    while ((op = fgetc(f)) != EOF)
    {
        mem[PC++] = op;
    }

    fclose(f);

    PC = RAM_OFFSET;
}

void run()
{
    for (;;)
    {
        opcode = mem[PC++];
        instructions_table[opcode];

        sleep(1.0 / CLOCK_SPEED);
    }
}

