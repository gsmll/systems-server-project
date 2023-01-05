CC=cc
CFLAGS=-Wall -Wextra -Werror -Wpedantic -Wno-unused-variable -std=c2x 
HEADERS=inc/termbox.h inc/utiltype.h
OBJ=hangman.o

hangman.o: $(HEADERS) src/hangman.c
	$(CC) $(CFLAGS) -ltermbox -c src/hangman.c -o hangman.o

compile: $(OBJ)
	$(CC) hangman.o -o hangman~

run: compile 
	./hangman~

clean: 
	rm *.o hangman-local~

all: compile run clean
