CC=gcc
CMNCFLAGS=-I include -Wall -Wextra
CFLAGS=$(CMNCFLAGS) -O3
DBCFLAGS=$(CMNCFLAGS) -O0
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

db:
	$(CC) -g -o bin/main_db.exe src/main.c src/DAFl.c $(DBCFLAGS)
	gdb bin/main_db.exe

pre: src/main.c
	$(CC) -E $^ $(CFLAGS) > preprocessor_build.c

clean:
	del /f src\obj\*.o