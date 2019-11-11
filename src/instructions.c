#include "instructions.h"
#include "cpu.h"

#include "stdlib.h"
#include "stdio.h"

void ADC()
{
    if (A + operand > 0xFF)
        set_flag(C);
    else
        unset_flag(C);

    A += operand;

    if (A == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (A <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void AND()
{
    A &= operand;

    if (A == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (A <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void ASL()
{
    switch (opcode)
    {
        case 0x0A:
        break;
        case 0x06:
        break;
        case 0x16:
        break;
        case 0x0E:
        break;
        case 0x1E:
        break;
    }
}

INLINE void BCC()
{
    if (!is_flag_set(C))
        PC = PC + (char) mem[PC];
    else
        PC++;
}

INLINE void BCS()
{
    if (is_flag_set(C))
        PC = PC + (char) mem[PC];
    else
        PC++;
}

INLINE void BEQ()
{
    if (is_flag_set(Z))
        PC = PC + (char) mem[PC];
    else
        PC++;
}

INLINE void BIT()
{

}

INLINE void BMI()
{
    if (is_flag_set(N))
        PC = PC + (char) mem[PC];
    else
        PC++;
}

INLINE void BNE()
{
    if (!is_flag_set(Z))
        PC = PC + (char) mem[PC];
    else
        PC++;
}

INLINE void BPL()
{
    if (!is_flag_set(N))
        PC = PC + (char) mem[PC];
    else
        PC++;
}

INLINE void BRK()
{
    set_flag(I);
    push(PC+2);
    push(SR);
    PC = mem[0xFFFE] | (mem[0xFFFF] << 8);
}

INLINE void BVC()
{
    if (!is_flag_set(V))
        PC = PC + (char) mem[PC];
    else
        PC++;
}

INLINE void BVS()
{
    if (is_flag_set(V))
        PC = PC + (char) mem[PC];
    else
        PC++;
}

INLINE void CLC()
{
    unset_flag(C);
}

INLINE void CLD()
{
    unset_flag(D);
}

INLINE void CLI()
{
    unset_flag(I);
}

INLINE void CLV()
{
    unset_flag(V);
}

// TODO: carry flag
INLINE void CMP()
{
    byte r;
    r = A - operand;

    if (r == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (r <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void CPX()
{
    byte r;
    r = X - operand;

    if (r == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (r <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void CPY()
{
    byte r;
    r = Y - operand;

    if (r == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (r <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void DEC()
{
    switch (opcode)
    {
        case 0xC6:
        break;
        case 0xD6:
        break;
        case 0xCE:
        break;
        case 0xDE:
        break;
    }
}

INLINE void DEX()
{
    X--;

    if (X == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (X <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void DEY()
{
    Y--;

    if (Y == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (Y <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void INC()
{
    switch (opcode)
    {
        case 0xE6:
        break;
        case 0xF6:
        break;
        case 0xEE:
        break;
        case 0xFE:
        break;
    }
}

INLINE void INX()
{
    X++;

    if (X == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (X <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void INY()
{
    Y++;

    if (Y == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (Y <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void JMP()
{
    word p;
    switch (opcode)
    {
        case 0x4C:
            PC = mem[read_16()];
        break;
        case 0x6C:
            p = read_16();
            PC = mem[mem[p] | (mem[p+1] << 8)];
        break;
    }
}

INLINE void JSR()
{
    push_word(PC+2);
    PC = mem[read_16()];
}

INLINE void LDA()
{
    A = operand;

    if (A == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (A <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void LDX()
{
    X = operand;

    if (X == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (X <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void LDY()
{
    Y = operand;

    if (Y == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (Y <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void LSR()
{

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

INLINE void PLA()
{
    A = pull();

    if (A == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (A <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void PLP()
{
    SR = pull();
}

INLINE void SEC()
{
    set_flag(C);
}

INLINE void SED()
{
    set_flag(D);
}

INLINE void SEI()
{
    set_flag(I);
}

INLINE void STA()
{
    switch (opcode)
    {
        case 0x85:
            mem[read_8()] = A;
        break;
        case 0x95:
            mem[read_8() + X] = A;
        break;
        case 0x8D:
            mem[read_16()] = A;
        break;
        case 0x9D:
            mem[read_16() + X] = A;
        break;
        case 0x99:
            mem[read_16() + Y] = A;
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
            mem[read_16() + Y] = X;
        break;
        case 0x8E:
            mem[read_16()] = X;
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
            mem[read_16() + X] = Y;
        break;
        case 0x8C:
            mem[read_16()] = Y;
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

