/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>


int getMergeItem(char ** a, int aLen, int aCount) {
    if(aCount < aLen) {
        char * aStr = a[aCount];
        return atoi(aStr);
    }
    return 0;
}


void setMergeItem(char ** d, int dCount, int a) {
    // all numbers that are representable by int will fit in a 12-char array
    int maxIntChars = 12;
    d[dCount] = realloc(d[dCount], (sizeof(char) * maxIntChars) + 1);
    snprintf(d[dCount], maxIntChars, "%d", a);
    return;
}


int sortAscending(const void * p1, const void * p2) {
    return *(const int *)p1 - *(const int *)p2;
}


/**
 * 
 * @internal: d must be allocated large enough to hold char * of (bLen + cLen length)
 * 
 * @param b
 * @param bLen
 * @param c
 * @param cLen
 * @param d
 * @return 
 */
void mergeAndCountSplitInv(char ** b, int bLen, char ** c, int cLen, char ** d, mpz_t z) {
    
    int i = 0;
    int j = 0;
    int k = 0;
    int n = bLen + cLen;
    
    mpz_t mpzBLen;
    mpz_init(mpzBLen);
    mpz_add_ui(mpzBLen, mpzBLen, bLen);
    
    // for each input up to the total, n
    while(k < n) {
        
        // safely get each merge item
        // if the source array is invalid a placeholder 0 int will be used
        int x = getMergeItem(b, bLen, i);
        int y = getMergeItem(c, cLen, j);
        
        // if either:
            // b is equal to c (prefer left array)
            // b input is smaller than c OR
            // c is out of inputs to copy
        if ((x < y || x == y || j == cLen) && i < bLen ) {
            setMergeItem(d, k, x);
        
            i++;
            
        // if either:
           // c input is smaller than b OR
           // b is out of inputs to copy
        } else if ((x > y || i == bLen) && j < cLen) {
            setMergeItem(d, k, y);
            
            j++;
            
            // inversions increment by number of elements left in b
            // when the item was copied from c
            mpz_t diff;
            mpz_init(diff);
            
            mpz_sub_ui(diff, mpzBLen, i);
            mpz_add(z, z, diff);
            
            mpz_clear(diff);
        }
        k ++;
    }
    
    // return the number of split inversions as z's new value
    return;
}


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


char ** allocateSlice(char ** array, int len, int idx, int * destLen) {
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
