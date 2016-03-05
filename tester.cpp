#include <iostream>
using namespace std;
#include "net.h"

int main(){
    /*Net net;
    net.add_layer(2,BIAS_OFF,SIGM);
    net.add_layer(3,BIAS_OFF,SIGM);
    net.add_layer(1,BIAS_OFF,SIGM);*/
    Net net;
    load(&net,"./net_1");
    
    float * inp = new float[net.get_in_len()];
    inp[0] = 1; inp[1] = 1;
    float * r = net.feed(inp);

    for(int i = 0; i < net.get_out_len(); i++)
        cout<<r[i]<<" ";
    cout<<endl;

    //save(net,"net_1");
    print(net);
}
