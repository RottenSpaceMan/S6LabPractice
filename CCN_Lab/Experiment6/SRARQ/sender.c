#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/time.h>

#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10
#define LOSS_PROBABILITY 0.2
#define PORT 8080
#define TIMEOUT 2 // seconds

int sockfd;
struct sockaddr_in receiver_addr;
socklen_t addr_len;

bool send_frame(int seq_num){
    if((float)rand() / RAND_MAX < LOSS_PROBABILITY){
        printf("Frame %d lost\n", seq_num);
        return false;
    }
    printf("Frame %d sent\n", seq_num);

    char buffer[10];
    sprintf(buffer, "%d", seq_num);
    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&receiver_addr, addr_len);
    return true;    
}

bool receive_ack(int seq_num){
    char ack_buffer[10];
    fd_set readfds;
    struct timeval tv;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;

    // Select check for incoming ACKs
    // with a timeout
    int ret = select(sockfd + 1, &readfds, NULL, NULL, &tv);

    // ret = 0 means timeout, >0 means data is available
    // ret < 0 means error
    if(ret == 0){
        printf("Timeout for ACK %d, retransmitting...\n", seq_num);
        return false; // Timeout, no ACK received
    } else if (ret < 0)
    {
        perror("select() failed");
    }
    recvfrom(sockfd, ack_buffer, sizeof(ack_buffer), 0, (struct sockaddr*)&receiver_addr, &addr_len);
    int ack_num = atoi(ack_buffer);
    if(ack_num == seq_num){
        printf("ACK %d received\n", ack_num);
        return true; // ACK received
    }
    return false; // ACK not received
}

void simulate(){
    int base = 0, next_seq_num = 0;
    while(base < TOTAL_FRAMES){
        // Send frames within the window size
        for(int i = 0; i < WINDOW_SIZE && next_seq_num < TOTAL_FRAMES; i++){
            if(send_frame(next_seq_num)){
                if(receive_ack(next_seq_num)){
                    base++;
                }
            }
            next_seq_num++;
        }

        sleep(1); // Simulate some delay

        // Handle retransmissions for frames that didnt get ACKed
        for(int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++){
            if(!receive_ack(i)){
                send_frame(i);
            }
        }
    }
}

int main(){
    sreand(time(NULL));
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = INADDR_ANY;
    receiver_addr.sin_port = htons(PORT);
    addr_len = sizeof(receiver_addr);

    simulate();
    close(sockfd);
    return 0;
}