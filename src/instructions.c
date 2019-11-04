#include "instructions.h"
#include "cpu.h"

void ADC()
{
    
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
        PC = mem[PC];
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

void NIP() {}

