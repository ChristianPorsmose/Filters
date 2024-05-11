#include "fir_filter.h"
#include "noise.h"
#include <stdio.h>
#include "iir_filter.h"
#include "numerator_coeffs.h"
#include "denominator_coeffs.h"
#define NUM_FILTERS 6


// void HOLD() {
// //     double iresp[] = {
// //   -0.003471276445115, -0.00485120373109,-0.004245630750047, 0.008891029945241,
// //     0.04423731627554,   0.1002331073527,   0.1601002781948,   0.1991063791579,
// //      0.1991063791579,   0.1601002781948,   0.1002331073527,  0.04423731627554,
// //    0.008891029945241,-0.004245630750047, -0.00485120373109,-0.003471276445115
// // }; //lowpass filter


// //     //highpass filter
// //     double iresp2[] = {
// //   -2.118751962554e-17,-0.002826276798961,   0.0118315825606, -0.03170921997543,
// //      0.0630166048201,  -0.1005891991146,   0.1347915451181,  -0.1552355716123,
// //      0.1552355716123,  -0.1347915451181,   0.1005891991146,  -0.0630166048201,
// //     0.03170921997543,  -0.0118315825606, 0.002826276798961,2.118751962554e-17
// //     };

// //     FIRFilter *fil = (FIRFilter *)malloc(sizeof(FIRFilter));
// //         if (fil == NULL) {
// //             fprintf(stderr, "Memory allocation failed\n");
// //             return 1;
// //         }

// //         FIRFilter_Init(fil);
// //     // Apply the filter to the noise signal
// //     // for (int i = 0; i < num_samples; i++) {
// //     //     output_signal[i] = FIRFILTER_Update(fil, noise_signal[i], iresp);
// //     // }

// }



int main() {
    int num_samples = SAMPLE_RATE * DURATION;
    double *noise_signal = (double *)malloc(num_samples * sizeof(double));
    if (noise_signal == NULL) return 1;
    generate_noise(noise_signal, num_samples);

    //create filters array
    SecondOrderIIR **fil = (SecondOrderIIR **)malloc(NUM_FILTERS * sizeof(SecondOrderIIR *));
    if (fil == NULL) {return 1;}

    for (int i = 0; i < NUM_FILTERS; i++) {
        fil[i] = (SecondOrderIIR *)malloc(sizeof(SecondOrderIIR));
        if (fil[i] == NULL) return 1;
        SecondOrderIIR_Init(fil[i], numerator_coeffs[i], denominator_coeffs[i]);
    }

    //create a simple second order IIR filter
    // SecondOrderIIR *fil = (SecondOrderIIR *)malloc(sizeof(SecondOrderIIR));
    // if (fil == NULL) return 1;

    // SecondOrderIIR_Init(fil, numerator_coeffs[0], denominator_coeffs[0]);

     //lowpass filter

 
    //  FIRFilter *fil = (FIRFilter *)malloc(sizeof(FIRFilter));
    //     if (fil == NULL) {  return 1; }
    // FIRFilter_Init(fil);
          
    //create output signal
    double *output_signal = (double *)malloc(num_samples * sizeof(double));
    if (output_signal == NULL) return 1;

//         double iresp[] = {
//   -0.003471276445115, -0.00485120373109,-0.004245630750047, 0.008891029945241,
//     0.04423731627554,   0.1002331073527,   0.1601002781948,   0.1991063791579,
//      0.1991063791579,   0.1601002781948,   0.1002331073527,  0.04423731627554,
//    0.008891029945241,-0.004245630750047, -0.00485120373109,-0.003471276445115
// }; //lowpass filter //lowpass filter
 
// //     //Apply the filter to the noise signal
//     for (int i = 0; i < num_samples; i++) {
//         output_signal[i] = FIRFILTER_Update(fil, noise_signal[i], iresp);
//     }

     //Apply the filter to the noise signal
    for (int i = 0; i < num_samples; i++) {
        output_signal[i] = NOrderIIR_Update(fil, noise_signal[i], NUM_FILTERS);
    }

    // for (int i = 0; i < num_samples; i++) {
    //     output_signal[i] = SecondOrderIIR_Update(fil, noise_signal[i]);
    // }


    //first order IIR filter
    // FirstOrderIIR *fil = (FirstOrderIIR *)malloc(sizeof(FirstOrderIIR));
    // if (fil == NULL) return 1;
    // FirstOrderIIR_Init(fil, 0.3);
    // for (int i = 0; i < num_samples; i++) {
    //     output_signal[i] = FirstOrderIIR_Update(fil, noise_signal[i]);
    // }


    //write input and output signals to file
    FILE *f = fopen("iir_in.dat", "w+");
    if (f == NULL) return 1;
    for (int i = 0; i < num_samples; i++) {
        fprintf(f, "%f\n", noise_signal[i]);
    } fclose(f);

    f = fopen("iir_out.dat", "w+");
    if (f == NULL) return 1;
    for (int i = 0; i < num_samples; i++) {
        fprintf(f, "%f\n", output_signal[i]);
    } fclose(f);


    //free array memory
    for (int i = 0; i < NUM_FILTERS; i++) {
        free(fil[i]);
    }  

    free(fil);
    free(output_signal);
    free(noise_signal);
    return 0;
}