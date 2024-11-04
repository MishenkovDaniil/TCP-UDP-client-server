#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp.hpp"
#include <unistd.h>

int main(int argc, char **argv){
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return -1;
    }

    int port = atoi(argv[1]);
    int socket_fd = tcp::create_socket ();

    char buffer[1024];

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY; // inet_addr (ip)
    
    int connect_status = tcp::connect_to_server (socket_fd, (const sockaddr *)&addr, sizeof (addr));
    if (connect_status) {
        perror ("connect");
        return -1;
    }

    bzero(buffer, 1024);
    strcpy(buffer, "Hello, World!");
    int bytes_num = tcp::send_to (socket_fd, buffer, sizeof(buffer), 0);
    printf("[+]Data send %d: %s\n",bytes_num, buffer);

    bzero(buffer, 1024);
    socklen_t addr_size = sizeof(addr);
    tcp::recv_from(socket_fd, buffer, sizeof(buffer), 0);
    printf("[+]Data recv: %s\n", buffer);
    
    close (socket_fd);

    return 0;
}