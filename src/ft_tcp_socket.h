#ifndef FT_TCP_SOCKET_H
#define FT_TCP_SOCKET_H

#include <stdint.h>
#include <sys/types.h>

struct ft_tcpSocket {
    int fd;
    char *host;
    uint16_t port;
};

struct ft_tcpSocket *ft_tcpSocketCreate(char *host, uint16_t port);
int ft_tcpSocketConnect(struct ft_tcpSocket *socket);
ssize_t ft_tcpSocketReceive(struct ft_tcpSocket *socket, void *buffer, size_t nBytes);
ssize_t ft_tcpSocketSend(struct ft_tcpSocket *socket, const void *buffer, size_t nBytes);
int ft_tcpSocketShutdown(struct ft_tcpSocket *socket);
int ft_tcpSocketClose(struct ft_tcpSocket *socket);
void ft_tcpSocketDestroy(struct ft_tcpSocket *socket);

#endif // FT_TCP_SOCKET_H
