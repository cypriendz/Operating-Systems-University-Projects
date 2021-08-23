CFLAGS=-std=c99

SRC = characters.c room.c items.c adventure.c 

OBJ = characters.o room.o items.o adventure.o

PROG = GAME

$(PROG): $(OBJ)
	gcc $(OBJ) -o $(PROG)

$(OBJ): $(SRC)
	gcc -c $(SRC)
