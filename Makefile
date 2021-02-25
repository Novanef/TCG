CC=gcc
CFLAGS=-g -Wall -Wextra -std=c99
EXEC=main
BIN=bin/
HDR=headers/
SRC=src/

all: $(EXEC)

main : main.o plateau.o interface.o structures.o carte.o deck.o
	$(CC) $(BIN)interface.o $(BIN)structures.o $(BIN)plateau.o $(BIN)deck.o $(BIN)main.o -o $(BIN)main $(CFLAGS)

main.o : $(SRC)main.c $(HDR)plateau.h $(HDR)interface.h $(HDR)carte.h $(HDR)deck.h
	$(CC) -o $(BIN)main.o -c $(SRC)main.c $(CFLAGS)

carte.o : $(SRC)carte.c $(HDR)structures.h $(HDR)carte.h
	$(CC) -o $(BIN)carte.o -c $(SRC)carte.c $(CFLAGS)

plateau.o: $(SRC)plateau.c $(HDR)plateau.h $(HDR)carte.h
	$(CC) -o  $(BIN)plateau.o  -c $(SRC)plateau.c $(CFLAGS)

interface.o : $(SRC)interface.c plateau.o structures.o
	$(CC) -o  $(BIN)interface.o  -c $(SRC)interface.c $(CFLAGS)

structures.o : $(SRC)structures.c
	$(CC) -o  $(BIN)structures.o -c $(SRC)structures.c $(CFLAGS)

deck.o : $(SRC)deck.c
	$(CC) -o  $(BIN)deck.o -c $(SRC)deck.c $(CFLAGS)
clean:
	rm -rf  $(BIN)*.o

mrproper: clean
	rm -rf  $(BIN)$(EXEC)

run:
	$(BIN)$(EXEC)