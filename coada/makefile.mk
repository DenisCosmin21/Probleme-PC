CC = gcc

CFLAGS = -g -Wall -O3

TARGET = program

all : ${TARGET}

$(TARGET):
	$(CC) $(CFLAGS) -c Queue.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(TARGET).x Queue.o client.o

clean:
	$(RM) $(TARGET).x
