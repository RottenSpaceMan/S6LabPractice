#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_file(int sock, char *filename){
    char buffer[BUFFER_SIZE];
    FILE *fp = fopen("sample.txt", "r");

    int bytes_read;
    while((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0){
        printf("Sending: %s\n", buffer);
        send(sock, buffer, bytes_read, 0);
    }

    fclose(fp);
    printf("File sent");
}

int main(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("Connected to server\n");

    send_file(sock, "sample.txt");
    close(sock);
    return 0;
}