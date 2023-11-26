#ifndef CPU_H_
#define CPU_H_

#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;

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
    word pc;
    // 8-bit accumulator register
    byte a;
    // 8-bit index registers
    byte x;
    byte y;
    // 8-bit status register [NV-BDIZC]
    byte sr;
    // 8-bit stack pointer
    byte sp;
};

struct emu_state {
    struct registers regs;

    /*
     * 64KB memory:
     *  $0000, $00FF  zero page RAM
     *  $0100, $01FF  Stack
     *  $0200, $FFF9  RAM
     *  $FFFA, $FFFB  NMI (Non-Maskable Interrupt) vector
     *  $FFFC, $FFFD  RES (Reset) vector
     *  $FFFE, $FFFF  IRQ (Interrupt Request) vector
     */
    byte mem[0x10000];

    byte opcode;
    byte *operand;
};

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

byte read_8(struct emu_state *state);
word read_16(struct emu_state *state);

void push(struct emu_state *state, byte b);
void push_word(struct emu_state *state, word w);
byte pull(struct emu_state *state);

void update_flag(struct emu_state *state, byte val, byte flag);
byte is_flag_set(struct emu_state *state, byte flag);

byte *read_operand(struct emu_state *state);

void reset(struct emu_state *state);
void load_rom(struct emu_state *state, const char *filename);
void run(struct emu_state *state);

#endif
