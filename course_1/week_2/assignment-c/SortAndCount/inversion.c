/* 
 * @title: Array Inversion Source File
 * @author: Jake Schroeder 
 * @license:     
 *      This file is part of "Array Inversion Computation in C" 
 *  
 *      "Array Inversion Computation in C" is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 * 
 *      "Array Inversion Computation in C" is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 * 
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>


/**
 * getMergeItem
 * ============================================================================
 * As long as a is not out of values
 * Gets value at aCount in source array a, converts to an integer and returns
 * 
 * @internal
 *      here again is our assumption that the user's input array of strings 
 *      will all have values within the bounds of an integer
 * 
 *      see also: setMergeItem
 * 
 * @param a
 * @param aLen
 * @param aCount
 * @return 
 */
int getMergeItem(char ** a, int aLen, int aCount) {
    if(aCount < aLen) {
        char * aStr = a[aCount];
        return atoi(aStr);
    }
    return 0;
}

/**
 * setMergeItem
 * ============================================================================
 * Sets the value of the destination array d at dCount to the string value of a 
 * 
 * @internal 
 *      note that all numbers that are representable by int will fit in a 
 *      12-char array
 * 
 *      in this way, we assume the users input array of strings contains 
 *      only values within the bounds of a traditional integer
 * 
 * @param d; destination array
 * @param dCount; index at destination array where a should be set
 * @param a; integer value to be converted and set in d
 */
void setMergeItem(char ** d, int dCount, int a) {
    // all numbers that are representable by int will fit in a 12-char array
    int maxIntChars = 12;
    d[dCount] = realloc(d[dCount], (sizeof(char) * maxIntChars) + 1);
    snprintf(d[dCount], maxIntChars, "%d", a);
    return;
}


/**
 * mergeAndCountSplitInv
 * ============================================================================
 * Calculate split inversions using the "trick" of calculating differential
 * inversions (documented below).
 * 
 * @param b; first slice of original input array, sorted
 * @param bLen; length of b
 * @param c; second slice of original input array, sorted
 * @param cLen; length of c
 * @param d; destination array where full sorted outcome will be set
 * @param z; inversion result; any discovered inversions will be added to this
 */
void mergeAndCountSplitInv(char ** b, int bLen, char ** c, int cLen, char ** d, mpz_t z) {
    
    // initialize counters for b, c and d: i, j, k
    int i = 0;
    int j = 0;
    int k = 0;
    
    // calculate the final length of d: n
    int n = bLen + cLen;
    
    // initialize a bignum int for bLen so we can properly compute total 
    // inversions as z
    mpz_t mpzBLen;
    mpz_init(mpzBLen);
    mpz_add_ui(mpzBLen, mpzBLen, bLen);
    
    // for each input up to the total, n
    while(k < n) {
        
        // safely get each merge item
        // if the source array is invalid a placeholder 0 int will be used
        int x = getMergeItem(b, bLen, i);
        int y = getMergeItem(c, cLen, j);
        
        // NON-INVERSION CASES
        // if either:
            // b is equal to c (prefer left array)
            // b input is smaller than c OR
            // c is out of inputs to copy
        if ((x < y || x == y || j == cLen) && i < bLen ) {
            
            // set index k of d to value of b (x)
            setMergeItem(d, k, x);
            i++;
            
        // INVERSION CASES
        // if either:
           // c input is smaller than b OR
           // b is out of inputs to copy
        } else if ((x > y || i == bLen) && j < cLen) {
            
            // set index k of d to value of c (y)
            setMergeItem(d, k, y);
            j++;
            
            // initialize a bignum int for computing the differential 
            // inversions
            mpz_t diff;
            mpz_init(diff);
            
            // calculate differential inversions as 
            // 
            // number of elements left in b
            // when the item was copied from c 
            //
            // aka: (b's length minus b's counter)
            mpz_sub_ui(diff, mpzBLen, i);
            
            // add differential inversions to total inversions: z
            mpz_add(z, z, diff);
            
            // clear the memory allocated for the differential inversion
            // count
            // @internal: you may be able to optimize this so we don't have
            //      to clear for each inversion instance
            mpz_clear(diff);
        }
        
        // always increment d's counter
        k ++;
    }
    
    return;
}

/**
 * copyArray
 * ============================================================================
 * Helper function to copy all members of x into a y given len
 * 
 * @param x; input array to copy
 * @param len; number of input array elements to copy, starting at x[0]
 * @return malloc'd char ** pointer to x-copy, y
 */
char ** copyArray(char ** x, int len) {
    char ** y = NULL;
    for(int i = 0; i < len; i ++) {
        y = realloc(y, sizeof(y) * (i + 1));
        int sLen = strlen(x[i]);
        y[i] = malloc(sizeof(x[i]) * (sLen + 1));
        strncpy(y[i], x[i], sLen);
        y[i][sLen] = '\0';
    }
    return y;
}

/**
 * allocateSlice
 * ============================================================================
 * Helper function to determine how to use copyArray, given whether this is 
 * the first or second slice (idx), and the nature of len (odd or even)
 * 
 * @param array; input array of strings, see "sortAndCount"
 * @param len; length of given array, see "sortAndCount"
 * @param idx; whether this is the first (0) or second (1) slice
 * @param destLen; initialized integer pointer we can set the
 *      resulting length to
 * @return 
 */
char ** allocateSlice(char ** array, int len, int idx, int * destLen) {
    
    // initialize and set the point where the first array (idx = 0) should be 
    // copied to and where the second array's (idx = 1) copy should begin
    //
    // dynamically set the length pointer based on these conditions, keeping
    // in mind special handling required for the second half of odd-len
    // string arrays (see: midpoint + 1)
    int midpoint;
    if (len % 2 == 0) {
        midpoint = len / 2;
        *destLen = midpoint;
    } else {
        if (idx == 0) {
            midpoint = len / 2;
            *destLen = midpoint;
        } else {
            midpoint = len - (len / 2) - 1;
            *destLen = midpoint + 1;
        }
    }  

    if (idx == 0) {
        // if we want the first slice, we simply need to return the array (array[0])
        return copyArray(array, midpoint);
    } else {
        // otherwise, we will return the ptr at the midpoint (destLen)
        return copyArray(&array[midpoint], *destLen);
    }
}


/**
 * sortAndCount
 * ============================================================================
 * The main method of the inversion module
 * 
 * For a given array of strings, char ** array, of a given length int len
 * divide and conquer to compute the total number of inversions, stored as 
 * mpz_t result
 * 
 * @param array; input array of strings, properly null terminated and clear
 *      of any non-numeric input (no \n)
 * @param len; length of given array exactly equalling number of strings 
 *      contained therein
 * @param result; bignum integer, initialized, which the resulting number of 
 *      inversions will be added to
 */
void sortAndCount(char ** array, int len, mpz_t result) {
    // base condition - return no inversions if the length is one
    // @internal: since mpz_init sets value to 0, we do not have to worry
    //      about setting a 0 value
    if (len == 1) {
        return;
    }
    
    // divide the input array into its sub-parts: b, c
    // @internal note that we copy these sub-arrays to enable free transformation
    //      as a potential optimization, you may be able to get away with not 
    //      copying the sub-arrays, though during the merge step I am not 
    //      confident if this will impact the newly set array
    int bLen, cLen;
    char ** b = allocateSlice(array, len, 0, &bLen);
    char ** c = allocateSlice(array, len, 1, &cLen);
    
    // initialize bignum integers for b and c inversion counts: x, y
    mpz_t x, y;
    mpz_init(x);
    mpz_init(y);
    
    // for each slice b and c, set the inversion count to x and y respectively
    // @internal these are recursive steps until given len = 1
    sortAndCount(b, bLen, x);
    sortAndCount(c, cLen, y);
    
    // calculate and set split inversions: z
    mpz_t z;
    mpz_init(z);
    mergeAndCountSplitInv(b, bLen, c, cLen, array, z); 
   
    // free the helper string array copies: b, c
    free(b);
    free(c);
    
    // compute and set result to the bignum equivalent of x + y + z
    mpz_add(result, result, x);
    mpz_add(result, result, y);
    mpz_add(result, result, z);
    
    // clear memory for helper variables: x, y, z
    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(z);
    
    return;
}
