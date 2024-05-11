
#include "iir_filter.h"
#include <stdio.h>

void SecondOrderIIR_Init(SecondOrderIIR *fil, double *b, double *a) {
    memcpy(fil->a, a, IIR_POLES * sizeof(double));
    memcpy(fil->b , b, IIR_ZEROES * sizeof(double));
    fil->bufIndex = 0;
    for(int i=0;i < IIR_ZEROES; i++) {
        fil->buf[i] = 0.0;
    }
}

double SecondOrderIIR_Update(SecondOrderIIR *fil, double inp) {
    //formula 9.18
    fil->buf[fil->bufIndex] = (-fil->a[0]*fil->buf[fil->bufIndex] - fil->a[1]*fil->buf[(fil->bufIndex+1)%IIR_ZEROES]) - inp; 
    //formula 9.20
    double out = fil->buf[fil->bufIndex]*fil->b[0] + fil->buf[(fil->bufIndex+1)%IIR_ZEROES]*fil->b[1] + fil->buf[(fil->bufIndex+2)%IIR_ZEROES]*fil->b[2];
    //update buf + check for bounds
    fil->bufIndex = (fil->bufIndex < 0) ? fil->bufIndex=IIR_ZEROES-1 : fil->bufIndex-1;
    return out;
}

void NOrderIIR_Init(SecondOrderIIR **fil, double **b, double **a, int order) {
    for(int i = 0; i < order; i++) {
        SecondOrderIIR_Init(fil[i], b[i], a[i]);
    }
}


double NOrderIIR_Update(SecondOrderIIR **fil, double inp, int order) {
    double out = 0;
    for(int i = 0; i < order; i++) {
        out += SecondOrderIIR_Update(fil[i], inp);
    }
    return out;
}