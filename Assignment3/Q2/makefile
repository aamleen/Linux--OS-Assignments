FIFO = fifo_reader fifo_writer
MSG_PASSING = msg_passing_writer msg_passing_reader
SOCKET = socket_writer socket_reader

all: fifo msg_passing socket

msg_passing: $(MSG_PASSING)

fifo: $(FIFO)

socket: $(SOCKET)

fifo_writer: fifo_P1.c
	gcc fifo_P1.c -o fifo_writer

fifo_reader: fifo_P2.c
	gcc fifo_P2.c -o fifo_reader

msg_passing_writer: msg_passing_writer.c
	gcc -o msg_passing_writer msg_passing_writer.c

msg_passing_reader: msg_passing_reader.c
	gcc -o msg_passing_reader msg_passing_reader.c

socket_writer:	socket_client.c
	gcc -o socket_writer socket_client.c

socket_reader:	socket_server.c
	gcc -o socket_reader socket_server.c

clean:
	rm -f $(FIFO)
	rm -f $(MSG_PASSING)
	rm -f $(SOCKET)
	rm -r Q2_FIFO