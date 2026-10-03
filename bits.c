/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return (0x80) << 24;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~((~((~x)&y))&(~(x&(~y))));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  return (~((x >> 31) & x)) + 1;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  dst = dst << 3;
  src = src << 3;
  int x_dst = (x & (~(0xFF << dst)));
  int x_src = (((x & (0xFF << src)) >> src) & 0xFF) << dst;
  return x_dst | x_src;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  x = x >> n;
  int mask = ~(((1 << 31) >> n) << 1);
  x = x & mask;
  return x;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask = 0xF;
  mask = mask | (mask << 8);
  mask = mask | (mask << 16);
  int low_nibble = x & mask;
  int mask_shifted = mask << 4;
  int high_nibble = x & mask_shifted;
  low_nibble = low_nibble << 4;
  high_nibble = high_nibble >> 4;
  high_nibble = high_nibble & (mask | (mask >> 4));
  return low_nibble | high_nibble;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  x = x | (x + 1);
  int x_plus_1 = x + 1;
  int second_lowest_zero_bit = x_plus_1 & (~x);
  return second_lowest_zero_bit;
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  int mask = 0xFF;
  mask = mask | (mask << 8);
  int mask_shifted = mask << 16;
  x = ((x & mask) << 16) ^ (x & mask_shifted);
  mask = (0xFF) << 16;
  mask_shifted = mask << 8;
  x = ((x & mask) << 8) ^ (x & mask_shifted);
  mask = (0xF) << 24;
  mask_shifted = mask << 4;
  x = ((x & mask) << 4) ^ (x & mask_shifted);
  mask = (0x3) << 28;
  mask_shifted = mask << 2;
  x = ((x & mask) << 2) ^ (x & mask_shifted);
  mask = (0x4) << 28;
  mask_shifted = mask << 1;
  x = ((x & mask) << 1) ^ (x & mask_shifted);
  x = x >> 31;
  return (~x) & 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int mask = ~(((1 << 31) >> n) << 1);
  x = ((x >> n) & mask) | (x << ((31 ^ n) + 1));
  return x;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int n_minus_1 = ((n ^ 31) + 1);
  int exactly_halfway = !(!((x << n_minus_1) << 1));
  n_minus_1 = n_minus_1 ^ 31;
  x = x >> n_minus_1;
  int round_up = x & 1;
  x = x >> 1;
  x = x + (round_up & ((x & 1) | exactly_halfway));
  x = x << n;
  return x;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int x_xor_y = x ^ y;
  int mid_point = (x & y) + (x_xor_y >> 1);
  int mask = 0xFF;
  mask = mask | (mask << 8);
  mask = mask | (mask << 16);
  y = y ^ mask;
  int mask_top = 0x80 << 24;
  mask = mask ^ mask_top;
  int different_signs = (x_xor_y >> 31) & 1;
  int x_greater_than_y = ((!(!((((x >> 1) & mask) + ((y >> 1) & mask) + (x & y & 1)) & mask_top))) & (!different_signs)) | (different_signs & ((~x) >> 31));
  mid_point = mid_point + (x_xor_y & 1 & x_greater_than_y);
  return mid_point;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int x_xor_a = x ^ a;
  int x_xor_b = x ^ b;
  int mask = 0xFF;
  mask = mask | (mask << 8);
  mask = mask | (mask << 16);
  a = a ^ mask;
  b = b ^ mask;
  int mask_top = 0x80 << 24;
  mask = mask ^ mask_top;
  int different_signs_x_a = (x_xor_a >> 31) & 1;
  int different_signs_x_b = (x_xor_b >> 31) & 1;
  int x_greater_than_a = ((!(!((((x >> 1) & mask) + ((a >> 1) & mask) + (x & a & 1)) & mask_top))) & (!different_signs_x_a)) | (different_signs_x_a & ((~x) >> 31));
  int x_greater_than_b = ((!(!((((x >> 1) & mask) + ((b >> 1) & mask) + (x & b & 1)) & mask_top))) & (!different_signs_x_b)) | (different_signs_x_b & ((~x) >> 31));
  return (x_greater_than_a ^ x_greater_than_b) | (!x_xor_a) | (!x_xor_b);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int opposite_x = ~x;
  int is_negative = (x >> 31) & 1;
  int mask = 1 << 31;
  int INT_MAX = ~mask;
  int not_overflow = 1;
  int x_times_2 = x << 1;
  not_overflow = not_overflow & ((x_times_2 ^ opposite_x) >> 31) ;
  int x_times_4 = x_times_2 << 1;
  not_overflow = not_overflow & ((x_times_4 ^ opposite_x) >> 31) ;
  int x_times_5 = x_times_4 + x;
  not_overflow = not_overflow & ((x_times_5 ^ opposite_x) >> 31) ;
  INT_MAX = (INT_MAX + (is_negative | not_overflow)) << not_overflow;
  not_overflow = not_overflow << 31;
  not_overflow = not_overflow >> 31;
  return (x_times_5 & not_overflow) | INT_MAX ;
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int different_signs_x_y = ((x ^ y) >> 31) & 1;
  int mask = !different_signs_x_y;
  mask = mask | (mask << 1);
  mask = mask | (mask << 2);
  mask = mask | (mask << 4); 
  mask = mask | (mask << 8);
  mask = mask | (mask << 16);
  y = y ^ (z & mask);
  z = z ^ (y & mask);
  y = y ^ (z & mask);
  different_signs_x_y = ((x ^ y) >> 31) & 1;
  int not_overflow = 1;
  int opposite_x = ~x;
  int x_plus_y = x + y;
  int is_negative = (x >> 31) & 1;
  int is_positive = !is_negative;
  not_overflow = not_overflow & ((((x_plus_y ^ opposite_x) >> 31) & 1) | different_signs_x_y);
  x = x_plus_y;
  opposite_x = ~x;
  int different_signs_x_z = ((x ^ z) >> 31) & 1;
  int x_plus_z = x + z;
  is_negative = (not_overflow & ((x >> 31) & 1)) | (is_negative & (!not_overflow));
  is_positive = !is_negative;
  not_overflow = not_overflow & ((((x_plus_z ^ opposite_x) >> 31) & 1) | different_signs_x_z);
  is_negative = is_negative & (~not_overflow);
  is_positive = is_positive & (~not_overflow);
  return is_positive + (~is_negative) + 1;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  if((uf & 0x7F800000) == 0x7F800000){
    return uf;
  }
  if(!(uf & 0x7F800000)) {
    int val = uf & 0x007FFFFF;
    int mask = val & 0x00000001;
    val = val + (val >> 1);
    val = val + (val & mask);
    return (uf & 0xFF800000) + val;
  }
  int val = (uf & 0x007FFFFF) + 0x00800000;
  int mask = val & 0x00000001;
  val = val + (val >> 1);
  if (val & 0x01000000) {
    mask = ((val & 0x00000001) << 1) + mask;
    val = val >> 1;
    val = val ^ 0x00800000;
    if(mask == 3){
      val = val + 1;
    }
    if(mask == 2){
      mask = 1;
      val = val + (val & mask);
    }
    uf = (uf & 0xFF800000) + 0x00800000 + val;
  }
  else{
    val =val ^ 0x00800000;
    val = val + (val & mask);
    uf = (uf & 0xFF800000) + val;
  }
  if((uf & 0x7F800000) == 0x7F800000){
    return uf & 0xFF800000;
  }
  return uf;
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  if((uf & 0x7F800000) == 0x7F800000){
    return uf;
  }
  int mask = (uf & 0x7F800000) >> 23;
  if(mask < 126){
    return uf & 0x80000000;
  }
  if(mask == 126){
    if(uf & 0x007FFFFF){
      return uf & 0x80000000;
    }
    if(uf & 0x80000000){
      return 0xBF800000;
    }
    else{
      return 0x3F800000;
    }
  }
  if(mask >= 150){
    return uf;
  }
  int val = (uf & 0x007FFFFF) + 0x00800000;
  mask = mask - 127;
  mask = 23 - mask;
  int lower_val = val >> mask;
  int higher_val = (val >> mask) + 1;
  lower_val = lower_val << mask;
  higher_val = higher_val << mask;
  if(val - lower_val < higher_val - val){
    val = lower_val;
  }
  else if(val - lower_val > higher_val - val){
    val = higher_val;
  }
  else{
    val = (higher_val >> 1) << 1;
  }
  val = val - 0x00800000;
  val = val + (uf & 0xFF800000);
  return val;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  return 17;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int mask = 0x55;
  mask = mask | (mask << 8);
  mask = mask | (mask << 16);
  int lower_x = x & mask;
  int higher_x = (x >> 1) & mask;
  x = lower_x + higher_x;
  mask = 0x33;
  mask = mask | (mask << 8);
  mask = mask | (mask << 16);
  lower_x = x & mask;
  higher_x = (x >> 2) & mask;
  x = lower_x + higher_x;
  mask = 0xF;
  mask = mask | (mask << 8);
  mask = mask | (mask << 16);
  lower_x = x & mask;
  higher_x = (x >> 4) & mask;
  x = lower_x + higher_x;
  mask = 0xFF;
  mask = mask | (mask << 16);
  lower_x = x & mask;
  higher_x = (x >> 8) & mask;
  x = lower_x + higher_x;
  mask = 0xFF;
  mask = mask | (mask << 8);
  lower_x = x & mask;
  higher_x = (x >> 16) & mask;
  x = lower_x + higher_x;
  return x;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int mask = 0xFF;
  mask = mask | (mask << 8);
  x = (x << 16) | ((x >> 16) & mask);
  mask = mask ^ (mask << 8);
  x = ((x & mask) << 8) | ((x >> 8) & mask);
  mask = mask ^ (mask << 4);
  x = ((x & mask) << 4) | ((x >> 4) & mask);
  mask = mask ^ (mask << 2);
  x = ((x & mask) << 2) | ((x >> 2) & mask);
  mask = mask ^ (mask << 1);
  x = ((x & mask) << 1) | ((x >> 1) & mask);
  return x;
}
