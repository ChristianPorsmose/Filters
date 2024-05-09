
#include <math.h>
#include <stdlib.h>
#include "noise.h"
#define M_PI 3.14159265358979323846


double rand_double() {
    return (double)rand() / RAND_MAX;
}

void generate_noise(double *noise_signal, int nsamples) {
    for (int i = 0; i < nsamples; i++) {
        noise_signal[i] = 0.5 * sin(2 * M_PI * 1000 * i / SAMPLE_RATE) + 0.5 * rand_double();
    }
}




