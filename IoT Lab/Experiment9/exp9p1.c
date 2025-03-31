#include <reg51.h>
void main(){
	TMOD = 0x20;
	TH1 = 0xFA;
	TL1 = 0xFA;
	TR1 = 1;
	SCON = 0x50;
	for(;;){
		SBUF = 'A';
		while(TI == 0);
		TI = 0;
	}
	TR1 = 0;
	TF1 = 0;
}