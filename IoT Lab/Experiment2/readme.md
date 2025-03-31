# Program 1

## Aim
To sort a set of numbers in ascending order using bubble sort algorithm.

## Algorithm
1. Read the number of elements to be sorted as Count.
2. Set Inner_Loop_Counter to Count - 1
3. Set Outer_Loop_Counter to Inner_Loop_Counter
4. Is Outer_Loop_Counter = 0?
   - No: Go to step 5
   - Yes: Go to step 10
5. Set Inner_Loop_Counter to Inner_Loop_Counter - 1
6. Is Inner_Loop_Counter = 0?
   - No: Go to step 7
   - Yes: Go to step 4
7. Compare the current element cur_el with the next element next_el
8. If cur_el > next_el, swap the elements, else skip
9. Decrement Inner_Loop_Counter and go to step 6
10. Numbers are sorted in ascending order.
11. End

## Procedure
1. Enter the program in memory locations starting from 4100H
2. Enter the numbers in memory location starting from 4500H
3. Execute the program and verify result in memory locations starting from 4501H

# Program 2
## Aim
To write the assembly language program to find the largest number in a sequence 

## Algorithm
1. Input the Count
2. Get the first number in any register and second number the Accumulator
3. Decrement the counter
4. Compare the two numbers. If they are equal, skip to step 6
5. If there is no carry, swap the numbers such that the Register has the largest number
6. Decrement the counter and if not zero, get the next number in Accumulator and go to step 4
7. Store the largest number in externa memory

## Procedure
1. Enter the program in memory locations starting from 4100H
2. Enter the count as 5 in 4500H and the 5 numbers from 4501H
3. Execute the program and verify the result in memory location 4506H

