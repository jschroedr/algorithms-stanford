/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: jake
 *
 * Created on August 9, 2020, 5:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "inversion.h"


/*
 * 
 */
int main() {
    char * fileName = "data/numbers.txt";
    // char * fileName = "data/numbers_test_10_16.txt";
    
    FILE * fp;
    fp = fopen(fileName, "r");
    if(fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    size_t len = 0;
    size_t lineCount = 1;
    int nread;
    char * line = NULL;
    char ** lineArray = NULL;
    while((nread = getline(&line, &len, fp)) != -1) {
        int lineLen = strlen(line);
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
    fclose(fp);
    
    mpz_t result;
    mpz_init(result);
    
    sortAndCount(lineArray, (int)(lineCount - 1), result);

    /*
    for(int i = 0; i < (lineCount - 1); i ++) {
        printf("%s\n", lineArray[i]);
    }
    */
    
    char * resultStr = mpz_get_str(NULL, 10, result);
    
    printf("\nTotal Inversions is %s", resultStr);
    return (EXIT_SUCCESS);
}

