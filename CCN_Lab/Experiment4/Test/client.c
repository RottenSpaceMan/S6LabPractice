#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){
    int sockfd;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    int r1, c1, r2, c2, mat1[10][10], mat2[10][10], result[10][10];

    printf("Enter number of columns and rows of first matrix: ");
    scanf("%d%d",&r1,&c1);
    printf("Enter number of columns and rows of second matrix: ");
    scanf("%d%d",&r2,&c2);

    if(c1 != r2){
        printf("The two dimensions and incompatible, exiting program");
        close(sockfd);
        return 0;
    }

    printf("Enter elements of first matrix:\n");
    for(int i = 0; i < r1; i++){
        for(int j = 0; j < c1; j++){
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("Enter elements of second matrix:\n");
    for(int i = 0; i < r2; i++){
        for(int j = 0; j < c2; j++){
            scanf("%d", &mat2[i][j]);
        }
    }

    int len = sizeof(serv_addr);

    sendto(sockfd, &r1, sizeof(r1), 0, (struct sockaddr *)&serv_addr, len);
    sendto(sockfd, &c1, sizeof(c1), 0, (struct sockaddr *)&serv_addr, len);
    sendto(sockfd, &r2, sizeof(r2), 0, (struct sockaddr *)&serv_addr, len);
    sendto(sockfd, &c2, sizeof(c2), 0, (struct sockaddr *)&serv_addr, len);
    sendto(sockfd, &mat1, sizeof(mat1), 0, (struct sockaddr *)&serv_addr, len);
    sendto(sockfd, &mat2, sizeof(mat2), 0, (struct sockaddr *)&serv_addr, len);

    recvfrom(sockfd, &result, sizeof(result), MSG_WAITALL, (struct sockaddr *)&serv_addr, &len);

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