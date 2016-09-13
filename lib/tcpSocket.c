#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include "tcpSocket.h"

struct TcpSocket *tcpSocketCreate(char *host, int port) {
    struct TcpSocket *sock = (struct TcpSocket *) malloc(sizeof(struct TcpSocket));
    if (sock == 0) {
        return NULL;
    }

    sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->fd == -1) {
        return NULL;
    }

    sock->host = host;
    sock->port = port;

    return sock;
}

int tcpSocketConnect(struct TcpSocket *socket) {
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(struct sockaddr_in));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(socket->host);
    serverAddress.sin_port = htons(socket->port);

    int connectResult = connect(socket->fd, (struct sockaddr *) &serverAddress, sizeof(struct sockaddr_in));
    if (connectResult == -1) {
        return -1;
    }

    return 0;
}

ssize_t tcpSocketReceive(struct TcpSocket *socket, void *buffer, size_t nBytes) {
    return recv(socket->fd, buffer, nBytes, 0);
}

ssize_t tcpSocketSend(struct TcpSocket *socket, const void *buffer, size_t nBytes) {
    return send(socket->fd, buffer, nBytes, 0);
}

int tcpSocketClose(struct TcpSocket *socket) {
    int closeResult = close(socket->fd);
    if (closeResult == -1) {
        return -1;
    }

    return 0;
}
