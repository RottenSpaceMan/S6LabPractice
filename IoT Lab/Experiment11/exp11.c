#include <reg51.h>

sbit RS = P3^4;
sbit RW = P3^5;
sbit EN = P3^6;

void delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 1275; j++);
}

void lcd_cmd(unsigned char cmd) {
    RS = 0; // Command mode
    RW = 0; // Write mode
    P1 = cmd; // Send command to data port
    EN = 1
    delay(1);
    EN = 0;
}

void lcd_data(unsigned char data) {
    RS = 1; // Data mode
    RW = 0; // Write mode
    P1 = data; // Send data to data port
    EN = 1;
    delay(1);
    EN = 0;
}
void lcd_init() {
    lcd_cmd(0x38); // 8-bit mode, 2 lines, 5x7 dots
    delay(10);
    lcd_cmd(0x0E); // Display ON, cursor ON
    delay(10);
    lcd_cmd(0x01); // Clear display
    delay(10);
    lcd_cmd(0x06); // Increment cursor
    delay(10);
    lcd_cmd(0x84); // Set cursor position to 1st line, 1st column
    delay(10);
}
void main(){
    lcd_init();
    lcd_data('M');
    delay(10);
    lcd_data('B');
    delay(10);
    lcd_data('C');
    delay(10);
    lcd_data('E');
    delay(10);
    lcd_data('T');
    delay(10);
    while (1);    
}