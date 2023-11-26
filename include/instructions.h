#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_
#include "cpu.h"

#ifdef __C99__
#define INLINE inline
#else
#define INLINE __inline
#endif

extern void (* instructions_table[256])();
extern const unsigned char cycles_table[256];
extern const enum addressing_mode addrmode_table[256];

void ADC();  // Add Memory to Accumulator with Carry

void AND();  // AND Memory with Accumulator

void ASL();  // Shift Left One Bit (Memory or Accumulator)

void BCC();  // Branch on Carry Clear

void BCS();  // Branch on Carry Set

void BEQ();  // Branch on Result Zero

void BIT();  // Test Bits in Memory with Accumulator

void BMI();  // Branch on Result Minus

void BNE();  // Branch on Result not Zero

void BPL();  // Branch on Result Plus

void BRK();  // Force Break

void BVC();  // Branch on Overflow Clear

void BVS();  // Branch on Overflow Set

void CLC();  // Clear Carry Flag

void CLD();  // Clear Decimal Mode

void CLI();  // Clear Interrupt Disable Bit

void CLV();  // Clear Overflow Flag

void CMP();  // Compare Memory with Accumulator

void CPX();  // Compare Memory and Index X

void CPY();  // Compare Memory and Index Y

void DEC();  // Decrement Memory by One

void DEX();  // Decrement Index X by One

void DEY();  // Decrement Index Y by One

void EOR();  // Exclusive-OR Memory with Accumulator

void INC();  // Increment Memory by One

void INX();  // Increment Index X by One

void INY();  // Increment Index Y by One

void JMP();  // Jump to New Location

void JSR();  // Jump to New Location Saving Return Adress

void LDA();  // Load Accumulator with Memory

void LDX();  // Load Index X with Memory

void LDY();  // Load Index Y with Memory

void LSR();  // Shift One Bit Right (Memory or Accumulator)

void NOP();  // No Operation

void ORA();  // OR Memory with Accumulator

void PHA();  // Push Accumulator on Stack

void PHP();  // Push Processor Status on Stack

void PLA();  // Pull Accumulator from Stack

void PLP();  // Pull Processor Status from Stack

void RTI();  // Return from Interrupt

void RTS();  // Return from Subroutine

void SBC();  // Substract Memory from Accumulator with Borrow

void SEC();  // Set Carry Flag

void SED();  // Set Decimal Flag

void SEI();  // Set Interrupt Disable Status

void STA();  // Store Accumulator in Memory

void STX();  // Store Index X in Memory

void STY();  // Store Index Y in Memory

void TAX();  // Transfer Accumulator to Index X

void TAY();  // Transfer Accumulator to Index Y

void TSX();  // Transfer Stack Pointer to Index X

void TXA();  // Transfer Index X to Accumulator

void TXS();  // Transfer Index X to Stack Register

void TYA();  // Transfer Index Y to Accumulator

void NIP();         // Not Implemented

void IOP();         // Invalid Operation

#endif
