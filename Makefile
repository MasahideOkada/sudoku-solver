CC = gcc
CFLAGS = -fdiagnostics-color=always -Wall -I$(HOME)/sudoku-solver/include
DEST = $(HOME)/sudoku-solver
OBJS = main.o grid.o
PROGRAM = sudoku

all: $(PROGRAM)

$(PROGRAM): src/main.c src/grid.c
			$(CC) $(CFLAGS) -o $(PROGRAM) src/main.c src/grid.c

clean: rm -f *.o *~ $(PROGRAM)

install:    $(PROGRAM)
			install -s $(PROGRAM) $(DEST)
