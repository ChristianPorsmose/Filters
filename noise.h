#ifndef NOISE_H
#define NOISE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SAMPLE_RATE 2000  // Sample rate in Hz
#define DURATION 3        // Duration of the signal in seconds

double rand_double();

void generate_noise(double *noise_signal, int nsamples);

#endif

