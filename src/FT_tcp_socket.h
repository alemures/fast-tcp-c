#ifndef FT_TCP_SOCKET_H
#define FT_TCP_SOCKET_H

struct FT_TcpSocket {
    int fd;
    char *host;
    int port;
};

struct FT_TcpSocket *FT_TcpSocketCreate(char *host, int port);
int FT_TcpSocketConnect(struct FT_TcpSocket *socket);
ssize_t FT_TcpSocketReceive(struct FT_TcpSocket *socket, void *buffer, size_t nBytes);
ssize_t FT_TcpSocketSend(struct FT_TcpSocket *socket, const void *buffer, size_t nBytes);
int FT_TcpSocketClose(struct FT_TcpSocket *socket);
void FT_TcpSocketDestroy(struct FT_TcpSocket *socket);

#endif /* FT_TCP_SOCKET_H */
