#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "tcp.hpp"
#include "../shared.hpp"

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
    const int buf_max_size = 1023;
    char buf [buf_max_size + 1] = "";
    
    int n_written_bytes = 0;

    while (1) {
        printf ("> ");
        fflush (stdout);

        int input_size = read(STDIN_FILENO, buf, buf_max_size);
        if (input_size < 0) {
            fprintf (stderr, "No input.\n");
            return -1;
        } 

        skip_whitespaces(buf);

        if (!strcmp(buf, "exit")) {
            tcp::send_to(server_fd, (void*)buf, input_size, 0);
            printf ("bye-bye!\n");
            break;
        }
        n_written_bytes += tcp::send_to(server_fd, (void*)buf, input_size, 0);
        
        printf ("Awaiting server response...\n");
        
        memset(&buf, 0, sizeof(buf));
        
        char *msg = (char *)tcp::recv_all(server_fd, (void*)buf, buf_max_size, 0);
        if (!msg) {
            perror ("recv error");
            return ERROR_CODE;
        }

        skip_whitespaces (msg);

        if(!strcmp(msg, "exit")) {
            printf ("Server has quit the session.\n");
            break;
        }

        printf ("Server: %s\n", msg);
        char *buf_addr = &buf[0];
        if (msg != buf_addr) 
            free (msg);

        memset(&buf, 0, sizeof(buf));
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
    
    close (socket_fd);

    return 0;
}