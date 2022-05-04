SOCKET: socket_P1 socket_P2

all: sockets

sockets: $(SOCKETS)

socket_P2: socket_server.c
	gcc socket_server.c -o socket_P2

socket_P1: socket_client.c
	gcc socket_client.c -o socket_P1

clean:
	rm -r socket_P1 socket_P2