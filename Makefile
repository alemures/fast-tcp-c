CC=gcc
CFLAGS=-c -Wall

all: directories compile
	
directories:
	mkdir -p build

compile:
	$(CC) $(CFLAGS) lib/TcpSocket.c -o build/TcpSocket.o
	$(CC) $(CFLAGS) lib/Utils.c -o build/Utils.o

examples:
	$(CC) build/TcpSocket.o build/Utils.o example/tcpClient.c -o build/tcpClient
	$(CC) lib/Utils.c example/test.c -o build/test

clean:
	rm -r build/
