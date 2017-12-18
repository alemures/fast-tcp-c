#ifndef FT_SOCKET_H
#define FT_SOCKET_H

#include <stdbool.h>
#include <pthread.h>
#include <stdint.h>
#include "ft_tcp_socket.h"

extern const char FT_EVENT_CONNECT;
extern const char FT_EVENT_SOCKET_CONNECT;
extern const char FT_EVENT_END;
extern const char FT_EVENT_CLOSE;
extern const char FT_EVENT_ERROR;
extern const char FT_EVENT_RECONNECTING;

extern const uint32_t FT_MAX_MESSAGE_ID;

struct ft_socket {
    struct ft_tcpSocket *socket;
    bool connected;
    uint32_t messageId;
    char *id;

    pthread_t *receiverThread;
};

struct ft_socket *ft_socketCreate(char *host, uint16_t port);
void ft_socketConnect(struct ft_socket *socket);
void ft_socketClose(struct ft_socket *socket);
void ft_socketDestroy(struct ft_socket *socket);

uint32_t ft_socketNextMessageId(struct ft_socket *socket);
void *ft_socketReceiverThreadHandler(void *args);
void ft_socketReceiver(struct ft_socket *socket);
void ft_socketProcess(struct ft_socket *socket, unsigned char *buffer);

#endif // FT_SOCKET_H
