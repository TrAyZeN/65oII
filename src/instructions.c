#include "instructions.h"
#include "cpu.h"

#include "stdlib.h"
#include "stdio.h"

void ADC()
{
    if (A + C + (*operand) > 0xFF)
        set_flag(C);
    else
        unset_flag(C);

    A += (*operand);

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
    A &= (*operand);

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
    if ((*operand) & 0b10000000)
        set_flag(C);
    else
        unset_flag(C);

    *operand <<= 1;

    if ((*operand) == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if ((*operand) <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
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
    r = A - (*operand);

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
    r = X - (*operand);

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
    r = Y - (*operand);

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
    (*operand)--;

    if (*operand == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (*operand <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
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

INLINE void EOR()
{
    A ^= (*operand);

    if (A == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (A <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);

}

INLINE void INC()
{
    (*operand)++;

    if (*operand == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (*operand <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
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
    PC = (*operand);
}

INLINE void JSR()
{
    push_word(PC+2);
    PC = (*operand);
}

INLINE void LDA()
{
    A = (*operand);

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
    X = (*operand);

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
    Y = (*operand);

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
    if ((*operand) & 0b00000001)
        set_flag(C);
    else
        unset_flag(C);

    *operand >>= 1;

    if ((*operand) == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if ((*operand) <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);

}

INLINE void NOP() {}

INLINE void ORA()
{
    A |= (*operand);

    if (A == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (A <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);

}

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
    *operand = A;
}

INLINE void STX()
{
    *operand = X;
}

INLINE void STY()
{
    *operand = Y;
}

INLINE void TAX()
{
    X = A;

    if (X == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (X <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void TAY()
{
    Y = A;

    if (Y == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (Y <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void TSX()
{
    X = SP;

    if (X == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (X <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void TXA()
{
    A = X;

    if (A == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (A <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
}

INLINE void TXS()
{
    SP = X;
}

INLINE void TYA()
{
    A = Y;

    if (A == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (A <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
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

