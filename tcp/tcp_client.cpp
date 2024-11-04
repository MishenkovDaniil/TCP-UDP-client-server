#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp.hpp"
#include <unistd.h>

const int ERROR_CODE = -1;

int init_tsp_client (int port) {
    int socket_fd = tcp::create_socket ();
    if (socket_fd < 0) {
        return ERROR_CODE;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    int connect_status = tcp::connect_to_server (socket_fd, (const sockaddr *)&addr, sizeof (addr));
    if (connect_status) {
        perror ("connect");
        return ERROR_CODE;
    }

    return socket_fd;
}

int run_client_loop (int server_fd) {
    char msg [1024] = "";
    
    int n_read_bytes = 0;
    int n_written_bytes = 0;

    while (1) {
        printf ("> ");
        fflush (stdout);

        int input_size = read(STDIN_FILENO, msg, 1024);
        if (input_size < 0) {
            fprintf (stderr, "No input.\n");
            return -1;
        } 

        msg[input_size - 1] = '\0'; // rm '\n' for strcmp 

        if (!strcmp(msg, "exit")) {
            tcp::send_to(server_fd, (void*)msg, input_size, 0);
            printf ("bye-bye!\n");
            break;
        }

        n_written_bytes += tcp::send_to(server_fd, (void*)msg, input_size, 0);
        
        printf ("Awaiting server response...\n");
        
        memset(&msg, 0, sizeof(msg));
        
        n_read_bytes += tcp::recv_from(server_fd, (void*)msg, sizeof(msg), 0);
        
        if(!strcmp(msg, "exit")) {
            printf ("Server has quit the session.\n");
            break;
        }

        printf ("Server: %s\n", msg);
        memset(&msg, 0, sizeof(msg));
    }
    return 0;
}

int main(int argc, char **argv){
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return -1;
    }

    int port = atoi(argv[1]);
    
    int socket_fd = init_tsp_client (port);
    if (socket_fd == ERROR_CODE) {
        return ERROR_CODE;
    }

    run_client_loop (socket_fd);
    // char buffer[1024] = "";

    // bzero(buffer, 1024);
    // strcpy(buffer, "Hello, World!");
    // int bytes_num = tcp::send_to (socket_fd, buffer, sizeof(buffer), 0);
    // printf("[+]Data send %d: %s\n",bytes_num, buffer);

    // bzero(buffer, 1024);
    // tcp::recv_from(socket_fd, buffer, sizeof(buffer), 0);
    // printf("[+]Data recv: %s\n", buffer);
    
    close (socket_fd);

    return 0;
}