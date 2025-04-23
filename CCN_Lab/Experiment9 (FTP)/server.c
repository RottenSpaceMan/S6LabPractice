#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

# define PORT 8080
#define BUFFER_SIZE 1024

void receive_file(int client_socket){
    char buffer[BUFFER_SIZE];
    FILE *fp = fopen("received_file.txt", "wb");
    if(!fp){
        perror("File opening failed");
        return;
    }

    int bytes_received;
    while((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0){
        fwrite(buffer, sizeof(char), bytes_received, fp);
    }

    fclose(fp);
    printf("File received successfully.\n");
}
int main(){
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if(listen(server_socket, 5) < 0){
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    int addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
    if(client_socket < 0){
        perror("Accept failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    receive_file(client_socket);
    close(client_socket);
    close(server_socket);
    return 0;
}