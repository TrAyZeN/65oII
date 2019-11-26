#include "cpu.h"
#include "debug.h"
#include "instructions.h"
#include "utils.h"
#include "stdio.h"

int main()
{
    reset();
    load_ROM("rom");
    memoryDump(RAM_OFFSET, 0x30);

    run();

    return 0;
}

