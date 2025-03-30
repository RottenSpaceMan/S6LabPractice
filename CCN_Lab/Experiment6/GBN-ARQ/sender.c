#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>

#define MAX_PACKET_SIZE 1024
#define WINDOW_SIZE 4
#define TOTAL_PACKETS 10
#define PORT 8080

typedef struct {
    int seq_num;
    char data[MAX_PACKET_SIZE];
} Packet;

int main(){
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1){
        perror("socket");
        exit(1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    socklen_t addr_len = sizeof(server_addr);
    Packet packets[TOTAL_PACKETS];

    // Initialize packets
    for(int i = 0; i < TOTAL_PACKETS; i++){
        packets[i].seq_num = i;
        snprintf(packets[i].data, MAX_PACKET_SIZE, "Packet %d data", i);
    }

    int base = 0;
    int next_seq_num = 0;
    int ack;
    srand(time(NULL)); // Seed for random number generation

    while(base < TOTAL_PACKETS){
        while(next_seq_num < base + WINDOW_SIZE && next_seq_num < TOTAL_PACKETS){
            printf("Sending packet %d\n", next_seq_num);

            // Simulate random packet loss
            if(rand() % 5 != 0){
                // 80% success rate
                if(sendto(sock, &packets[next_seq_num], sizeof(Packet), 0, (struct sockaddr*)&server_addr, addr_len) == -1){
                    perror("sendto");
                    close(sock);
                    exit(1);
                }
            } else {
                printf("Simulated packet loss for packet %d\n", next_seq_num);
            }
            next_seq_num++;
        }

        struct timeval timeout;
        timeout.tv_sec = 1; // 1 second timeout
        timeout.tv_usec = 0; // 0 microseconds
        fd_set fds; // Initialize file descriptor set
        FD_ZERO(&fds); // Clear the set
        FD_SET(sock, &fds); // Add the socket to the set

        // select() to wait for an ACK or timeout
        // The select() function monitors the file descriptor set for readiness
        // to perform I/O operations. It blocks until one of the file descriptors
        // becomes "ready" (i.e., data is available to read) or the timeout expires.
        // The timeout parameter specifies the maximum time to wait for an event.
        // If the timeout expires, select() returns 0, indicating that no file
        // descriptors were ready within the specified time.
        // If a file descriptor is ready, select() returns the number of ready
        // file descriptors, which can be used to check which file descriptor(s)
        // are ready for reading.
        int retval = select(sock + 1, &fds, NULL, NULL, &timeout);

        if (retval == -1){
            perror("select");
            close(sock);
            exit(1);
        } else if (retval == 0) {
            // Timeout occurred, resend the base packet
            printf("Timeout occurred, resending packet %d\n", base);
            next_seq_num = base; // Reset next_seq_num to base
        } else {
            // ACK received
            if(recvfrom(sock, &ack, sizeof(int), 0, (struct sockaddr*)&server_addr, &addr_len) == -1){
                perror("recvfrom");
                close(sock);
                exit(1);
            }
            printf("Received ACK for packet %d\n", ack);
            if(ack >= base){
                base = ack + 1; // Move the base to the next unacknowledged packet
            } else {
                printf("Received duplicate ACK. Ignoring");
            }
        }
    }
    printf("Transmission complete\n");
    close(sock);
    return 0;
}