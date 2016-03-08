#include <math.h>
#include "net.h"
#include <iostream>
using namespace std;

float sigmoid(float x){
    return 1.0/(1.0+exp(-x));
}

float tanh(float x){
    float p = exp(x), n = exp(-x);
    return (p+n)/(p-n);
}

float activation(float x, int type){
    float res;
    switch(type){
        case SIGM: return 1.0/(1.0+exp(-x));
        case TANH: return tanh(x);
        case SMAX: //TODO: Softmax here
                   break;
        case SIGM_DER: res = sigmoid(x);
                       return res*(1-res);
        case TANH_DER: res = tanh(x);
                       return (1-x*x);
    }
}

//--------------------*What follows may be useless*-----------------------------------//
float rms_error(float * output, float * target, int out_len){
        float err = 0, diff;
        for(int i = 0; i < out_len; i++){
            diff = output[i]-target[i];
            err += diff*diff;
        }
        return sqrt(err);
    }

    float sq_error(float * output, float * target, int out_len){
        float err = 0, diff;
        for(int i = 0; i < out_len; i++){
            diff = output[i]-target[i];
            err += diff*diff;
        }
        return 0.5*err;
    }

    float * sub_error(float * output, float * target, int out_len){
        float * err = new float[out_len];
        for(int i = 0; i < out_len; i++){
            err[i] = target[i] - output[i];
        }
        return err;
    }
