IDIR=include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11
SDIR=src
ODIR=obj
LDIR=lib
BDIR=bin

LIBS=-lm

_DEPS = calc1c.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = calc1c.o  
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

install: $(OBJ)
	$(CC) -o $(BDIR)/calc1c $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
