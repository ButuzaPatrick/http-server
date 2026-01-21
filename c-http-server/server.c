#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define ROOT "C:/Users/butuz/Documents/Projects/http-server/http-server/c-http-server/files"

int main(int argc, char *argv[]) {
    if (argc < 2 || strcmp(argv[1], "run") != 0) {
        printf("Usage: ./server run");
        exit(1);
    }

    int server_fd = socket()

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