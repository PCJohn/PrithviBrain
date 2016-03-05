#include <iostream>
#include <fstream>
#include "net.h"
using namespace std;

//Save net to file
void save(Net net, char * path){
    ofstream out(path);
    //Save topology
    out<<net.lay_count<<endl;
    for(int i = 0; i < net.lay_count; i++)
        out<<net.node_count[i]<<" ";
    out<<endl;
    //Save layer types
    for(int i = 0; i < net.lay_count; i++)
        out<<net.lay_type[i]<<" ";
    out<<endl;
    //Save fan in values
    for(int i = 0; i < net.lay_count; i++)
        for(int j = 0; j < net.node_count[i]; j++)
            out<<net.fan_in[i][j]<<" ";
    out<<endl;
    //Save fan in activations
    for(int i = 0; i < net.lay_count; i++)
        for(int j = 0; j < net.node_count[i]; j++)
            out<<net.fan_f[i][j]<<" ";
    out<<endl;
    //Save weights
    for(int i = 0; i < net.lay_count-1; i++)
        for(int j = 0; j < net.node_count[i+1]; j++)
            for(int k = 0; k < net.node_count[i]; k++)
                out<<net.wt[i][j][k]<<" ";
    out<<endl;
}

//Load net from file
void load(Net * net, char * path){
    ifstream in(path);
    in>>net->lay_count;
    //Load topology
    net->node_count = new int[net->lay_count];
    for(int i = 0; i < net->lay_count; i++)
        in>>net->node_count[i];
    net->in_len = net->node_count[0];
    net->out_len = net->node_count[net->lay_count-1];
    //Load layer types
    net->lay_type = new int[net->lay_count];
    for(int i = 0; i < net->lay_count; i++)
        in>>net->lay_type[i];
    //Load fan in values
    net->fan_in = new float *[net->lay_count];
    for(int i = 0; i < net->lay_count; i++){
        net->fan_in[i] = new float[net->node_count[i]];
        for(int j = 0; j < net->node_count[i]; j++)
            in>>net->fan_in[i][j];
    }
    //Load fan in activations
    net->fan_f = new float *[net->lay_count];
    for(int i = 0; i < net->lay_count; i++){
        net->fan_f[i] = new float[net->node_count[i]];
        for(int j = 0; j < net->node_count[i]; j++)
            in>>net->fan_f[i][j];
    }
    //Load weights
    net->wt = new float**[net->lay_count];
    for(int i = 0; i < net->lay_count-1; i++){
        net->wt[i] = new float*[net->node_count[i+1]];
        for(int j = 0; j < net->node_count[i+1]; j++){
            net->wt[i][j] = new float[net->node_count[i]];
            for(int k = 0; k < net->node_count[i]; k++)
                in>>net->wt[i][j][k];
        }
    }
}

//Prints the matrices of the current network
void print(Net net){
    cout<<"____________Values in current network____________"<<endl; 
    for(int n = 0; n < net.lay_count-1; n++){
        cout<<endl<<"Layer "<<(n+1)<<" -- "<<(n+2)<<endl;
        for(int i = 0; i < net.node_count[n+1]; i++){
            for(int j = 0; j < net.node_count[n]; j++)
                cout<<net.wt[n][i][j]<<" ";
            cout<<endl;
        }
    }
    cout<<"____________Fan ins in current network____________"<<endl;
    for(int i = 0; i < net.lay_count; i++){
        cout<<"Layer "<<(i+1)<<": ";
        for(int j = 0; j < net.node_count[i]; j++)
            cout<<net.fan_in[i][j]<<" ";
        cout<<endl;
    }
    cout<<"____________Fan in activations in current network____________"<<endl;
    for(int i = 0; i < net.lay_count; i++){
        cout<<"Layer "<<(i+1)<<": ";
        for(int j = 0; j < net.node_count[i]; j++)
            cout<<net.fan_f[i][j]<<" ";
        cout<<endl;
    }
    cout<<"____________Backprop delta in network____________"<<endl;
    for(int i = 0; i < net.lay_count; i++){
        cout<<"Layer "<<(i+1)<<": ";
        for(int j = 0; j < net.node_count[i]; j++)
            cout<<net.del_in[i][j]<<" ";
        cout<<endl;
    }
    cout<<"____________Weight updates____________"<<endl;
    for(int i = 0; i < net.lay_count-1; i++){
        cout<<"Layer "<<(i+1)<<": "<<endl;
        for(int j = 0; j < net.node_count[i+1]; j++){
            for(int k = 0; k < net.node_count[i]; k++)
                cout<<net.del_w[i][j][k]<<" ";
            cout<<endl;
        }
    }
    cout<<"__________________________________________________"<<endl;
}
