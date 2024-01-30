#include "cpu.h"
#include "utils.h"

byte full_adder(const byte a, const byte b, byte *c) {
    byte r = 0;
    byte c_out;

    byte c_in = *c;
    for (int i = 0; i < 8; i++) {
        byte ba = a >> i & 1;
        byte bb = b >> i & 1;

        c_out = (ba & bb) | (bb & c_in) | (ba & c_in);
        r |= (c_in ^ (ba ^ bb)) << i;

        c_in = c_out;
    }

    *c = c_out;
    return r;
}

byte bcd_adder(byte a, byte b, byte *c) {
    byte r = 0;
    byte c_out;

    byte c_in = *c;
    for (int i = 0; i < 2; i++) {
        byte ba = (a & 0xF << i * 4) >> i * 4;
        byte bb = (b & 0xF << i * 4) >> i * 4;

        byte rr = ba + bb + c_in
            + 6; // simple addition and + 6 to convert back to BCD

        r |= (rr & 0xF) << i * 4;
        c_out = rr & 0x10;

        c_in = c_out;
    }

    *c = c_out;
    return r;
}
