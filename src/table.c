#include "cpu.h"
#include "instructions.h"

// clang-format off

void (* instructions_table[256])() =
{
//        00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F
/* 00 */ BRK, ORA, IOP, IOP, IOP, ORA, ASL, IOP, PHP, ORA, ASL, IOP, IOP, ORA, ASL, IOP,
/* 10 */ BPL, ORA, IOP, IOP, IOP, ORA, ASL, IOP, CLC, ORA, IOP, IOP, IOP, ORA, ASL, IOP,
/* 20 */ JSR, AND, IOP, IOP, BIT, AND, NIP, IOP, PLP, AND, NIP, IOP, NIP, AND, NIP, IOP,
/* 30 */ BMI, AND, IOP, IOP, IOP, AND, NIP, IOP, SEC, AND, IOP, IOP, IOP, AND, NIP, IOP,
/* 40 */ RTI, EOR, IOP, IOP, IOP, EOR, LSR, IOP, PHA, EOR, LSR, IOP, JMP, EOR, LSR, IOP,
/* 50 */ BVC, EOR, IOP, IOP, IOP, EOR, LSR, IOP, CLI, EOR, IOP, IOP, IOP, EOR, LSR, IOP,
/* 60 */ RTS, NIP, IOP, IOP, IOP, NIP, NIP, IOP, PLA, NIP, NIP, IOP, JMP, NIP, NIP, IOP,
/* 70 */ BVS, NIP, IOP, IOP, IOP, NIP, NIP, IOP, SEI, NIP, IOP, IOP, IOP, NIP, NIP, IOP,
/* 80 */ IOP, STA, IOP, IOP, STY, STA, STX, IOP, DEY, IOP, TXA, IOP, STY, STA, STX, IOP,
/* 90 */ BCC, STA, IOP, IOP, STY, STA, STX, IOP, TYA, STA, TXS, IOP, IOP, STA, IOP, IOP,
/* A0 */ LDY, LDA, LDX, IOP, LDY, LDA, LDX, IOP, TAY, LDA, TAX, IOP, LDY, LDA, LDX, IOP,
/* B0 */ BCS, LDA, IOP, IOP, LDY, LDA, LDX, IOP, NIP, LDA, TSX, IOP, LDY, LDA, LDX, IOP,
/* C0 */ CPY, CMP, IOP, IOP, CPY, CMP, DEC, IOP, INY, CMP, DEX, IOP, CPY, CMP, DEC, IOP,
/* D0 */ BNE, CMP, IOP, IOP, IOP, CMP, DEC, IOP, CLD, CMP, IOP, IOP, IOP, CMP, DEC, IOP,
/* E0 */ CPX, SBC, IOP, IOP, CPX, SBC, INC, IOP, INX, SBC, NOP, IOP, CPX, SBC, INC, IOP,
/* F0 */ BEQ, SBC, IOP, IOP, IOP, SBC, INC, IOP, SED, SBC, IOP, IOP, IOP, SBC, INC, IOP
};

const unsigned char cycles_table[256] =
{
//        00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F
/* 00 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 10 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 20 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 30 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 40 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 50 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 60 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 70 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 80 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* 90 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* A0 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* B0 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* C0 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* D0 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* E0 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0,
/* F0 */   7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0
};

const enum addressing_mode addrmode_table[256] =
{
//         00    01    02    03    04    05    06    07    08    09    0A    0B    0C    0D    0E    0F
/* 00 */ IMPL, XIND, NONE, NONE, NONE,  ZPG,  ZPG, NONE, IMPL,  IMM,  ACC, NONE, NONE,  ABS,  ABS, NONE,
/* 10 */  REL, INDY, NONE, NONE, NONE, ZPGX, ZPGX, NONE, IMPL, ABSY, NONE, NONE, NONE, ABSX, ABSX, NONE,
/* 20 */  ABS, XIND, NONE, NONE,  ZPG,  ZPG,  ZPG, NONE, IMPL,  IMM,  ACC, NONE,  ABS,  ABS,  ABS, NONE,
/* 30 */  REL, INDY, NONE, NONE, NONE, ZPGX, ZPGX, NONE, IMPL, ABSY, NONE, NONE, NONE, ABSX, ABSX, NONE,
/* 40 */ IMPL, XIND, NONE, NONE, NONE,  ZPG,  ZPG, NONE, IMPL,  IMM,  ACC, NONE,  ABS,  ABS,  ABS, NONE,
/* 50 */  REL, INDY, NONE, NONE, NONE, ZPGX, ZPGX, NONE, IMPL, ABSY, NONE, NONE, NONE, ABSX, ABSX, NONE,
/* 60 */ IMPL, XIND, NONE, NONE, NONE,  ZPG,  ZPG, NONE, IMPL,  IMM,  ACC, NONE,  IND,  ABS,  ABS, NONE,
/* 70 */  REL, INDY, NONE, NONE, NONE, ZPGX, ZPGX, NONE, IMPL, ABSY, NONE, NONE, NONE, ABSX, ABSX, NONE,
/* 80 */ NONE, XIND, NONE, NONE,  ZPG,  ZPG,  ZPG, NONE, IMPL, NONE, IMPL, NONE,  ABS,  ABS,  ABS, NONE,
/* 90 */  REL, INDY, NONE, NONE, ZPGX, ZPGX, ZPGY, NONE, IMPL, ABSY, IMPL, NONE, NONE, ABSX, NONE, NONE,
/* A0 */  IMM, XIND,  IMM, NONE,  ZPG,  ZPG,  ZPG, NONE, IMPL,  IMM, IMPL, NONE,  ABS,  ABS,  ABS, NONE,
/* B0 */  REL, INDY, NONE, NONE, ZPGX, ZPGX, ZPGY, NONE, IMPL, ABSY, IMPL, NONE, ABSX, ABSX, ABSY, NONE,
/* C0 */  IMM, XIND, NONE, NONE,  ZPG,  ZPG,  ZPG, NONE, IMPL, ABSY, IMPL, NONE,  ABS,  ABS,  ABS, NONE,
/* D0 */  REL, INDY, NONE, NONE, NONE, ZPGX, ZPGX, NONE, IMPL, ABSY, NONE, NONE, NONE, ABSX, ABSX, NONE,
/* E0 */  IMM, XIND, NONE, NONE,  ZPG,  ZPG,  ZPG, NONE, IMPL,  IMM, IMPL, NONE,  ABS,  ABS,  ABS, NONE,
/* F0 */  REL, INDY, NONE, NONE, NONE, ZPGX, ZPGX, NONE, IMPL, ABSY, NONE, NONE, NONE, ABSX, ABSX, NONE
};

// clang-format on
