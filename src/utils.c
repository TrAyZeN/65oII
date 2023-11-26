#include "utils.h"

#include "cpu.h"

byte full_adder(const byte a, const byte b, byte *c) {
    int i;
    byte ba, bb, cin, cout, r;

    cin = *c;
    for (i = 0, r = 0; i < 8; i++) {
        ba = a >> i & 1;
        bb = b >> i & 1;

        cout = (ba & bb) | (bb & cin) | (ba & cin);
        r |= (cin ^ (ba ^ bb)) << i;

        cin = cout;
    }

    *c = cout;
    return r;
}

byte BCD_adder(byte a, byte b, byte *c) {
    int i;
    byte ba, bb, cin, cout, r, rr;

    cin = *c;
    for (i = 0, r = 0; i < 2; i++) {
        ba = (a & 0xF << i * 4) >> i * 4;
        bb = (b & 0xF << i * 4) >> i * 4;

        rr =
            ba + bb + cin + 6; // simple addition and + 6 to convert back to BCD

        r |= (rr & 0xF) << i * 4;
        cout = rr & 0x10;

        cin = cout;
    }

    *c = cout;
    return r;
}
