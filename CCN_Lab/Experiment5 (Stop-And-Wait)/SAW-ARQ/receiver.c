#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define MAX_FRAME 5

void main() {
    int sockfd;
    struct sockaddr_in receiver_addr, sender_addr;
    socklen_t addr_len = sizeof(sender_addr);
    char buffer[1024];
    int expected_frame = 0;

    // Create and bind socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
    }
    srand(time(0)); // Seed for random ACK loss simulation

    // Receive frames and send ACKs
    while (expected_frame < MAX_FRAME) {
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&sender_addr, &addr_len);
        if (n > 0) {
            buffer[n] = '\0';
            printf("Received: %s\n", buffer);

            // Simulate ACK loss randomly
            if ((rand() % 10) < 2) {
                printf("Simulating ACK loss\n");
                continue;
            }

            // Send ACK for received frame
            sprintf(buffer, "ACK %d", expected_frame);
            sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&sender_addr, addr_len);
            expected_frame++;
        }
    }
    close(sockfd);
}
