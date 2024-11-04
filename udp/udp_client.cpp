#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "udp.hpp"
#include "../shared.hpp"

const int ERROR_CODE = -1;

int run_client_loop (int client_fd, int port) {
    const int buf_max_size = 1023;
    char buf[buf_max_size + 1] = "";
    char *buf_addr = &buf[0];

    while (1) {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        printf ("> ");
        fflush (stdout);

        int input_size = read(STDIN_FILENO, buf, buf_max_size);
        if (input_size < 0) {
            fprintf (stderr, "No input.\n");
            return -1;
        } 

        skip_whitespaces(buf);
        if (!strcmp(buf, "exit")) {
            udp::send_to (client_fd, buf, input_size, 0, (struct sockaddr*)&addr, sizeof(addr));
            printf ("bye-bye!\n");
            break;
        }

        printf ("send %s\n", buf);
        int status = udp::send_to (client_fd, buf, input_size, 0, (struct sockaddr*)&addr, sizeof(addr));
        if (status < 0) {
            perror ("send() error");
            return ERROR_CODE;
        }
        printf ("Awaiting server response...\n");

        memset(&buf, 0, sizeof(buf));

        socklen_t addr_size = sizeof(addr);
        char *msg = (char *)udp::recv_all(client_fd, buf, buf_max_size, 0, (struct sockaddr*)&addr, &addr_size);
        if (!msg) {
            perror ("recv() error");
            return ERROR_CODE;
        }
        
        if(!strcmp(msg, "exit")) {
            printf ("Server has quit the session.\n");
            if (msg != buf_addr) {
                free (msg);
            }
            break;
        }

        printf("Server: %s\n", msg);

        if (msg != buf_addr) {
            free (msg);
        } else {
            memset(&buf, 0, sizeof(buf));
        }
    }

    return 0;
}

int main(int argc, char **argv){
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    int port = atoi(argv[1]);

    int socket_fd = udp::create_socket ();

    run_client_loop (socket_fd, port);

    close (socket_fd);

    return 0;
}