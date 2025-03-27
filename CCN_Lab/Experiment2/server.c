#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

int main(){
    int server_fd, client_fd; // FDs for server and client
    struct sockaddr_in server_addr, client_addr; // IP and port of server and client
    socklen_t addr_len = sizeof(client_addr); // Length of client address to be used in accept
    char buffer[BUFFER_SIZE]; // Buffer to store message from client

    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0){
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT); // Convert to network byte order(little endian to big endian)

    // Bind the socket on server_fd to the IP and port
    if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        // (struct socakddr *)&server_addr is typecasting server_addr from sockaddr_in to sockaddr
        perror("Bind failed");
        return 1;
    }

    // Listen for incoming connections
    if(listen(server_fd, MAX_CLIENTS) == -1){
        perror("Listen failed");
        return 1;
    }

    printf("Server listening on port %d\n", PORT);

    // Accept incoming connections from server_fd and put it in client_fd
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    if(client_fd == -1){
        perror("Accept failed");
        close(server_fd);
        return 1;
    }
    printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));
    // inet_ntoa converts IP address from binary to string

    // Receive message from client
    ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if(bytes_received == -1){
        perror("Receive failed");
    }else{
        buffer[bytes_received] = '\0'; // Null terminate the string
        printf("Client: %s\n", buffer);
    }

    // Send response to clinet
    const char *response = "Hello from server";
    send(client_fd, response, strlen(response), 0);

    // Close sockets
    close(client_fd);
    close(server_fd);
}