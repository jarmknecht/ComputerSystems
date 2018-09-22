How to build my program all you have to type is make. This will make the object array file that is the program itself. Then one needs to type ./array to run the program. If it is done this way the input is typed by the user into the terminal. Another way the program can be run is by vim input.txt and inputing what numbers you want to be inputed into the program. Then run the command cat input.txt | ./array this will take what ever is in the text file and use it as the input for the array program. If one runs make clean the linker and object files will be deleted and the user will need to type "make" again in order to run the program.
I included test cases in the .c file but here they are here: Test case 1:
   Input: 21 1 2 3 4 5
   Expected Output: Error will print saying array is too large
   Output was correct.
Test case 2:
   Input: 0 1 2 3 4
   Expected Output: nothing will be printed because the array size is zero.
   Output was correct.
Test case 3:
   Input: 4 50 100 30 4
   Expected Output: The array contents will be printed in numerical order 4 30 50 100.
   Output was correct.
I also tested it by ensuring that if a user did not input the correct number of integers to be input into the array that the error will be printed and the program will terminate. If the error and exit code were not there an infinite loop would run. All of this was done in a single terminal!
