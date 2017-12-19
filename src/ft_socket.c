#include <stdlib.h>
// In header file: <stdbool.h> <pthread.h> <stdint.h>
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

const uint32_t FT_MAX_MESSAGE_ID = 4294967295;
const size_t FT_RECEIVER_CHUNK_SIZE = 1024;
const size_t FT_RECEIVER_BUFFER_NUM = 256;

struct ft_socket *ft_socketCreate(char *host, uint16_t port) {
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
    int res = pthread_create(socket->receiverThread, NULL, &ft_socketReceiverThreadHandler, socket);
    if (res != 0) {
        ft_utilLogError("Error creating thread");
    }
}

void ft_socketClose(struct ft_socket *socket) {
    int res = ft_tcpSocketShutdown(socket->socket);
    if (res == -1) {
        ft_utilLogError("Error shutting down socket");
        return;
    }

    res = pthread_join(*socket->receiverThread, NULL);
    if (res != 0) {
        ft_utilLogError("Error joining thread");
    }
}

void ft_socketDestroy(struct ft_socket *socket) {
    free(socket->id);
    free(socket->receiverThread);
    ft_tcpSocketDestroy(socket->socket);
    free(socket);
}

uint32_t ft_socketNextMessageId(struct ft_socket *socket) {
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
    unsigned char chunk[FT_RECEIVER_CHUNK_SIZE];
    unsigned char *buffers[FT_RECEIVER_BUFFER_NUM];
    struct ft_reader *reader = ft_readerCreate();
    if (reader == NULL) {
        ft_utilLogError("Could not create ft_reader in thread");
        return;
    }

    while(true) {
        ssize_t bytesRead = ft_tcpSocketReceive(socket->socket, &chunk, FT_RECEIVER_CHUNK_SIZE);
        if (bytesRead == -1) {
            ft_utilLogError("Could not receive data in thread");
            break;
        } else if (bytesRead == 0) {
            ft_utilLogWarning("No messages available or socket disconnected in thread");
            break;
        }

        ssize_t buffersRead = ft_readerRead(reader, chunk, bytesRead, buffers);
        if (buffersRead == -1) {
            ft_utilLogError("Chunk of bytes couldn't be processed");
            break;
        } else if (buffersRead > 0) {
            for (size_t i = 0; i < buffersRead; i++) {
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
