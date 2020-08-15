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
#include "inversion.h"

/*
 * 
 */
int main() {
    char * input = "8422323423423234323";
    char * dest = malloc(sizeof(input) + 1);
    strncpy(dest, input, strlen(input));
    // TODO: inversions not calculating properly!
    int inv = sortAndCount(dest);
        
    printf("Total Inversions for %s: %d", input, inv);
    return (EXIT_SUCCESS);
}

