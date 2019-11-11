#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#ifdef __C99__
#define INLINE inline
#else
#define INLINE __inline
#endif

INLINE void ADC();  // Add Memory to Accumulator with Carry

INLINE void AND();  // AND Memory with Accumulator

INLINE void BCC();  // Branch on Carry Clear

INLINE void BCS();  // Branch on Carry Set

INLINE void BEQ();  // Branch on Result Zero

INLINE void BIT();  // Test Bits in Memory with Accumulator

INLINE void BMI();  // Branch on Result Minus

INLINE void BNE();  // Branch on Result not Zero

INLINE void BPL();  // Branch on Result Plus

INLINE void BRK();  // Force Break

INLINE void BVC();  // Branch on Overflow Clear

INLINE void BVS();  // Branch on Overflow Set

INLINE void CLC();  // Clear Carry Flag

INLINE void CLD();  // Clear Decimal Mode

INLINE void CLI();  // Clear Interrupt Disable Bit

INLINE void CLV();  // Clear Overflow Flag

INLINE void CMP();  // Compare Memory with Accumulator

INLINE void CPX();  // Compare Memory and Index X

INLINE void CPY();  // Compare Memory and Index Y

INLINE void DEC();  // Decrement Memory by One

INLINE void DEX();  // Decrement Index X by One

INLINE void DEY();  // Decrement Index Y by One

INLINE void INC();  // Increment Memory by One

INLINE void INX();  // Increment Index X by One

INLINE void INY();  // Increment Index Y by One

INLINE void JMP();  // Jump to New Location

INLINE void JSR();  // Jump to New Location Saving Return Adress

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

INLINE void STX();  // Store Index X in Memory

INLINE void STY();  // Store Index Y in Memory

void NIP();         // Not Implemented

void IOP();         // Invalid Operation

#endif

