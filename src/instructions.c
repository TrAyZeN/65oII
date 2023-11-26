#include "cpu.h"
#include "instructions.h"
#include "stdio.h"
#include "stdlib.h"
#include "utils.h"

void adc() {
    int i;
    byte a, b, cin, cout;
    cin = is_flag_set(SR_C);

    if (is_flag_set(SR_D)) {
        for (i = 0; i < 2; i++) {
            a = (regs.a & 0xF << i * 4) >> i * 4;
            b = ((*operand) & 0xF << i * 4) >> i * 4;

            byte r = a + b + cin
                + 6; // simple addition and + 6 to convert back to BCD
            cout = r & 0x10;

            regs.a = (regs.a | 0xF << i * 4) & (r & 0xF) << i * 4;

            cin = cout;
        }
    } else {
        regs.a = full_adder(regs.a, (*operand), &cin);
    }

    update_flag(cin, SR_C);
    update_flag(!regs.a, SR_Z);
    update_flag(regs.a >> 7, SR_N);
}

void and () {
    regs.a &= (*operand);

    update_flag(!regs.a, SR_Z);
    update_flag(regs.a >> 8, SR_N);
}

void asl() {
    update_flag((*operand) >> 7, SR_C);

    *operand <<= 1;

    update_flag(!(*operand), SR_Z);
    update_flag((*operand) >> 7, SR_N);
}

void bcc() {
    if (!is_flag_set(SR_C)) {
        regs.pc = regs.pc + (char)(*operand);
    }
}

void bcs() {
    if (is_flag_set(SR_C)) {
        regs.pc = regs.pc + (char)(*operand);
    }
}

void beq() {
    if (is_flag_set(SR_Z)) {
        regs.pc = regs.pc + (char)(*operand);
    }
}

void bit() {
    update_flag((*operand) & 0b10000000, SR_N);
    update_flag((*operand) & 0b01000000, SR_V);
    update_flag(((*operand) & regs.a) == 0x00, SR_Z);
}

void bmi() {
    if (is_flag_set(SR_N)) {
        regs.pc = regs.pc + (char)(*operand);
    }
}

void bne() {
    if (!is_flag_set(SR_Z)) {
        regs.pc = regs.pc + (char)(*operand);
    }
}

void bpl() {
    if (!is_flag_set(SR_N)) {
        regs.pc = regs.pc + (char)(*operand);
    }
}

void ibrk() {
    update_flag(1, SR_I);
    push(regs.pc + 2);
    push(regs.sr);
    regs.pc = mem[0xFFFF] | (mem[0xFFFF] << 8);
}

void bvc() {
    if (!is_flag_set(SR_V)) {
        regs.pc = regs.pc + (char)(*operand);
    }
}

void bvs() {
    if (is_flag_set(SR_V)) {
        regs.pc = regs.pc + (char)(*operand);
    }
}

void clc() {
    update_flag(0, SR_C);
}

void cld() {
    update_flag(0, SR_D);
}

void cli() {
    update_flag(0, SR_I);
}

void clv() {
    update_flag(0, SR_V);
}

// TODO: carry flag
void cmp() {
    byte r;
    r = regs.a - (*operand);

    update_flag(!r, SR_Z);
    update_flag(r >> 7, SR_N);
}

void cpx() {
    byte r;
    r = regs.x - (*operand);

    update_flag(!r, SR_Z);
    update_flag(r >> 7, SR_N);
}

void cpy() {
    byte r;
    r = regs.y - (*operand);

    update_flag(!r, SR_Z);
    update_flag(r >> 7, SR_N);
}

void dec() {
    (*operand)--;

    update_flag(!(*operand), SR_Z);
    update_flag((*operand) >> 7, SR_N);
}

void dex() {
    regs.x--;

    update_flag(!regs.x, SR_Z);
    update_flag(regs.x >> 7, SR_N);
}

void dey() {
    regs.y--;

    update_flag(!regs.y, SR_Z);
    update_flag(regs.y >> 7, SR_N);
}

void eor() {
    regs.a ^= (*operand);

    update_flag(!regs.a, SR_Z);
    update_flag(regs.a >> 7, SR_N);
}

void inc() {
    (*operand)++;

    update_flag(!(*operand), SR_Z);
    update_flag((*operand) >> 7, SR_N);
}

void inx() {
    regs.x++;

    update_flag(!regs.x, SR_Z);
    update_flag(regs.x >> 7, SR_N);
}

void iny() {
    regs.y++;

    update_flag(!regs.y, SR_Z);
    update_flag(regs.y >> 7, SR_N);
}

void jmp() {
    regs.pc = (*operand);
}

void jsr() {
    push_word(regs.pc + 2);
    regs.pc = (*operand);
}

void lda() {
    regs.a = (*operand);

    update_flag(!regs.a, SR_Z);
    update_flag(regs.a >> 7, SR_N);
}

void ldx() {
    regs.x = (*operand);

    update_flag(!regs.x, SR_Z);
    update_flag(regs.x >> 7, SR_N);
}

void ldy() {
    regs.y = (*operand);

    update_flag(!regs.y, SR_Z);
    update_flag(regs.y >> 7, SR_N);
}

void lsr() {
    update_flag((*operand) & 0b00000001, SR_C);

    *operand >>= 1;

    update_flag(!(*operand), SR_Z);
    update_flag((*operand) >> 7, SR_N);
}

void nop() {
}

void ora() {
    regs.a |= (*operand);

    update_flag(!regs.a, SR_Z);
    update_flag(regs.a >> 7, SR_N);
}

void pha() {
    push(regs.a);
}

void php() {
    push(regs.sr);
}

void pla() {
    regs.a = pull();

    update_flag(!regs.a, SR_Z);
    update_flag(regs.a >> 7, SR_N);
}

void plp() {
    regs.sr = pull();
}

void rti() {
    regs.sr = pull();
    regs.pc = pull();
}

void rts() {
    regs.pc = pull() | pull() << 4;
    regs.pc++;
}

void sbc() {
    int i;
    byte a, b, bin, bout;
    bin = is_flag_set(SR_C);

    for (i = 0; i < 8; i++) {
        a = regs.a >> i;
        b = (*operand) >> i;

        bout = (~a & bin) | (~a & b) | (b & bin);
        regs.a |= ((a ^ b) ^ bin) << i;

        bin = bout;
    }

    update_flag(bout, SR_C);
    update_flag(!(*operand), SR_Z);
    update_flag(*operand >> 7, SR_N);
}

void sec() {
    update_flag(1, SR_C);
}

void sed() {
    update_flag(1, SR_D);
}

void sei() {
    update_flag(1, SR_I);
}

void sta() {
    *operand = regs.a;
}

void stx() {
    *operand = regs.x;
}

void sty() {
    *operand = regs.y;
}

void tax() {
    regs.x = regs.a;

    update_flag(!regs.x, SR_Z);
    update_flag(regs.x >> 7, SR_N);
}

void tay() {
    regs.y = regs.a;

    update_flag(!regs.y, SR_Z);
    update_flag(regs.y >> 7, SR_N);
}

void tsx() {
    regs.x = regs.sp;

    update_flag(!regs.x, SR_Z);
    update_flag(regs.x >> 7, SR_N);
}

void txa() {
    regs.a = regs.x;

    update_flag(!regs.a, SR_Z);
    update_flag(regs.a >> 7, SR_N);
}

void txs() {
    regs.sp = regs.x;
}

void tya() {
    regs.a = regs.y;

    update_flag(!regs.a, SR_Z);
    update_flag(regs.a >> 7, SR_N);
}

void nip() {
    printf("Not Implemented Operation : %02X\n", opcode);
    exit(EXIT_FAILURE);
}

void iop() {
    printf("Invalid Operation : %02X\n", opcode);
    printf("PC : $%04X\n", regs.pc);
    exit(EXIT_FAILURE);
}
