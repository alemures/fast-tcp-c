#ifndef SOCKET_H
#define SOCKET_H 1

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

#endif
