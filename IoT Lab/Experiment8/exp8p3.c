#include <reg51.h>
void main(){
	unsigned char value = 0xFD;
	P0 = value/100;
	P1 = (value%100)/10;
	P2 = value % 10;
}