#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>

#define MAX_PACKET_SIZE 1024
#define WINDOW_SIZE 4
#define PORT 8080
#define TOTAL_PACKETS 12

typedef struct {
    int seq_num;
    char data[MAX_PACKET_SIZE];
} Packet;

int main(){
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    socklen_t addr_len = sizeof(server_addr);
    Packet packets[TOTAL_PACKETS];

    for(int i = 0; i < TOTAL_PACKETS; i++){
        packets[i].seq_num = i;
        sprintf(packets[i].data, "Packet %d", i);
    }

    int base = 0;
    int next_seq_num = 0;
    int ack;
    srand(time(NULL));
    while(base < TOTAL_PACKETS){
        while(next_seq_num < base + WINDOW_SIZE && next_seq_num < TOTAL_PACKETS){
            printf("Sending packet %d\n", next_seq_num);

            if(rand() % 5 != 0){
                sendto(sock, &packets[next_seq_num], sizeof(Packet), 0, (struct sockaddr *)&server_addr, addr_len);
            } else {
                printf("Simulated packet loss\n");
            }
            next_seq_num++;
        }
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(sock, &fds);
        int retval = select(sock + 1, &fds, NULL, NULL, &timeout);

        if(retval == 0){
            printf("Timeout! sending from packet %d\n", base);
            next_seq_num = base;
        } else {
            recvfrom(sock, &ack, sizeof(ack), 0, (struct sockaddr *)&server_addr, &addr_len);
            printf("Ack received for packet %d\n", ack);
            if(ack >= base){
                base = ack + 1;
            }
        }
    }
    close(sock);
    return 0;
}