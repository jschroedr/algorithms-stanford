#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


char * splitInput(char * input, char * split, int index, int len) {
    if (len == 1 && index == 0) {
        // zero-pad single length inputs that need to be split
        strcpy(split, "0");
    }
    else if (len == 1 && index == 1) {
        // take the single input for the second half of the split
        strcpy(split, input);
    } else if (len > 1) {
        // split using integer (floor) division
        int splitIdx = len / 2;
        if (index == 0) {
            split = realloc(split, sizeof(input[0]) * (splitIdx + 1));
            strncpy(split, input, splitIdx);
        } else {
            split = realloc(split, sizeof(input[0]) * (splitIdx + 1));
            strncpy(split, input + splitIdx, len - splitIdx);
        }
    } else {
        printf("ERROR: %s, %d, %d", input, index, len);
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
float karatsuba(char * x, char * y) {
    
    // get the length of each input str, and convert them to integers
    int lenX = strlen(x);
    int lenY = strlen(y);
    
    int nMax = (lenX > lenY) ? lenX : lenY;

    // base condition: if both arguments are size 1, then simply multiply and return
    if(lenX == 1 && lenY == 1) {
        printf("BASE CONDITION %s %s\n", x, y);
        return atoi(x) * atoi(y);
    }
    
    char * a = malloc(sizeof(a));
    a = splitInput(x, a, 0, lenX);
    char * b = malloc(sizeof(b));
    b = splitInput(x, b, 1, lenX);
    char * c = malloc(sizeof(c));
    c = splitInput(y, c, 0, lenY);
    char * d = malloc(sizeof(d));
    d = splitInput(y, d, 1, lenY);
    
    printf("a: %s, b: %s, c: %s, d: %s\n", a, b, c, d);
    
    // subproblem one and two
    long resultA = karatsuba(a, c);
    long resultB = karatsuba(b, d);

    // prepare for the third subproblem - add, cast to str, and recursive call
    long z1 = atoi(a) + atoi(b);
    long z2 = atoi(c) + atoi(d);

    char * z1Str = malloc(sizeof(z1Str) * nMax);
    char * z2Str = malloc(sizeof(z2Str) * nMax);

    sprintf(z1Str, "%ld", z1);
    sprintf(z2Str, "%ld", z2);

    // printf("z1: %s, z2: %s \n", z1Str, z2Str);
    long resultC = karatsuba(z1Str, z2Str) - resultA - resultB;
    
    // printf("ra: %d, rb: %d, rc: %d \n", resultA, resultB, resultC);

    // free up now unused memory
    free(a);
    free(b);
    free(c);
    free(d);
    free(z1Str);
    free(z2Str);

    // get the products of 10**n/2 and 10**n
    float nMaxHalf = (float)nMax / (float)2;
    long nPowHalf = pow(10, nMaxHalf);
    long nPow = pow(10, nMax);
    printf("nMax: %d, nMaxHalf: %f, nPowHalf: %ld, nPow: %ld\n", nMax, nMaxHalf, nPowHalf, nPow);
    
    // return using Karatsuba's insight - this allows us to use 3 subproblems instead of 4
    return (resultA * nPow) + (resultC * nPowHalf) + resultB;
}
