CC=cc
CFLAGS=-Wall -Wextra -Werror -Wpedantic -Wno-unused-variable -Wno-unused-parameter -std=c2x 
HEADERS=inc/termbox.h inc/utiltype.h
OBJ=hangman.o hangman-conf.o hangman-fileio.o hangman-flag.o

hangman.o: $(HEADERS) src/hangman.c
	$(CC) $(CFLAGS) -ltermbox -c src/hangman.c -o hangman.o

hangman-conf.o: $(HEADERS) src/hangman-conf.c 
	$(CC) $(CFLAGS) -c src/hangman-fileio.c -o hangman-conf.o

hangman-fileio.o: $(HEADERS) src/hangman-fileio.c 
	$(CC) $(CFLAGS) -c src/hangman-fileio.c -o hangman-fileio.o

hangman-flag.o: $(HEADERS) src/hangman-flag.c 
	$(CC) $(CFLAGS) -c src/hangman-flag.c -o hangman-flag.o

compile: $(OBJ)
	$(CC) $(OBJ) -o hangman~

run: compile 
	./hangman~

clean: 
	rm *.o hangman-local~

all: compile run clean
