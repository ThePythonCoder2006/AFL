CC=gcc
CFLAGS=-I include -Wall -Wextra
DEPS=include/HPCP.h
ODIR=src/obj

all: comphead comp run

run:
	./bin/main

comp: $(ODIR)/main.o $(ODIR)/HPCP.o
	$(CC) -o bin/main $^ $(CFLAGS)

comphead: $(ODIR)/header_before_comp.o
	./bin/comphead

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pre: src/main.c
	$(CC) -E $^ $(CFLAGS) > build.c

clean:
	del /f src\obj\*.o