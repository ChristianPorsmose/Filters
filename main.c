#include "fir_filter.h"
#include "noise.h"
#include <stdio.h>


int main() {
    int num_samples = SAMPLE_RATE * DURATION;
    double *noise_signal = (double *)malloc(num_samples * sizeof(double));
    double iresp[] = {
  -0.003471276445115, -0.00485120373109,-0.004245630750047, 0.008891029945241,
    0.04423731627554,   0.1002331073527,   0.1601002781948,   0.1991063791579,
     0.1991063791579,   0.1601002781948,   0.1002331073527,  0.04423731627554,
   0.008891029945241,-0.004245630750047, -0.00485120373109,-0.003471276445115
}; //lowpass filter


    //highpass filter
    double iresp2[] = {
  -2.118751962554e-17,-0.002826276798961,   0.0118315825606, -0.03170921997543,
     0.0630166048201,  -0.1005891991146,   0.1347915451181,  -0.1552355716123,
     0.1552355716123,  -0.1347915451181,   0.1005891991146,  -0.0630166048201,
    0.03170921997543,  -0.0118315825606, 0.002826276798961,2.118751962554e-17
    };



    if (noise_signal == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    FIRFilter *fil = (FIRFilter *)malloc(sizeof(FIRFilter));
    if (fil == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    FIRFilter_Init(fil);

    generate_noise(noise_signal, num_samples);

    //create output signal
    double *output_signal = (double *)malloc(num_samples * sizeof(double));
    if (output_signal == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Apply the filter to the noise signal
    for (int i = 0; i < num_samples; i++) {
        output_signal[i] = FIRFILTER_Update(fil, noise_signal[i], iresp);
    }

    //write input and output signals to file
    FILE *f = fopen("input_signal1.dat", "w+");
    if (f == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }
    for (int i = 0; i < num_samples; i++) {
        fprintf(f, "%f\n", noise_signal[i]);
    }
    fclose(f);

    f = fopen("output_signal1.dat", "w+");
    if (f == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }
    for (int i = 0; i < num_samples; i++) {
        fprintf(f, "%f\n", output_signal[i]);
    }
    fclose(f);


    free(fil);
    free(output_signal);
    free(noise_signal);
    return 0;
}