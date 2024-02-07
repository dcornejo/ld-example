
/*
 * @file
 *
 * A simple example of modulation, up-sampling, demodulation, and down-sampling
 * process using liquid-dsp.
 */

#include <stdio.h>
#include <math.h>
//#include <complex.h>
#include <liquid/liquid.h>

#include "utils.h"

#define NUM_SYMBOLS 8

/**
 * Modulates input data using a given modem configuration.
 *
 * @param mod The modem configuration used for modulation.
 * @param input The input data to be modulated.
 * @param modulated The modulated output data.
 * @param len The length of the input data and modulated output data arrays.
 */
void modulate (modemcf mod, uint32_t input[], liquid_float_complex modulated[], size_t len) {
    for (size_t i = 0; i < len; i++) {
        modemcf_modulate (mod, input[i], &modulated[i]);
    }
}

/**
* @brief Demodulates a sequence of complex-modulated symbols using a given modem configuration.
*
* This function takes a modem configuration `demod` and applies it to each complex-modulated symbol in the
* `modulated` array. The result of each demodulation is stored in the corresponding position in the `output` array.
*
* @param demod The modem configuration to use for demodulation.
* @param modulated The array of complex-modulated symbols to demodulate.
* @param output The array where the demodulated symbols will be stored.
* @param len The length of the input arrays `modulated` and `output`.
*
* @note The `modulated` and `output` arrays must be of the same length.
*
* @see modemcf_demodulate
*/
void demodulate (liquid_float_complex modulated[], uint32_t output[], size_t len) {

    modulation_scheme ms = LIQUID_MODEM_DPSK2;
    modemcf demod = modemcf_create (ms);

    for (size_t i = 0; i < len; i++) {
        modemcf_demodulate (demod, modulated[i], &output[i]);
    }

    modemcf_destroy (demod);
}


/**
 * @brief Process the input data by modulating and demodulating using the given modulator and demodulator objects
 *
 * This function takes in an array of input data and performs modulation and demodulation on it using the provided
 * modulator and demodulator objects. The modulator modulates the input data and stores the modulated data into the
 * modulated array. The demodulator then demodulates the modulated data and stores the output into the output array.
 *
 * @param mod The modulator object to perform modulation
 * @param demod The demodulator object to perform demodulation
 * @param input An array of input data to be processed
 * @param modulated An array to store the modulated data
 * @param output An array to store the demodulated data
 * @param len The length of the input, modulated, and output arrays
 */
void process (modemcf mod, uint32_t input[], liquid_float_complex modulated[], uint32_t output[],
              size_t len) {
    modulate (mod, input, modulated, len);
    demodulate (modulated, output, len);
}


int main () {
    modulation_scheme ms = LIQUID_MODEM_DPSK2;

    modemcf mod = modemcf_create (ms);

    modemcf_print (mod);
    printf ("\n");

    uint32_t input[NUM_SYMBOLS] = {0, 1, 1, 0, 1, 0};
    liquid_float_complex modulated[NUM_SYMBOLS];
    uint32_t output[NUM_SYMBOLS];

    process (mod, input, modulated, output, NUM_SYMBOLS);

    printIntegerArray (input, NUM_SYMBOLS);
    printComplexArray (modulated, NUM_SYMBOLS);
    printIntegerArray (output, NUM_SYMBOLS);

    modemcf_destroy (mod);

    // resample experiments below
    //   resample baseband to 20Msps

    // filter semi-length (filter delay)
    unsigned int h_len = 13;
    // resampling rate (output/input)
    float r = 4.0f;
    // resampling filter bandwidth
    float bw = 0.4f;
    // resampling filter sidelobe suppression level
    float slsl = 20.0f;
    // number of filters in bank (timing resolution)
    unsigned int npfb = 32;

    unsigned int y_len = (unsigned int) ceilf (1.1f * NUM_SYMBOLS * r) + 4;
    liquid_float_complex resampled[y_len];
    unsigned int ny = 0;

    // create up-sampled signal
    resamp_crcf q = resamp_crcf_create (r, h_len, bw, slsl, npfb);
    printf("\n");
    resamp_crcf_print (q);
    printf("\n");

    resamp_crcf_execute_block (q, modulated, NUM_SYMBOLS, resampled, &ny);
    printComplexArray (resampled, ny);

    resamp_crcf_destroy (q);

    // demodulate it
    uint32_t X[ny];

    demodulate (resampled, X, ny);

    printIntegerArray (X, ny);


    return 0;
}
