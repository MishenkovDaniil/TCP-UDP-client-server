#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp.hpp"

int tcp::create_socket () {
    return socket (AF_INET, tcp::TCP_TYPE, 0);
}

int tcp::listen_on_socket (int socket_fd) {
    return listen (socket_fd, 5);
}

int tcp::accept_client (int socket_fd, struct sockaddr *addr, socklen_t *addrlen) {
    return accept(socket_fd, addr, addrlen);
}

int tcp::connect_to_server (int socket_fd, const struct sockaddr *address, socklen_t address_len) {
    return connect (socket_fd, address, address_len);
}

int tcp::bind_socket (int socket_fd, int port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    return bind (socket_fd, (sockaddr *)&addr, sizeof (addr));
}

int tcp::send_to (int socket_fd, const void *message, size_t length, int flags) {
    static size_t len;
    len = length;
    send (socket_fd, &len, sizeof (len), flags);
    return send(socket_fd, message, length, flags);
}

int tcp::recv_from (int socket_fd, void *buf, size_t len, int flags) {
    size_t send_len;
    recv (socket_fd, &send_len, sizeof (send_len), flags);
    return recv (socket_fd, buf, len, flags);
}

void *tcp::recv_all (int socket_fd, void *buf, size_t len, int flags) {
    size_t send_len;
    recv (socket_fd, &send_len, sizeof (send_len), flags);

    void *main_buf = buf;
    if (send_len <= len) {
        int status = recv (socket_fd, buf, len, flags);
        return (status == -1) ? nullptr : buf; 
    }

    main_buf = (void *)calloc (send_len + 1, sizeof(char));

    int status = recv (socket_fd, main_buf, send_len, flags);
    return (status == -1) ? nullptr : main_buf; 
}
