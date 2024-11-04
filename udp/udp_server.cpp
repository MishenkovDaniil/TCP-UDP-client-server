#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "udp.hpp"


int main(int argc, char **argv){
    if (argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);
    
    int socket_fd = udp::create_socket ();
    if (socket_fd == -1) {
        perror("[-]socket error");
        exit(1);
    }

    int bind_status = udp::bind_socket (socket_fd, port, ip);
    if (bind_status) {
        perror ("Bind error:");
        exit (1);
    }

    char buffer[1024];

    bzero(buffer, 1024);
    struct sockaddr_in client_addr;
    memset(&client_addr, '\0', sizeof(client_addr));
    socklen_t client_addr_size = sizeof(client_addr);
    
    udp::recv_from (socket_fd, buffer, 1024, 0, (struct sockaddr*)&client_addr, &client_addr_size);
    printf("[+]Data recv: %s\n", buffer);
    bzero(buffer, 1024);

    strcpy(buffer, "Welcome to the UDP Server.");
    udp::send_to(socket_fd, buffer, 1024, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
    printf("[+]Data send: %s\n", buffer);

    return 0;
}