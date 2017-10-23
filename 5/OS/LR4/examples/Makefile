TARGETS = signal.out pipe.out \
fifo_server.out fifo_client.out \
msg_server.out msg_client.out \
semaphore_master.out semaphore_slave.out \
shmem_writer.out shmem_reader.out 


CC = gcc
CFLAGS = -Wall

all: $(TARGETS)

%.out: %.c
		$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

shmem_writer.out: shmem_writer.c shmem_msg.c
		$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

shmem_reader.out: shmem_reader.c shmem_msg.c
		$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
		rm -f $(TARGETS)
