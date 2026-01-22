#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);  // must match server port
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        return 1;
    }

    // Send data
    // PING = 0
    // GET = 1
    uint8_t type = 1;
    uint16_t size = 6;
    char payload[] = "hello\n";

    char msg[9];
    msg[0] = type;
    memcpy(msg + 1, &size, 2);
    memcpy(msg + 3, payload, 6);

    printf("MESSAGE: ");
    for (int i = 0; i < 9; i++) {
        printf("%02X ", (uint8_t)msg[i]);
    }
    printf("\n");

    send(sockfd, msg, 9, 0);

    // Receive response
    char buffer[1024];
    int bytes = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("REPLY: ");
        for (int i = 0; i < sizeof(buffer); i++) {
            printf("%02X ", (uint8_t)buffer[i]);
        }
        printf("\n");
    }

    // NEED TO PARSE RESPONSES

    close(sockfd);
    return 0;
}
