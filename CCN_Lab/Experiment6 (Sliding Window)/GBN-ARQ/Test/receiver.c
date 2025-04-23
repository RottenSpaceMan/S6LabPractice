#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_PACKET_SIZE 1024
#define TOTAL_PACKETS 12

typedef struct
{
    int seq_num;
    char data[MAX_PACKET_SIZE];
} Packet;


int main(){
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    socklen_t addr_len = sizeof(client_addr);
    Packet received_packet;
    int expected_seq_num = 0;
    int received[TOTAL_PACKETS] = {0};

    while(expected_seq_num <= TOTAL_PACKETS){
        recvfrom(sock, &received_packet, sizeof(Packet), 0, (struct sockaddr *)&client_addr, &addr_len);
        printf("Received packet %d : %s\n", received_packet.seq_num, received_packet.data);
        if(received_packet.seq_num == expected_seq_num){
            int ack = received_packet.seq_num;
            sendto(sock, &ack, sizeof(ack), 0, (struct sockaddr *)&client_addr, addr_len);
            printf("Sent ack for packet %d\n", ack);
            received[ack] = 1;
            expected_seq_num++;
        } else if (received_packet.seq_num < expected_seq_num){
            int ack = received_packet.seq_num;
            sendto(sock, &ack, sizeof(ack), 0, (struct sockaddr *)&client_addr, addr_len);
            printf("Sent duplicate ACK for packet %d\n", ack);
        } else {
            int ack = expected_seq_num - 1;
            if(ack >= 0){
                sendto(sock, &ack, sizeof(ack), 0, (struct sockaddr *)&client_addr, addr_len);
                printf("Sent ACK for %d, expecting %d\n", ack, expected_seq_num);
            }
        }
    }
    close(sock);
    return 0;
}