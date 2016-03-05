#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "net.h"
using namespace std;

//class Net{

    /*public:
    float *** wt, *** del_w;
    int lay_count, * node_count, * lay_type;
    float ** fan_in, ** del_in;
    float ** fan_f, ** del_f;
    float lrate;
    int in_len, out_len;
    int init_type;
    
    public:
    */
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
        srand(time(NULL));
    }

    void Net::add_layer(int len, int bias_mode, int type){
        if(bias_mode == BIAS_ON){
            //TODO: Add a node with value always 1
        }
        node_count[lay_count] = len;
        lay_type[lay_count] = type;
        out_len = len;
        if(lay_count == 0){
            lay_count++;
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

    /*void print(float ** arr, int r, int c){
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++)
                cout<<arr[i][j]<<" ";
                cout<<endl;
        }
    }*/

    float * Net::mul(float ** w, int T, int r, int c, float * vec){
        float * res = new float[r];
        for(int i = 0; i < r; i++){
            res[i] = 0;
            for(int j = 0; j < c; j++){
                if(T == FEED)
                    res[i] += w[i][j]*vec[j];
                else if(T == REV)
                    res[i] += w[j][i]*vec[j];
            }
        }
        return res;
    }

    float * Net::feed(float * input){
        for(int i = 0; i < lay_count-1; i++){
            if(i == 0){
                //TODO: Deep copy here?
                fan_in[i] = input;
                fan_f[i] = input;
            }
            fan_in[i+1] = mul(wt[i],FEED,node_count[i+1],node_count[i],fan_f[i]);
            fan_f[i+1] = new float[node_count[i+1]];
            for(int j = 0; j < node_count[i+1]; j++){
                fan_f[i+1][j] = activation(fan_in[i+1][j],lay_type[i+1]);
            }
        }
        return fan_f[lay_count-1];
    }

    //Add one input for training
    void Net::add_train(float * input, float * target){
        float * res = feed(input);
        for(int i = lay_count-1; i >= 0; i--){
            if(i == lay_count-1){
                del_in[i] = new float[out_len];
                for(int j = 0; j < out_len; j++)
                    del_in[i][j] = (res[j]-target[j])*activation(fan_in[i][j],lay_type[i]+DER);
                continue;
            }
            del_in[i] = mul(wt[i],REV,node_count[i],node_count[i+1],del_in[i+1]);
            for(int j = 0; j < node_count[i+1]; j++){
                for(int k = 0; k < node_count[i]; k++)
                    del_w[i][j][k] += lrate*del_in[i][k];//TODO;
            }
        }
    }

    int Net::get_in_len(){
        return in_len;
    }

    int Net::get_out_len(){
        return out_len;
    }

    void set_init(int type){
        init_type = type;
    }

    void set_learn_rate(float rate){
        lrate = rate;
    }
};

/*int main(){
    Net net;
    net.add_layer(2,BIAS_OFF,SIGM);
    net.add_layer(3,BIAS_OFF,SIGM);
    //net.add_layer(10,BIAS_OFF,SIGM);
    //net.add_layer(10,BIAS_OFF,SIGM);
    net.add_layer(1,BIAS_OFF,SIGM);

    float ** ds = new float*[2];
    ds[0] = new float[3];
    ds[1] = new float[3];
    ds[0][0] = 0; ds[0][1] = 0; ds[0][2] = 0;
    ds[1][0] = 1; ds[1][1] = 1; ds[1][2] = 1;

    float * inp = new float[net.get_in_len()];
    inp[0] = 1; inp[1] = 1;
    float * r = net.feed(inp);
    
    for(int i = 0; i < net.get_out_len(); i++)
        cout<<r[i]<<" ";
    cout<<endl;

    net.train(ds,2,1,0.5);
    net.print();
}*/
