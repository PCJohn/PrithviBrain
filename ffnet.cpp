#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "net.h"
using namespace std;

Net::Net(){
    wt = new float**[MAX_LAYERS];
    del_w = new float**[MAX_LAYERS];
    lay_count = 0;
    init_type = RAND;
    node_count = new int[MAX_LAYERS];
    lay_type = new int[MAX_LAYERS];
    fan_in = new float*[MAX_LAYERS];
    fan_f = new float*[MAX_LAYERS];
    del_in = new float*[MAX_LAYERS];
    del_f = new float*[MAX_LAYERS];
    in_len = 0; out_len = 0;
    lrate = 0.01;
    total_error = 99999;
    srand(time(NULL));
}

void Net::add_layer(int len, int out_mode, int type){
    if(out_mode == HIDDEN){
        len++;
        out_len = len-1;
    }
    else
        out_len = len;
    node_count[lay_count] = len;
    lay_type[lay_count] = type;
    if(lay_count == 0){
        lay_count++;
        if(out_mode == HIDDEN)
            in_len = len-1;
        else
            in_len = len;
        return;
    }
    int prev_len = node_count[lay_count-1];
    wt[lay_count-1] = new float*[len];
    del_w[lay_count-1] = new float*[len];
    for(int i = 0; i < len; i++){
        wt[lay_count-1][i] = new float[prev_len];
        del_w[lay_count-1][i] = new float[prev_len];
        for(int j = 0; j < prev_len; j++){
            switch(init_type){
                case RAND: wt[lay_count-1][i][j] = (rand()%10000)/10000.0; //Random initialzation
                           break;
                case ONE:  wt[lay_count-1][i][j] = 1;
                           break;
            }
            del_w[lay_count-1][i][j] = 0;
        }
    }
    lay_count++;
}

float * Net::mul(float ** w, int T, int r, int c, float * vec){
    float * res;
    if(T == FEED){
        res = new float[r];
        for(int i = 0; i < r; i++){
            res[i] = 0;
            for(int j = 0; j < c; j++)
                res[i] += w[i][j]*vec[j];
        }
    }
    return res;
}

float * Net::feed(float * input){
    for(int i = 0; i < lay_count-1; i++){
        if(i == 0){
            fan_in[i] = new float[node_count[i]-1];
            fan_f[i] = new float[node_count[i]];
            for(int j = 0; j < in_len; j++){
                fan_in[i][j] = input[j];
                fan_f[i][j] = input[j];
            }
            fan_f[i][node_count[i]-1] = 1;
        }
        fan_in[i+1] = mul(wt[i],FEED,node_count[i+1],node_count[i]-1,fan_f[i]);
        fan_f[i+1] = new float[node_count[i+1]];
        int l = node_count[i+1]-1;
        if(i+1 == lay_count-1)
            l = node_count[i+1];
        for(int j = 0; j < l; j++){
            fan_f[i+1][j] = activation(fan_in[i+1][j],lay_type[i+1]);
        }
        if(i+1 < lay_count-1)
            fan_f[i+1][node_count[i+1]-1] = 1;
    }
    
    return fan_f[lay_count-1];
}

//Add one input for training
void Net::add_train(float * input, float * target){
    float * res = feed(input);
    //cout<<*input<<" -- "<<*res<<" -- "<<*target<<" -- "<<(target[0]-res[0])*(target[0]-res[0])<<endl;
    for(int i = lay_count-1; i >= 0; i--){
        del_in[i] = new float[node_count[i]];
        if(i == lay_count-1){
            for(int j = 0; j < out_len; j++){
                float diff = (target[j]-res[j]);
                //cout<<target[j]<<" - "<<res[j]<<endl;
                del_in[i][j] = diff*activation(fan_in[i][j],lay_type[i]+DER);
                //cout<<diff<<" -- "<<fan_in[i][j]<<" == "<<activation(fan_in[i][j],lay_type[i]+DER)<<endl;
                total_error += diff*diff;
            }
            continue;
        }
        //Calculate del_j
        for(int j = 0; j < node_count[i]; j++){
            del_in[i][j] = 0;
            for(int k = 0; k < node_count[i+1]; k++)
                del_in[i][j] += del_in[i+1][k]*wt[i][k][j];
            del_in[i][j] *= activation(fan_in[i][j],lay_type[i]+DER);
            //cout<<"????"<<fan_in[i][j]<<" == "<<activation(fan_in[i][j],lay_type[i]+DER)<<endl;
        }
        for(int j = 0; j < node_count[i]; j++){
            for(int k = 0; k < node_count[i+1]; k++){
                del_w[i][k][j] += lrate*del_in[i+1][k]*fan_f[i][j];
                //cout<<del_w[i][k][j]<<" = "<<lrate<<" "<<del_in[i+1][k]<<" "<<fan_f[i][j]<<endl;
            }
        }
    }
}

//Update weights
void Net::update_wt(){
    for(int i = 0; i < lay_count-1; i++)
        for(int j = 0; j < node_count[i+1]; j++)
            for(int k = 0; k < node_count[i]; k++){
                wt[i][j][k] += del_w[i][j][k];
                del_w[i][j][k] = 0;
            }
}
