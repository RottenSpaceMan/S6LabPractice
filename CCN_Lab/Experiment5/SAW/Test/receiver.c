#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){
    int server_fd, client_fd, byte_size, frame = 0; // Initialize frame to 0
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(server_fd, 3);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);

    while(frame < 9){
        byte_size = recv(client_fd, &frame, sizeof(frame), 0);
        if(byte_size > 0){
            printf("Receiver: Frame %d received\n", frame);
            send(client_fd, "ACK", strlen("ACK"), 0);
            printf("Receiver: ACK sent for frame %d\n", frame);
        }
        else{
            printf("Receiver: No data received\n");
        }
    }

    close(server_fd);
    close(client_fd);
    return 0;
}