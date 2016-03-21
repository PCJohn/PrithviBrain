#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "net.h"
using namespace std;

void Net::train(char * path,
                char * dest,
                int minibatch_size,
                float learn_rate,
                bool adaptive_lrate,
                float momentum,
                int save_part,
                bool verbose,
                int max_epochs){
    ifstream in(path);
    ofstream out(dest);
    char * line = new char[10000];
    float * inp = new float[100000];
    float ** buff = new float*[BUFF_LEN];
    int pos = 0, len, i = 0, N = 0, epoch, buff_pos = 0;

    lrate = learn_rate;
    mtm = momentum;
    epoch = 0;
    while(1){
        in.clear();
        in.seekg(0,ios::beg);
        //Read dimensions
        in>>line;
        in_len = atoi(line);
        in>>line;
        out_len = atoi(line);
        len = in_len+out_len;
        line = new char[len+1];
        inp = new float[len+1];

        N = 0;
        prev_error = total_error;
        total_error = 0;
        while(in>>line){
            *inp++ = atof(line);
            pos++;
            if(pos < len)
                continue;
            pos = 0;
            inp -= len;
            N++;
            
            //buff[buff_pos] = inp;
            //buff_pos++;
            
            add_train(inp,inp+in_len);

            i = (i+1)%minibatch_size;
            if(i == 0){
                update_wt(adaptive_lrate);
            }
        }
        epoch++;
        //TODO: Check if prev > curr error here
        if((epoch == max_epochs)){// || ((prev_error - total_error) < ERR_LIM)){
            if(!updated)
                update_wt(adaptive_lrate);
            save(dest);
            total_error /= (2*N);
            cout<<"Total error: "<<total_error<<endl;
            cout<<" _____ "<<(prev_error-total_error)<<endl;
            break;
        }
        //if(epoch%save_part == 0){
        //    save(dest);
        //}
        if(verbose){
            total_error /= (2*N);
            cout<<"Total error (epoch "<<epoch<<"): "<<total_error<<endl;
        }
    }
}
