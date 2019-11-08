#ifndef CPU_H_
#define CPU_H_

typedef unsigned char byte;
typedef unsigned short word;

#ifndef DEF_CONSTS_
#define DEF_CONSTS_
static const unsigned int CLOCK_SPEED  = 1000000;  // 1 MHz clock speed
static const word STACK_OFFSET = 0x0100;
static const word RAM_OFFSET   = 0x0200;
#endif

byte A;             // 8-bit accumulator register
byte X, Y;          // 8-bit index registers
byte SP;            // 8-bit stack pointer
word PC;            // 16-bit program counter

/*
 * SR Flags:
 * N    Negative
 * V    Overflow
 * -    ignored
 * B    Break
 * D    Decimal (use BCD for arithmetics)
 * I    Interrupt (IRQ disable)
 * Z    Zero
 * C    Carry
 */
byte SR;            // 8-bit status register [NV-BDIZC]

/*
 *  $0000, $00FF  zero page RAM
 *  $0100, $01FF  Stack
 *  $0200, $FFF9  RAM
 *  $FFFA, $FFFB  NMI (Non-Maskable Interrupt) vector
 *  $FFFC, $FFFD  RES (Reset) vector
 *  $FFFE, $FFFF  IRQ (Interrupt Request) vector
 */
byte mem[0x10000];  // 64KB memory
byte opcode;        // opcode

byte counter;

void reset();
void loadROM(const char *filename);
void run();

#endif

