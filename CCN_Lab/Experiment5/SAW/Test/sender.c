#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_FRAME 1

int main(){
    int sockfd, frame = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while(frame < 10){
        printf("Sending frame %d\n", frame);
        send(sockfd, &frame, sizeof(frame), 0);

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