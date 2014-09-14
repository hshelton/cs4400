/* 
 * CS:APP Data Lab 
 * 
 * Hayden Shelton u0658884
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
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
	/* 1. right shift by 31 to get all ones or zeros
	 * 2. XOR result of step 1 with x. For x>=0, this will result in x
	 * 	  for x <1, this number will be one too high
	 * 3. For positive x add 0, for negative x add -1. Return sum
	 */	
	
	int shifted = x >>31;
	int result = shifted ^ x; 
	
	int subtractMe = ~shifted;
	subtractMe = subtractMe +1;
	
	return result + subtractMe;
	
	

}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  /* 1. Set up a mask of 01010101 01010101 01010101 01010101
   * 2. bitwise AND this with x to check for even ones
   * 3. if the number has all even-numbered bits set to 1, then
   *    the result of step 2 will be zero, so return 1 & vice versa
   */
  int comp = 85;
  int t1 = (comp<<8)+85;
  int t2 = (t1<<8) +85;
  int mask = (t2<<8) + 85;

   int res = x & mask;
   int same = mask ^ res;
  return !same;
       
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	/* zero is the only number where the sign bit doesn't change when negated */
	int sign = x >>31;
	int neg_sign = ((~x) + 1)>>31;
	

  return (~(sign | neg_sign)) & 1;
}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
/*
 * An AND gate can be constructed with three NOR gates*/
  int not_x = ~x;
  int not_y = ~y;

  return ~(not_x | not_y);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	/* Mask off bits one at time and add it to a running totoal */
	int sum = 0;
	 sum = sum + (x & 1);
  sum = sum + ((x >> 1) & 1);
  sum = sum + ((x >> 2) & 1);
  sum = sum + ((x >> 3) & 1);
  sum = sum + ((x >> 4) & 1);
  sum = sum + ((x >> 5) & 1);
  sum = sum + ((x >> 6) & 1);
  sum = sum + ((x >> 7) & 1);
  sum = sum + ((x >> 8) & 1);
  sum = sum + ((x >> 9) & 1);
  sum = sum + ((x >> 10) & 1);
  sum = sum + ((x >> 11) & 1);
  sum = sum + ((x >> 12) & 1);
  sum = sum + ((x >> 13) & 1);
  sum = sum + ((x >> 14) & 1);
  sum = sum + ((x >> 15) & 1);
  sum = sum + ((x >> 16) & 1);
  sum = sum + ((x >> 17) & 1);
  sum = sum + ((x >> 18) & 1);
  sum = sum + ((x >> 19) & 1);
  sum = sum + ((x >> 20) & 1);
  sum = sum + ((x >> 21) & 1);
  sum = sum + ((x >> 22) & 1);
  sum = sum + ((x >> 23) & 1);
  sum = sum + ((x >> 24) & 1);
  sum = sum + ((x >> 25) & 1);
  sum = sum + ((x >> 26) & 1);
  sum = sum + ((x >> 27) & 1);
  sum = sum + ((x >> 28) & 1);
  sum = sum + ((x >> 29) & 1);
  sum = sum + ((x >> 30) & 1);
  sum = sum + ((x >> 31) & 1);
  return sum;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /* If 'x' is equal to anything other than zero, the left side of 'result' will equal 'y' and the right
     side will equal 0.  If 'x' is zero, the left side of 'result' will equal 0 and the right side will
     equal 'z'. */
  int bool_x = (!x);
  int result = (y & (~(!bool_x) + 1)) + (z & (~(bool_x) + 1));
  
  return result;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	/* First find the sign bit, then figure out the bias you need to add if n <1, perform shift and add bias
	 */
	int sign = (x >>31) & 1;
	int bias = (sign <<n) + ((~sign) + 1);
    return (x + bias) >> n;
}
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
  return 2;
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
 return 2;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  return 2;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	/* to get byte n shift left by 0, 8, or 24  and use mask to strip off all but the LSB
	 */
	int shift = n <<3;
	int shifted = x >> shift;
	return shifted & 0xff;

}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /* Subtracts x from y and checks the sign of the result. Checks edge cases separately. */
  int diff = y + ((~x) + 1);
  int diff_sign = (diff >> 31) & 1;

  int x_sign = (x >> 31) & 1;
  int y_sign = (y >> 31) & 1;

  int sign_check_1 = (x_sign | 0) & (!y_sign); 
  int sign_check_2 = (y_sign | 0) & (!x_sign); 

  int result = ((!(x ^ y)) | ((sign_check_1 | !diff_sign) & (!sign_check_2)));
  return result;

}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
/* Masks off the sign bit and returns it */
  int sign_bit = (x >> 31) & 1;

  return sign_bit;

}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
	/* Masks off the sign bit, returns !sign bit
	 */
	int sign_bit = (x >> 31) & 1;

  return !(sign_bit);

}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  /*
   * A positive power of 2 will have exactly one 1.
   * So if we subtract 1 from this number, the rest should be all ones.
   * For x:x is power of 2, a bitwise AND with x should result in 0.
   * e.g. x = 32 00000000 00000000 0000001 00000000
   * 	res = 31 00000000 00000000 0000000 11111111
   *     x&res = 00000000 00000000 0000000 00000000
   * Additionally, we know in advance to return 0 if x <= 0. 
   * 
   */
   int isZero = (!(0 ^x)) & 1;
	
   int isNegative = (x >>31) & 1;
     
   int minusOne = (1<<31)>>31; 
   int res = x + minusOne;

   int a = !(x & res);
   int b = !(isZero);
   int c = !(isNegative);
 
   return !( !a | !b |!c); 
}
	
  
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {

	
  return 2;
}
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
/* XOR with zero to compute equality */
  return !(x ^ 0);
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
	
	
  return 2;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  /*The strategy is to setup the correct mask to cancel out the 
   * ones that were inserted by the arithmetic right shift. If no ones 
   * were inserted, doing bitwise AND with the mask doesn't change result.
   * suppose we have -255   11111111 11111111 11111111 00000001
   * -255 >>2               11111111 11111111 11111111 11000000
   * to make logical &  w/  00111111 11111111 11111111 11111111
   */
  int mask = 1 <<31;
  mask = (mask >>n) <<1; 
  mask = ~mask;
   x = x >>n;
  return x & mask;
 
}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  return (1<<31)>>31;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	  /* flip the bits and add 1 */
  int neg_x = (~(x) + 1);
  return neg_x;

}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  return 2;
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
  /* Extract the signed bit. Negate either all ones or all zeros, return whether the sign is negative or
   * (- (x >>31) & 1) or -1 if neg. */
  int x_shifted_31 = x >> 31;
  int negx_shifted_31 = (~x + 1) >> 31;

  return x_shifted_31 | (negx_shifted_31 & 1);
  
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	return 1 <<31;

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
	/* 1. for n <32, right shift 10000000 00000000 00000000 00000000 by n-1 
	 * 2. if n = 32, right shift 10000000 00000000 00000000 00000000 by
	 * 31
	 */ 
	  int mask = 1 << 31;
  int is_32 = (~(!(n ^ 32))) + 1;
  mask = (mask >> (n + is_32)) << (1 + is_32);
	  
	return mask;
  
}


