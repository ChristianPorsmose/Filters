#ifndef FIR_FILTER_H
#define FIR_FILTER_H

#include <stdint.h>

#define FIR_FILTER_LENGTH 16

typedef struct {
    double buf[FIR_FILTER_LENGTH];
    int bufIndex;
} FIRFilter;

void FIRFilter_Init(FIRFilter *fil);
double FIRFILTER_Update(FIRFilter *fil, double input, double *iresp); 





#endif