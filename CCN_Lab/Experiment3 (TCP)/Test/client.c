#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int sock = 0;
    struct sockaddr_in servaddr;
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("Enter string to send to the server: ");
    fgets(message, BUFFER_SIZE, stdin);
    message[strcspn(message, "\n")] = 0;

    send(sock, message, strlen(message), 0);
    recv(sock, buffer, BUFFER_SIZE, 0);
    printf("Reversed string: %s\n", buffer);

    close(sock);
    return 0;
}