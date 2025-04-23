#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024
#define MAX_CLIENTS 5

int main(){
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(server_addr);
    char buffer[BUF_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, addr_len);
    listen(server_fd, MAX_CLIENTS);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);

    int bytes = recv(client_fd, buffer, sizeof(buffer), 0);
    buffer[bytes] = '\0';
    printf("Client : %s\n", buffer);

    const char *response = "Hello from server";
    send(client_fd, response, strlen(response), 0);

    close(server_fd);
    close(client_fd);
    return 0;
}