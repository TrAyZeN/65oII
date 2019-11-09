#include "cpu.h"
#include "utils.h"
#include "instructions.h"
//#include "disassembler.h"

int main()
{
    reset();
    load_ROM("rom");
    memoryDump(RAM_OFFSET, 0x30);

    run();

    //disassemble("rom", "rom.asm");

    return 0;
}

