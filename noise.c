
#include <math.h>
#include <stdlib.h>
#include "noise.h"
#define M_PI 3.14159265358979323846


double rand_double() {
    return (double)rand() / RAND_MAX;
}

void generate_noise(double *noise_signal, int nsamples) {
    for (int i = 0; i < nsamples; i++) {
        noise_signal[i] = 10*cos(i);
        //printf("%f\n", noise_signal[i]);
    }
}




