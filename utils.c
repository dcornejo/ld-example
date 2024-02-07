
//#include "utils.h"

#include <stdio.h>
#include <complex.h>
#include <liquid/liquid.h>

/**
 * @brief Prints the elements of an integer array.
 *
 * This function takes an integer array and its length as input parameters,
 * and prints all the elements of the array separated by commas.
 *
 * @param input The integer array to be printed.
 * @param len The length of the input array.
 *
 * @note The input array must be non-null.
 * @note The len parameter must be greater than 0.
 *
 * @return None.
 */
void printIntegerArray (uint32_t input[], size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf ("%s%d", (i > 0) ? ", " : "", input[i]);
    }
    printf ("\n");
}

/**
 * @brief Prints an array of complex numbers.
 *
 * This function prints the real and imaginary parts of each complex number
 * in the given array, separated by a comma and space. The format for each
 * complex number is "(real + imaginary*i)".
 *
 * @param modulated The array of complex numbers to print.
 * @param len The length of the array.
 */
void printComplexArray (liquid_float_complex modulated[], size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf ("%s%f%+fi", (i > 0) ? ", " : "", creal (modulated[i]), cimagf (modulated[i]));
    }
    printf ("\n");
}
