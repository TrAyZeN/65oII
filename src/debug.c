#include "cpu.h"
#include "debug.h"
#include "stdio.h"

void dump_memory(struct emu_state *state, int start, int length) {
    for (int i = start; i < start + length; i++) {
        if ((i - start) % 16 == 0) {
            printf("%08X ", i);
        }

        printf("%02X ", state->mem[i]);

        if ((i - start) % 16 == 15) {
            printf("\n");
        }
    }

    printf("\n");
}
