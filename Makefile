CC=gcc
CFLAGS=-c -Wall -std=c11
LDFLAGS=

all: create_build_dir FT_tcp_socket.o FT_serializer.o FT_util.o FT_socket.o

create_build_dir:
	mkdir -p build

FT_tcp_socket.o:
	$(CC) $(CFLAGS) src/FT_tcp_socket.c -o build/FT_tcp_socket.o

FT_serializer.o:
	$(CC) $(CFLAGS) src/FT_serializer.c -o build/FT_serializer.o

FT_util.o:
	$(CC) $(CFLAGS) src/FT_util.c -o build/FT_util.o

FT_socket.o:
	$(CC) $(CFLAGS) src/FT_socket.c -o build/FT_socket.o

test_build: build
	${CC} ${LDFLAGS} build/FT_tcp_socket.o build/FT_util.o test/tcp_client.c -o build/tcp_client
	$(CC) ${LDFLAGS} build/FT_util.o test/test.c -o build/test
	$(CC) ${LDFLAGS} build/FT_util.o build/FT_serializer.o  test/serializer.c -o build/serializer

clean:
	rm -r build