#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "tcp.hpp"

const int ERROR_CODE = -1;

int init_tsp_server (int port) {
    int socket_fd = tcp::create_socket ();
    if (socket_fd == -1) {
        perror("create socket error");
        return ERROR_CODE;
    }
    
    int fcntl_status = fcntl (socket_fd, F_SETFL, O_NONBLOCK);
    if (fcntl_status) {
        perror ("fcntl error");
        return ERROR_CODE;
    }

    int bind_status = tcp::bind_socket (socket_fd, port);
    if (bind_status) {
        perror ("bind error");
        return ERROR_CODE;
    }

    int listen_status = tcp::listen_on_socket (socket_fd);
    if (listen_status < 0) {
        perror ("listen error");
        return ERROR_CODE;
    }

    return socket_fd;
}

void skip_whitespaces (char *str, int len = -1) {
    if (len < 0) 
        len = strlen (str);
    while (len) {
        if (isspace(str[len - 1])) {
            --len;
        }else {
            break;
        }
    }
    str[len] = '\0';
}

int run_server_loop (int client_fd) {
    const int buf_max_size = 255;
    char buf [buf_max_size] = "";
    
    int n_written_bytes = 0;
    int is_full = 1;

    while (1) {
        printf ("Awaiting client msg...\n");

        char *msg = (char *)tcp::recv_all(client_fd, (void*)buf, buf_max_size - 1, 0);
        if (!msg) {
            perror ("recv() error");
            return ERROR_CODE;
        }
        skip_whitespaces (msg);

        if(!strcmp(msg, "exit")) {
            printf ("client quit the session.\n");
            break;
        }

        printf ("client %d: %s\n>", client_fd, msg);
        fflush (stdout);
        char *buf_addr = &buf[0];
        if (msg != buf_addr)
            free (msg);

        memset(&buf, 0, sizeof(buf));

        int input_size = read(STDIN_FILENO, buf, buf_max_size);
        if (input_size < 0) {
            fprintf (stderr, "No input.\n");
            return -1;
        } 

        skip_whitespaces (buf);
        
        if (!strcmp(buf, "exit")) {
            tcp::send_to(client_fd, (void*)buf, input_size, 0);
            printf ("bye-bye!\n");
            break;
        }

        n_written_bytes += tcp::send_to(client_fd, (void*)buf, input_size, 0);
        memset(&buf, 0, sizeof(buf));
    }
    return 0;
}

int shall_stop_accept () {
    while (1) {
        printf ("No clients detected, continue?(y/n)");
        char ans;
        while (isspace(ans = getchar())) {;}

        if (ans == 'y') {
            return 0;
        } else if (ans == 'n') {
            return 1;
        }
    }
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

    int client_socket_fd = 0;
    
    int step = 0;
    while (1) {
        char cmd[64] = "";
        int quit = 0;

        if(!step) {
            printf ("Waiting for client...\n");
            step = 1;
        }
     
        sleep(5);
        client_socket_fd = tcp::accept_client (socket_fd, NULL, NULL); //todo: use select () with timeout 
        if (client_socket_fd < 0) {
            if (errno == EAGAIN) {
                if (!(quit = shall_stop_accept ())) {
                    continue;
                }
                break;
            }
        }

        if (client_socket_fd < 0) {
            perror ("accept error");
            return ERROR_CODE;
        }

        printf ("Socket %d just connected.\n", client_socket_fd);

        run_server_loop (client_socket_fd);
        step = 0;
    }

    close (socket_fd);

    return 0;
}