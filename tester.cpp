#include <iostream>
using namespace std;
#include "net.h"

int main(){
    Net net;
    net.add_layer(1,BIAS_OFF,SIGM);
    //net.add_layer(10,BIAS_OFF,SIGM);
    net.add_layer(8,BIAS_OFF,SIGM);
    //net.add_layer(10,BIAS_OFF,SIGM);
    net.add_layer(1,BIAS_OFF,SIGM);
    
    net.train("./data", //Path to training data
              "./model", //Path to destination folder
              1, //Mini batch size (=1 for online learning)
              0.005, //Learning rate
              1, //Saves intermediate models every CYC batches later
              true, //Switch to turn verbose feature on/off
              20 //Maximum number of epochs
             );

    //net.load("./model");
    for(int i = 0; i < 314; i++){
        float inp = i/10;
        cout<<*net.feed(&inp)<<", ";
    }
    cout<<endl;
}
