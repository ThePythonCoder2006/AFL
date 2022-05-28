CC=gcc
CFLAGS=-I include
DEPS=include/HPCP.h
ODIR=src/obj

comp: $(ODIR)/main.o $(ODIR)/HPCP.o
	$(CC) -o bin/main $^

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	del /f src\obj\*.o