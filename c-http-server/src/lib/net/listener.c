#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int listener(char* host, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    // configure socket
}