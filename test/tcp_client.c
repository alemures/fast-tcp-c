#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/FT_tcp_socket.h"
#include "../src/FT_util.h"

#define BUFFER_SIZE 32
char buffer[BUFFER_SIZE];

void sendString(struct FT_TcpSocket *socket, char *string) {
    sprintf(buffer, "%s", string);
    printf("-> %s\n", buffer);

    ssize_t bytesSent = FT_TcpSocketSend(socket, string, strlen(string));
    if (bytesSent == -1) {
        FT_UtilLogError("Could not receive data");
        exit(-1);
    } else if (bytesSent == 0) {
        FT_UtilLogWarning("No messages available or socket disconnected");
        exit(-1);
    }
}

void receiveString(struct FT_TcpSocket *socket) {
    ssize_t bytesRead = FT_TcpSocketReceive(socket, buffer, BUFFER_SIZE);
    if (bytesRead == -1) {
        FT_UtilLogError("Could not receive data");
        exit(-1);
    } else if (bytesRead == 0) {
        FT_UtilLogWarning("No messages available or socket disconnected");
        exit(0);
    }

    buffer[bytesRead] = '\0';
    printf("<- %s\n", buffer);
}

int main(int argc, char *argv[]) {
    struct FT_TcpSocket *socket = FT_TcpSocketCreate("127.0.0.1", 5000);
    if (socket == NULL) {
        FT_UtilLogError("Error creating socket\n");
        exit(-1);
    }

    int res = FT_TcpSocketConnect(socket);
    if (res == -1) {
        FT_UtilLogError("Could not connect");
        exit(-1);
    }

    sendString(socket, "hi server");
    receiveString(socket);

    sendString(socket, "goodbye");
    receiveString(socket);

    res = FT_TcpSocketClose(socket);
    if (res == -1) {
        FT_UtilLogError("Could not close");
        exit(-1);
    }

    FT_TcpSocketDestroy(socket);

    return 0;
}
