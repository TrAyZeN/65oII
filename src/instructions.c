#include "cpu.h"
#include "instructions.h"
#include "stdio.h"
#include "stdlib.h"
#include "utils.h"

void ADC() {
    int i;
    byte a, b, cin, cout;
    cin = is_flag_set(SR_C);

    if (is_flag_set(SR_D)) {
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

    update_flag(cin, SR_C);
    update_flag(!regs.A, SR_Z);
    update_flag(regs.A >> 7, SR_N);
}

void AND() {
    regs.A &= (*operand);

    update_flag(!regs.A, SR_Z);
    update_flag(regs.A >> 8, SR_N);
}

void ASL() {
    update_flag((*operand) >> 7, SR_C);

    *operand <<= 1;

    update_flag(!(*operand), SR_Z);
    update_flag((*operand) >> 7, SR_N);
}

void BCC() {
    if (!is_flag_set(SR_C)) {
        regs.PC = regs.PC + (char)(*operand);
    }
}

void BCS() {
    if (is_flag_set(SR_C)) {
        regs.PC = regs.PC + (char)(*operand);
    }
}

void BEQ() {
    if (is_flag_set(SR_Z)) {
        regs.PC = regs.PC + (char)(*operand);
    }
}

void BIT() {
    update_flag((*operand) & 0b10000000, SR_N);
    update_flag((*operand) & 0b01000000, SR_V);
    update_flag(((*operand) & regs.A) == 0x00, SR_Z);
}

void BMI() {
    if (is_flag_set(SR_N)) {
        regs.PC = regs.PC + (char)(*operand);
    }
}

void BNE() {
    if (!is_flag_set(SR_Z)) {
        regs.PC = regs.PC + (char)(*operand);
    }
}

void BPL() {
    if (!is_flag_set(SR_N)) {
        regs.PC = regs.PC + (char)(*operand);
    }
}

void BRK() {
    update_flag(1, SR_I);
    push(regs.PC + 2);
    push(regs.SR);
    regs.PC = mem[0xFFFF] | (mem[0xFFFF] << 8);
}

void BVC() {
    if (!is_flag_set(SR_V)) {
        regs.PC = regs.PC + (char)(*operand);
    }
}

void BVS() {
    if (is_flag_set(SR_V)) {
        regs.PC = regs.PC + (char)(*operand);
    }
}

void CLC() {
    update_flag(0, SR_C);
}

void CLD() {
    update_flag(0, SR_D);
}

void CLI() {
    update_flag(0, SR_I);
}

void CLV() {
    update_flag(0, SR_V);
}

// TODO: carry flag
void CMP() {
    byte r;
    r = regs.A - (*operand);

    update_flag(!r, SR_Z);
    update_flag(r >> 7, SR_N);
}

void CPX() {
    byte r;
    r = regs.X - (*operand);

    update_flag(!r, SR_Z);
    update_flag(r >> 7, SR_N);
}

void CPY() {
    byte r;
    r = regs.Y - (*operand);

    update_flag(!r, SR_Z);
    update_flag(r >> 7, SR_N);
}

void DEC() {
    (*operand)--;

    update_flag(!(*operand), SR_Z);
    update_flag((*operand) >> 7, SR_N);
}

void DEX() {
    regs.X--;

    update_flag(!regs.X, SR_Z);
    update_flag(regs.X >> 7, SR_N);
}

void DEY() {
    regs.Y--;

    update_flag(!regs.Y, SR_Z);
    update_flag(regs.Y >> 7, SR_N);
}

void EOR() {
    regs.A ^= (*operand);

    update_flag(!regs.A, SR_Z);
    update_flag(regs.A >> 7, SR_N);
}

void INC() {
    (*operand)++;

    update_flag(!(*operand), SR_Z);
    update_flag((*operand) >> 7, SR_N);
}

void INX() {
    regs.X++;

    update_flag(!regs.X, SR_Z);
    update_flag(regs.X >> 7, SR_N);
}

void INY() {
    regs.Y++;

    update_flag(!regs.Y, SR_Z);
    update_flag(regs.Y >> 7, SR_N);
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

    update_flag(!regs.A, SR_Z);
    update_flag(regs.A >> 7, SR_N);
}

void LDX() {
    regs.X = (*operand);

    update_flag(!regs.X, SR_Z);
    update_flag(regs.X >> 7, SR_N);
}

void LDY() {
    regs.Y = (*operand);

    update_flag(!regs.Y, SR_Z);
    update_flag(regs.Y >> 7, SR_N);
}

void LSR() {
    update_flag((*operand) & 0b00000001, SR_C);

    *operand >>= 1;

    update_flag(!(*operand), SR_Z);
    update_flag((*operand) >> 7, SR_N);
}

void NOP() {
}

void ORA() {
    regs.A |= (*operand);

    update_flag(!regs.A, SR_Z);
    update_flag(regs.A >> 7, SR_N);
}

void PHA() {
    push(regs.A);
}

void PHP() {
    push(regs.SR);
}

void PLA() {
    regs.A = pull();

    update_flag(!regs.A, SR_Z);
    update_flag(regs.A >> 7, SR_N);
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
    bin = is_flag_set(SR_C);

    for (i = 0; i < 8; i++) {
        a = regs.A >> i;
        b = (*operand) >> i;

        bout = (~a & bin) | (~a & b) | (b & bin);
        regs.A |= ((a ^ b) ^ bin) << i;

        bin = bout;
    }

    update_flag(bout, SR_C);
    update_flag(!(*operand), SR_Z);
    update_flag(*operand >> 7, SR_N);
}

void SEC() {
    update_flag(1, SR_C);
}

void SED() {
    update_flag(1, SR_D);
}

void SEI() {
    update_flag(1, SR_I);
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

    update_flag(!regs.X, SR_Z);
    update_flag(regs.X >> 7, SR_N);
}

void TAY() {
    regs.Y = regs.A;

    update_flag(!regs.Y, SR_Z);
    update_flag(regs.Y >> 7, SR_N);
}

void TSX() {
    regs.X = regs.SP;

    update_flag(!regs.X, SR_Z);
    update_flag(regs.X >> 7, SR_N);
}

void TXA() {
    regs.A = regs.X;

    update_flag(!regs.A, SR_Z);
    update_flag(regs.A >> 7, SR_N);
}

void TXS() {
    regs.SP = regs.X;
}

void TYA() {
    regs.A = regs.Y;

    update_flag(!regs.A, SR_Z);
    update_flag(regs.A >> 7, SR_N);
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
