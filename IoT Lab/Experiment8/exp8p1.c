#include <reg51.h>
void main(){
	unsigned char bcd = 0x29;
	P1 = ((bcd >> 4) & 0x0F) + '0';
	P2 = (bcd&0x0F) + '0';
}