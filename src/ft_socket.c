#include <stdlib.h>
// In header file: <stdbool.h> <pthread.h>
#include "ft_socket.h"
#include "ft_tcp_socket.h"
#include "ft_reader.h"
#include "ft_serializer.h"
#include "ft_util.h"

const char FT_EVENT_CONNECT = 1;
const char FT_EVENT_SOCKET_CONNECT = 2;
const char FT_EVENT_END = 3;
const char FT_EVENT_CLOSE = 4;
const char FT_EVENT_ERROR = 5;
const char FT_EVENT_RECONNECTING = 6;

const unsigned int FT_MAX_MESSAGE_ID = 4294967295;

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
    pthread_create(socket->receiverThread, NULL, &ft_socketReceiverThreadHandler, socket);
}

void ft_socketClose(struct ft_socket *socket) {
    pthread_join(*socket->receiverThread, NULL);
}

void ft_socketDestroy(struct ft_socket *socket) {
    free(socket->id);
    free(socket->receiverThread);
    ft_tcpSocketDestroy(socket->socket);
    free(socket);
}

unsigned int ft_socketNextMessageId(struct ft_socket *socket) {
    if (++socket->messageId >= FT_MAX_MESSAGE_ID) {
        socket->messageId = 1;
    }
    return socket->messageId;
}

void *ft_socketReceiverThreadHandler(void *args) {
    struct ft_socket *socket = (struct ft_socket *) args;

    int res = ft_tcpSocketConnect(socket->socket);
    if (res == -1) {
        ft_utilLogError("Could not connect in thread");
        return NULL;
    }

    socket->connected = true;
    ft_socketReceiver(socket);
    socket->connected = false;

    ft_tcpSocketClose(socket->socket);
    return NULL;
}

void ft_socketReceiver(struct ft_socket *socket) {
    ssize_t bytesRead;
    unsigned char chunk[1024];
    int buffersRead = 0;
    unsigned char *buffers[256];
    struct ft_reader *reader = ft_readerCreate();
    if (reader == NULL) {
        ft_utilLogError("Could not create ft_reader in thread");
        return;
    }

    while(true) {
        bytesRead = ft_tcpSocketReceive(socket->socket, &chunk, 1024);
        if (bytesRead == -1) {
            ft_utilLogError("Could not receive data in thread");
            return;
        } else if (bytesRead == 0) {
            ft_utilLogWarning("No messages available or socket disconnected in thread");
            return;
        }

        buffersRead = ft_readerRead(reader, chunk, bytesRead, buffers);
        if (buffersRead > 0) {
            for (int i = 0; i < buffersRead; i++) {
                ft_socketProcess(socket, buffers[i]);
                free(buffers[i]);
            }
        }
    }

    ft_readerDestroy(reader);
}

void ft_socketProcess(struct ft_socket *socket, unsigned char *buffer) {
    size_t bufferLength = ft_serializerBufferLength(buffer);
    char mt = ft_serializerDeserializeMt(buffer);

    if (mt == FT_MT_DATA) {
        ft_utilPrintBytes(buffer, bufferLength);
    } else if (mt == FT_MT_REGISTER) {
        socket->id = ft_serializerDeserializeDataString(buffer);
    } else if (mt == FT_MT_ERROR) {
        char *error = ft_serializerDeserializeDataString(buffer);
        ft_utilLogDebug("MT error: %s", error);
    }
}
