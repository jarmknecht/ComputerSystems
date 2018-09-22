/* 
 * CS:APP Data Lab 
 * 
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* Rating 1 -- 2 points each */
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
	/* x generates the bytes 0101 0101 0101 0101 0101 0101
	 * y Bitwise-OR's x with a 16-left-bit-shifted copy of itself.
	 */

	int x = (0x55 << 8) | (0x55);
	int y = x | (x << 16);
	return y;
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
	/* shift bits into a short size, and then shift back to the right to int size.
	 * When shifting right, all the left bits assume the same value as the most-significant bit.
	 * The resulting value is always a valid short, because, the left 17 bits are all 0 or all 1.
	 * If the initial x were a valid short, it would be the resulting value.
	 * XOR-ing this resulting value against the original x tells us if it was indeed the valid short.
	 * The result of the XOR gives us 0 if the bits are all the same (valid x), and non-zero if is different (invalid x)
	 * returning the logical NOT (!) of a non-zero value gives zero (invalid x), or of a zero value (valid x) gives a one.
	 */
	
	int y = (((x << 16) >> 16) ^ x);
	return !y;
}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
	/* A two's compliment -1 always has 1's in all the bits.
	 * Using a bitwise not on the value zero, all the 0's turn into 1's,
	 * which results in a -1 value.
	 */

	return ~0;
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {
	/* To get the upper bits of the number given to us we take the !! of the number so it will
	* give us either a single 1 if the number was a nonzero and a 0 if it was zero. Then & it to one
	* will gives us 1 that we then push left by 31 zero 100....00 then right shifting by the n + 11...11
	* this effectively pads the n upperBits with ones
	*/ 	

	return ((!!n & 1) << 31) >> (n+ ~0);
	
}
/* Rating 2 -- 3 points each */
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	/* To get the correct byte you need to shift x to the right (n * 8) bits, and take the least-significant byte.
	 * To calculate (n * 8), simply left-shift n by three bits.
	 * To obtain the least-significant byte, bitwise-AND that value by 0xFF.
	 */ 
	int bitshift = n << 3;
	int shifted = x >> bitshift;
	return (shifted & 0xFF);
}

/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1)  = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
	/* In CS 236, we learned that p -> q is the same as "not p or q" (!p | q), which we return here. */
	return ((!x) | y);
}
/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
	/* XOR-ing a number with itself gives zero; if they are NOT equal, the operation gives a non-zero result.
	 * To make this non-zero into a 1, logic "NOT" (!) it twice.
	 * The first Logic NOT makes the non-zero value into zero.
	 * The second Login NOT makes the zero value into one.
	 */
	return !!(x ^ y);
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
	/* We first stored whether x is zero or not (if it is, we set isZero to all 0's, otherwise, to all 1's).
	 * We then set allMSB so that the most significant bit filled all the bit slots.
	 * At this point, a positive number is 0, and a negative number is -1 (-1 being all ones).
	 * We need the positive 0 to be a positive 1. We shift the number one bit to the left and set it as one.
	 * This makes the 0 into a one, but doesn't change the -1.
	 * At this point, a positive number is 1, and a negative number is -1.
	 * Finally, we bitwise-AND the value with isZero -- if it is not zero (all 1's) it properly returns the 1 or negative 1.
	 *    -- if it is zero (all 0's), the 1 or negative 1 becomes 0, and is returned.
	 */

	int isZero = ((!!x) << 31) >> 31;
	int allMSB = x >> 31;
	int oneOrNegOne = (allMSB << 1) + 1;
	return oneOrNegOne & isZero;
}
/* Rating 3 -- 2 points each */
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	/* We first stored whether x is non-zero or not (if it is non-zero, we set all bits to 1, if it is zero, we set all bits to 0).
	 * We then AND-ed it to y, which would give us y if x was non-zero, and added z, which is AND'd to isNonZero's compliment.
	 * Doing so gives the same functionality as the ternary operator.
	 */
	int isNonZero = ((!!x) << 31) >> 31;
	return ((y & isNonZero) + (z & (~isNonZero)));
}

/* Rating 4 -- 1 point each */
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
	/*Checks to see if the greatest sig bit is 0 or 1
	* Take the complement of x and add one to it to make it negative
	* Returns the positive value if it was negative, or simple x if it was positive.
	*/
	int isNeg = x >> 31;
	int absValIfNeg = (~x) + 1;
	return (absValIfNeg & isNeg) + (x & (~isNeg));	
}

/* Float Rating 2 -- 3 points each */
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
	/*First we take uf and shift it to the right by the size of the mantissa so that the exponent bits are the first
	* Eight bits seen then we and if with 0xFF to check if it gives back all 1's which means that the exponent is  all ones
	* Next we take the mantissa and eliminate the sign bit and the exponent bits and then right shift to have the most significant
	* bit of the mantissa all on the right so if it is nonZero and the exponents are all ones we know that it is NaN so we return uf
	* Finally we take uf AND it to ~(10000....000) which lets us change the bit sign if it is one or keep it zero if zero 
	*/
	unsigned isAllOnesExponent = (((uf >> 23) & 0xFF) == 0xFF);
	unsigned mantissaIsNonZero = (uf << 9) >> 9;
	if (isAllOnesExponent && mantissaIsNonZero)
		return uf;
	
	return uf & ~(1 << 31);
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	/* We check if the exponents are all ones by getting rid of the mantissa bits and then comparing the remaining 8 bits to 0xFF
	* which will be 1 if they are equal zero if they are not
	* Then check if all of the bits in the mantissa or zero or not by checking the most significant bit so if it is nonZero and the exponents are all
	* ones we knew that it is NaN so we return uf
	* Otherwise we XOR uf to 1000....0000 making negative floats into positivie floats and positive floats into negative floats
	*/

	unsigned isAllOnesExponent = (((uf >> 23) & 0xFF) == 0xFF);
	unsigned mantissaIsNonZero = (uf << 9) >> 9;
	if (isAllOnesExponent && mantissaIsNonZero)
		return uf;

	return uf ^ (1 << 31);
}