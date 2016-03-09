#include <iostream>
using namespace std;
#include "net.h"

int main(){
    Net net;
    net.add_layer(1,HIDDEN,SIGM);
    //net.add_layer(10,HIDDEN,SIGM);
    net.add_layer(10,HIDDEN,SIGM);
    //net.add_layer(10,HIDDEN,SIGM);
    net.add_layer(1,OUTPUT,SIGM);
    
    net.train("./data", //Path to training data
              "./model_cos_sq_one_lobe", //Path to destination folder
              1, //Mini batch size (=1 for online learning)
              0.02, //Learning rate
              1, //Saves intermediate models every CYC batches later
              true, //Switch to turn verbose feature on/off
              20000 //Maximum number of epochs
             );
    
    net.load("./model_cos_sq_one_lobe");

    for(int i = 0; i < 314; i++){
        float inp = i/100.0;
        cout<<*net.feed(&inp)<<", ";
    }
    cout<<endl;
    /*for(int i = 0; i < 314; i+=(314/8)){
        float inp = i/100.0;
        cout<<inp<<", ";
    }*/
    cout<<endl;
    //net.print();
}
