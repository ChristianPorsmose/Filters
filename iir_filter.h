#ifndef IIR_FILTER_H
#define IIR_FILTER_H

#define IIR_ZEROES 3
#define IIR_POLES 2

#include <string.h>

typedef struct
{
    double buf[IIR_ZEROES];
    int bufIndex;
    double b[IIR_ZEROES];
    double a[IIR_POLES];
    
}SecondOrderIIR;

typedef struct
{
    double out;
    double a;
}FirstOrderIIR;

void FirstOrderIIR_Init(FirstOrderIIR *fil, double a);
double FirstOrderIIR_Update(FirstOrderIIR *fil, double inp);
void SecondOrderIIR_Init(SecondOrderIIR *fil, double *b, double *a);
double SecondOrderIIR_Update(SecondOrderIIR *fil, double inp);
double NOrderIIR_Update(SecondOrderIIR **fil, double inp, int order); 
void NOrderIIR_Init(SecondOrderIIR **fil, double **b, double **a, int order);

#endif