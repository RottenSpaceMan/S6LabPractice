#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define TOTAL_FRAMES 10

int sockfd;
struct sockaddr_in receiver_addr, sender_addr;
socklen_t addr_len;
int ACK[TOTAL_FRAMES] = {0};

void main(){
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;

    addr_len = sizeof(receiver_addr);

    bind(sockfd, (struct sockaddr *)&receiver_addr, addr_len);
    printf("Receiver is ready to receive packets...\n");

    int ack_buffer = -1;
    int seq_num = 0;
    while(1){
        recvfrom(sockfd, &ack_buffer, sizeof(ack_buffer), 0, (struct sockaddr *)&sender_addr, &addr_len);
        printf("Received packet %d\n", ack_buffer);

        ACK[ack_buffer] = 1;
        printf("ACK %d sent\n", ack_buffer);
        sendto(sockfd, &ack_buffer, sizeof(ack_buffer), 0, (struct sockaddr *)&sender_addr, addr_len);
        
        int all_received = 1;
        for (int i = 0; i < TOTAL_FRAMES; i++) {
            if (ACK[i] == 0) {
            all_received = 0;
            }
        }
        if (all_received) {
            printf("All packets received. Exiting...\n");
            break;
        }
    }
    close(sockfd);
}