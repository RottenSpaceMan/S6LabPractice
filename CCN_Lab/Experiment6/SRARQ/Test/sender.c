#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10
#define PORT 8080

int sockfd;
struct sockaddr_in receiver_addr;
socklen_t addr_len;
int ACK[TOTAL_FRAMES] = {0};

bool send_frame(int seq_num){
    if(rand() % 5 == 0){
        printf("Packet loss simulated for Packet %d\n", seq_num);
        return false;
    }
    printf("Packet %d sent\n", seq_num);

    sendto(sockfd, &seq_num, sizeof(seq_num), 0, (struct sockaddr *)&receiver_addr, addr_len);
    return true;
}

bool receive_ack(int seq_num){
    int ack_buffer = -1;
    fd_set readfds;
    struct timeval tv;

    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    int ret = select(sockfd + 1, &readfds, NULL, NULL, &tv);
    if(ret == 0){
        printf("Timeout for ACK %d, retransmitting...\n", seq_num);
        return false;
    }
    recvfrom(sockfd, &ack_buffer, sizeof(ack_buffer), 0, (struct sockaddr *)&receiver_addr, &addr_len);
    if(ack_buffer == seq_num){
        printf("ACK %d received\n", ack_buffer);
        return true;
    }
    return false;
}

void main(){
    srand(time(NULL));
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;

    addr_len = sizeof(receiver_addr);

    int base = 0;
    int next_seq_num = 0;
    while(base < TOTAL_FRAMES){
        while(next_seq_num < base + WINDOW_SIZE && next_seq_num < TOTAL_FRAMES){
            send_frame(next_seq_num);
            if(receive_ack(next_seq_num)){
                ACK[next_seq_num] = 1;
            }
            next_seq_num++;
        }
        sleep(1);
        for(int i = base; i < next_seq_num; i++){
            if(ACK[i] == 0){
                if(send_frame(i)){
                    if(receive_ack(i)){
                        ACK[i] = 1;
                    }
                }
            }
        }
        while(ACK[base] == 1 && base < TOTAL_FRAMES){
            base++;
        }
    }

    close(sockfd);
}