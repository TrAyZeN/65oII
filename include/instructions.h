#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_
#include "cpu.h"

#ifdef __C99__
#define INLINE inline
#else
#define INLINE __inline
#endif

extern void (*instructions_table[256])();
extern const unsigned char cycles_table[256];
extern const enum addressing_mode addrmode_table[256];

void adc(); // Add Memory to Accumulator with Carry

// clang-format off
void and(); // AND Memory with Accumulator
// clang-format on

void asl(); // Shift Left One Bit (Memory or Accumulator)

void bcc(); // Branch on Carry Clear

void bcs(); // Branch on Carry Set

void beq(); // Branch on Result Zero

void bit(); // Test Bits in Memory with Accumulator

void bmi(); // Branch on Result Minus

void bne(); // Branch on Result not Zero

void bpl(); // Branch on Result Plus

// WARN: brk naming conflicts with glibc function
void ibrk(); // Force Break

void bvc(); // Branch on Overflow Clear

void bvs(); // Branch on Overflow Set

void clc(); // Clear Carry Flag

void cld(); // Clear Decimal Mode

void cli(); // Clear Interrupt Disable Bit

void clv(); // Clear Overflow Flag

void cmp(); // Compare Memory with Accumulator

void cpx(); // Compare Memory and Index X

void cpy(); // Compare Memory and Index Y

void dec(); // Decrement Memory by One

void dex(); // Decrement Index X by One

void dey(); // Decrement Index Y by One

void eor(); // Exclusive-OR Memory with Accumulator

void inc(); // Increment Memory by One

void inx(); // Increment Index X by One

void iny(); // Increment Index Y by One

void jmp(); // Jump to New Location

void jsr(); // Jump to New Location Saving Return Adress

void lda(); // Load Accumulator with Memory

void ldx(); // Load Index X with Memory

void ldy(); // Load Index Y with Memory

void lsr(); // Shift One Bit Right (Memory or Accumulator)

void nop(); // No Operation

void ora(); // OR Memory with Accumulator

void pha(); // Push Accumulator on Stack

void php(); // Push Processor Status on Stack

void pla(); // Pull Accumulator from Stack

void plp(); // Pull Processor Status from Stack

void rti(); // Return from Interrupt

void rts(); // Return from Subroutine

void sbc(); // Substract Memory from Accumulator with Borrow

void sec(); // Set Carry Flag

void sed(); // Set Decimal Flag

void sei(); // Set Interrupt Disable Status

void sta(); // Store Accumulator in Memory

void stx(); // Store Index X in Memory

void sty(); // Store Index Y in Memory

void tax(); // Transfer Accumulator to Index X

void tay(); // Transfer Accumulator to Index Y

void tsx(); // Transfer Stack Pointer to Index X

void txa(); // Transfer Index X to Accumulator

void txs(); // Transfer Index X to Stack Register

void tya(); // Transfer Index Y to Accumulator

void nip(); // Not Implemented

void iop(); // Invalid Operation

#endif
