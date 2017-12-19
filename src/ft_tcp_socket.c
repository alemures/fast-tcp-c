#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
// In header file: <sys/types.h> <stdint.h>
#include "ft_tcp_socket.h"

struct ft_tcpSocket *ft_tcpSocketCreate(char *host, uint16_t port) {
    struct ft_tcpSocket *socket = (struct ft_tcpSocket *) malloc(sizeof(struct ft_tcpSocket));
    if (socket == NULL) return NULL;

    socket->host = host;
    socket->port = port;

    return socket;
}

int ft_tcpSocketConnect(struct ft_tcpSocket *sock) {
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

ssize_t ft_tcpSocketReceive(struct ft_tcpSocket *socket, void *buffer, size_t nBytes) {
    return recv(socket->fd, buffer, nBytes, 0);
}

ssize_t ft_tcpSocketSend(struct ft_tcpSocket *socket, const void *buffer, size_t nBytes) {
    return send(socket->fd, buffer, nBytes, 0);
}

int ft_tcpSocketShutdown(struct ft_tcpSocket *socket) {
    return shutdown(socket->fd, SHUT_RDWR);
}

int ft_tcpSocketClose(struct ft_tcpSocket *socket) {
    return close(socket->fd);
}

void ft_tcpSocketDestroy(struct ft_tcpSocket *socket) {
    free(socket);
}
