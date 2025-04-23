#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_FRAME 1

int main(){
    int sockfd, frame = 0;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0){
        perror("Invalid address");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Connect to the receiver
    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    while(frame < 10){
        // Send data
        printf("Sending frame %d\n", frame);
        send(sockfd, &frame, sizeof(frame), 0);

        // Wait for ACK
        read(sockfd, buffer, sizeof(buffer));
        if(strcmp(buffer, "ACK") == 0){
            printf("Sender: ACK received for frame %d\n", frame);
            frame++;
        }
        else{
            printf("Sender: No ACK received for frame %d, resending...\n", frame);
        }
        sleep(1);
    }
    close(sockfd);
    return 0;
}