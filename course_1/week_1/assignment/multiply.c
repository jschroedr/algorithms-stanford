#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


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
    int lenx = strlen(x);
    int leny = strlen(y);
    
    int xInt = atoi(x);
    int yInt = atoi(y);

    // base condition: if both arguments are size 1, then simply multiply and return
    if(lenx <= 1 && leny <= 1) {
        if(lenx == 0) {
            return yInt;
        } else if (leny == 0) {
            return xInt;
        } else {
            return xInt * yInt;
        }
    }
    printf("RECURSION\n");
    // recursive condition
    // determine max input length between x and y
    int nMax = (lenx >= leny) ? lenx : leny;

    // determine if each input lengths are even
    int xEven = lenx % 2 == 0;   
    int yEven = leny % 2 == 0;
    
    // get the floor midpoint based on integer division
    int xIdx = lenx / 2;
    int yIdx = leny / 2;

    printf("lenx: %d, xIdx: %d, leny: %d, yIdx: %d\n", lenx, xIdx, leny, yIdx);

    // split each input string in half
    char * x1 = malloc(sizeof(x1) * nMax);
    char * x2 = malloc(sizeof(x2) * nMax);
    char * y1 = malloc(sizeof(y1) * nMax);
    char * y2 = malloc(sizeof(y2) * nMax);
    
    // first halves are always to the floor idx
    x1 = strncpy(x1, x, xIdx);
    y1 = strncpy(y1, y, yIdx);
    
    // second halves depend on whether the input lengths are even or not
    if(xEven == 1) {
        x2 = strncpy(x2, &x[xIdx], xIdx);
    } else {
        x2 = strncpy(x2, &x[xIdx], xIdx + 1);
    }
    if(yEven == 1) {
        y2 = strncpy(y2, &y[yIdx], yIdx);
    } else {
        y2 = strncpy(y2, &y[yIdx], yIdx + 1);
    }
    printf("x: %s, y: %s, x1: %s, x2: %s, y1: %s, y2: %s\n", x, y, x1, x2, y1, y2);

    // subproblem one and two
    int resultA = karatsuba(x1, y1);
    int resultB = karatsuba(x2, y2);
    
    // prepare for the third subproblem - add, cast to str, and recursive call
    int z1 = atoi(x1) + atoi(x2);
    int z2 = atoi(y1) + atoi(y2);

    char * z1Str = malloc(sizeof(z1Str) * nMax);
    char * z2Str = malloc(sizeof(z2Str) * nMax);

    sprintf(z1Str, "%d", z1);
    sprintf(z2Str, "%d", z2);

    int resultC = karatsuba(z1Str, z2Str) - resultA - resultB;

    // free up now unused memory
    free(x1);
    free(x2);
    free(y1);
    free(y2);
    free(z1Str);
    free(z2Str);

    // get the products of 10**n/2 and 10**n
    int nPowHalf = pow(10, nMax / 2);
    int nPow = pow(10, nMax);

    // return using Karatsuba's insight - this allows us to use 3 subproblems instead of 4
    return (resultA * nPow) + (resultC * nPowHalf) + resultB;
}
