FIFO = fifo_reader fifo_writer
MSG_PASSING = msg_passing_writer msg_passing_reader

all: fifo

msg_passing: $(MSG_PASSING)

fifo: $(FIFO)

fifo_writer: fifo_P1.c
	gcc fifo_P1.c -o fifo_writer

fifo_reader: fifo_P2.c
	gcc fifo_P2.c -o fifo_reader

fifo_blocking_writer: named_fifo_writer.c
	gcc -o fifo_blocking_writer named_fifo_writer.c

fifo_blocking_reader: named_fifo_reader.c
	gcc -o fifo_blocking_reader named_fifo_reader.c

fifo_non_blocking_writer: named_fifo_writer_nb.c
	gcc -o fifo_non_blocking_writer named_fifo_writer_nb.c

fifo_non_blocking_reader: named_fifo_reader_nb.c
	gcc -o fifo_non_blocking_reader named_fifo_reader_nb.c

msg_passing_writer: msg_passing_writer.c
	gcc -o msg_passing_writer msg_passing_writer.c

msg_passing_reader: msg_passing_reader.c
	gcc -o msg_passing_reader msg_passing_reader.c

clean:
	rm -f $(FIFO)
	rm -r Q2_FIFO