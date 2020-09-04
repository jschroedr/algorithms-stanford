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

/*
 * 
 */
int main(int argc, char** argv) {
    
    int * arr = malloc(sizeof(arr) * 8);
    
    arr[0] = 3;
    arr[1] = 8;
    arr[2] = 2;
    arr[3] = 5;
    arr[4] = 1;
    arr[5] = 4;
    arr[6] = 7;
    arr[7] = 6;
    
    // swap(arr, 0, 1);
    partition(arr, 0, 7);
    
    for(int i = 0; i < 8; i ++) {
        printf("%d", arr[i]);
    }
    
    return (EXIT_SUCCESS);
}

