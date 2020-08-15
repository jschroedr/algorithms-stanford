/* 
 * @title: Array Inversion Computation in C
 * @author: Jake Schroeder 
 * @license:      
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 * 
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 * 
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * @internal:
 *      
 *      The intent of this code is to find the number of index inversions
 *      in a a file of one-integer-per-line values named "numbers.txt"
 *      stored in a relative directory "data"
 * 
 *      Please also note that this assignment depends on the use of the 
 *      GNU BigNum library to compute large integer values that exceed
 *      the maximums of built-ins.
 * 
 *      Tested on Ubuntu 20.04, GCC 9.3.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "inversion.h"


int main() {
    
    // set the file name for the input data
    // @internal: decide to read in the production or test file here
    char * fileName = "data/numbers.txt";
    // char * fileName = "data/numbers_test_10_16.txt";
    
    // set the file pointer and attempt to read
    // let the error propagate if we cannot access the file for any reason
    FILE * fp;
    fp = fopen(fileName, "r");
    if(fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    // read each line in the input file and store in lineArray
    // keeping track of lineCount along the way
    size_t len = 0;
    size_t lineCount = 1;
    int nread;
    char * line = NULL;
    char ** lineArray = NULL;
    while((nread = getline(&line, &len, fp)) != -1) {
        int lineLen = strlen(line);
        // here we check if atoi() failes
        // @internal it is assumed that all values in numbers.txt are non-zero
        if (atoi(line) == 0) {
            break;
        }
        lineArray = realloc(lineArray, (lineCount * sizeof(lineArray)));
        lineArray[lineCount - 1] = malloc((lineLen + 1) * sizeof(lineArray[lineCount - 1]));
        strncpy(lineArray[lineCount - 1], line, lineLen);
        if(lineArray[lineCount - 1][lineLen - 1] == '\n') {
            lineArray[lineCount - 1][lineLen - 1] = '\0';
        } else {
            lineArray[lineCount -1] = lineArray[lineCount - 1] + '\0';
        }
        lineCount ++;
    }
    // close the file
    fclose(fp);
    
    // initialize where the total number of inversions will be stored
    mpz_t result;
    mpz_init(result);
    
    // call sortAndCount and compute inversions
    // @internal note we use lineCount -1 because the last line is typically 
    //      an empty string
    sortAndCount(lineArray, (int)(lineCount - 1), result);
    
    // convert the bignum result to a string for display in stdout
    char * resultStr = mpz_get_str(NULL, 10, result);
    printf("\nTotal Inversions is %s", resultStr);
    return (EXIT_SUCCESS);
}

