/* 
 * @title: Karatsuba Multiplication Source File
 * @author: Jake Schroeder 
 * @license:     
 *      This file is part of "Karatsuba Multiplication in C" 
 *  
 *      "Karatsuba Multiplication in C" is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 * 
 *      "Karatsuba Multiplication in C" is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 * 
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gmp.h>


/**
 * zeroPad
 * ===========================================================================
 * Pads the given char * x based on the directive given by int left 
 * 
 * Expects left to be one of (1 = yes, 0 = no)
 * 
 * xLen is the length of the input string x, and digits is the number of 
 * digits to pad with
 * 
 * @internal
 *      There is likely a memory leak in this function in cases where
 *      x is not a string constant from main (i.e. in recursive cases).
 *      
 *      A remedy might be applied by handling x differently in the calling
 *      function - for example explicitly storing x's contents in an alloc'd
 *      character array
 * 
 * @param x
 * @param xLen
 * @param digits
 * @param left
 * @return newX (char *), ptr to the newly padded character array
 */
char * zeroPad(char * x, int xLen, int digits, int left) {
    char * newX = malloc(sizeof(char) * (xLen + digits + 1));
    if (left == 0) {
        strncpy(newX, x, xLen);
        int start = xLen;
        while(start < (xLen + digits)) {
            newX[start] = '0';
            start ++;
        }
        newX[start] = '\0';
        return newX;
    } else {
        int start = 0;
        int xStart = 0;
        while(start < (xLen + digits)) {
            if(start < digits) {
                newX[start] = '0';
            } else {
                newX[start] = x[xStart];
                xStart ++;
            }
            start ++;
        }
        newX[start + 1] = '\0';
        // free(x);
        return newX;
    }
}


/**
 * allocateSlice
 * ===========================================================================
 * Performs a string copy and ensures the null terminator is appended 
 * properly.
 * 
 * Expects int idx to be one of (0 = first half, 1 = second half)
 * 
 * @param x
 * @param j
 * @param idx
 * @return 
 */
char * allocateSlice(char * x, int j, int idx) {
    char * dest = malloc(sizeof(x) * (j + 1));
    if(idx == 0) {
        strncpy(dest, x, j);
    } else {
        strncpy(dest, &x[j], j);
    }
    dest[j] = '\0';
    return dest;
}

/**
 * karatsuba
 * ===========================================================================
 * Recursively computes the product of x and y using Karatsuba multiplication
 * and stores the product in mpz_t result (from GNU BigNum library)
 * 
 * @internal
 *      The "base" of mpz_set_str is a little fuzzy here - really it should
 *      probably be 10 all around, but this function was tested to work as-is.
 * 
 *      Note that a base of 0 does open the opportunity for BigNum to interpret
 *      leading zeros as part of a hexadecimal value. Therefore as a future
 *      optimization it would be advisable to ensure all bases are 10 (or 
 *      at least some consistent non-zero number0
 * 
 * @param x
 * @param y
 * @param result
 */
void karatsuba(char * x, char * y, mpz_t result) {
    
    // get the length of each input str, and convert them to integers
    int xLen = strlen(x);
    int yLen = strlen(y);
    
    // base condition: if both arguments are size 1, then simply multiply and return
    if(xLen == 1 && yLen == 1) {
        signed int base = atoi(x) * atoi(y);
        mpz_set_ui(result, base);
        return;
    }
    // determine n - the shared input length - and use 0-padding to handle
    // any inconsistencies
    int n;
    if (xLen < yLen) {
        x = zeroPad(x, xLen, yLen - xLen, 1);
        n = yLen;
    } else if (yLen < xLen) {
        y = zeroPad(x, yLen, xLen - yLen, 1);
        n = xLen;
    } else {
        n = xLen;
    }

    // guarantee n is divisible by two and left-pad if needed
    if (n % 2 != 0) {
        x = zeroPad(x, n, 1, 1);
        y = zeroPad(y, n, 1, 1);
        n ++;
    }

    // compute the padding for sub problem one (result a) and two (result b) 
    int j = n / 2;
    printf("\nJ = %d\n", j);
    printf("\nX = %s, Y = %s\n", x, y);
    int bZeroPadding = n - j;
    int aZeroPadding = bZeroPadding * 2;
    
    // slice the normalized inputs
    char * a = allocateSlice(x, j, 0);
    char * b = allocateSlice(x, j, 1);
    char * c = allocateSlice(y, j, 0);
    char * d = allocateSlice(y, j, 1);
    printf("\n%s, %s, %s, %s\n", a, b, c, d);
    
    // subproblem one and two - these are required to compute the later solutions
    mpz_t ac;
    mpz_init(ac);
    karatsuba(a, c, ac);
    mpz_t bd;
    mpz_init (bd);
    karatsuba(b, d, bd);

    // compute ab and cd which are required to compute k
    mpz_t aNum;
    mpz_init(aNum);
    mpz_set_str(aNum, a, 0);
    
    mpz_t bNum;
    mpz_init(bNum);
    mpz_set_str(bNum, b, 0);
    
    mpz_t cNum;
    mpz_init(cNum);
    mpz_set_str(cNum, c, 0);
    
    mpz_t dNum;
    mpz_init(dNum);
    mpz_set_str(dNum, d, 0);
    
    mpz_t ab;
    mpz_init(ab);
    
    mpz_t cd;
    mpz_init(cd);
    
    mpz_add(ab, aNum, bNum);
    mpz_add(cd, cNum, dNum);

    char * abStr = mpz_get_str(NULL, 0, ab);
    char * cdStr = mpz_get_str(NULL, 0, cd);

    // compute k: temporary variable to solve third sub-problem
    mpz_t k;
    mpz_init(k);
    karatsuba(abStr, cdStr, k);
    
    /*
     * Solution 1
     * `````````````````````````````````````````````````````````````````
     * the first term to be used in Gauss' trick
     */
    // convert solution 1 to a char * and pad it accordingly (equivalent of pow 10)
    char * acStr = mpz_get_str(NULL, 0, ac);
    acStr = zeroPad(acStr, strlen(acStr), aZeroPadding, 0);
    
    // convert solution 1 back to mpz_t so we may use it in Gauss' trick
    mpz_t aResult;
    mpz_init(aResult);
    mpz_set_str(aResult, acStr, 10);

    /*
     * Solution 2
     * ````````````````````````````````````````````````````````````````
     * the second term to be used in Gauss' trick
     */
    // compute solution 2 using k
    mpz_sub(k, k, ac);
    mpz_sub(k, k, bd);
    
    // zero-pad k in preparation for solution 2
    char * kStr = mpz_get_str(NULL, 0, k);
    kStr = zeroPad(kStr, strlen(kStr), bZeroPadding, 0);
    
    // convert solution 2 to mpz_t in preparation for the trick
    mpz_t bResult;
    mpz_init(bResult);
    mpz_set_str(bResult, kStr, 0);
    
    /*
     * Gauss' Trick
     * ``````````````````````````````````````````````````````````````````
     * use the two solutions, a and b, along with the second subproblem 
     * bd to as the three terms in Gauss' trick - which enabled O(nlogn)
     * running time
     */
    // perform Gauss' trick using solution 1 and 2 (and subtracting subproblem 2, bd)
    mpz_add(result, aResult, bResult);
    mpz_add(result, result, bd);
    
    // deallocate primitive objects
    free(a);
    free(b);
    free(c);
    free(d);
    
    // deallocate big num objects
    mpz_clear(ac);
    mpz_clear(bd);
    mpz_clear(aNum);
    mpz_clear(bNum);
    mpz_clear(cNum);
    mpz_clear(dNum);
    mpz_clear(ab);
    mpz_clear(cd);
    mpz_clear(k);
    mpz_clear(aResult);
    mpz_clear(bResult);
    
    return;
}