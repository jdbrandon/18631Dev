TARG=vuln.c
OBJ=vuln.o
CC=gcc
CFLAGS= -m32 -fno-stack-protector -Wall -Werror
all: $(OBJ) server

$(OBJ): $(TARG)
	$(CC) -o vuln $(CFLAGS) $(TARG)
server: server.c
	gcc -o server server.c
clean:
	rm vuln server
