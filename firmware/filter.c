/*
 Zhonghao Shi  UCL   Scenario X
 */

#include "filter.h"

float bandstop_buf[3] = {0,0,0};
float lowpass_a_buf[3] = {0,0,0};
float lowpass_b_buf[3] = {0,0,0};

//////
// Implements Infinite Impulse Response Filter
//////

// Bandstop filter, 2nd order (1 section)
float bandstop(float input){
    
    update_buffer(bandstop_buf);
    float output = filter(input, bandstop_buf, bandstop_den, bandstop_num);
    return output; //* bandstop_g;
}

// Second-order IIR filter, direct form II
float filter(float x, float *w, float *a, float *b){
    w[2] = x - (a[1] * w[1]) - (a[2] * w[0]);
    float y = (b[0] * w[2]) + (b[1] * w[1]) + (b[2] * w[0]);
    return y;
}

void update_buffer(float *REG){
    REG[0] = REG[1];
    REG[1] = REG[2];
}



// Lowpass filter, 4th order (2 sections)
float lowpass(float input){
    
    update_buffer(lowpass_a_buf);
    float outa = filter(input, lowpass_a_buf, lowpass_a_num, lowpass_a_den);
    update_buffer(lowpass_b_buf);
    float output = filter(outa/* * lowpass_a_g*/, lowpass_b_buf, lowpass_b_num, lowpass_b_den);
    
}

