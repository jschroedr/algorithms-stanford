#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>



char * splitFirstHalf(char * x, int xlen) {
    int xIdx = xlen > 1 ? xlen / 2 : 1;
    char * half = malloc(sizeof(half) * xIdx);
    if(xlen > 1) {
        strncpy(half, x, xIdx);
    } else {
        strcpy(half, "0");
    }
    return half;
}

char * splitLastHalf(char * x, int xlen) {
    int xIdx = xlen > 1 ? xlen / 2 : 1;
    char * half = malloc(sizeof(half) * xIdx);
    if(xIdx % 2 == 0) {
        strncpy(half, &x[xIdx - 1], xIdx);
    } else {
        if(xlen == 1) {
            strncpy(half, &x[xIdx - 1], xIdx);
        } else {
            strncpy(half, &x[xIdx], xIdx);
        }
    }
    return half;
}


char * splitInput(char * input, int index, int len) {
    char * split = malloc(sizeof(input));
    if (len == 1 && index == 0) {
        // zero-pad single length inputs that need to be split
        strcpy(split, "0");
    }
    else if (len == 1 && index == 1) {
        // take the single input for the second half of the split
        strcpy(split, input);
    } else {
        // split using integer (floor) division
        int splitIdx = len / 2;
        if (index == 0) {
            strncpy(split, input, splitIdx);
        } else {
            strncpy(split, &input[splitIdx - 1], len - splitIdx);
        }
    }
    return split;
}

/**
 * karatsuba
 * ``````````````````````````````````````````````````````````````````````````````````````````````
 * An illustrative example of karatsuba recursive multiplication in C
 * Given two input strings, divide and conquer the products 
 * 
 * TIP: these lecture notes were EXTREMELY HELPFUL 
 *  https://courses.csail.mit.edu/6.006/spring11/exams/notes3-karatsuba
 * 
 * @param x: input string 1, a number that can be safely transformed to int using atoi()
 * @param y: input string 2, ''
 */
int karatsuba(char * x, char * y) {
    
    // get the length of each input str, and convert them to integers
    int lenX = strlen(x);
    int lenY = strlen(y);
    
    int nMax = (lenX > lenY) ? lenX : lenY;

    // base condition: if both arguments are size 1, then simply multiply and return
    if(lenX == 1 && lenY == 1) {
        return atoi(x) * atoi(y);
    }
    
    char * a = splitInput(x, 0, lenX);
    char * b = splitInput(x, 1, lenX);
    char * c = splitInput(y, 0, lenY);
    char * d = splitInput(y, 1, lenY);

    printf("a: %s, b: %s, c: %s, d: %s\n", a, b, c, d);

    // subproblem one and two
    int resultA = karatsuba(a, c);
    int resultB = karatsuba(b, d);

    // prepare for the third subproblem - add, cast to str, and recursive call
    int z1 = atoi(a) + atoi(b);
    int z2 = atoi(c) + atoi(d);

    char * z1Str = malloc(sizeof(z1Str) * nMax);
    char * z2Str = malloc(sizeof(z2Str) * nMax);

    sprintf(z1Str, "%d", z1);
    sprintf(z2Str, "%d", z2);

    // printf("z1: %s, z2: %s \n", z1Str, z2Str);
    int resultC = karatsuba(z1Str, z2Str) - resultA - resultB;
    
    // printf("ra: %d, rb: %d, rc: %d \n", resultA, resultB, resultC);

    // free up now unused memory
    free(a);
    free(b);
    free(c);
    free(d);
    free(z1Str);
    free(z2Str);

    // get the products of 10**n/2 and 10**n
    int nMaxHalf = nMax % 2 == 0 ? nMax / 2 : (nMax + 1) / 2;
    int nPowHalf = pow(10, nMaxHalf);
    int nPow = pow(10, nMax);
    printf("nMax: %d, nMaxHalf: %d, nPowHalf: %d, nPow: %d\n", nMax, nMaxHalf, nPowHalf, nPow);
    
    // return using Karatsuba's insight - this allows us to use 3 subproblems instead of 4
    return (resultA * nPow) + (resultC * nPowHalf) + resultB;
}
