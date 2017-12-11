#ifndef FT_SOCKET_H
#define FT_SOCKET_H

#include <stdbool.h>
#include <pthread.h>
#include "ft_tcp_socket.h"

struct ft_socket {
    struct ft_tcpSocket *socket;
    bool connected;
    int messageId;
    char *id;

    pthread_t *thread;
};

struct ft_socket *ft_socketCreate(char *host, int port);
void ft_socketConnect(struct ft_socket *socket);
void ft_socketClose(struct ft_socket *socket);
void ft_socketDestroy(struct ft_socket *socket);

void *ft_socketReceiver(void *args);

#endif // FT_SOCKET_H
