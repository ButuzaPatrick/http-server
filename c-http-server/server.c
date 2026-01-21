#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define ROOT "C:/Users/butuz/Documents/Projects/http-server/http-server/c-http-server/files"
#define SUCCESS 1
#define FAIL 0
#define MAX_BACKLOG 100
#define MAX_PAYLOAD 1024
#define IP_ADDRESS "127.0.0.1"
#define PORT 8080

#define TYPES_COUNT 2
#define PING 0
#define GET 1

typedef struct {
    uint8_t type;
    uint16_t size;
    char payload[MAX_PAYLOAD];
} Request;

Request parse_request(char *content, uint16_t len_content);
Request invalid_request();
char* gen_response(Request request);

int main(int argc, char *argv[]) {
    if (argc < 2 || strcmp(argv[1], "run") != 0) {
        printf("Usage: ./server run\n");
        exit(1);
    }

    int server_fd = socket(AF_INET, SOCK_STREAM, 0); // create socket, server_fd is a fd that points to our socket
    if (server_fd < 0) {
        printf("failed to create socket\n");
        exit(1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP_ADDRESS, &server_addr.sin_addr); // convert ip address and port using ip into network bytes
    memset(server_addr.sin_zero, 0, sizeof(server_addr.sin_zero)); // 0 out the padding

    int opt = 1; // flags
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // reuse old binding if server is forcefully stopped
    int binded = bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)); // tells OS that IP+PORT belongs to that server socket

    if (binded < 0) {
        printf("Bind failed\n");
        exit(1);
    }

    int listening = listen(server_fd, MAX_BACKLOG); // makes OS know its available and begins filling wait queue with requests
    if (listening < 0) {
        printf("Failed to set listening\n");
        exit(1);
    }

    printf("Listening on...\n");
    printf("PORT: %d\n", PORT);
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &server_addr.sin_addr, ip_str, sizeof(ip_str)); 
    printf("IP: %s\n", ip_str);

    while(1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        int client_sock = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

        if (client_sock < 0) {
            printf("failed to accept client socket\n");
            continue;
        }

        printf("Client connected\n");
        
        char buffer[MAX_PAYLOAD];
        int bytes = recv(client_sock, buffer, sizeof(buffer) - 1, 0);

        if (bytes > 0) {
            buffer[bytes] = '\0';

            Request request;
            printf("MESSAGE: ");
            for (int i = 0; i < 9; i++) {
                printf("%02X ", (uint8_t)buffer[i]);
            }
            printf("\n");
            request = parse_request(buffer, bytes);

            if (request.size > 0) {
                printf("Valid request\n");
                printf("TYPE: %d\n", request.type);
                printf("Size: %d\n", request.size);
                printf("Payload: %s\n", request.payload);
            } else {
                printf("Invalid request\n");
                close(client_sock);
                continue;
            }

            char* response = gen_response(request);

            send(client_sock, response, strlen(response), 0);
        }

        close(client_sock);
    }

    // socket DONE
    // bind DONE
    // listen DONE
    // accept DONE
    // recv DONE
    // parse
    // get_file
    // build_response
    // send_response
    // close

    exit(0);
}

Request parse_request(char *content, uint16_t len_content) {
	if (len_content < 3) {
        printf("Header too small\n");
        return invalid_request();
    }

    Request request;

    request.type = content[0];
    
    if (request.type >= TYPES_COUNT) {
        printf("Invalid type\n");
        return invalid_request();
    }
    
    uint16_t len;
    memcpy(&len, content + 1, sizeof(uint16_t));

    request.size = len;

    if (request.size > MAX_PAYLOAD || 3 + request.size > len_content) {
        printf("Invalid size\n");
        return invalid_request();
    }

    memcpy(request.payload, content + 3, request.size);
    request.payload[request.size] = '\0';

    return request;
}

Request invalid_request() {
    Request invalid_request;
    invalid_request.type = 0;
    invalid_request.size = 0;
    memcpy(invalid_request.payload, "0\n", 1);

    return invalid_request;
}

char* gen_response(Request request) {
    if (request.type == PING) {
        char* response = "hey digga\n";
        return response;
    }
}