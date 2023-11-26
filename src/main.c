#include <err.h>
#include <stdlib.h>

#include "cpu.h"
#include "debug.h"
#include "instructions.h"
#include "stdio.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Not enough argument provided, "
               "use -h flag for more information\n");
        return 1;
    }

    struct emu_state *state = calloc(1, sizeof(struct emu_state));
    if (state == NULL) {
        err(1, "Failed to allocate state");
    }

    reset(state);
    load_rom(state, argv[1]);
    dump_memory(state, RAM_OFFSET, 0x31);

    run(state);

    free(state);

    return 0;
}
