#include "utils.h"
#include "cpu.h"
#include "stdio.h"

void memoryDump(int start, int length)
{
    int i;

    for (i = start; i < start+length; i++)
    {
        if ((i-start)%16 == 0)
            printf("%08X ", i);

        printf("%02X ", mem[i]);

        if ((i-start)%16 == 15)
            printf("\n");
    }

    printf("\n");
}

