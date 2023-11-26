#ifndef CPU_H_
#define CPU_H_

typedef unsigned char byte;
typedef unsigned short word;

#define CLOCK_SPEED 1000000 // 1 MHz clock speed
#define STACK_OFFSET 0x0100
#define RAM_OFFSET 0x0200

// SR flags
#define SR_N 0b10000000 // Negative
#define SR_V 0b01000000 // Overflow
//      -                  ignored
#define SR_B 0b00010000 // Break
#define SR_D 0b00001000 // Decimal (use BCD for arithmetics)
#define SR_I 0b00000100 // Interrupt (IRQ disable)
#define SR_Z 0b00000010 // Zero
#define SR_C 0b00000001 // Carry

struct registers {
    // 16-bit program counter
    word PC;
    // 8-bit accumulator register
    byte A;
    // 8-bit index registers
    byte X;
    byte Y;
    // 8-bit status register [NV-BDIZC]
    byte SR;
    // 8-bit stack pointer
    byte SP;
};

extern struct registers regs;

/*
 *  $0000, $00FF  zero page RAM
 *  $0100, $01FF  Stack
 *  $0200, $FFF9  RAM
 *  $FFFA, $FFFB  NMI (Non-Maskable Interrupt) vector
 *  $FFFC, $FFFD  RES (Reset) vector
 *  $FFFE, $FFFF  IRQ (Interrupt Request) vector
 */
extern byte mem[0x10000]; // 64KB memory
extern byte opcode; // opcode
extern byte *operand;

enum addressing_mode {
    NONE,
    ACC,
    ABS,
    ABSX,
    ABSY,
    IMM,
    IMPL,
    IND,
    XIND,
    INDY,
    REL,
    ZPG,
    ZPGX,
    ZPGY
};

byte read_8();
word read_16();

void push(byte b);
void push_word(word w);
byte pull();

void update_flag(byte val, byte flag);
byte is_flag_set(byte flag);

byte *read_operand();

void reset();
void load_ROM(const char *filename);
void run();

#endif
