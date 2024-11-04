#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "udp.hpp"

int main(int argc, char **argv){
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);

    int socket_fd = udp::create_socket ();

    struct sockaddr_in addr;
    char buffer[1024];
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY; // inet_addr (ip)

    bzero(buffer, 1024);
    strcpy(buffer, "Hello, World!");
    udp::send_to (socket_fd, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));
    printf("[+]Data send: %s\n", buffer);

    bzero(buffer, 1024);
    socklen_t addr_size = sizeof(addr);
    udp::recv_from(socket_fd, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
    printf("[+]Data recv: %s\n", buffer);

    return 0;
}