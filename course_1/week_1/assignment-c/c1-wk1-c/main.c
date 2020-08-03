/* 
 * @title: Karatsuba Multiplication in C
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
 *      This code may be augmented to use argv as a source of input strings
 *      
 *      The intent of this code is to multiply two strings whose input length
 *      n is the same. Program behavior when input lengths differ is 
 *      undefined.
 * 
 *      Please also note that this assignment depends on the use of the 
 *      GNU BigNum library to compute large integer values that exceed
 *      the maximums of built-ins.
 * 
 *      Tested on Ubuntu 20.04, GCC 9.3.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "multiply.h"
/*
 * main
 * ======================================================================
 * Using karatsuba multiplication, print the product of x and y
 * 
 */
int main() {

    char * x = "3141592653589793238462643383279502884197169399375105820974944592";
    char * y = "2718281828459045235360287471352662497757247093699959574966967627";
    
    printf("\nX = %s, Y = %s\n", x, y);
    
    // initialize and get the result
    mpz_t result;
    mpz_init(result);
    karatsuba(x, y, result);
    
    char * resultStr = mpz_get_str(NULL, 0, result);
    printf(
        "\nResult of %s * %s using karatsuba multiplication is %s\n", 
        x, 
        y, 
        resultStr
    );
    
    return (EXIT_SUCCESS);
}
