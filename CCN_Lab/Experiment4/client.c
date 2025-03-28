#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define MAX 1024

int main(){
    int sockfd;
    char buffer[MAX];
    struct sockaddr_in servaddr;

    // Creating socket file descriptor;
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int r1,c1,r2,c2;
    int mat1[10][10], mat2[10][10], result[10][10];

    // Input dimensions and matrices
    printf("Enter rows and columns of first matrix: ");
    scanf("%d %d", &r1, &c1);
    printf("Enter rows and columns of second matrix: ");
    scanf("%d %d", &r2, &c2);

    if(c1 != r2){
        printf("Matrix multiplication not possible with given dimensions.\n");
        close(sockfd);
        return 0;
    }

    printf("Enter elements of first matrix:\n");
    for(int i = 0; i < r1; i++){
        for(int j = 0; j < c1; j++){
            scanf("%d",&mat1[i][j]);
        }
    }

    printf("Enter elements of second matrix:\n");
    for(int i = 0; i < r2; i++){
        for(int j = 0; j < c2; j++){
            scanf("%d",&mat2[i][j]);
        }
    }

    int len = sizeof(servaddr);

    // Send dimensions and matrices to the server
    sendto(sockfd, &r1, sizeof(r1), 0, (const struct sockaddr *)&servaddr, len);
    sendto(sockfd, &c1, sizeof(c1), 0, (const struct sockaddr *)&servaddr, len);
    sendto(sockfd, &r2, sizeof(r2), 0, (const struct sockaddr *)&servaddr, len);
    sendto(sockfd, &c2, sizeof(c2), 0, (const struct sockaddr *)&servaddr, len);
    sendto(sockfd, &mat1, sizeof(mat1), 0, (const struct sockaddr *)&servaddr, len);
    sendto(sockfd, &mat2, sizeof(mat2), 0, (const struct sockaddr *)&servaddr, len);

    // Receive the result matrix from the server
    recvfrom(sockfd, result, sizeof(result), MSG_WAITALL, (struct sockaddr *)&servaddr, &len);

    // Print the result matrix
    printf("Resultant matrix:\n");
    for(int i = 0; i < r1; i++){
        for(int j = 0; j < c2; j++){
            printf("%d", result[i][j]);
        }
        printf("\n");
    }
    close(sockfd);
    return 0;
}