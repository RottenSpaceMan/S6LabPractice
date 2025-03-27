#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void reverse_string(char *str){
    int n = strlen(str);
    for(int i = 0; i < n/2; i++){
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

int main(){
    int server_fd, client_fd;
    struct sockaddr_in serv_addr;
    int addrlen = sizeof(serv_addr);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket file descriptor
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the network
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if(listen(server_fd, 3) < 0){
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    if((client_fd = accept(server_fd, (struct sockaddr *)&serv_addr, (socklen_t *)&addrlen)) < 0){
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    read(client_fd, buffer, BUFFER_SIZE);
    printf("Received: %s\n", buffer);

    reverse_string(buffer);
    send(client_fd, buffer, strlen(buffer), 0);
    printf("Reversed string sent: %s\n", buffer);

    close(client_fd);
    close(server_fd);

    return 0;
}