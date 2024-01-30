#include "cpu.h"
#include "utils.h"

byte full_adder(const byte a, const byte b, byte *c) {
    byte r = 0;
    byte cout;

    byte cin = *c;
    for (int i = 0; i < 8; i++) {
        byte ba = a >> i & 1;
        byte bb = b >> i & 1;

        cout = (ba & bb) | (bb & cin) | (ba & cin);
        r |= (cin ^ (ba ^ bb)) << i;

        cin = cout;
    }

    *c = cout;
    return r;
}

byte bcd_adder(byte a, byte b, byte *c) {
    byte r = 0;
    byte cout;

    byte cin = *c;
    for (int i = 0; i < 2; i++) {
        byte ba = (a & 0xF << i * 4) >> i * 4;
        byte bb = (b & 0xF << i * 4) >> i * 4;

        byte rr =
            ba + bb + cin + 6; // simple addition and + 6 to convert back to BCD

        r |= (rr & 0xF) << i * 4;
        cout = rr & 0x10;

        cin = cout;
    }

    *c = cout;
    return r;
}
