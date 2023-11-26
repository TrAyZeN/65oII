#include "instructions.h"

#include "cpu.h"
#include "stdio.h"
#include "stdlib.h"
#include "utils.h"

void ADC() {
    int i;
    byte a, b, cin, cout;
    cin = is_flag_set(C);

    if (is_flag_set(D)) {
        for (i = 0; i < 2; i++) {
            a = (regs.A & 0xF << i * 4) >> i * 4;
            b = ((*operand) & 0xF << i * 4) >> i * 4;

            byte r = a + b + cin
                + 6; // simple addition and + 6 to convert back to BCD
            cout = r & 0x10;

            regs.A = (regs.A | 0xF << i * 4) & (r & 0xF) << i * 4;

            cin = cout;
        }
    } else {
        regs.A = full_adder(regs.A, (*operand), &cin);
    }

    update_flag(cin, C);
    update_flag(!regs.A, Z);
    update_flag(regs.A >> 7, N);
}

void AND() {
    regs.A &= (*operand);

    update_flag(!regs.A, Z);
    update_flag(regs.A >> 8, N);
}

void ASL() {
    update_flag((*operand) >> 7, C);

    *operand <<= 1;

    update_flag(!(*operand), Z);
    update_flag((*operand) >> 7, N);
}

void BCC() {
    if (!is_flag_set(C)) {
        regs.PC = regs.PC + (char)(*operand);
    }
}

void BCS() {
    if (is_flag_set(C)) {
        regs.PC = regs.PC + (char)(*operand);
    }
}

void BEQ() {
    if (is_flag_set(Z)) {
        regs.PC = regs.PC + (char)(*operand);
    }
}

void BIT() {
    update_flag((*operand) & 0b10000000, N);
    update_flag((*operand) & 0b01000000, V);
    update_flag(((*operand) & regs.A) == 0x00, Z);
}

void BMI() {
    if (is_flag_set(N))
        regs.PC = regs.PC + (char)(*operand);
}

void BNE() {
    if (!is_flag_set(Z))
        regs.PC = regs.PC + (char)(*operand);
}

void BPL() {
    if (!is_flag_set(N))
        regs.PC = regs.PC + (char)(*operand);
}

void BRK() {
    update_flag(1, I);
    push(regs.PC + 2);
    push(regs.SR);
    regs.PC = mem[0xFFFF] | (mem[0xFFFF] << 8);
}

void BVC() {
    if (!is_flag_set(V))
        regs.PC = regs.PC + (char)(*operand);
}

void BVS() {
    if (is_flag_set(V))
        regs.PC = regs.PC + (char)(*operand);
}

void CLC() {
    update_flag(0, C);
}

void CLD() {
    update_flag(0, D);
}

void CLI() {
    update_flag(0, I);
}

void CLV() {
    update_flag(0, V);
}

// TODO: carry flag
void CMP() {
    byte r;
    r = regs.A - (*operand);

    update_flag(!r, Z);
    update_flag(r >> 7, N);
}

void CPX() {
    byte r;
    r = regs.X - (*operand);

    update_flag(!r, Z);
    update_flag(r >> 7, N);
}

void CPY() {
    byte r;
    r = regs.Y - (*operand);

    update_flag(!r, Z);
    update_flag(r >> 7, N);
}

void DEC() {
    (*operand)--;

    update_flag(!(*operand), Z);
    update_flag((*operand) >> 7, N);
}

void DEX() {
    regs.X--;

    update_flag(!regs.X, Z);
    update_flag(regs.X >> 7, N);
}

void DEY() {
    regs.Y--;

    update_flag(!regs.Y, Z);
    update_flag(regs.Y >> 7, N);
}

void EOR() {
    regs.A ^= (*operand);

    update_flag(!regs.A, Z);
    update_flag(regs.A >> 7, N);
}

void INC() {
    (*operand)++;

    update_flag(!(*operand), Z);
    update_flag((*operand) >> 7, N);
}

void INX() {
    regs.X++;

    update_flag(!regs.X, Z);
    update_flag(regs.X >> 7, N);
}

void INY() {
    regs.Y++;

    update_flag(!regs.Y, Z);
    update_flag(regs.Y >> 7, N);
}

void JMP() {
    regs.PC = (*operand);
}

void JSR() {
    push_word(regs.PC + 2);
    regs.PC = (*operand);
}

void LDA() {
    regs.A = (*operand);

    update_flag(!regs.A, Z);
    update_flag(regs.A >> 7, N);
}

void LDX() {
    regs.X = (*operand);

    update_flag(!regs.X, Z);
    update_flag(regs.X >> 7, N);
}

void LDY() {
    regs.Y = (*operand);

    update_flag(!regs.Y, Z);
    update_flag(regs.Y >> 7, N);
}

void LSR() {
    update_flag((*operand) & 0b00000001, C);

    *operand >>= 1;

    update_flag(!(*operand), Z);
    update_flag((*operand) >> 7, N);
}

void NOP() {
}

void ORA() {
    regs.A |= (*operand);

    update_flag(!regs.A, Z);
    update_flag(regs.A >> 7, N);
}

void PHA() {
    push(regs.A);
}

void PHP() {
    push(regs.SR);
}

void PLA() {
    regs.A = pull();

    update_flag(!regs.A, Z);
    update_flag(regs.A >> 7, N);
}

void PLP() {
    regs.SR = pull();
}

void RTI() {
    regs.SR = pull();
    regs.PC = pull();
}

void RTS() {
    regs.PC = pull() | pull() << 4;
    regs.PC++;
}

void SBC() {
    int i;
    byte a, b, bin, bout;
    bin = is_flag_set(C);

    for (i = 0; i < 8; i++) {
        a = regs.A >> i;
        b = (*operand) >> i;

        bout = (~a & bin) | (~a & b) | (b & bin);
        regs.A |= ((a ^ b) ^ bin) << i;

        bin = bout;
    }

    update_flag(bout, C);
    update_flag(!(*operand), Z);
    update_flag(*operand >> 7, N);
}

void SEC() {
    update_flag(1, C);
}

void SED() {
    update_flag(1, D);
}

void SEI() {
    update_flag(1, I);
}

void STA() {
    *operand = regs.A;
}

void STX() {
    *operand = regs.X;
}

void STY() {
    *operand = regs.Y;
}

void TAX() {
    regs.X = regs.A;

    update_flag(!regs.X, Z);
    update_flag(regs.X >> 7, N);
}

void TAY() {
    regs.Y = regs.A;

    update_flag(!regs.Y, Z);
    update_flag(regs.Y >> 7, N);
}

void TSX() {
    regs.X = regs.SP;

    update_flag(!regs.X, Z);
    update_flag(regs.X >> 7, N);
}

void TXA() {
    regs.A = regs.X;

    update_flag(!regs.A, Z);
    update_flag(regs.A >> 7, N);
}

void TXS() {
    regs.SP = regs.X;
}

void TYA() {
    regs.A = regs.Y;

    update_flag(!regs.A, Z);
    update_flag(regs.A >> 7, N);
}

void NIP() {
    printf("Not Implemented Operation : %02X\n", opcode);
    exit(EXIT_FAILURE);
}

void IOP() {
    printf("Invalid Operation : %02X\n", opcode);
    printf("PC : $%04X\n", regs.PC);
    exit(EXIT_FAILURE);
}
