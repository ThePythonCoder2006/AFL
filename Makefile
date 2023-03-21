CC=gcc

CMNCFLAGS=-Wall -Wextra -std=c11
CFLAGS=$(CMNCFLAGS) -O3
DBCFLAGS=$(CMNCFLAGS) -O0 -dH

LKFLAGS=-I include

IDIR=include
DEPS=$(wildcard $(IDIR)/*.h)

SRCDIR=src
SRCFILES=$(wildcard $(SRCDIR)/DAFL*.c)

ODIR=src/obj
OFILES= $(addprefix $(ODIR)/, $(notdir $(patsubst %.c, %.o, $(SRCFILES))))

run: comphead comp
	./bin/main

comp: $(OFILES) src/obj/main.o
	$(CC) -o bin/main $^ $(LKFLAGS) $(CFLAGS)

comphead:
	./comphead

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(LKFLAGS) $(CFLAGS)

db:
	$(CC) -ggdb3 -o bin/main_db.exe -D_DEBUG $(SRCFILES) src/main.c $(LKFLAGS) $(DBCFLAGS)
	gdb bin/main_db.exe

pre: $(SRCFILES) src/main.c
	$(CC) -E $^ $(LKFLAGS) $(CFLAGS) > preprocessor_build.c

clean:
	del /f src\obj\*.o