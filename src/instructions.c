#include "instructions.h"
#include "cpu.h"

#include "stdlib.h"
#include "stdio.h"

INLINE void ADC()
{
    update_flag((A + C + (*operand)) > 0xFF, C);

    A += (*operand);

    update_flag(A == 0x00, Z);
    update_flag(A <= 0x7F, N);
}

INLINE void AND()
{
    A &= (*operand);

    update_flag(A == 0x00, Z);
    update_flag(A <= 0x7F, N);
}

INLINE void ASL()
{
    update_flag((*operand) & 0b10000000, C);

    *operand <<= 1;

    update_flag((*operand) == 0x00, Z);
    update_flag((*operand) <= 0x7F, N);
}

INLINE void BCC()
{
    if (!is_flag_set(C))
        PC = PC + (char) (*operand);
}

INLINE void BCS()
{
    if (is_flag_set(C))
        PC = PC + (char) (*operand);
}

INLINE void BEQ()
{
    if (is_flag_set(Z))
        PC = PC + (char) (*operand);
}

INLINE void BIT()
{

}

INLINE void BMI()
{
    if (is_flag_set(N))
        PC = PC + (char) (*operand);
}

INLINE void BNE()
{
    if (!is_flag_set(Z))
        PC = PC + (char) (*operand);
}

INLINE void BPL()
{
    if (!is_flag_set(N))
        PC = PC + (char) (*operand);
}

INLINE void BRK()
{
    update_flag(1, I);
    push(PC+2);
    push(SR);
    PC = mem[0xFFFE] | (mem[0xFFFF] << 8);
}

INLINE void BVC()
{
    if (!is_flag_set(V))
        PC = PC + (char) (*operand);
}

INLINE void BVS()
{
    if (is_flag_set(V))
        PC = PC + (char) (*operand);
}

INLINE void CLC()
{
    update_flag(0, C);
}

INLINE void CLD()
{
    update_flag(0, D);
}

INLINE void CLI()
{
    update_flag(0, I);
}

INLINE void CLV()
{
    update_flag(0, V);
}

// TODO: carry flag
INLINE void CMP()
{
    byte r;
    r = A - (*operand);

    update_flag(r == 0x00, Z);
    update_flag(r <= 0x7F, N);
}

INLINE void CPX()
{
    byte r;
    r = X - (*operand);

    update_flag(r == 0x00, Z);
    update_flag(r <= 0x7F, N);
}

INLINE void CPY()
{
    byte r;
    r = Y - (*operand);

    update_flag(r == 0x00, Z);
    update_flag(r <= 0x7F, N);
}

INLINE void DEC()
{
    (*operand)--;

    update_flag((*operand) == 0x00, Z);
    update_flag((*operand) <= 0x7F, N);
}

INLINE void DEX()
{
    X--;

    update_flag(X == 0x00, Z);
    update_flag(X <= 0x7F, N);
}

INLINE void DEY()
{
    Y--;

    update_flag(Y == 0x00, Z);
    update_flag(Y <= 0x7F, N);
}

INLINE void EOR()
{
    A ^= (*operand);

    update_flag(A == 0x00, Z);
    update_flag(A <= 0x7F, N);
}

INLINE void INC()
{
    (*operand)++;

    update_flag((*operand) == 0x00, Z);
    update_flag((*operand) <= 0x7F, N);
}

INLINE void INX()
{
    X++;

    update_flag(X == 0x00, Z);
    update_flag(X <= 0x7F, N);
}

INLINE void INY()
{
    Y++;

    update_flag(Y == 0x00, Z);
    update_flag(Y <= 0x7F, N);
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

    update_flag(A == 0x00, Z);
    update_flag(A <= 0x7F, N);
}

INLINE void LDX()
{
    X = (*operand);

    update_flag(X == 0x00, Z);
    update_flag(X <= 0x7F, N);
}

INLINE void LDY()
{
    Y = (*operand);

    update_flag(Y == 0x00, Z);
    update_flag(Y <= 0x7F, N);
}

INLINE void LSR()
{
    update_flag((*operand) & 0b00000001, C);

    *operand >>= 1;

    update_flag((*operand) == 0x00, Z);
    update_flag((*operand) <= 0x7F, N);
}

INLINE void NOP() {}

INLINE void ORA()
{
    A |= (*operand);

    update_flag(A == 0x00, Z);
    update_flag(A <= 0x7F, N);
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

    update_flag(A == 0x00, Z);
    update_flag(A <= 0x7F, N);
}

INLINE void PLP()
{
    SR = pull();
}

INLINE void RTI()
{
    SR = pull();
    PC = pull();
}

INLINE void RTS()
{
    PC = pull();
    PC++;
}

INLINE void SBC()
{

}

INLINE void SEC()
{
    update_flag(1, C);
}

INLINE void SED()
{
    update_flag(1, D);
}

INLINE void SEI()
{
    update_flag(1, I);
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

    update_flag(X == 0x00, Z);
    update_flag(X <= 0x7F, N);
}

INLINE void TAY()
{
    Y = A;

    update_flag(Y == 0x00, Z);
    update_flag(Y <= 0x7F, N);
}

INLINE void TSX()
{
    X = SP;

    update_flag(X == 0x00, Z);
    update_flag(X <= 0x7F, N);
}

INLINE void TXA()
{
    A = X;

    update_flag(A == 0x00, Z);
    update_flag(A <= 0x7F, N);
}

INLINE void TXS()
{
    SP = X;
}

INLINE void TYA()
{
    A = Y;

    update_flag(A == 0x00, Z);
    update_flag(A <= 0x7F, N);
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

