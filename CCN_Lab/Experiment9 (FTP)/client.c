#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_file(int socket, const char *filename){
    char buffer[BUFFER_SIZE];
    FILE *fp = fopen(filename, "rb");
    if(!fp){
        perror("File opening failed");
        return;
    }

    int bytes_read;
    while(bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)){
        send(socket, buffer, bytes_read, 0);
    }

    fclose(fp);
    printf("File sent successfully.\n");
}

int main(){
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if(connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server.\n");
    send_file(client_socket, "sample.txt");
    close(client_socket);
    return 0;
}