/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: jake
 *
 * Created on August 27, 2020, 7:55 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"


int main(int argc, char** argv) {
    
    // read in input data file (test case(s) or assignment data)
    char * filename = "data/assn.txt";
    // char * filename = "data/data.txt";
    
    // iterate over each problem type
    for(int p = 1; p <= 3; p ++) {
        
        // for each problem, we open the file anew and read its content
        FILE * fp;
        fp = fopen(filename, "r");
        if(fp == NULL) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }
        
        int nread;
        size_t len = 0;
        size_t lineCount = 1;

        char * line = NULL;
        int * arr = malloc(sizeof(arr));
        int item;
        
        // @internal using getline from C11 (for safety)
        while(nread = getline(&line, &len, fp) != -1) {
            // @internal each member of the file's contents are within
            // the boundaries of what defines an integer - this is safe
            item = atoi(line);
            arr = realloc(arr, sizeof(arr[0]) * (lineCount + 1));
            arr[lineCount - 1] = item;
            lineCount ++;
        }
        
        if(lineCount == 1) {
            break;
        }
        
        // allocate the counter who will keep track of our number of "swaps"
        int * tcmp = malloc(sizeof(int));
        *tcmp = 0;
        
        // @internal since lineCount is iterated once more before termination
        // we need to pass lineCount - 1 as a valid n
        // @internal also note that p is problem type
        quicksort(arr, lineCount - 1, p, tcmp);

        // print the problem type and the comparison count
        printf("\n================================================");
        printf("\nProblem %d", p);
        printf("\ntotal comparisons: %d", *tcmp);
        printf("\n================================================\n");
        
        // free up any allocated resources for this iteration
        free(arr);
        free(tcmp);
        
        // close the file - we will re-open again for the next iteration
        // if needed
        fclose(fp);
        
    }
    
    return (EXIT_SUCCESS);
}

