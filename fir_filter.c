#include "fir_filter.h"

void FIRFilter_Init(FIRFilter *fil) {

    for(int i=0; i<FIR_FILTER_LENGTH; i++) {
        fil->buf[i] = 0.0;
    }
    fil->bufIndex = 0;
}

double FIRFILTER_Update(FIRFilter *fil, double input, double *iresp) {
    //update buf with newest input
    fil->buf[fil->bufIndex] = input;

    //increment buf + check for bounds
    fil->bufIndex++;
    if (fil->bufIndex == FIR_FILTER_LENGTH) {
        fil->bufIndex = 0;
    }
    int shift = fil->bufIndex;
    double out = 0.0;
    //convolve 
    for (int i=0; i < FIR_FILTER_LENGTH; i++) {
        if (shift > 0) {
            shift--;
        }
        else {
            shift = FIR_FILTER_LENGTH - 1;
        }
        out += iresp[fil->bufIndex] * fil->buf[shift]; 
    }
    return out;
}

