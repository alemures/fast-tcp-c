#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include "FT_tcp_socket.h"

struct FT_TcpSocket *FT_TcpSocketCreate(char *host, int port) {
    struct FT_TcpSocket *socket = (struct FT_TcpSocket *) malloc(sizeof(struct FT_TcpSocket));
    if (socket == 0) {
        return NULL;
    }

    socket->host = host;
    socket->port = port;

    return socket;
}

int FT_TcpSocketConnect(struct FT_TcpSocket *sock) {
    sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->fd == -1) {
        return -1;
    }

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(struct sockaddr_in));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(sock->host);
    serverAddress.sin_port = htons(sock->port);

    int connectResult = connect(sock->fd, (struct sockaddr *) &serverAddress, sizeof(struct sockaddr_in));
    if (connectResult == -1) {
        return -1;
    }

    return 0;
}

ssize_t FT_TcpSocketReceive(struct FT_TcpSocket *socket, void *buffer, size_t nBytes) {
    return recv(socket->fd, buffer, nBytes, 0);
}

ssize_t FT_TcpSocketSend(struct FT_TcpSocket *socket, const void *buffer, size_t nBytes) {
    return send(socket->fd, buffer, nBytes, 0);
}

int FT_TcpSocketClose(struct FT_TcpSocket *socket) {
    int closeResult = close(socket->fd);
    if (closeResult == -1) {
        return -1;
    }

    return 0;
}

void FT_TcpSocketDestroy(struct FT_TcpSocket *socket) {
    free(socket);
}
