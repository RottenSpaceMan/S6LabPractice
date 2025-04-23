#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void receive_file(int sock){
    char buffer[BUFFER_SIZE];
    FILE *fp = fopen("received_file.txt", "w");

    int bytes_received;
    while((bytes_received = recv(sock, buffer, sizeof(buffer), 0)) > 0){
        printf("Received: %s\n", buffer);
        fwrite(buffer, 1, bytes_received, fp);
    }

    fclose(fp);
    printf("File received successfully.\n");
}

int main(){
    int server_sock = socket(AF_INET, SOCK_STREAM, 0), client_sock;
    struct sockaddr_in serv_addr, client_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    socklen_t addr_len = sizeof(client_addr);

    bind(server_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(server_sock, 5);

    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);

    receive_file(client_sock);

    close(client_sock);
    close(server_sock);
    return 0;
}