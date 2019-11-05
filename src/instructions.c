#include "instructions.h"
#include "cpu.h"

#include "stdlib.h"
#include "stdio.h"

// Stack operations
INLINE void push(byte B)
{
    mem[STACK_OFFSET + SP++] = B;
}

// Flag operations
INLINE void set_N()
{
    SR |= 0b10000000;
}

INLINE void unset_N()
{
    SR &= 0b01111111;
}

INLINE void set_V()
{
    SR |= 0b01000000;
}

INLINE void unset_V()
{
    SR &= 0b10111111;
}

INLINE void set_B()
{
    SR |= 0b00010000;
}

INLINE void unset_B()
{
    SR &= 0b11101111;
}

INLINE void set_D()
{
    SR |= 0b00001000;
}

INLINE void unset_D()
{
    SR &= 0b11110111;
}

INLINE void set_I()
{
    SR |= 0b00000100;
}

INLINE void unset_I()
{
    SR &= 0b11111011;
}

INLINE void set_Z()
{
    SR |= 0b00000010;
}

INLINE void unset_Z()
{
    SR &= 0b11111101;
}

INLINE void set_C()
{
    SR |= 0b00000001;
}

INLINE void unset_C()
{
    SR &= 0b11111110;
}

void ADC()
{
    if (opcode == 0x69)
    {
        
    }
}

INLINE void BCC()
{
    if (SR & 0b00000001 == 0)
        PC = PC + (char) mem[PC];
    else
        PC++;
}

INLINE void BCS()
{
    if (SR & 0b00000001 == 1)
        PC = PC + (char) mem[PC];
    else
        PC++;
}

INLINE void BEQ()
{
    if (SR & 0b00000010 == 1)
        PC = PC + (char) mem[PC];
    else
        PC++;
}

void BIT();         // Test Bits in Memory with Accumulator

INLINE void BMI()
{
    if (SR & 0b10000000 == 1)
        PC = PC + (char) mem[PC];
    else
        PC++;
}

INLINE void BNE()
{
    if (SR & 0b00000010 == 0)
        PC = PC + (char) mem[PC];
    else
        PC++;
}

INLINE void BPL()
{
    if (SR & 0b10000000 == 0)
        PC = PC + (char) mem[PC];
    else
        PC++;
}

INLINE void BRK()
{
    SR |= 0b00000100;   // Set interrupt flag
    push(PC+2);
    push(SR);
}

INLINE void CLC()
{
    unset_C();
}

INLINE void CLD()
{
    unset_D();
}

INLINE void CLI()
{
    unset_I();
}

INLINE void CLV()
{
    unset_V();
}

INLINE void DEY()
{
    Y--;
    if (Y == 0x00)
        set_Z();
    else
        unset_Z();

    if (Y <= 0x7F)
        unset_N();
    else
        set_N();
}

INLINE void JMP()
{
    word p;
    switch (opcode)
    {
        case 0x4C:
            PC = mem[mem[PC] | (mem[PC+1] << 8)];
        break;
        case 0x6C:
            p = mem[PC] | (mem[PC+1] << 8);
            PC = mem[mem[p] | (mem[p+1] << 8)];
        break;
    }
}

INLINE void LDA()
{
    switch (opcode)
    {
        case 0xA9:
            A = mem[PC++];
        break;
        case 0xA5:
            A = mem[mem[PC++]];
        break;
        case 0xB5:
            A = A;
        break;
        case 0xAD:
            A = mem[mem[PC] | (mem[PC+1] << 8)];
            PC += 2;
        break;
        case 0xBD:
            A = A;
        break;
        case 0xB9:
            A = A;
        break;
        case 0xA1:
            A = A;
        break;
        case 0xB1:
            A = A;
        break;
    }

    if (A == 0x00)
        set_Z();
    else
        unset_Z();

    if (A <= 0x7F)
        unset_N();
    else
        set_N();
}

INLINE void LDX()
{
    switch (opcode)
    {
        case 0xA2:
            X = mem[PC++];
        break;
        case 0xA6:
            X = mem[mem[PC++]];
        break;
        case 0xB6:
            X = X;
        break;
        case 0xAE:
            X = mem[mem[PC] | (mem[PC+1] << 8)];
            PC += 2;
        break;
        case 0xBE:
            X = X;
        break;
    }

    if (X == 0x00)
        set_Z();
    else
        unset_Z();

    if (X <= 0x7F)
        unset_N();
    else
        set_N();
}

INLINE void LDY()
{
    switch (opcode)
    {
        case 0xA0:
            Y = mem[PC++];
        break;
        case 0xA4:
            Y = mem[mem[PC++]];
        break;
        case 0xB4:
            Y = Y;
        break;
        case 0xAC:
            Y = mem[mem[PC] | (mem[PC+1] << 8)];
            PC += 2;
        break;
        case 0xBC:
            Y = Y;
        break;
    }

    if (Y == 0x00)
        set_Z();
    else
        unset_Z();

    if (Y <= 0x7F)
        unset_N();
    else
        set_N();
}

INLINE void NOP() {}

INLINE void PHA()
{
    push(A);
}

INLINE void PHP()
{
    push(SR);
}

INLINE void SEC()
{
    set_C();
}

INLINE void SED()
{
    set_D();
}

INLINE void SEI()
{
    set_I();
}

INLINE void STA()
{
    switch (opcode)
    {
        case 0x85:
            mem[mem[PC++]] = A;
        break;
        case 0x95:
        break;
        case 0x8D:
            mem[mem[PC] | (mem[PC+1] << 8)] = A;
            PC += 2;
        break;
        case 0x9D:
        break;
        case 0x99:
        break;
        case 0x81:
        break;
        case 0x91:
        break;
    }
}

INLINE void STX()
{
    switch (opcode)
    {
        case 0x86:
            mem[PC++] = X;
        break;
        case 0x96:
        break;
        case 0x8E:
            mem[mem[PC] | (mem[PC+1] << 8)] = X;
            PC += 2;
        break;
    }
}

INLINE void STY()
{
    switch (opcode)
    {
        case 0x84:
            mem[PC++] = Y;
        break;
        case 0x94:
        break;
        case 0x8C:
            mem[mem[PC] | (mem[PC+1] << 8)] = Y;
            PC += 2;
        break;
    }
}

void NIP()
{
    printf("Not Implemented Operation : %02X\n", opcode);
    exit(EXIT_FAILURE);
}

void IOP()
{
    printf("Invalid Operation : %02X\n", opcode);
    printf("PC : $%04X\n", PC);
    exit(EXIT_FAILURE);
}

