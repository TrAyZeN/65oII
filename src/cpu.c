#include "cpu.h"
#include "instructions.h"
#include "stdio.h"
#include "stdlib.h"

#ifdef _WIN32
#include "Windows.h"
#else
#include "unistd.h"
#endif

byte read_8(struct emu_state *state) {
    return state->mem[state->regs.pc++];
}

word read_16(struct emu_state *state) {
    return state->mem[state->regs.pc++] | (state->mem[state->regs.pc++] << 8);
}

void push(struct emu_state *state, byte b) {
    state->mem[STACK_OFFSET + state->regs.sp++] = b;
}

void push_word(struct emu_state *state, word w) {
    push(state, (byte)(w & 0xFF));
    push(state, (byte)(w >> 8));
}

byte pull(struct emu_state *state) {
    return state->mem[STACK_OFFSET + state->regs.sp--];
}

void update_flag(struct emu_state *state, byte val, byte flag) {
    if (val) {
        state->regs.sr |= flag;
    } else {
        state->regs.sr &= ~flag;
    }
}

byte is_flag_set(struct emu_state *state, byte flag) {
    return state->regs.sr & flag;
}

byte *read_operand(struct emu_state *state) {
    switch (addrmode_table[state->opcode]) {
    case ACC:
        return &state->regs.a;
    case ABS:
        return &state->mem[read_16(state)];
    case ABSX:
        return &state->mem[read_16(state) + state->regs.x];
    case ABSY:
        return &state->mem[read_16(state) + state->regs.y];
    case IMM:
        return &state->mem[state->regs.pc++];
    case IND:
        return &state->mem[state->mem[read_16(state)]];
    case XIND:
        return &state->mem[state->mem[read_8(state) + state->regs.x]];
    case INDY:
        return &state->mem[state->mem[read_8(state)] + state->regs.y];
    case REL:
        return &state->mem[state->regs.pc++];
    case ZPG:
        return &state->mem[read_8(state)];
    case ZPGX:
        return &state->mem[read_8(state) + state->regs.x];
    case ZPGY:
        return &state->mem[read_8(state) + state->regs.y];
    default:
        printf("Error : invalid addressing mode\n");
        exit(EXIT_FAILURE);
    }
}

void reset(struct emu_state *state) {
    int i;

    state->regs.pc = RAM_OFFSET;
    state->regs.sp = 0;
    state->regs.sr = 0b00100000;

    for (i = 0; i < 64000; i++) {
        state->mem[i] = 0;
    }
}

void load_rom(struct emu_state *state, const char *filename) {
    FILE *f;
    int op;

    state->regs.pc = RAM_OFFSET;

    f = fopen(filename, "rb");
    if (f == NULL) {
        printf("Error : Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    while ((op = fgetc(f)) != EOF) {
        state->mem[state->regs.pc++] = (byte)op;
    }

    fclose(f);

    state->regs.pc = RAM_OFFSET;
}

void run(struct emu_state *state) {
    for (;;) {
        state->opcode = state->mem[state->regs.pc++];
        state->operand = read_operand(state);
        instructions_table[state->opcode](state);

        // sleep(1.0 / CLOCK_SPEED);
    }
}
