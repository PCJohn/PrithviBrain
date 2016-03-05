#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;

void train(Net net, char * path, char * dest, int batch_size, float learn_rate, int save_part, int verbose){
    ifstream in(path);
    ofstream out(dest);
    char * line = new char[10000];
    float * inp = new float[100000];
    int in_len, out_len, pos = 0, len, i = 0;

    //Read dimensions
    in>>line;
    in_len = atoi(line);
    in>>line;
    out_len = atoi(line);
    len = in_len+out_len;
    cout<<in_len<<" -- "<<out_len<<endl;

    //net.lrate = learn_rate;
    while(in>>line){
        int epoch = 0;
        *inp++ = atof(line);
        pos++;
        if(pos < len)
            continue;
        pos = 0;
        inp -= len;
        //Run backprop
        net.add_train(inp,target);
        //Batch weight update
        i = (i+1)%batch_size;
        if(i == 0){
            for(int n = 0; n < net.lay_count-1; n++)
                for(int j = 0; j < net.node_count[n+1]; j++)
                    for(int k = 0; k < net.node_count[n]; k++){
                        net.wt[n][j][k] += del_w[n][j][k];
                        net.del_w[n][j][k] = 0;
                    }
            epoch++;
            if(verbose){
                cout<<"____________Epoch "<<epoch<<"_____________"<<endl;
                cout<<"Total error: "<<net.total_error()<<endl;
                cout<<"__________________________________________"<<endl;
            }
            if(epoch%save_part == 0){
                save(net,dest+"e"+epoch);
            }
        }
    }
}
