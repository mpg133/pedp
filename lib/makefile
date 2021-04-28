CC=g++
OPTIONS= -g 
DEBUG= #-D DEBUG
LIBDIR=lib
INCLUDEDIR=include
_OBJ= tcalendario.o tvectorcalendario.o tlistacalendario.o 
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

tad:    src/tad20.cpp $(OBJ)
	$(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) src/tad20.cpp $(OBJ) -o tad

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -o $@ $<

clean:
	rm -f $(OBJ) 
