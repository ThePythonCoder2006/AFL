CC=gcc
CFLAGS=-I include -Wall -Wextra
DEPS=include/HPCP.h
ODIR=src/obj

comp: $(ODIR)/main.o $(ODIR)/HPCP.o
	$(CC) -o bin/main $^ $(CFLAGS)

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pre: src/main.c
	$(CC) -E $^ $(CFLAGS) > build.c

clean:
	del /f src\obj\*.o