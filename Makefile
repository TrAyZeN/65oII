CC=gcc
CFLAGS=-I./include/
LDFLAGS=
EXEC=emulator
DASM=65oII_disassembler

all: $(EXEC) $(DASM)

$(EXEC): mrproper
	$(CC) src/*.c -o $(EXEC) $(CFLAGS) $(LDFLAGS)

$(DASM):
	$(CC) disassembler/disassembler.c -o $(DASM) -I./disassembler/

clean:
	rm -f *.o core

mrproper: clean
	rm -f $(EXEC) $(DASM)

