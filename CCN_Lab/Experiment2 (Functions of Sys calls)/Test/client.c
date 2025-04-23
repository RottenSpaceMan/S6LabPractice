#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUF_SIZE 1024

int main(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE] = "Hello from client";

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    send(sock, buffer, strlen(buffer), 0);

    recv(sock, buffer, BUF_SIZE, 0);
    printf("Server : %s\n", buffer);
    close(sock);
    return 0;
}