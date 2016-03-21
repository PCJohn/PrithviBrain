#include <iostream>
#include <fstream>
#include "net.h"
using namespace std;

//Save net to file
void Net::save(char * path){
    ofstream out(path);
    //Save topology
    out<<lay_count<<endl;
    for(int i = 0; i < lay_count; i++)
        out<<node_count[i]<<" ";
    out<<endl;
    //Save layer types
    for(int i = 0; i < lay_count; i++)
        out<<lay_type[i]<<" ";
    out<<endl;
    //Save weights
    for(int i = 0; i < lay_count-1; i++)
        for(int j = 0; j < node_count[i+1]; j++)
            for(int k = 0; k < node_count[i]; k++)
                out<<wt[i][j][k]<<" ";
    out<<endl;
}

//Load net from file
void Net::load(char * path){
    ifstream in(path);
    in>>lay_count;
    //Load topology
    node_count = new int[lay_count];
    for(int i = 0; i < lay_count; i++)
        in>>node_count[i];
    in_len = node_count[0];
    out_len = node_count[lay_count-1];
    //Load layer types
    lay_type = new int[lay_count];
    for(int i = 0; i < lay_count; i++)
        in>>lay_type[i];
    //Load weights
    wt = new float**[lay_count];
    for(int i = 0; i < lay_count-1; i++){
        wt[i] = new float*[node_count[i+1]];
        for(int j = 0; j < node_count[i+1]; j++){
            wt[i][j] = new float[node_count[i]];
            for(int k = 0; k < node_count[i]; k++)
                in>>wt[i][j][k];
        }
    }
}

//Prints the matrices of the current network
void Net::print(){
    cout<<"____________Values in current network____________"<<endl; 
    for(int n = 0; n < lay_count-1; n++){
        cout<<endl<<"Layer "<<(n+1)<<" -- "<<(n+2)<<endl;
        for(int i = 0; i < node_count[n+1]; i++){
            for(int j = 0; j < node_count[n]; j++)
                cout<<wt[n][i][j]<<" ";
            cout<<endl;
        }
    }
    cout<<"____________Fan ins in current network____________"<<endl;
    for(int i = 0; i < lay_count; i++){
        cout<<"Layer "<<(i+1)<<": ";
        for(int j = 0; j < node_count[i]; j++)
            cout<<fan_in[i][j]<<" ";
        cout<<endl;
    }
    cout<<"____________Fan in activations in current network____________"<<endl;
    for(int i = 0; i < lay_count; i++){
        cout<<"Layer "<<(i+1)<<": ";
        for(int j = 0; j < node_count[i]; j++)
            cout<<fan_f[i][j]<<" ";
        cout<<endl;
    }
    cout<<"____________Backprop delta in network____________"<<endl;
    for(int i = 0; i < lay_count; i++){
        cout<<"Layer "<<(i+1)<<": ";
        for(int j = 0; j < node_count[i]; j++)
            cout<<del_in[i][j]<<" ";
        cout<<endl;
    }
    cout<<"____________Weight updates____________"<<endl;
    for(int i = 0; i < lay_count-1; i++){
        cout<<"Layer "<<(i+1)<<": "<<endl;
        for(int j = 0; j < node_count[i+1]; j++){
            for(int k = 0; k < node_count[i]; k++)
                cout<<del_w[i][j][k]<<" ";
            cout<<endl;
        }
    }
    cout<<"__________________________________________________"<<endl;
}
