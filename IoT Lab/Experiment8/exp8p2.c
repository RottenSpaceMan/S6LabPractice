#include <reg51.h>
void main(){
	unsigned char a = '4', b = '7';
	P1 = ((a - '0') << 4)|(b - '0');
}