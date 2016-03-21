#include <iostream>
using namespace std;
#include "net.h"

int main(){
    Net net;
    net.add_layer(1,HIDDEN,TANH);
    net.add_layer(10,HIDDEN,TANH);
    net.add_layer(10,HIDDEN,TANH);
    net.add_layer(10,HIDDEN,TANH);
    net.add_layer(1,OUTPUT,TANH);
    
    net.train("./data", //Path to training data
              "./model_cos_tanh", //Path to destination folder
              1, //Mini batch size (=1 for online learning)
              0.001, //Learning rate
              false, //Turn on adaptive learning rates
              0.0, //Momentum
              1, //Saves intermediate models every CYC batches later
              true, //Switch to turn verbose feature on/off
              1000 //Maximum number of epochs
             );
    
    net.load("./model_cos_tanh");

    for(int i = 0; i < 628; i++){
        float inp = i/100.0;
        cout<<*net.feed(&inp)<<", ";
    }
    cout<<endl;
    net.print();
}
