#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <netinet/in.h>

#include "udp.hpp"

int udp::create_socket () {
    return socket (AF_INET, udp::UDP_TYPE, 0);
}

int udp::bind_socket (int socket_fd, int port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    return bind (socket_fd, (sockaddr *)&addr, sizeof (addr));
}

int udp::send_to (int socket_fd, const void *message, size_t length, int flags, 
                const struct sockaddr *dest_addr, socklen_t dest_len) {
    static size_t len;
    len = length;
    printf ("len = %d\n", len);
    sendto (socket_fd, &len, sizeof (len), flags, dest_addr, dest_len);
    return sendto(socket_fd, message, length, flags, dest_addr, dest_len);
}

int udp::recv_from (int socket_fd, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen) {
    size_t send_len;
    recvfrom (socket_fd, &send_len, sizeof (send_len), flags, from, fromlen);
    printf ("send_len = %d\n", send_len);
    return recvfrom (socket_fd, buf, len, flags, from, fromlen);
}

void *udp::recv_all (int socket_fd, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen) {
    size_t send_len;
    recvfrom (socket_fd, &send_len, sizeof (send_len), flags, from, fromlen);
    printf ("send_len = %d\n", send_len);

    void *main_buf = buf;
    if (send_len <= len) {
        int status = recv (socket_fd, buf, len, flags);
        return (status == -1) ? nullptr : buf; 
    }

    main_buf = (void *)calloc (send_len + 1, sizeof(char));

    int status = recv (socket_fd, main_buf, send_len, flags);
    return (status == -1) ? nullptr : main_buf; 
}