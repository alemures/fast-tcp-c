#ifndef SOCKET_H
#define SOCKET_H 1

#include "tcpSocket.h"

struct Socket {
    struct TcpSocket *socket;
    int connected;
    int messageId;
    char *id;
};

struct Socket *socketCreate(char *host, int port);
void socketConnect(struct Socket *socket);
void socketClose(struct Socket *socket);
void socketDestroy(struct Socket *socket);

#endif
