#ifndef FT_TCP_SOCKET_H
#define FT_TCP_SOCKET_H

struct TcpSocket {
    int fd;
    char *host;
    int port;
};

struct TcpSocket *tcpSocketCreate(char *host, int port);
int tcpSocketConnect(struct TcpSocket *socket);
ssize_t tcpSocketReceive(struct TcpSocket *socket, void *buffer, size_t nBytes);
ssize_t tcpSocketSend(struct TcpSocket *socket, const void *buffer, size_t nBytes);
int tcpSocketClose(struct TcpSocket *socket);
void tcpSocketDestroy(struct TcpSocket *socket);

#endif // FT_TCP_SOCKET_H
