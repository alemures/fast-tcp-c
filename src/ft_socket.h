#ifndef FT_SOCKET_H
#define FT_SOCKET_H

#include "ft_tcp_socket.h"

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

#endif // FT_SOCKET_H
