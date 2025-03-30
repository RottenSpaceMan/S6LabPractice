#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define packetCount 10

int main(){
    srand(time(NULL));
    int packets[packetCount], i, rate, buckeSize, remainingSize = 0, timeToTransmit, clk, op;

    for(i = 0; i < packetCount; i++){
        packets[i] = (rand() % 6 + 1) * 10; // Generate packet size between 10 and 60
    }
    printf("Enter output rate: ");
    scanf("%d", &rate);
    printf("Enter bucket size: ");
    scanf("%d", &buckeSize);

    i = 0;
    while(i < packetCount || remainingSize > 0){
        if(i < packetCount){
            if((packets[i] + remainingSize > buckeSize)){
                printf("Packet %d dropped (size: %d)\n", i, packets[i]);
            } else {
                remainingSize += packets[i];
                printf("Packet %d of size %d added to bucket, remaining size: %d\n", i, packets[i] ,remainingSize);
            }
            i++;
        }
        timeToTransmit = (rand() % 4 + 1) * 10; // Random time to transmit between 10 and 40
        printf("Time to transmit: %d\n", timeToTransmit);
        for(clk = 10; clk <= timeToTransmit; clk += 10){
            sleep(1);
            if(remainingSize > 0){
                if(remainingSize <= rate){
                    op = remainingSize;
                    remainingSize = 0;
                } else {
                    op = rate;
                    remainingSize -= rate;
                }
                printf("Packet transmitted: %d, remaining size: %d\n", op, remainingSize);
            } else {
                printf("Time left: %d\n", timeToTransmit - clk);
                printf("Bucket empty\n");
            }
        }
    }
    return 0;
}