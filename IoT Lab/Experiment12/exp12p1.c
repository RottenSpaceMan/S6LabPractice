#include <reg51.h>

sbit rd = P2^5;
sbit wr = P2^6;
sbit intr = P2^7;

void delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 1275; j++);
}
void main(){
    intr = 1;
    rd = 1;
    wr = 1;
    while(1){
        wr = 0;
        wr = 1;
        while(intr == 1);
        rd = 0;
        P0 = P1;
        delay(10);
        rd = 1;
    }
}