#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/ft_tcp_socket.h"
#include "../src/ft_util.h"

#define BUFFER_SIZE 32
char buffer[BUFFER_SIZE];

void sendString(struct ft_tcpSocket *socket, char *string) {
    sprintf(buffer, "%s", string);
    printf("-> %s\n", buffer);

    ssize_t bytesSent = ft_tcpSocketSend(socket, string, strlen(string));
    if (bytesSent == -1) {
        ft_utilLogError("Could not receive data");
        exit(-1);
    } else if (bytesSent == 0) {
        ft_utilLogWarning("No messages available or socket disconnected");
        exit(-1);
    }
}

void receiveString(struct ft_tcpSocket *socket) {
    ssize_t bytesRead = ft_tcpSocketReceive(socket, buffer, BUFFER_SIZE);
    if (bytesRead == -1) {
        ft_utilLogError("Could not receive data");
        exit(-1);
    } else if (bytesRead == 0) {
        ft_utilLogWarning("No messages available or socket disconnected");
        exit(0);
    }

    buffer[bytesRead] = '\0';
    printf("<- %s\n", buffer);
}

int main(int argc, char *argv[]) {
    struct ft_tcpSocket *socket = ft_tcpSocketCreate("127.0.0.1", 5000);
    if (socket == NULL) {
        ft_utilLogError("Error creating ft_tcpSocket");
        exit(-1);
    }

    int res = ft_tcpSocketConnect(socket);
    if (res == -1) {
        ft_utilLogError("Could not connect");
        exit(-1);
    }

    receiveString(socket);

    sendString(socket, "hi server");
    receiveString(socket);

    sendString(socket, "goodbye");
    receiveString(socket);

    res = ft_tcpSocketClose(socket);
    if (res == -1) {
        ft_utilLogError("Could not close");
        exit(-1);
    }

    ft_tcpSocketDestroy(socket);

    return 0;
}
