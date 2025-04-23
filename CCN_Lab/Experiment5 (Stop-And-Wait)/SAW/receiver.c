#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){
    int server_fd, client_fd, valread;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t addr_len = sizeof(cli_addr);
    int frame = 0;

    // Create socket
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // Bind socket
    if(bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for sender
    if(listen(server_fd, 3) < 0){
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Accept connection
    if((client_fd = accept(server_fd, (struct sockaddr *)&cli_addr, &addr_len)) < 0){
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Receiver: Connected to sender\n");

    while(frame < 9){
        // Receive data
        valread = recv(client_fd, &frame, sizeof(frame), 0);
        if(valread > 0){
            printf("Receiver: Frame %d received\n", frame);
            // Always send ACK
            send(client_fd, "ACK", strlen("ACK"), 0);
            printf("Receiver: ACK sent for frame %d\n", frame);
        }
        else{
            printf("Receiver: No data received\n");
        }
    }
    
    // Close sockets
    close(client_fd);
    close(server_fd);
    return 0;
}
