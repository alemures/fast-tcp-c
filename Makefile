CC=gcc
CFLAGS=-c -Wall -std=c89

all: directories compile

directories:
	mkdir -p build

compile:
	$(CC) $(CFLAGS) lib/tcpSocket.c -o build/tcpSocket.o
	$(CC) $(CFLAGS) lib/serializer.c -o build/serializer.o
	$(CC) $(CFLAGS) lib/util.c -o build/util.o

examples:
	$(CC) build/tcpSocket.o build/util.o example/tcpClient.c -o build/tcpClient
	$(CC) build/util.o example/test.c -o build/test
	$(CC) build/util.o build/serializer.o  example/serializer.c -o build/serializer

clean:
	rm -r build/
