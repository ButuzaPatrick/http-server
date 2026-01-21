#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define ROOT "C:/Users/butuz/Documents/Projects/http-server/http-server/c-http-server/files"
#define SUCCESS 1
#define FAIL 0

struct sockaddr {
    sa_family_t sa_family;
    char sa_data[14];
} SockAddr;

int create_socket();
int bind_socket(int server_fd, const struct sockaddr *addr, socklen_t addrlen);

int main(int argc, char *argv[]) {
    if (argc < 2 || strcmp(argv[1], "run") != 0) {
        printf("Usage: ./server run");
        exit(1);
    }

    int server_fd = create_socket();
    
    // socket
    // bind
    // listen
    // accept
    // recv
    // parse
    // get_file
    // build_response
    // send_response
    // close

    exit(0);
}

int create_socket() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    return server_fd;
}

int bind_socket(int server_fd, const struct sockaddr *addr, socklen_t addrlen) {
    bind(server_fd, addr, addrlen);

    return SUCCESS;
}
