#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "udp.hpp"
#include "../shared.hpp"

const int ERROR_CODE = -1;

int init_udp_server (int port) {
    int socket_fd = udp::create_socket ();
    if (socket_fd == -1) {
        perror("[-]socket error");
        return ERROR_CODE;
    }

    int bind_status = udp::bind_socket (socket_fd, port);
    if (bind_status) {
        perror ("Bind error:");
        return ERROR_CODE;
    }

    return socket_fd;
}

int run_server_loop (int socket_fd) {
    const int buf_max_size = 1023;
    
    char buf[buf_max_size + 1] = "";
    char *buf_addr = &buf[0];

    while (1) {
        struct sockaddr_in client_addr;
        memset(&client_addr, '\0', sizeof(client_addr));
        socklen_t client_addr_size = sizeof(client_addr);
        
        char *msg = (char *)udp::recv_all (socket_fd, buf, buf_max_size, 0, (struct sockaddr*)&client_addr, &client_addr_size);
        if (!msg) {
            perror ("recv() error");
            return ERROR_CODE;
        }
        
        skip_whitespaces (msg);

        if (!strcmp (msg, "exit")) {
            printf ("client has quit.\n");
            if (buf_addr != msg) {
                free (msg);
            }
            break;
        }

        printf("Client: %s\n", msg);

        if (buf_addr != msg) {
            free (msg);
        } else {
            memset(&buf, 0, sizeof(buf));
        }

        int input_size = read(STDIN_FILENO, buf, buf_max_size);
        if (input_size < 0) {
            fprintf (stderr, "No input.\n");
            return ERROR_CODE;
        } 

        skip_whitespaces (buf);

        udp::send_to(socket_fd, buf, input_size, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
        memset(&buf, 0, sizeof(buf));
    }
    return 0;
}

int main(int argc, char **argv){
    if (argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    int port = atoi(argv[1]);
    
    int socket_fd = init_udp_server (port);
    if (socket_fd == ERROR_CODE) {
        return ERROR_CODE;
    }

    run_server_loop (socket_fd);

    close (socket_fd);
    return 0;
}