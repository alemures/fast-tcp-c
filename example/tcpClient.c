#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/tcpSocket.h"
#include "../lib/util.h"

#define BUFFER_SIZE 32
char buffer[BUFFER_SIZE];

void sendString(struct TcpSocket *socket, char *string) {
    sprintf(buffer, "%s", string);
    printf("-> %s\n", buffer);

    ssize_t bytesSent = tcpSocketSend(socket, string, strlen(string));
    if (bytesSent == -1) {
        utilLogError("Could not receive data");
        exit(-1);
    } else if (bytesSent == 0) {
        utilLogWarning("No messages available or socket disconnected");
        exit(-1);
    }
}

void receiveString(struct TcpSocket *socket) {
    ssize_t bytesRead = tcpSocketReceive(socket, buffer, BUFFER_SIZE);
    if (bytesRead == -1) {
        utilLogError("Could not receive data");
        exit(-1);
    } else if (bytesRead == 0) {
        utilLogWarning("No messages available or socket disconnected");
        exit(0);
    }

    buffer[bytesRead] = '\0';
    printf("<- %s\n", buffer);
}

int main(int argc, char *argv[]) {
    struct TcpSocket *socket = tcpSocketCreate("127.0.0.1", 5000);
    if (socket == NULL) {
        utilLogError("Error creating socket\n");
        exit(-1);
    }

    int res = tcpSocketConnect(socket);
    if (res == -1) {
        utilLogError("Could not connect");
        exit(-1);
    }

    sendString(socket, "hi server");
    receiveString(socket);

    sendString(socket, "goodbye");
    receiveString(socket);

    tcpSocketClose(socket);

    return 0;
}
