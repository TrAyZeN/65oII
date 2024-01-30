#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_
#include "cpu.h"

#ifdef __C99__
#define INLINE inline
#else
#define INLINE __inline
#endif

typedef void (*instruction_func)(struct emu_state *);

extern instruction_func instructions_table[256];
extern const unsigned char cycles_table[256];
extern const enum addressing_mode addrmode_table[256];

void adc(struct emu_state *state); // Add Memory to Accumulator with Carry

// clang-format off
void and(struct emu_state *state); // AND Memory with Accumulator
// clang-format on

void asl(struct emu_state *state); // Shift Left One Bit (Memory or Accumulator)

void bcc(struct emu_state *state); // Branch on Carry Clear

void bcs(struct emu_state *state); // Branch on Carry Set

void beq(struct emu_state *state); // Branch on Result Zero

void bit(struct emu_state *state); // Test Bits in Memory with Accumulator

void bmi(struct emu_state *state); // Branch on Result Minus

void bne(struct emu_state *state); // Branch on Result not Zero

void bpl(struct emu_state *state); // Branch on Result Plus

// WARN: brk naming conflicts with glibc function
void ibrk(struct emu_state *state); // Force Break

void bvc(struct emu_state *state); // Branch on Overflow Clear

void bvs(struct emu_state *state); // Branch on Overflow Set

void clc(struct emu_state *state); // Clear Carry Flag

void cld(struct emu_state *state); // Clear Decimal Mode

void cli(struct emu_state *state); // Clear Interrupt Disable Bit

void clv(struct emu_state *state); // Clear Overflow Flag

void cmp(struct emu_state *state); // Compare Memory with Accumulator

void cpx(struct emu_state *state); // Compare Memory and Index X

void cpy(struct emu_state *state); // Compare Memory and Index Y

void dec(struct emu_state *state); // Decrement Memory by One

void dex(struct emu_state *state); // Decrement Index X by One

void dey(struct emu_state *state); // Decrement Index Y by One

void eor(struct emu_state *state); // Exclusive-OR Memory with Accumulator

void inc(struct emu_state *state); // Increment Memory by One

void inx(struct emu_state *state); // Increment Index X by One

void iny(struct emu_state *state); // Increment Index Y by One

void jmp(struct emu_state *state); // Jump to New Location

void jsr(struct emu_state *state); // Jump to New Location Saving Return Adress

void lda(struct emu_state *state); // Load Accumulator with Memory

void ldx(struct emu_state *state); // Load Index X with Memory

void ldy(struct emu_state *state); // Load Index Y with Memory

void lsr(
    struct emu_state *state); // Shift One Bit Right (Memory or Accumulator)

void nop(struct emu_state *state); // No Operation

void ora(struct emu_state *state); // OR Memory with Accumulator

void pha(struct emu_state *state); // Push Accumulator on Stack

void php(struct emu_state *state); // Push Processor Status on Stack

void pla(struct emu_state *state); // Pull Accumulator from Stack

void plp(struct emu_state *state); // Pull Processor Status from Stack

void rti(struct emu_state *state); // Return from Interrupt

void rts(struct emu_state *state); // Return from Subroutine

// Substract Memory from Accumulator with Borrow
void sbc(struct emu_state *state);

void sec(struct emu_state *state); // Set Carry Flag

void sed(struct emu_state *state); // Set Decimal Flag

void sei(struct emu_state *state); // Set Interrupt Disable Status

void sta(struct emu_state *state); // Store Accumulator in Memory

void stx(struct emu_state *state); // Store Index X in Memory

void sty(struct emu_state *state); // Store Index Y in Memory

void tax(struct emu_state *state); // Transfer Accumulator to Index X

void tay(struct emu_state *state); // Transfer Accumulator to Index Y

void tsx(struct emu_state *state); // Transfer Stack Pointer to Index X

void txa(struct emu_state *state); // Transfer Index X to Accumulator

void txs(struct emu_state *state); // Transfer Index X to Stack Register

void tya(struct emu_state *state); // Transfer Index Y to Accumulator

void nip(struct emu_state *state); // Not Implemented

void iop(struct emu_state *state); // Invalid Operation

#endif
