CC=gcc
CFLAGS=-c -Wall -std=c11
LDFLAGS=

all: create_build_dir ft_tcp_socket.o ft_serializer.o ft_util.o ft_socket.o

create_build_dir:
	mkdir -p build

ft_tcp_socket.o:
	$(CC) $(CFLAGS) src/ft_tcp_socket.c -o build/ft_tcp_socket.o

ft_serializer.o:
	$(CC) $(CFLAGS) src/ft_serializer.c -o build/ft_serializer.o

ft_util.o:
	$(CC) $(CFLAGS) src/ft_util.c -o build/ft_util.o

ft_socket.o:
	$(CC) $(CFLAGS) src/ft_socket.c -o build/ft_socket.o

test_build: build
	${CC} ${LDFLAGS} build/ft_tcp_socket.o build/ft_util.o test/tcp_client.c -o build/tcp_client
	$(CC) ${LDFLAGS} build/ft_util.o test/test.c -o build/test
	$(CC) ${LDFLAGS} build/ft_util.o build/ft_serializer.o  test/serializer.c -o build/serializer

clean:
	rm -r build