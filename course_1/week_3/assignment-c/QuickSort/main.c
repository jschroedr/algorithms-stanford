/* 
 * @title: QuickSort Algorithm in C
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
 *      Tested on Ubuntu 20.04, GCC 9.3.0
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

