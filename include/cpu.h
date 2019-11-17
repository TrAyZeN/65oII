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

// SR flags
#define N 0b10000000    // Negative
#define V 0b01000000    // Overflow
//      -                  ignored
#define B 0b00010000    // Break
#define D 0b00001000    // Decimal (use BCD for arithmetics)
#define I 0b00000100    // Interrupt (IRQ disable)
#define Z 0b00000010    // Zero
#define C 0b00000001    // Carry
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
word *operand;

enum addressing_mode
{
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

byte counter;

byte read_8();
word read_16();

void push(byte b);
void push_word(word w);
byte pull();

void update_flag(byte val, byte flag);
byte is_flag_set(byte flag);

word *read_operand();

void reset();
void load_ROM(const char *filename);
void run();

#endif

