CC=gcc
CFLAGS=-I include -Wall -Wextra -O3
DEPS=include/HPCP.h
ODIR=src/obj

CHECKS_BIN_DIR=checks/bin
CHECKS_SRC_DIR=checks

CHECKS_SRC=limb.c
CHECKS=$(addprefix $(CHECKS_BIN)/, $(CHECKS_SRC:.c=.exe))

all: comphead comp run

run:
	./bin/main

comp: $(ODIR)/main.o $(ODIR)/HPCP.o
	$(CC) -o bin/main $^ $(CFLAGS)

comphead: $(ODIR)/header_before_comp.o
	$(CC) -o bin/comphead $^ $(CFLAGS)
	./bin/comphead

check: $(CHECKS)
	./$(CHECKS)

$(CHECKS_BIN_DIR)/%.exe: check/%.c $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pre: src/main.c
	$(CC) -E $^ $(CFLAGS) > preprocessor_build.c

clean:
	del /f src\obj\*.o