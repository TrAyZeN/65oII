#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#ifdef __C99__
#define INLINE inline
#else
#define INLINE __inline
#endif

void ADC();         // Add Memory to Accumulator with Carry

void AND();         // AND Memory with Accumulator

INLINE void BCC();  // Branch on Carry Clear

INLINE void BCS();  // Branch on Carry Set

INLINE void BEQ();  // Branch on Result Zero

void BIT();         // Test Bits in Memory with Accumulator

INLINE void BMI();  // Branch on Result Minus

INLINE void BNE();  // Branch on Result not Zero

INLINE void BPL();  // Branch on Result Plus

INLINE void CLC();  // Clear Carry Flag

INLINE void CLD();  // Clear Decimal Mode

INLINE void CLI();  // Clear Interrupt Disable Bit

INLINE void CLV();  // Clear Overflow Flag

INLINE void DEY();  // Decrement Index Y by One

INLINE void LDA();  // Load Accumulator with Memory

INLINE void LDX();  // Load Index X with Memory

INLINE void LDY();  // Load Index Y with Memory

INLINE void NOP();  // No Operation

INLINE void PHA();  // Push Accumulator on Stack

INLINE void PHP();  // Push Processor Status on Stack

INLINE void PLA();  // Pull Accumulator from Stack

INLINE void PLP();  // Pull Processor Status from Stack

INLINE void SEC();  // Set Carry Flag

INLINE void SED();  // Set Decimal Flag

INLINE void SEI();  // Set Interrupt Disable Status

INLINE void STA();  // Store Accumulator in Memory

void NIP();         // Not Implemented

void IOP();         // Invalid Operation

#endif

