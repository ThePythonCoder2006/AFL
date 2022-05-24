IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)

LIBS=-lhpcp
LDIR=lib
ODIR=src/obj

_DEPS=hpcp.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=HPCP.o main.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

comp: $(OBJ)
	$(CC) -o bin/main $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~