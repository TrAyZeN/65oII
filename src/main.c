#include "cpu.h"
#include "debug.h"
#include "instructions.h"
#include "stdio.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Not enough argument provided, \
            use -h flag for more information\n");
        return 1;
    }
    reset();
    load_rom(argv[1]);
    dump_memory(RAM_OFFSET, 0x31);

    run();

    return 0;
}
