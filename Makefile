CC=gcc
CFLAGS=-I include -Wall -Wextra -O3
DEPS=include/DAFL.h
ODIR=src/obj

CHECKS_BIN=checks/bin

CHECKS_SRC=limb.c
CHECKS=$(addprefix $(CHECKS_BIN)/, $(CHECKS_SRC:.c=.exe))

all: comphead comp run

run:
	./bin/main

comp: $(ODIR)/main.o $(ODIR)/DAFL.o
	$(CC) -o bin/main $^ $(CFLAGS)

comphead:
	./comphead

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pre: src/main.c
	$(CC) -E $^ $(CFLAGS) > preprocessor_build.c

clean:
	del /f src\obj\*.o