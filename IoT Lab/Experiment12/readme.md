# Program 1
## Aim
To write an embedded C program to interface ADC 0804 with 8051 microcontroller.
## Agorithm
1. Start
2. Set rd, wr, and intr pins
3. Enable intr
4. Start conversion with wr pin
5. Wait and then set wr = 1
6. Check until intr = 0
7. Set rd = 1
8. Wait and then set rd = 0
9. Goto step 3
10. Stop

# Program 2
## Aim
To write and embedded C program to interface DAC 0808 with 8051 microcontroller.
## Algorithm
1. Start
2. Set initial value to 0x00 to x
3. P1 = x
4. Set x = 0xFF
5. P1 = x
6. Set x = 0x00
7. Goto step 3
8. Stop
