#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tcp.hpp"

const int ERROR_CODE = -1;

int init_tsp_server (int port) {
    int socket_fd = tcp::create_socket ();
    if (socket_fd == -1) {
        perror("create socket error");
        return ERROR_CODE;
    }

    int bind_status = tcp::bind_socket (socket_fd, port);
    if (bind_status) {
        perror ("bind error:");
        return ERROR_CODE;
    }

    int listen_status = tcp::listen_on_socket (socket_fd);
    if (listen_status < 0) {
        perror ("listen error");
        return ERROR_CODE;
    }

    return socket_fd;
}

int run_server_loop (int client_fd) {
    char msg [1024] = "";
    
    int n_read_bytes = 0;
    int n_written_bytes = 0;

    while (1) {
        printf ("Awaiting client msg...\n");
        n_read_bytes += tcp::recv_from(client_fd, (void*)msg, sizeof(msg), 0);
        
        if(!strcmp(msg, "exit")) {
            printf ("client quit the session.\n");
            break;
        }

        printf ("client %d: %s\n>", client_fd, msg);
        fflush (stdout);
        
        memset(&msg, 0, sizeof(msg));

        int input_size = read(STDIN_FILENO, msg, 1024);
        if (input_size < 0) {
            fprintf (stderr, "No input.\n");
            return -1;
        } 

        msg[input_size - 1] = '\0'; // rm '\n' for strcmp 
        
        if (!strcmp(msg, "exit")) {
            tcp::send_to(client_fd, (void*)msg, input_size, 0);
            printf ("bye-bye!\n");
            break;
        }

        n_written_bytes += tcp::send_to(client_fd, (void*)msg, input_size, 0);
        memset(&msg, 0, sizeof(msg));
    }
    return 0;
}

int main(int argc, char **argv){
    if (argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        return ERROR_CODE;
    }

    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);
    
    int socket_fd = init_tsp_server (port);
    if (socket_fd == ERROR_CODE) {
        return ERROR_CODE;
    }

    // char buffer[1024]= "";

    struct sockaddr_in client_addr;
    memset(&client_addr, '\0', sizeof(client_addr));
    socklen_t client_addr_size = sizeof(client_addr);
    
    int client_socket_fd = tcp::accept_client (socket_fd, NULL, NULL);
    printf ("%d\n", client_socket_fd);

    run_server_loop (client_socket_fd);

    // int bytes_recv = tcp::recv_from (client_socket_fd, buffer, sizeof(buffer), 0);
    // printf("[+]Data recv %d: %s\n",bytes_recv, buffer);
    // bzero(buffer, 1024);

    // strcpy(buffer, "Welcome");
    // tcp::send_to(client_socket_fd, buffer, sizeof(buffer), 0);
    // printf("[+]Data send: %s\n", buffer);

    close (socket_fd);

    return 0;
}