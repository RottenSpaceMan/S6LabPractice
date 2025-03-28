#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void multiplyMatrices(int a[10][10], int b[10][10], int res[10][10], int r1, int c1, int c2){
    for(int i = 0; i < r1; i++){
        for(int j = 0; j < c2; j++){
            res[i][j] = 0;
            for(int k = 0; k < c1; k++){
                res[i][j] += a[i][k]*b[k][j];
            }
        }
    }
}

int main(){
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    int len = sizeof(cli_addr);
    int r1, c1, r2, c2, mat1[10][10], mat2[10][10], result[10][10];

    recvfrom(sockfd, &r1, sizeof(r1), MSG_WAITALL, (struct sockaddr *)&cli_addr, &len);
    recvfrom(sockfd, &c1, sizeof(c1), MSG_WAITALL, (struct sockaddr *)&cli_addr, &len);
    recvfrom(sockfd, &r2, sizeof(r2), MSG_WAITALL, (struct sockaddr *)&cli_addr, &len);
    recvfrom(sockfd, &c2, sizeof(c2), MSG_WAITALL, (struct sockaddr *)&cli_addr, &len);
    recvfrom(sockfd, &mat1, sizeof(mat1), MSG_WAITALL, (struct sockaddr *)&cli_addr, &len);
    recvfrom(sockfd, &mat2, sizeof(mat2), MSG_WAITALL, (struct sockaddr *)&cli_addr, &len);

    multiplyMatrices(mat1, mat2, result, r1, c1, c2);

    sendto(sockfd, &result, sizeof(result), 0, (struct sockaddr *)&cli_addr, len);

    close(sockfd);
    return 0;
}