#include <reg51.h>
void MSDelay(unsigned int time){
	unsigned int i, j;
	for(i = 0 ; i < time ; i++){
		for(j = 0 ; j < 1275 ; j++);
	}
}

void main(){
	unsigned char step[] = {0x09, 0x03, 0x06, 0x0C}, i = 0;
	while(1){
		P1 = step[i];
		MSDelay(100);
		i = (i + 1)%4;
	}
}