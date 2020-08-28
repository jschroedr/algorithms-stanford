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
    
    int arr[5] = {1, 9, 2, 5, 0};
    
    partition(arr, 0, 5);
    
    for(int i = 0; i < 5; i ++) {
        printf("%d ", arr[i]);
    }
    
    return (EXIT_SUCCESS);
}

