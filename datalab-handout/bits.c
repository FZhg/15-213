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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    /* In A, matching ones of x and y will be one.
     * In B, matching zeros of x and y will be one.
     * If A and B has a matching zeros, then both conditions above are excluded.*/
    int A = x & y;
    int B = ~x & ~y;
    return ~A & ~B;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    /*tmin bit patterns. 1 followed by 31 0s.*/
    return 1 << 31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    /*
     * when x = -1 or Tmax, x + 1 is complement of x.
     * In other words, when x + 1 is not zero and is the complement of x, x is the Tmax.
     * */
    int y = x + 1;
    return (!(~y ^ x)) & !(!(y ^ 0));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    /*
     * I first construct a mask as 0xAAAAAAAA.
     * the odd bits of x should be the same with the mask.
     * So x & mask will be equal to  mask.
     * */
    int mask = 0xAA;
    mask = mask + (mask << 8);
    mask = mask + (mask << 16);
    return !((x & mask) ^ mask);


}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    /**
     * this is from the textbook
     */
    return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {

    /**
     * The pattern of x can be one of the following
     * 1.  0000...00110???
     * 2.  0000...0011100?
     */
    int mask1 = (~0) << 4;
    int A = x & mask1;
    int isSecondHexOk = !(A ^ 0x30);

    //case 1: 100x
    int mask2 = 0xE;
    int B = x & mask2;
    int isCase1Ok  = !(B^0x8);

    // case 2: 0xxx
    int mask3 = 0x8;
    int C = x & mask3;
    int isCase2Ok = !(C^0);

    int isFirstHexOk = (isCase1Ok | isCase2Ok);

    return isFirstHexOk & isSecondHexOk;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    /**
     * Create a mask of 111..., when x is zero;
     * Create a mask of 0000...., when x is one;
     */
    int isXZero = !x;
    int mask = ((isXZero << 31) >>31);
  return (~mask & y) | (mask & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    /**
     *  if  xy < 0, it is possible to overflow.  Just check the sign of x or y.
     *  if xy >= 0, check the sign of y - x, which should be 0 if x <=y.
     */

  // case 1: different sign
    int signMask = 1;
    int signX = (x >> 31) & signMask;
    int signY = (y >> 31) & signMask;
    int isSignsDifferent = signX ^ signY;
    int case1Ok = isSignsDifferent & (!(signY ^ 0));




  // case 2: the same sign
  int negX = ~x + 1;
  int yMinusX = y + negX;
  int signYMinusX = (yMinusX >> 31) & signMask;
  int case2OK =(!isSignsDifferent) & (!(signYMinusX ^ 0));

  return  case1Ok | case2OK ;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    /**
     * When x is zero or Tmin, the bitpatterns of x and -x are the same.
     * Then, their sign bits are the same. Otherwise, the sign bits are 0 and 1.
     * Check the sign of x and the XOR of sign bits of x and -x, which should be zero.
     */
    int signMask = 1;
    int signX = (x>>31) & signMask;

    int negX = ~x + 1;
    int A = x ^ negX;
    int signA = (A >> 31) & signMask;
    return (signA ^ 1) & (signX ^ 1);
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    /**
     * The author of this solution cleverly used two techniques:
     * 1. a binary search of the first one in the bit pattern
     * 2. use logical negation to detect ones in the subrange of the bit pattern.
     */
    //credit: https://github.com/codeAligned/CMU-15213-Lab/blob/master/1_DataLab/datalab-handout-solution/bits.c
    int bitNumTotal = 0;
    int mask1 = (0xFF | 0xFF << 8) << 16; //0xFFFF0000
    int bitNum = 0;
    int mask2 = 0xFF << 8; // 0x0000FF00
    int mask3 = 0xF0; // 0x000000F0
    int mask4 = 0xC; //0X00.....001100;
    int mask5 = 0x2; //0X00.....000010;
    int mask6 = 0x1;//0X00.....000001;


    x = x ^ (x >> 31);
    // if x is negative, convert x into a positive number sharing the same necessary two-complement bit numbers.


    // Case 1:  31rst - 16th bits contains at least a 1.
    bitNum = (!!(x & mask1)) << 4; // 16 or 0
    x = x >> bitNum;
    bitNumTotal += bitNum;

    // Case 2: 15th - 8th bits contains at least a 1;

    bitNum = (!!(x & mask2)) << 3; // 8 or 0
    x = x >> bitNum;
    bitNumTotal += bitNum;

    //Case 3: 7th -4th bits contains at least a 1;

    bitNum = (!!(x & mask3)) << 2; //  4 or 0
    x = x >> bitNum;
    bitNumTotal += bitNum;

    // Case 4: 3rd-2nd bits contains at least 1
    bitNum = (!!(x & mask4)) << 1; //2 or 0
    x = x >> bitNum;
    bitNumTotal += bitNum;

    // case 5: 1rst bit contains 1

    bitNum = (!!(x & mask5)); // 1 or 0
    x = x >> bitNum;
    bitNumTotal += bitNum;


    // case 6: 0th bit contains 1
    bitNum = (x & mask6); // 1 or 0
    bitNumTotal += bitNum;


    bitNumTotal += 1; // at least need one bit for the 0th bit

    return bitNumTotal;
}


//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    /**
     * There is smooth transition from denorm to norm.
     * So for case 2, a simple leftshift works.
     */
    int expMask = 0x7F800000;
    int fracMask = 0x007FFFFF;
    int signMask = 1 << 31;

    int e = uf & expMask;
    int frac = uf & fracMask;
    int sign = uf & signMask;

    // case 1: uf is NaN and infinity
    if (!(e ^ expMask)) {
        return uf;
    } else if (!e) {
        // case 2: uf is in denorm
        // case 2.1 without overflow
        // case 2.1 with overflow
        frac = frac << 1;
        return sign | e | frac;

    } else {
        // case 3: uf is in norm
        e = e + (1 << 23);
        return sign | e | frac;
    }

}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    /**
     * For normalized float, just shift the frac according to E.
     */
    int expMask = 0x7F800000;
    int fracMask = 0x007FFFFF;
    int signMask = 1 << 31;

    int exp = uf & expMask;
    int frac = uf & fracMask;
    int sign = uf & signMask;

    // case 1: uf is NaN and infinity
    if (!(exp ^ expMask)) {
        return 0x80000000u;
    } else if (!exp) {
        // case 2: uf is in denorm
        return 0; // round towards zero
    } else {
        // case 3: uf is in norm
        int bias = 127;
        int e = (exp >> 23);
        int E = e - bias;
        if (E < 0) {
            return 0; // round towards zero
        } else if (E > 31) {
            return 0x80000000u; // overflow

        } else {

            int significandLeftShifted23 = ((1 << 30) >> 7) | frac;
            int significandRounded = 0;
            if (E - 23 > 0) {
                significandRounded = significandLeftShifted23 << (E - 23);
            } else {
                significandRounded = significandLeftShifted23 >> (23 - E);
            }
            if (sign == (1 << 31)) {
                return -significandRounded;
            } else {
                return significandRounded;
            }

        }
    }
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    /**
     * The fraction for denormalized float has to contain a single 1;
     * The fraction for the normalized float has to be all zeros.
     */
    int minE = (1 - 127) + (-23);
    int bias = 127;
    int maxE = 0xFE - bias;
    if (x < minE) {
        return 0; // underflow
    } else if (x > maxE) {
        return (0xFF << 23); // overflow
    } else {
        int denormE = 1 - bias;
        int maxDenormE = denormE - 1;
        if (x <= maxDenormE) {
            // represent by a denorm
            int fracExp = x - denormE;
            int frac = 1 << (22 + fracExp + 1);
            return 0 | frac;
        } else {
            //represent by a norm
            int e = x + bias;
            return (e << 23);
        }
    }
}
