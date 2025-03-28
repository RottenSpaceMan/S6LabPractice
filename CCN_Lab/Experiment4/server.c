#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define MAX 1024

void multiplyMatrices(int a[10][10], int b[10][10], int result[10][10], int r1, int c1, int c2){
    for(int i = 0; i < r1; i++){
        for(int j = 0; j < c2; j++){
            result[i][j] = 0;
            for(int k = 0; k < c1; k++){
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main(){
    int sockfd;
    char buffer[MAX];
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;
    len = sizeof(cliaddr);

    int r1,c1,r2,c2;
    int mat1[10][10], mat2[10][10], result[10][10];

    // Receive dimensions and matrix data from the client
    recvfrom(sockfd, &r1, sizeof(r1), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    recvfrom(sockfd, &c1, sizeof(c1), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    recvfrom(sockfd, &r2, sizeof(r2), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    recvfrom(sockfd, &c2, sizeof(c2), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    recvfrom(sockfd, &mat1, sizeof(mat1), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    recvfrom(sockfd, &mat2, sizeof(mat2), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);

    // Perform matrix multiplication
    multiplyMatrices(mat1, mat2, result, r1, c1, c2);

    // Send the result back to the client
    sendto(sockfd, result, sizeof(result), 0, (const struct sockaddr *)&cliaddr, len);

    close(sockfd);
    return 0;
}