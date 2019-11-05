#include "instructions.h"
#include "cpu.h"

#include "stdlib.h"
#include "stdio.h"

void ADC()
{
    if (opcode == 0x69)
    {
        
    }
}

INLINE void BCC()
{
    if (SR & 0b00000001 == 0)
        PC = mem[PC];
}

INLINE void BCS()
{
    if (SR & 0b00000001 == 1)
        PC = mem[PC];
}

INLINE void BEQ()
{
    if (SR & 0b00000010 == 1)
        PC = mem[PC];
}

void BIT();         // Test Bits in Memory with Accumulator

INLINE void BMI()
{
    if (SR & 0b10000000 == 1)
        PC = mem[PC];
}

INLINE void BNE()
{
    if (SR & 0b00000010 == 0)
        PC = mem[RAM_OFFSET + PC];
}

INLINE void BPL()
{
    if (SR & 0b10000000 == 0)
        PC = mem[PC];
}

INLINE void CLC()
{
    SR &= 0b11111110;
}

INLINE void CLD()
{
    SR &= 0b11110111;
}

INLINE void CLI()
{
    SR &= 0b11111011;
}

INLINE void CLV()
{
    SR &= 0b10111111;
}

INLINE void DEY()
{
    Y--;
    if (Y == 0x00)
        SR |= 0b00000010;
    else
        SR &= 0b11111101;

    if (Y <= 0x7F)
        SR &= 0b01111111;
    else
        SR |= 0b10000000;
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
        SR |= 0b00000010;
    else
        SR &= 0b11111101;

    if (A <= 0x7F)
        SR &= 0b01111111;
    else
        SR |= 0b10000000;
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
        SR |= 0b00000010;
    else
        SR &= 0b11111101;

    if (Y <= 0x7F)
        SR &= 0b01111111;
    else
        SR |= 0b10000000;
}

INLINE void NOP() {}

INLINE void PHA()
{
    mem[STACK_OFFSET + SP++] = A;
}

INLINE void PHP()
{
    mem[STACK_OFFSET + SP++] = SR;
}

INLINE void SEC()
{
    SR |= 0b00000001;
}

INLINE void SED()
{
    SR |= 0b00001000;
}

INLINE void SEI()
{
    SR |= 0b00000100;
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

