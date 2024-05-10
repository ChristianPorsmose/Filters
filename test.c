//formula 9.18
    for(int i = 1; i < IIR_POLES; i++) {
        fil->buf[fil->bufIndex] += -1*fil->a[i] * fil->buf[shift1] + inp;
        
        if (shift1 > 0) {
            shift1--;
        }
        else {
            shift1 = IIR_POLES - 1;
        }
    }

    int shift2 = fil->bufIndex;
    double out = 0;
    
    //formula 9.20
    for(int i = 0; i < IIR_ZEROES; i++) {
        out += fil->b[i]*fil->buf[shift2];
        //printf("out: %f", out);
        if (shift2 > 0) {
            shift2--;
        }
        else {
            shift2 = IIR_ZEROES - 1;
        }
    }
    
    //update buffer
    fil->bufIndex++;
    if (fil->bufIndex == IIR_POLES) {
        fil->bufIndex = 0;
    }
