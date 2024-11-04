#pragma once

#include <sys/types.h>
#include <sys/socket.h>

namespace udp {
    const int UDP_TYPE = SOCK_DGRAM;
    int create_socket ();
    int bind_socket (int socket_fd, int port, char *ip);
    int send_to (int socket_fd, const void *message, size_t length, int flags, 
                const struct sockaddr *dest_addr, socklen_t dest_len);
    int recv_from (int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);
};