#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ROOT "C:/Users/butuz/Documents/Projects/http-server/http-server/c-http-server/files"
#define SUCCESS 1
#define FAIL 0
#define MAX_BACKLOG 100

int create_socket(char *ip_address, int port);
int bind_socket(int server_fd, const struct sockaddr *addr, socklen_t addrlen);

int main(int argc, char *argv[]) {
    if (argc < 2 || strcmp(argv[1], "run") != 0) {
        printf("Usage: ./server run\n");
        exit(1);
    }

    int server_fd = create_socket("192.168.1.100", 8080);
    if (server_fd == FAIL) {
        printf("Failed to create socket\n");
    }
    
    int listening = listen(server_fd, MAX_BACKLOG);
    if (listening < 0) {
        printf("Failed to set listening\n");
        exit(1);
    }
    printf("Listening...\n");

    

    // socket DONE
    // bind DONE
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

int create_socket(char *ip_address, int port) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip_address, &addr.sin_addr); // convert ip address and port using ip into network bytes
    memset(addr.sin_zero, 0, sizeof(addr.sin_zero));

    printf("Family: %d\n", addr.sin_family);
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr.sin_addr, ip_str, sizeof(ip_str)); 
    printf("Address: %s\n", ip_str);
    printf("Port: %d\n", ntohs(addr.sin_port));

    return server_fd;
}

int bind_socket(int server_fd, const struct sockaddr *addr, socklen_t addrlen) {
    bind(server_fd, addr, addrlen);

    return SUCCESS;
}
