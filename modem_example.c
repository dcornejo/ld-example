
/*
 * @file
 *
 * A simple example of a modulate, up-sampling, demodulation, and down-sampling
 * process using liquid-dsp
 */

#include <stdio.h>
#include <liquid/liquid.h>

#define NUM_SYMBOLS 8

/**
 * @brief Process the input data by modulating and demodulating.
 *
 * This function takes an input array and processes it by modulating and demodulating
 * the data using the given modemcf objects. The modulated and demodulated data is
 * stored in separate arrays.
 *
 * @param mod The modemcf object used for modulation.
 * @param demod The modemcf object used for demodulation.
 * @param input The input data array to be processed.
 * @param modulated The array to store the modulated data.
 * @param output The array to store the demodulated data.
 * @param len The length of the input data array.
 */
void process(modemcf mod, modemcf demod, uint32_t input[], liquid_float_complex  modulated[], uint32_t output[], size_t len) {
    for (size_t i = 0; i < len; i++) {
        modemcf_modulate(mod, input[i], &modulated[i]);
        modemcf_demodulate(demod, modulated[i], &output[i]);
    }
}

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
void printIntegerArray(uint32_t input[], size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%s%d", (i > 0) ? ", " : "", input[i]);
    }
    printf("\n");
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
void printComplexArray(liquid_float_complex modulated[], size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%s%f%+fi", (i > 0) ? ", " : "", creal(modulated[i]), cimagf(modulated[i]));
    }
    printf("\n");
}

int main() {
    modulation_scheme ms = LIQUID_MODEM_DPSK2;

    modemcf mod = modemcf_create(ms);
    modemcf demod = modemcf_create(ms);

    modemcf_print(mod);
    printf("\n");

    uint32_t input[NUM_SYMBOLS] = {0, 1, 1, 0, 1, 0};
    liquid_float_complex modulated[NUM_SYMBOLS];
    uint32_t output[NUM_SYMBOLS];

    process(mod, demod, input, modulated, output, NUM_SYMBOLS);

    printIntegerArray(input, NUM_SYMBOLS);
    printComplexArray(modulated, NUM_SYMBOLS);
    printIntegerArray(output, NUM_SYMBOLS);

    modemcf_destroy(mod);
    modemcf_destroy(demod);

    // resample here

    return 0;
}
