#INSTRUCTIONS
    Give the command make, to compile all the programs and make their execs. 
    make clean: To remove all the generated exec files
    make fifo: to make fifo files   (run writer first)
    make msg_passing: to make Message Queues execs  (run writer first)
    make socket: to make UNIX-Domain Socket execs   (run reader first with sudo)

Data-Structute Used:
    In all 3 methods, struct was used as it can easily contain the message that has to be passed and also the ID of the msg.

General Idea: 
    Generate an array of strings in msgs.h. Also created a struct containing the string of message to be sent and the int ID of the same. Then 1 by 1 copied the string from array to the struct created, along with its ID.
    Then in a group of 5, sent those structs/packets to the process P2 using various IPC techniques. Upon receiving those 5 packets in P2, finding the greates ID arrived & also printing side-by-side. Then passing the highest ID in a group, to P1 as an acknowledgment.
    P1 then makes the received acknowledgment as its starting index and passes the next 5.. This continues till P1 recives 50 as acknowledgment, then closes the respective IPC mechanism. 

FIFO:
    Created a FIFO using mkfifo, then opened in blocking(default) manner. Then one-by-one started writing the strings in structs & writing those structs on the FIFO. After 5 write-ups, closing the FIFO. Meanwhile, since FIFO was in a blocking manner, a reader process P2 is attached which starts reading & makes sure that the msgs are not read by the same process later.
    When P2 has read all the structs in a group of 5, it captures the highest arrived ID, and then sends it back to P1, while opeing it in write mode. The process P1 receives the acknowledgment ID, and sends the next 5. This continues for all 50 strings, and then P1 destroys the FIFO after receiving the last acknowledgment from P2
    Since, the FIFO was in blocing mode, and in the same process, while switching from read to write or vice-versa, the FIFO was closed and then opened again in required mode. This ensured that the message from one process is not read by the same process only, i.e. controlling the flow of messages.

MESSAGE_QUEUE:
    Created a unique key, and then using it created a message queue. Then created the structs that contained the msg, ID & type of msg. Then sent it in a queue. The messages from P1 were of type1
    P2 was attached to the same message queue using the same unique key. Then it read the messages of type1, printed the ids & msgs. Meanwhile, for every set of 5 msgs, it finds the greatest ID and sends it to P1, but this time the msg type is 2.
    P1 reads the messages of type 2 & receives the acknowledgment from P2, then sending the next 5 packs. 
    While reading, the queue status was checked constantly using msgctl & IPC_STAT. Msgs were read till the queue did not become empty.

SOCKETS:
    In the server, created a socket using the pathname as currernt directory, Then unlinked any previous(if) linked servers to the pathname. Then binded the socket with the server, after which listening mode was made on, for the server to be in active mode. Then in always true while loop, a client(P1) was attached, and the messages it sent was printed. Then an acknowledgment was sent to the client, using write.
    In the client, generated array of 50 random strings & then passed each of them to the server socket, after creating a socket here & linking/connecting it to the server socket. After that, waited for the acknowledgment from server, and then proceeded to send next 5, till 50.
    The sockets were made in local domain, i.e. UNIX Domain using AF_UNIX
