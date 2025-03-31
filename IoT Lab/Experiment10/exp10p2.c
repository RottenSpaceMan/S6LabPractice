#include <reg51.h>
sbit en = P1^0;
sbit in1 = P1^1;
sbit in2 = P1^2;
sbit dir = P2^0;
sbit inc = P2^1;
sbit dec = P2^2;

unsigned char duty = 50;
void PWM(unsigned char duty){
	unsigned int i;
	for(i = 0; i < 255; i++){
		en = (i < duty) ? 1 : 0;
	}
}

void main(){
	while(1){
		if(dir){
			in1 = 1;
			in2 = 0;
		}else{
		in1 = 0;
		in2 = 1;
		}
		if(!inc && duty < 255){
			duty += 1;
			while(!inc);
		}
		if(!dec && duty > 0){
			duty -= 1;
			while(!dec);
		}
		PWM(duty);
	}
}