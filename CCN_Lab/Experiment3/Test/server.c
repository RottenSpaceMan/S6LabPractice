#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void string_rev(char *str){
    int n = strlen(str);
    for(int i = 0; i < n/2 ; i++){
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

int main(){
    int server_fd, client_fd;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&address, addrlen);

    listen(server_fd, 5);

    client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);

    read(client_fd, buffer, BUFFER_SIZE);
    printf("Received: %s\n", buffer);

    string_rev(buffer);
    printf("Reversed string: %s\n", buffer);
    send(client_fd, buffer, strlen(buffer), 0);

    close(client_fd);
    close(server_fd);
    return 0;
}