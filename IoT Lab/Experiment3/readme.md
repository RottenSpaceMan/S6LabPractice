# Program 1
## Aim
To write a program to add two 16 bit numbers

## Algorithm
1. The two 16 bit numbers are stored in external memory
2. Take the lower 8 bytes of both the numbers
3. Add the lower bytes and save it in a memory location
4. If the addition of lower bytes results in a carry, then add the carry to the higher bytes using a register
5. Take the higher bytes of both the numbers
6. Add the higher bytes and the previous carry save it in a memory location
7. The result is stored in the memory location
9. If the addition of higher bytes results in a carry store it in a memory location

# Program 2
## Aim
To write a program to subtract two 16 bit numbers

## Algorithm
1. The two 16 bit numbers are stored in external memory
2. Take the lower 8 bytes of both the numbers
3. Lower bytes of the second number are subtracted from the first number
4. If the subtraction of lower bytes results in a borrow, then subtract the borrow from the higher bytes using a register
5. Take the higher bytes of both the numbers
6. Subtract the higher bytes and the previous borrow save it in a memory location
7. If the first number is less than the second number, to indicate that the result is negative, the MSB of the result is set as FF otherwise the MSB is set as 00

# Program 3
## Aim
To write a program to multiply two 8 bit numbers

## Algorithm
1. The two 8 bit numbers are stored in external memory
2. Take the second number and store it in B
3. Take the first number and store it in A
4. The two numbers are then multiplied. Multiplication of two 8 bit numbers results in a 16 bit number. The lower and higher bytes of the multiplication operations are moved to the external memory. The higher bytes of the result after the multiplication operation will be in B and the lower bytes will be in A
5. If the result of the operation is higher thn FF, the overflow flag is set, else it is cleared
6. Carry flag is cleared in all multiplication operations

# Porgram 4
## Aim
To write a program to divide two 8 bit numbers

## Algorithm
1. The dividend and divisor are stored in external memory
2. The dividend is stored in A and the divisor is stored in B
3. Division operation is carried out wich divides the number in A by the number in B
4. The quotient is stored in A and the remainder is stored in B, which is to be stored in external memory
5. If B = 0, the overflow flag will be set. Otherwise the overflow flag will always be cleared
6. The carry flag is cleared in all division operations

# Program 5
## Aim
To write a program to find the square of an 8 bit number

## Algorithm
1. The number is stored in external memory
2. The number is stored in A and B
3. A and B is multiplied
4. The result is stored in external memory

# Program 6
## Aim
To write a program to find the cube of an 8 bit number

## Algorithm
1. The number is stored in external memory
2. The number is stored in A and B
3. A and B is multiplied
4. The lower and higher bytes are multiplied separately and added to get the cube stored in three memory locations