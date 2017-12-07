#ifndef FT_SOCKET_H
#define FT_SOCKET_H

#include "ft_tcp_socket.h"

struct ft_socket {
    struct ft_tcpSocket *socket;
    int connected;
    int messageId;
    char *id;
};

struct ft_socket *ft_socketCreate(char *host, int port);
void ft_socketConnect(struct ft_socket *socket);
void ft_socketClose(struct ft_socket *socket);
void ft_socketDestroy(struct ft_socket *socket);

#endif // FT_SOCKET_H
