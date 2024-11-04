#pragma once

#include <sys/types.h>
#include <sys/socket.h>

namespace tcp {
    const int TCP_TYPE = SOCK_STREAM;
    int create_socket ();
    int bind_socket (int socket_fd, int port);
    int listen_on_socket (int socket_fd);
    int accept_client (int s, struct sockaddr *addr, socklen_t *addrlen);
    int send_to (int socket_fd, const void *message, size_t length, int flags);
    int recv_from (int s, void *buf, size_t len, int flags);
    void *recv_all  (int s, void *buf, size_t len, int flags); //nullprt on failure
    int connect_to_server (int socket, const struct sockaddr *address, socklen_t address_len);
};