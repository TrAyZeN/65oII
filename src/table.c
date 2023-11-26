#include "cpu.h"
#include "instructions.h"

// clang-format off

instruction_func instructions_table[256] =
{
//        00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F
/* 00 */ ibrk, ora, iop, iop, iop, ora, asl, iop, php, ora, asl, iop, iop, ora, asl, iop,
/* 10 */ bpl, ora, iop, iop, iop, ora, asl, iop, clc, ora, iop, iop, iop, ora, asl, iop,
/* 20 */ jsr, and, iop, iop, bit, and, nip, iop, plp, and, nip, iop, nip, and, nip, iop,
/* 30 */ bmi, and, iop, iop, iop, and, nip, iop, sec, and, iop, iop, iop, and, nip, iop,
/* 40 */ rti, eor, iop, iop, iop, eor, lsr, iop, pha, eor, lsr, iop, jmp, eor, lsr, iop,
/* 50 */ bvc, eor, iop, iop, iop, eor, lsr, iop, cli, eor, iop, iop, iop, eor, lsr, iop,
/* 60 */ rts, nip, iop, iop, iop, nip, nip, iop, pla, nip, nip, iop, jmp, nip, nip, iop,
/* 70 */ bvs, nip, iop, iop, iop, nip, nip, iop, sei, nip, iop, iop, iop, nip, nip, iop,
/* 80 */ iop, sta, iop, iop, sty, sta, stx, iop, dey, iop, txa, iop, sty, sta, stx, iop,
/* 90 */ bcc, sta, iop, iop, sty, sta, stx, iop, tya, sta, txs, iop, iop, sta, iop, iop,
/* A0 */ ldy, lda, ldx, iop, ldy, lda, ldx, iop, tay, lda, tax, iop, ldy, lda, ldx, iop,
/* B0 */ bcs, lda, iop, iop, ldy, lda, ldx, iop, nip, lda, tsx, iop, ldy, lda, ldx, iop,
/* C0 */ cpy, cmp, iop, iop, cpy, cmp, dec, iop, iny, cmp, dex, iop, cpy, cmp, dec, iop,
/* D0 */ bne, cmp, iop, iop, iop, cmp, dec, iop, cld, cmp, iop, iop, iop, cmp, dec, iop,
/* E0 */ cpx, sbc, iop, iop, cpx, sbc, inc, iop, inx, sbc, nop, iop, cpx, sbc, inc, iop,
/* F0 */ beq, sbc, iop, iop, iop, sbc, inc, iop, sed, sbc, iop, iop, iop, sbc, inc, iop
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
