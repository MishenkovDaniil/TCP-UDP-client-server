#include "udp.hpp"
// #include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <netinet/in.h>
#include <arpa/inet.h>

int udp::create_socket () {
    return socket (AF_INET, udp::UDP_TYPE, 0);
}

int udp::bind_socket (int socket_fd, int port, char *ip) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    return bind (socket_fd, (sockaddr *)&addr, sizeof (addr));
}

int udp::send_to (int socket_fd, const void *message, size_t length, int flags, 
                const struct sockaddr *dest_addr, socklen_t dest_len) {
    return sendto(socket_fd, message, length, flags, dest_addr, dest_len);
}

int udp::recv_from (int socket_fd, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen) {
    return recvfrom (socket_fd, buf, len, flags, from, fromlen);
}