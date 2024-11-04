#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tcp.hpp"


int main(int argc, char **argv){
    if (argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        return -1;
    }

    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);
    
    int socket_fd = tcp::create_socket ();
    if (socket_fd == -1) {
        perror("[-]socket error");
        return -1;
    }

    int bind_status = tcp::bind_socket (socket_fd, port);
    if (bind_status) {
        perror ("Bind error:");
        return -1;
    }

    int listen_status = tcp::listen_on_socket (socket_fd);
    if (listen_status < 0) {
        perror ("listen");
        return -1;
    }

    char buffer[1024];

    bzero(buffer, 1024);
    struct sockaddr_in client_addr;
    memset(&client_addr, '\0', sizeof(client_addr));
    socklen_t client_addr_size = sizeof(client_addr);
    
    int client_socket_fd = tcp::accept_client (socket_fd, NULL, NULL);
    printf ("%d\n", client_socket_fd);

    int bytes_recv = tcp::recv_from (client_socket_fd, buffer, sizeof(buffer), 0);
    printf("[+]Data recv %d: %s\n",bytes_recv, buffer);
    bzero(buffer, 1024);

    strcpy(buffer, "Welcome");
    tcp::send_to(client_socket_fd, buffer, sizeof(buffer), 0);
    printf("[+]Data send: %s\n", buffer);

    close (socket_fd);

    return 0;
}