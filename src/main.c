#include "cpu.h"
#include "utils.h"
#include "instructions.h"

int main()
{
    reset();
    loadROM("rom");
    memoryDump(0, 0x30);

    run();

    return 0;
}

