#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 8080
#define MAX_FRAME 5
#define TIMEOUT 2

void main() {
    int sockfd;
    struct sockaddr_in receiver_addr;
    socklen_t addr_len = sizeof(receiver_addr);
    char buffer[1024];
    int frame_number = 0;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;

    // Set timeout for receiving ACKs
    struct timeval tv;
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    // Send frames one by one and wait for ACK
    while (frame_number < MAX_FRAME) {
        sprintf(buffer, "Frame %d", frame_number);
        printf("Sending: %s\n", buffer);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&receiver_addr, addr_len);

        // Wait for ACK
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&receiver_addr, &addr_len);
        if (n > 0) {
            buffer[n] = '\0';
            printf("Received: %s\n", buffer);
            frame_number++;
        } else {
            printf("Timeout! Resending frame ...\n");
        }
    }
    close(sockfd);
}