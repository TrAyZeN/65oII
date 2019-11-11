#include "cpu.h"
#include "utils.h"
#include "instructions.h"

int main()
{
    reset();
    load_ROM("rom");
    memoryDump(RAM_OFFSET, 0x30);

    run();

    return 0;
}

