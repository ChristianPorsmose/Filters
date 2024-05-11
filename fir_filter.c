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
    fil->bufIndex = (fil->bufIndex == 0) ? fil->bufIndex=FIR_FILTER_LENGTH-1 : fil->bufIndex-1;

    double out = 0.0;
    //convolve 
    for (int i=0; i < FIR_FILTER_LENGTH; i++) {
        out += iresp[i] * fil->buf[(fil->bufIndex+1)%FIR_FILTER_LENGTH]; 
    }
    return out;
}

