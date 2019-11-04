CC=gcc
CFLAGS=-I./include/
LDFLAGS=
EXEC=emulator

all: $(EXEC)

$(EXEC): mrproper
	$(CC) src/*.c -o $(EXEC) $(CFLAGS) $(LDFLAGS) \

clean:
	rm -f *.o core

mrproper: clean
	rm -f $(EXEC)

