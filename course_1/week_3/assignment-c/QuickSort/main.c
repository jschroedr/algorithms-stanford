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
    
    int * arr = malloc(sizeof(arr) * 3);
    
    arr[0] = 3;
    arr[1] = 1;
    arr[2] = 7;
    
    // swap(arr, 0, 1);
    partition(arr, 0, 2);
    
    printf("%d", arr[0]);
    printf("%d", arr[1]);
    printf("%d", arr[2]);
    
    
    return (EXIT_SUCCESS);
}

