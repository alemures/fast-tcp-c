#include <stdlib.h>
// In header file: <stdbool.h> <pthread.h>
#include "ft_socket.h"
#include "ft_tcp_socket.h"
#include "ft_util.h"

const unsigned int MAX_MESSAGE_ID = 4294967295;

struct ft_socket *ft_socketCreate(char *host, unsigned short port) {
    struct ft_socket *socket = (struct ft_socket *) malloc(sizeof(struct ft_socket));
    if (socket == NULL) return NULL;
    socket->socket = ft_tcpSocketCreate(host, port);
    if (socket->socket == NULL) {
        free(socket);
        return NULL;
    }
    socket->receiverThread = (pthread_t *) malloc(sizeof(pthread_t));
    if (socket->receiverThread == NULL) {
        ft_tcpSocketDestroy(socket->socket);
        free(socket);
        return NULL;
    }
    socket->connected = false;
    socket->messageId = 1;
    socket->id = NULL;
    return socket;
}

void ft_socketConnect(struct ft_socket *socket) {
    pthread_create(socket->receiverThread, NULL, &ft_socketReceiver, socket);
}

void ft_socketClose(struct ft_socket *socket) {
    pthread_join(*socket->receiverThread, NULL);
}

void ft_socketDestroy(struct ft_socket *socket) {
    free(socket->receiverThread);
    ft_tcpSocketDestroy(socket->socket);
    free(socket);
}

unsigned int ft_socketNextMessageId(struct ft_socket *socket) {
    if (++socket->messageId >= MAX_MESSAGE_ID) {
        socket->messageId = 1;
    }
    return socket->messageId;
}

void *ft_socketReceiver(void *args) {
    struct ft_socket *socket = (struct ft_socket *) args;

    int res = ft_tcpSocketConnect(socket->socket);
    if (res == -1) {
        ft_utilLogError("Could not connect in thread");
        return NULL;
    }

    char buffer[32];
    ssize_t bytesRead = ft_tcpSocketReceive(socket->socket, &buffer, 32);
    if (bytesRead == -1) {
        ft_utilLogError("Could not receive data in thread");
        return NULL;
    } else if (bytesRead == 0) {
        ft_utilLogWarning("No messages available or socket disconnected in thread");
        return NULL;
    }

    buffer[bytesRead] = '\0';
    ft_utilLogDebug("Received: %s\n", buffer);

    ft_tcpSocketClose(socket->socket);
    return NULL;
}
