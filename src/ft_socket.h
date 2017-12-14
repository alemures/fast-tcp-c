#ifndef FT_SOCKET_H
#define FT_SOCKET_H

#include <stdbool.h>
#include <pthread.h>
#include "ft_tcp_socket.h"

enum ft_event {
    FT_EVENT_CONNECT,
    FT_EVENT_SOCKET_CONNECT,
    FT_EVENT_END,
    FT_EVENT_CLOSE,
    FT_EVENT_ERROR,
    FT_EVENT_RECONNECTING
};

extern const unsigned int MAX_MESSAGE_ID;

struct ft_socket {
    struct ft_tcpSocket *socket;
    bool connected;
    unsigned int messageId;
    char *id;

    pthread_t *receiverThread;
};

struct ft_socket *ft_socketCreate(char *host, unsigned short port);
void ft_socketConnect(struct ft_socket *socket);
void ft_socketClose(struct ft_socket *socket);
void ft_socketDestroy(struct ft_socket *socket);

unsigned int ft_socketNextMessageId();
void *ft_socketReceiver(void *args);

#endif // FT_SOCKET_H
