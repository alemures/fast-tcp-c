#ifndef FT_SOCKET_H
#define FT_SOCKET_H

#include "FT_tcp_socket.h"

struct FT_Socket {
    struct FT_TcpSocket *socket;
    int connected;
    int messageId;
    char *id;
};

struct FT_Socket *FT_SocketCreate(char *host, int port);
void FT_SocketConnect(struct FT_Socket *socket);
void FT_SocketClose(struct FT_Socket *socket);
void FT_SocketDestroy(struct FT_Socket *socket);

#endif /* FT_SOCKET_H */
