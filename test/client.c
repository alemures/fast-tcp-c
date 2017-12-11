#include <stdio.h>
#include <stdlib.h>
#include "../src/ft_socket.h"
#include "../src/ft_util.h"

int main(int argc, char *argv[]) {
    struct ft_socket *socket = ft_socketCreate("127.0.0.1", 5000);
    if (socket == NULL) {
        ft_utilLogError("Error creating socket");
        exit(-1);
    }

    ft_socketConnect(socket);
    ft_socketClose(socket);
    ft_socketDestroy(socket);
}
