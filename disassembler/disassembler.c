#include "disassembler.h"
#include "stdio.h"
#include "stdlib.h"

// clang-format off

char *nemonic_table[256] =
{
//         00   01   02   03   04   05   06   07
/* 00 */ "BRK", "ORA (%02X,X)", "", "", "", "ORA %02X", "ASL %02X", "",
         "PHP", "ORA #%02X", "ASL A", "", "", "ORA %02X%02X", "ASL %02X%02X", "",
/* 10 */ "BPL %02X", "ORA (%02X),Y", "", "", "", "ORA %02X,X", "ASL %02X,X", "",
         "CLC", "ORA %02X%02X,Y", "", "", "", "ORA %02X%02X,X", "ASL %02X%02X,X", "",
/* 20 */ "JSR %02X%02X", "AND (%02X,X)", "", "", "BIT %02X", "AND %02X", "ROL %02X", "",
         "PLP", "AND #%02X", "ROL A", "", "BIT %02X%02X", "AND %02X%02X", "ROL %02X%02X", "",
/* 30 */ "BMI %02X", "AND (%02X),Y", "", "", "", "AND %02X,X", "ROL %02X,X", "", "SEC",
         "AND %02X%02X,Y", "", "", "", "AND %02X%02X,X", "ROL %02X%02X,X", "",
/* 40 */ "RTI", "EOR (%02X,X)", "", "", "", "EOR %02X", "LSR %02X", "",
         "PHA", "EOR #%02X","LSR A", "", "JMP %02X%02X", "EOR %02X%02X", "LSR %02X%02X", "",
/* 50 */ "BVC %02X", "EOR (%02X),Y", "", "", "", "EOR %02X,X", "LSR %02X,X", "",
         "CLI", "EOR %02X%02X,Y", "", "", "", "EOR %02X%02X,X", "LSR %02X%02X,X", "",
/* 60 */ "RTS", "ADC (%02X,X)", "", "", "", "ADC %02X", "ROR %02X", "",
         "PLA", "ADC #%02X", "ROR A", "", "JMP (%02X%02X)", "ADC %02X%02X", "ROR %02X%02X", "",
/* 70 */ "BVS %02X", "ADC (%02X),Y", "", "", "", "ADC %02X,X", "ROR %02X,X", "",
         "SEI", "ADC %02X%02X,Y", "", "", "", "ADC %02X%02X,X", "ROR %02X%02X,X", "",
/* 80 */ "", "STA (%02X, X)", "", "", "STY %02X", "STA %02X", "STX %02X", "",
         "DEY", "", "TXA", "", "STY %02X%02X", "STA %02X%02X", "STX %02X%02X", "",
/* 90 */ "BCC %02X", "STA (%02X),Y", "", "", "STY %02X,X", "STA %02X,X", "STX %02X,Y", "",
         "TYA", "STA %02X%02X,Y", "TXS", "", "", "STA %02X%02X,X", "", "",
/* A0 */ "LDY #%02X", "LDA (%02X,X)", "LDX #%02X", "", "LDY %02X", "LDA %02X", "LDX %02X",
         "", "TAY", "LDA #%02X", "TAX", "", "LDY %02X%02X", "LDA %02X%02X", "LDX %02X%02X", "",
/* B0 */ "BCS %02X", "LDA (%02X),Y", "", "", "LDY %02X,X", "LDA %02X,X", "LDX %02X,Y", "",
         "CLV", "LDA %02X%02X,Y", "TSX", "", "LDY %02X%02X,X", "LDA %02X%02X,X", "LDX %02X%02X,Y", "",
/* C0 */ "CPY #%02X", "CMP (%02X,X)", "", "", "CPY %02X", "CMP %02X", "DEC %02X", "",
         "INY", "CMP #%02X", "DEX", "", "CPY %02X%02X", "CMP %02X%02X", "DEC %02X%02X", "",
/* D0 */ "BNE %02X", "CMP (%02X),Y", "", "", "", "CMP %02X,X", "DEC %02X,X", "",
         "CLD", "CMP %02X%02X,Y", "", "", "", "CMP %02X%02X,X", "DEC %02X%02X,X", "",
/* E0 */ "CPX #%02X", "SBC (%02X,X)", "", "", "CPX %02X", "SBC %02X", "INC %02X", "",
         "INX", "SBC #%02X", "NOP", "", "CPX %02X%02X", "SBC %02X%02X", "INC %02X%02X", "",
/* F0 */ "BEQ %02X", "SBC (%02X),Y", "", "", "", "SBC %02C,X", "INC %02X,X", "",
         "SED", "SBC %02X%02X,Y", "", "", "", "SBC %02X%02X,X", "INC %02X%02X,X", ""
};

unsigned char bytes_table[256] =
{
//       00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
/* 00 */  2, 2, 0, 0, 0, 2, 2, 0, 1, 2, 2, 0, 0, 3, 3, 0,
/* 10 */  2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
/* 20 */  3, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
/* 30 */  2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
/* 40 */  1, 2, 0, 0, 0, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
/* 50 */  2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
/* 60 */  1, 2, 0, 0, 0, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
/* 70 */  2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
/* 80 */  0, 2, 0, 0, 2, 2, 2, 0, 1, 0, 1, 0, 3, 3, 3, 0,
/* 90 */  2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 0, 3, 0, 0,
/* 0A */  2, 2, 2, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
/* OB */  2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
/* 0C */  2, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
/* 0D */  2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
/* 0E */  2, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
/* 0F */  2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0
};

// clang-format on

void disassemble(const char *in_filename, const char *out_filename) {
    FILE *in_file, *out_file;
    char opcode;
    unsigned char next_byte, next_next_byte;

    in_file = fopen(in_filename, "rb");
    if (in_file == NULL) {
        printf("Error : Failed to open input file");
        exit(EXIT_FAILURE);
    }

    out_file = fopen(out_filename, "w");
    if (out_file == NULL) {
        printf("Error : Failed to open output file");
        exit(EXIT_FAILURE);
    }

    while ((opcode = fgetc(in_file)) != EOF) {
        switch (bytes_table[(unsigned char)opcode]) {
        case 1:
            fprintf(out_file, nemonic_table[(unsigned char)opcode]);
            break;
        case 2:
            next_byte = fgetc(in_file);
            fprintf(out_file, nemonic_table[(unsigned char)opcode], next_byte);
            break;
        case 3:
            next_byte = fgetc(in_file);
            next_next_byte = fgetc(in_file);
            fprintf(out_file, nemonic_table[(unsigned char)opcode],
                    next_next_byte, next_byte);
            break;
        default:
            printf("Invalid opcode : %02X\n", (unsigned char)opcode);
            break;
        }
        fprintf(out_file, "\n");
    }

    fclose(in_file);
    fclose(out_file);
}

int main() {
    disassemble("rom", "rom.asm");

    return 0;
}
