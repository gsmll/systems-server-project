CC=cc
CFLAGS= -Wall -Wextra -Werror -Wpedantic -Wno-unused-variable -Wno-unused-parameter -std=c2x -Wno-implicit-function-declaration
HEADERS=inc/includes.h


compile: client.o server.o 
	$(CC) -o client client.o
	$(CC) -o server server.o

client.o: $(HEADERS) src/client.c
		$(CC) -c src/client.c -o client.o

server.o: $(HEADERS) src/server.c
		$(CC) -c src/server.c -o server.o


server: server.o
		./server

client: client.o
		./client

all: server client

clean: 
	rm client.o server.o server client