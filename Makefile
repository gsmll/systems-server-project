CC=cc
CFLAGS= -Wall -Wextra -Werror -Wpedantic -Wno-unused-variable -Wno-unused-parameter -std=c2x -Wno-implicit-function-declaration
HEADERS=inc/termbox.h inc/utiltype.h inc/includes.h
OBJ=hangman.o 


client.o: $(HEADERS) src/client.c
		$(CC)  -ltermbox -c src/client.c -o client.o

server.o: $(HEADERS) src/server.c
		$(CC) -ltermbox -c src/server.c -o server.o

server: server.o
		./server

client: client.o
		./client

all: server.o client.o
