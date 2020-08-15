/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int getMergeItem(char ** a, int aLen, int aCount) {
    if(aCount < aLen) {
        return atoi(*a);
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
int mergeAndCountSplitInv(char ** b, int bLen, char ** c, int cLen, char ** d) {
    
    int i = 0;
    int j = 0;
    int k = 0;
    int inv = 0;
    int n = bLen + cLen;
    
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
        if ((x < y || x == y || j == bLen) && i != cLen ) {
            setMergeItem(d, k, x);
        
            i++;
            
        // if either:
           // c input is smaller than b OR
           // b is out of inputs to copy
        } else if ((x > y || i == cLen) && j != bLen) {
            setMergeItem(d, k, y);
            
            j++;
            
            // inversions increment by number of elements left in b
            // when the item was copied from c
            inv = inv + (bLen - i);
        }
        k ++;
    }
    
    // return the number of split inversions
    return inv;
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


void assignValues(char ** array, char ** x, int xLen) {
    for(int i = 0; i < xLen; i ++) {
        int len = strlen(x[i]);
        array[i] = realloc(array[i], sizeof(array[i]) * len);
        strncpy(array[i], x[i], len);
        array[i][len] = '\0';
    }
    return;
}



char ** allocateSlice(char ** array, int len, int idx, int * destLen) {
    int midpoint;
    if (len % 2 == 0) {
        midpoint = len / 2;
    } else {
        if (idx == 0) {
            midpoint = len / 2;
        } else {
            midpoint = len - (len / 2);
        }
    }
    
    *destLen = midpoint;

    if (idx == 0) {
        // if we want the first slice, we simply need to return the array (array[0])
        return copyArray(array, midpoint);
    } else {
        // otherwise, we will return the ptr at the midpoint (destLen)
        return copyArray(&array[midpoint], *destLen);
    }
}


long long int sortAndCount(char ** array, int len) {
    // base condition - return no inversions if the length is one
    if (len == 1) {
        return 0;
    }
    
    // divide the input array into its sub-parts: b and c
    int bLen, cLen;
    char ** b = allocateSlice(array, len, 0, &bLen);
    char ** c = allocateSlice(array, len, 1, &cLen);
    
    // calculate the inversions in each sub-part: x and y
    long long int x = sortAndCount(b, bLen);
    long long int y = sortAndCount(c, cLen);
    
    // assignValues(array, b, bLen);
    // assignValues(array, c, cLen);
    
    // find the split inversions between a and b and merge them: d
    // calculate split inversions as z
    
    // printf("\nCalling mergeAndCountSplitInv with %s and %s", *b, *c);
    
    // NOTE TO SELF: I think this is going to screw things up
    long long int z = mergeAndCountSplitInv(b, bLen, c, cLen, array);  
    
    free(b);
    free(c);
    
    // return the sum of the inversions
    return x + y + z;
}
