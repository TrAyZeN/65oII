#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "instructions.h"
#include "utils.h"

void adc(struct emu_state *state) {
    byte c_in = is_flag_set(state, SR_C);

    if (is_flag_set(state, SR_D)) {
        for (int i = 0; i < 2; i++) {
            byte a = (state->regs.a & 0xF << i * 4) >> i * 4;
            byte b = ((*state->operand) & 0xF << i * 4) >> i * 4;

            byte r = a + b + c_in
                + 6; // simple addition and + 6 to convert back to BCD
            byte c_out = r & 0x10;

            state->regs.a = (state->regs.a | 0xF << i * 4) & (r & 0xF) << i * 4;

            c_in = c_out;
        }
    } else {
        state->regs.a = full_adder(state->regs.a, (*state->operand), &c_in);
    }

    update_flag(state, c_in, SR_C);
    update_flag(state, !state->regs.a, SR_Z);
    update_flag(state, state->regs.a >> 7, SR_N);
}

// clang-format off
void and(struct emu_state *state) {
    state->regs.a &= (*state->operand);

    update_flag(state, !state->regs.a, SR_Z);
    update_flag(state, state->regs.a >> 8, SR_N);
}
// clang-format on

void asl(struct emu_state *state) {
    update_flag(state, (*state->operand) >> 7, SR_C);

    *state->operand <<= 1;

    update_flag(state, !(*state->operand), SR_Z);
    update_flag(state, (*state->operand) >> 7, SR_N);
}

void bcc(struct emu_state *state) {
    if (!is_flag_set(state, SR_C)) {
        state->regs.pc = state->regs.pc + (char)(*state->operand);
    }
}

void bcs(struct emu_state *state) {
    if (is_flag_set(state, SR_C)) {
        state->regs.pc = state->regs.pc + (char)(*state->operand);
    }
}

void beq(struct emu_state *state) {
    if (is_flag_set(state, SR_Z)) {
        state->regs.pc = state->regs.pc + (char)(*state->operand);
    }
}

void bit(struct emu_state *state) {
    update_flag(state, (*state->operand) & 0b10000000, SR_N);
    update_flag(state, (*state->operand) & 0b01000000, SR_V);
    update_flag(state, ((*state->operand) & state->regs.a) == 0x00, SR_Z);
}

void bmi(struct emu_state *state) {
    if (is_flag_set(state, SR_N)) {
        state->regs.pc = state->regs.pc + (char)(*state->operand);
    }
}

void bne(struct emu_state *state) {
    if (!is_flag_set(state, SR_Z)) {
        state->regs.pc = state->regs.pc + (char)(*state->operand);
    }
}

void bpl(struct emu_state *state) {
    if (!is_flag_set(state, SR_N)) {
        state->regs.pc = state->regs.pc + (char)(*state->operand);
    }
}

void ibrk(struct emu_state *state) {
    update_flag(state, 1, SR_I);
    push(state, state->regs.pc + 2);
    push(state, state->regs.sr);
    state->regs.pc = (state->mem[0xFFFF] << 8) | state->mem[0xFFFF];
}

void bvc(struct emu_state *state) {
    if (!is_flag_set(state, SR_V)) {
        state->regs.pc = state->regs.pc + (char)(*state->operand);
    }
}

void bvs(struct emu_state *state) {
    if (is_flag_set(state, SR_V)) {
        state->regs.pc = state->regs.pc + (char)(*state->operand);
    }
}

void clc(struct emu_state *state) {
    update_flag(state, 0, SR_C);
}

void cld(struct emu_state *state) {
    update_flag(state, 0, SR_D);
}

void cli(struct emu_state *state) {
    update_flag(state, 0, SR_I);
}

void clv(struct emu_state *state) {
    update_flag(state, 0, SR_V);
}

// TODO: carry flag
void cmp(struct emu_state *state) {
    byte r;
    r = state->regs.a - (*state->operand);

    update_flag(state, !r, SR_Z);
    update_flag(state, r >> 7, SR_N);
}

void cpx(struct emu_state *state) {
    byte r;
    r = state->regs.x - (*state->operand);

    update_flag(state, !r, SR_Z);
    update_flag(state, r >> 7, SR_N);
}

void cpy(struct emu_state *state) {
    byte r;
    r = state->regs.y - (*state->operand);

    update_flag(state, !r, SR_Z);
    update_flag(state, r >> 7, SR_N);
}

void dec(struct emu_state *state) {
    (*state->operand)--;

    update_flag(state, !(*state->operand), SR_Z);
    update_flag(state, (*state->operand) >> 7, SR_N);
}

void dex(struct emu_state *state) {
    state->regs.x--;

    update_flag(state, !state->regs.x, SR_Z);
    update_flag(state, state->regs.x >> 7, SR_N);
}

void dey(struct emu_state *state) {
    state->regs.y--;

    update_flag(state, !state->regs.y, SR_Z);
    update_flag(state, state->regs.y >> 7, SR_N);
}

void eor(struct emu_state *state) {
    state->regs.a ^= (*state->operand);

    update_flag(state, !state->regs.a, SR_Z);
    update_flag(state, state->regs.a >> 7, SR_N);
}

void inc(struct emu_state *state) {
    (*state->operand)++;

    update_flag(state, !(*state->operand), SR_Z);
    update_flag(state, (*state->operand) >> 7, SR_N);
}

void inx(struct emu_state *state) {
    state->regs.x++;

    update_flag(state, !state->regs.x, SR_Z);
    update_flag(state, state->regs.x >> 7, SR_N);
}

void iny(struct emu_state *state) {
    state->regs.y++;

    update_flag(state, !state->regs.y, SR_Z);
    update_flag(state, state->regs.y >> 7, SR_N);
}

void jmp(struct emu_state *state) {
    state->regs.pc = (*state->operand);
}

void jsr(struct emu_state *state) {
    push_word(state, state->regs.pc + 2);
    state->regs.pc = (*state->operand);
}

void lda(struct emu_state *state) {
    state->regs.a = (*state->operand);

    update_flag(state, !state->regs.a, SR_Z);
    update_flag(state, state->regs.a >> 7, SR_N);
}

void ldx(struct emu_state *state) {
    state->regs.x = (*state->operand);

    update_flag(state, !state->regs.x, SR_Z);
    update_flag(state, state->regs.x >> 7, SR_N);
}

void ldy(struct emu_state *state) {
    state->regs.y = (*state->operand);

    update_flag(state, !state->regs.y, SR_Z);
    update_flag(state, state->regs.y >> 7, SR_N);
}

void lsr(struct emu_state *state) {
    update_flag(state, (*state->operand) & 0b00000001, SR_C);

    *state->operand >>= 1;

    update_flag(state, !(*state->operand), SR_Z);
    update_flag(state, (*state->operand) >> 7, SR_N);
}

void nop(struct emu_state *state) {
}

void ora(struct emu_state *state) {
    state->regs.a |= (*state->operand);

    update_flag(state, !state->regs.a, SR_Z);
    update_flag(state, state->regs.a >> 7, SR_N);
}

void pha(struct emu_state *state) {
    push(state, state->regs.a);
}

void php(struct emu_state *state) {
    push(state, state->regs.sr);
}

void pla(struct emu_state *state) {
    state->regs.a = pull(state);

    update_flag(state, !state->regs.a, SR_Z);
    update_flag(state, state->regs.a >> 7, SR_N);
}

void plp(struct emu_state *state) {
    state->regs.sr = pull(state);
}

void rti(struct emu_state *state) {
    state->regs.sr = pull(state);
    state->regs.pc = pull(state);
}

void rts(struct emu_state *state) {
    state->regs.pc = pull(state) | pull(state) << 4;
    state->regs.pc++;
}

void sbc(struct emu_state *state) {
    byte b_out;
    byte b_in = is_flag_set(state, SR_C);

    for (int i = 0; i < 8; i++) {
        byte a = state->regs.a >> i;
        byte b = (*state->operand) >> i;

        b_out = (~a & b_in) | (~a & b) | (b & b_in);
        state->regs.a |= ((a ^ b) ^ b_in) << i;

        b_in = b_out;
    }

    update_flag(state, b_out, SR_C);
    update_flag(state, !(*state->operand), SR_Z);
    update_flag(state, *state->operand >> 7, SR_N);
}

void sec(struct emu_state *state) {
    update_flag(state, 1, SR_C);
}

void sed(struct emu_state *state) {
    update_flag(state, 1, SR_D);
}

void sei(struct emu_state *state) {
    update_flag(state, 1, SR_I);
}

void sta(struct emu_state *state) {
    *state->operand = state->regs.a;
}

void stx(struct emu_state *state) {
    *state->operand = state->regs.x;
}

void sty(struct emu_state *state) {
    *state->operand = state->regs.y;
}

void tax(struct emu_state *state) {
    state->regs.x = state->regs.a;

    update_flag(state, !state->regs.x, SR_Z);
    update_flag(state, state->regs.x >> 7, SR_N);
}

void tay(struct emu_state *state) {
    state->regs.y = state->regs.a;

    update_flag(state, !state->regs.y, SR_Z);
    update_flag(state, state->regs.y >> 7, SR_N);
}

void tsx(struct emu_state *state) {
    state->regs.x = state->regs.sp;

    update_flag(state, !state->regs.x, SR_Z);
    update_flag(state, state->regs.x >> 7, SR_N);
}

void txa(struct emu_state *state) {
    state->regs.a = state->regs.x;

    update_flag(state, !state->regs.a, SR_Z);
    update_flag(state, state->regs.a >> 7, SR_N);
}

void txs(struct emu_state *state) {
    state->regs.sp = state->regs.x;
}

void tya(struct emu_state *state) {
    state->regs.a = state->regs.y;

    update_flag(state, !state->regs.a, SR_Z);
    update_flag(state, state->regs.a >> 7, SR_N);
}

void nip(struct emu_state *state) {
    printf("Not Implemented Operation : %02X\n", state->opcode);
    exit(EXIT_FAILURE);
}

void iop(struct emu_state *state) {
    printf("Invalid Operation : %02X\n", state->opcode);
    printf("PC : $%04X\n", state->regs.pc);
    exit(EXIT_FAILURE);
}
