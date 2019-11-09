#include "instructions.h"
#include "cpu.h"

#include "stdlib.h"
#include "stdio.h"

void ADC()
{
    switch (opcode)
    {
        case 0x69:
            A += read_8();
        break;
        case 0x65:
            A += mem[read_8()];
        break;
        case 0x75:
            A += mem[read_8() + X];
        break;
        case 0x6D:
            A += mem[read_16()];
        break;
        case 0x7D:
            A += mem[read_16() + X];
        break;
        case 0x79:
            A += mem[read_16() + Y];
        break;
        case 0x61:
        break;
        case 0x71:
        break;
    }
}

INLINE void AND()
{
    switch (opcode)
    {
        case 0x29:
            A &= read_8();
        break;
        case 0x25:
            A &= mem[read_8()];
        break;
        case 0x35:
            A &= mem[read_8() + X];
        break;
        case 0x2D:
            A &= mem[read_16()];
        break;
        case 0x3D:
            A &= mem[read_16() + X];
        break;
        case 0x39:
            A &= mem[read_16() + Y];
        break;
        case 0x21:
        break;
        case 0x31:
        break;
    }

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
    switch (opcode)
    {
        case 0xC9:
            r = A - read_8();
        break;
        case 0xC5:
            r = A - mem[read_8()];
        break;
        case 0xD5:
            r = A - mem[read_8() + X];
        break;
        case 0xCD:
            r = A - mem[read_16()];
        break;
        case 0xDD:
            r = A - mem[read_16() + X];
        break;
        case 0xD9:
            r = A - mem[read_16() + Y];
        break;
        case 0xC1:
        break;
        case 0xD1:
        break;
    }

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
    switch (opcode)
    {
        case 0xE0:
            r = X - read_8();
        break;
        case 0xE4:
            r = X - mem[read_8()];
        break;
        case 0xEC:
            r = X - mem[read_16()];
        break;
    }

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
    switch (opcode)
    {
        case 0xC0:
            r = Y - read_8();
        break;
        case 0xC4:
            r = Y - mem[read_8()];
        break;
        case 0xCC:
            r = Y - mem[read_16()];
        break;
    }

    if (r == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (r <= 0x7F)
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

INLINE void LDA()
{
    switch (opcode)
    {
        case 0xA9:
            A = read_8();
        break;
        case 0xA5:
            A = mem[read_8()];
        break;
        case 0xB5:
            A = mem[read_8() + X];
        break;
        case 0xAD:
            A = mem[read_16()];
        break;
        case 0xBD:
            A = mem[read_16() + X];
        break;
        case 0xB9:
            A = mem[read_16() + Y];
        break;
        case 0xA1:
            A = A;
        break;
        case 0xB1:
            A = A;
        break;
    }

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
    switch (opcode)
    {
        case 0xA2:
            X = read_8();
        break;
        case 0xA6:
            X = mem[read_8()];
        break;
        case 0xB6:
            X = mem[read_8() + Y];
        break;
        case 0xAE:
            X = mem[read_16()];
        break;
        case 0xBE:
            X = mem[read_16() + Y];
        break;
    }

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
    switch (opcode)
    {
        case 0xA0:
            Y = read_8();
        break;
        case 0xA4:
            Y = mem[read_8()];
        break;
        case 0xB4:
            Y = mem[read_8() + X];
        break;
        case 0xAC:
            Y = mem[read_16()];
        break;
        case 0xBC:
            Y = mem[read_16() + X];
        break;
    }

    if (Y == 0x00)
        set_flag(Z);
    else
        unset_flag(Z);

    if (Y <= 0x7F)
        unset_flag(N);
    else
        set_flag(N);
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

