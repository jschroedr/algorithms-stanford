/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdlib.h>
#include <string.h>


int getMergeItem(char * a, int aLen, int aCount) {
    if(aCount < aLen) {
        char x = a[aCount] + '\0';
        int xInt = atoi(&x);
        return xInt;
    }
    return 0;
}


void setMergeItem(char * d, int dCount, int a) {
    // convert the number stored in a to a character and set
    d[dCount] = a + '0';
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
int mergeAndCountSplitInv(char * b, char * c, char * d) {
    
    // calculate the length of the input arrays assuming null termination 
    int bLen = strlen(b);
    int cLen = strlen(c);
    
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
    
    // null terminate d
    d[k] = '\0';
        
    // return the number of split inversions
    return inv;
}


int findMidpoint(int len, int idx) {
    if (len % 2 == 0) {
        return len / 2;
    } else {
        if (idx == 0) {
            return len / 2;
        } else {
            return len - (len / 2);
        }
    }
}


char * allocateSlice(char * a, int len, int idx) {
    
    // find the midpoint based on the even-ness of the number
    int midpoint = findMidpoint(len, idx);
    
    // allocate the character array slice on memory
    char * slice = malloc(sizeof(char) * (midpoint + 1));
    
    // copy the string
    if (idx == 0) {
        strncpy(slice, a, midpoint);        
    } else {
        strncpy(slice, &a[len / 2], midpoint);        
    }
    
    // null terminate the array
    slice[midpoint + 1] = '\0';
    
    // return the pointer
    return slice;
}


int sortAndCount(char * a) {
    
    // get the length of the input string, assuming its properly null terminated
    int len = strlen(a);
    
    // base condition - return no inversions if the length is one
    if (len == 1) {
        return 0;
    }

    // divide the input array into its sub-parts: b and c
    char * b = allocateSlice(a, len, 0);
    char * c = allocateSlice(a, len, 1);
    
    // calculate the inversions in each sub-part: x and y
    int x = sortAndCount(b);
    int y = sortAndCount(c);
        
    // find the split inversions between a and b and merge them: d
    // calculate split inversions as z
    int z = mergeAndCountSplitInv(b, c, a);  
    
    // return the sum of the inversions
    return x + y + z;
}
