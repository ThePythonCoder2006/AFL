CC=gcc

CMNCFLAGS=-Wall -Wextra
CFLAGS=$(CMNCFLAGS) -O3
DBCFLAGS=$(CMNCFLAGS) -O0

LKFLAGS=-I include

IDIR=include
DEPS=$(wildcard $(IDIR)/*.h)

SRCDIR=src
SRCFILES=$(wildcard $(SRCDIR)/DAFL*.c)

ODIR=src/obj
OFILES= $(addprefix $(ODIR)/, $(notdir $(patsubst %.c, %.o, $(SRCFILES))))

all: comphead comp run

run:
	./bin/main

comp: $(OFILES) src/obj/main.o
	$(CC) -o bin/main $^ $(LKFLAGS) $(CFLAGS)

comphead:
	./comphead

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(LKFLAGS) $(CFLAGS)

db:
	$(CC) -g -o bin/main_db.exe src/main.c src/DAFl.c $(DBCFLAGS)
	gdb bin/main_db.exe

pre: src/main.c
	$(CC) -E $^ $(CFLAGS) > preprocessor_build.c

clean:
	del /f src\obj\*.o