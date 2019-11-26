#include "instructions.h"
#include "cpu.h"

#include "utils.h"
#include "stdlib.h"
#include "stdio.h"

void ADC()
{
    int i;
    byte a, b, cin, cout;
    cin = is_flag_set(C);

    if (is_flag_set(D))
        for (i = 0; i < 2; i++)
        {
            a = (A & 0xF << i*4) >> i*4;
            b = ((*operand) & 0xF << i*4) >> i*4;

            byte r = a + b + cin + 6;   // simple addition and + 6 to convert back to BCD
            cout = r & 0x10;

            A = (A | 0xF << i*4) & (r & 0xF) << i*4;

            cin = cout;
        }
    else
        A = full_adder(A, (*operand), &cin);

    update_flag(cin, C);
    update_flag(!A, Z);
    update_flag(A >> 7, N);
}

void AND()
{
    A &= (*operand);

    update_flag(!A, Z);
    update_flag(A >> 7, N);
}

void ASL()
{
    update_flag((*operand) >> 7, C);

    *operand <<= 1;

    update_flag(!(*operand), Z);
    update_flag((*operand) >> 7, N);
}

void BCC()
{
    if (!is_flag_set(C))
        PC = PC + (char) (*operand);
}

void BCS()
{
    if (is_flag_set(C))
        PC = PC + (char) (*operand);
}

void BEQ()
{
    if (is_flag_set(Z))
        PC = PC + (char) (*operand);
}

void BIT()
{
    update_flag((*operand) & 0b10000000, N);
    update_flag((*operand) & 0b01000000, V);
    update_flag(((*operand) & A) == 0x00, Z);
}

void BMI()
{
    if (is_flag_set(N))
        PC = PC + (char) (*operand);
}

void BNE()
{
    if (!is_flag_set(Z))
        PC = PC + (char) (*operand);
}

void BPL()
{
    if (!is_flag_set(N))
        PC = PC + (char) (*operand);
}

void BRK()
{
    update_flag(1, I);
    push(PC+2);
    push(SR);
    PC = mem[0xFFFE] | (mem[0xFFFF] << 8);
}

void BVC()
{
    if (!is_flag_set(V))
        PC = PC + (char) (*operand);
}

void BVS()
{
    if (is_flag_set(V))
        PC = PC + (char) (*operand);
}

void CLC()
{
    update_flag(0, C);
}

void CLD()
{
    update_flag(0, D);
}

void CLI()
{
    update_flag(0, I);
}

void CLV()
{
    update_flag(0, V);
}

// TODO: carry flag
void CMP()
{
    byte r;
    r = A - (*operand);

    update_flag(!r, Z);
    update_flag(r >> 7, N);
}

void CPX()
{
    byte r;
    r = X - (*operand);

    update_flag(!r, Z);
    update_flag(r >> 7, N);
}

void CPY()
{
    byte r;
    r = Y - (*operand);

    update_flag(!r, Z);
    update_flag(r >> 7, N);
}

void DEC()
{
    (*operand)--;

    update_flag(!(*operand), Z);
    update_flag((*operand) >> 7, N);
}

void DEX()
{
    X--;

    update_flag(!X, Z);
    update_flag(X >> 7, N);
}

void DEY()
{
    Y--;

    update_flag(!Y, Z);
    update_flag(Y >> 7, N);
}

void EOR()
{
    A ^= (*operand);

    update_flag(!A, Z);
    update_flag(A >> 7, N);
}

void INC()
{
    (*operand)++;

    update_flag(!(*operand), Z);
    update_flag((*operand) >> 7, N);
}

void INX()
{
    X++;

    update_flag(!X, Z);
    update_flag(X >> 7, N);
}

void INY()
{
    Y++;

    update_flag(!Y, Z);
    update_flag(Y >> 7, N);
}

void JMP()
{
    PC = (*operand);
}

void JSR()
{
    push_word(PC+2);
    PC = (*operand);
}

void LDA()
{
    A = (*operand);

    update_flag(!A, Z);
    update_flag(A >> 7, N);
}

void LDX()
{
    X = (*operand);

    update_flag(!X, Z);
    update_flag(X >> 7, N);
}

void LDY()
{
    Y = (*operand);

    update_flag(!Y, Z);
    update_flag(Y >> 7, N);
}

void LSR()
{
    update_flag((*operand) & 0b00000001, C);

    *operand >>= 1;

    update_flag(!(*operand), Z);
    update_flag((*operand) >> 7, N);
}

void NOP() {}

void ORA()
{
    A |= (*operand);

    update_flag(!A, Z);
    update_flag(A >> 7, N);
}

void PHA()
{
    push(A);
}

void PHP()
{
    push(SR);
}

void PLA()
{
    A = pull();

    update_flag(!A, Z);
    update_flag(A >> 7, N);
}

void PLP()
{
    SR = pull();
}

void RTI()
{
    SR = pull();
    PC = pull();
}

void RTS()
{
    PC = pull() | pull() << 4;
    PC++;
}

void SBC()
{
    int i;
    byte a, b, bin, bout;
    bin = is_flag_set(C);

    for (i = 0; i < 8; i++)
    {
        a = A >> i;
        b = (*operand) >> i;

        bout = ~a & bin | ~a & b | b & bin;
        A |= ((a ^ b) ^ bin) << i;

        bin = bout;
    }

    update_flag(bout, C);
    update_flag(!(*operand), Z);
    update_flag(*operand >> 7, N);
}

void SEC()
{
    update_flag(1, C);
}

void SED()
{
    update_flag(1, D);
}

void SEI()
{
    update_flag(1, I);
}

void STA()
{
    *operand = A;
}

void STX()
{
    *operand = X;
}

void STY()
{
    *operand = Y;
}

void TAX()
{
    X = A;

    update_flag(!X, Z);
    update_flag(X >> 7, N);
}

void TAY()
{
    Y = A;

    update_flag(!Y, Z);
    update_flag(Y >> 7, N);
}

void TSX()
{
    X = SP;

    update_flag(!X, Z);
    update_flag(X >> 7, N);
}

void TXA()
{
    A = X;

    update_flag(!A, Z);
    update_flag(A >> 7, N);
}

void TXS()
{
    SP = X;
}

void TYA()
{
    A = Y;

    update_flag(!A, Z);
    update_flag(A >> 7, N);
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

