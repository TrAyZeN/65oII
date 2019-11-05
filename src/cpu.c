#include "cpu.h"
#include "instructions.h"

#include "stdlib.h"
#include "stdio.h"

#ifdef _WIN32
#include "Windows.h"
#else
#include "unistd.h"
#endif

void (* instructions_table[256])() =
{
//        00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F
/* 00 */ NIP, NIP, IOP, IOP, IOP, NIP, NIP, IOP, NIP, NIP, NIP, IOP, IOP, NIP, NIP, IOP,
/* 10 */ BPL, NIP, IOP, IOP, IOP, NIP, NIP, IOP, CLC, NIP, IOP, IOP, IOP, NIP, NIP, IOP,
/* 20 */ NIP, NIP, IOP, IOP, NIP, NIP, NIP, IOP, NIP, NIP, NIP, IOP, NIP, NIP, NIP, IOP,
/* 30 */ BMI, NIP, IOP, IOP, IOP, NIP, NIP, IOP, SEC, NIP, IOP, IOP, IOP, NIP, NIP, IOP,
/* 40 */ NIP, NIP, IOP, IOP, IOP, NIP, NIP, IOP, NIP, NIP, NIP, IOP, NIP, NIP, NIP, IOP,
/* 50 */ NIP, NIP, IOP, IOP, IOP, NIP, NIP, IOP, CLI, NIP, IOP, IOP, IOP, NIP, NIP, IOP,
/* 60 */ NIP, NIP, IOP, IOP, IOP, NIP, NIP, IOP, NIP, NIP, NIP, IOP, NIP, NIP, NIP, IOP,
/* 70 */ NIP, NIP, IOP, IOP, IOP, NIP, NIP, IOP, SEI, NIP, IOP, IOP, IOP, NIP, NIP, IOP,
/* 80 */ IOP, STA, IOP, IOP, NIP, STA, NIP, IOP, DEY, IOP, NIP, IOP, NIP, STA, NIP, IOP,
/* 90 */ BCC, STA, IOP, IOP, NIP, STA, NIP, IOP, NIP, STA, NIP, IOP, IOP, STA, IOP, IOP,
/* A0 */ LDY, LDA, NIP, IOP, LDY, LDA, NIP, IOP, NIP, LDA, NIP, IOP, LDY, LDA, NIP, IOP,
/* B0 */ BCS, LDA, IOP, IOP, LDY, LDA, NIP, IOP, NIP, LDA, NIP, IOP, LDY, LDA, NIP, IOP,
/* C0 */ NIP, NIP, IOP, IOP, NIP, NIP, NIP, IOP, NIP, NIP, NIP, IOP, NIP, NIP, NIP, IOP,
/* D0 */ BNE, NIP, IOP, IOP, IOP, NIP, NIP, IOP, CLD, NIP, IOP, IOP, IOP, NIP, NIP, IOP,
/* E0 */ NIP, NIP, IOP, IOP, NIP, NIP, NIP, IOP, NIP, NIP, NOP, IOP, NIP, NIP, NIP, IOP,
/* F0 */ BEQ, NIP, IOP, IOP, IOP, NIP, NIP, IOP, SED, NIP, IOP, IOP, IOP, NIP, NIP, IOP
};

unsigned char instructions_cycles[256] =
{

//        00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F
/* 00 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 10 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 20 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 30 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 40 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 50 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 60 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 70 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 80 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 90 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* A0 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* B0 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* C0 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* D0 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* E0 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* F0 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0
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
    if (f == NULL)
    {
        printf("Error : Failed to open file");
        exit(EXIT_FAILURE);
    }

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
        instructions_table[opcode]();

        sleep(1.0 / CLOCK_SPEED);
    }
}

