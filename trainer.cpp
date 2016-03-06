#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "net.h"
using namespace std;

/*char * concat(int num,...){
	va_list strings;
	char * conc;
	int i;

	va_start(strings, num);
	conc = (char *)malloc(MAX_PATH_LEN+1);

	for(i = 0 ; i < num; i++)
		strcat(conc, va_arg(strings, char *));

	va_end(strings);
	return conc;
}*/

void Net::train(char * path,
                char * dest,
                int minibatch_size,
                float learn_rate,
                int save_part,
                bool verbose,
                int max_epochs){
    ifstream in(path);
    ofstream out(dest);
    char * line = new char[10000];
    float * inp = new float[100000];
    int pos = 0, len, i = 0, N = 0, epoch;

    lrate = learn_rate;
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

        N = 0;
        total_error = 0;
        while(in>>line){
            *inp++ = atof(line);
            pos++;
            if(pos < len)
                continue;
            pos = 0;
            inp -= len;
            N++;
            //Add trainging data -- Run backprop
            add_train(inp,inp+in_len);
            //Mini batch weight update
            i = (i+1)%minibatch_size;
            if(i == 0){
                update_wt();
            }
        }
        epoch++;
        if(epoch == max_epochs){
            save(dest);//concat(dest,"/res/e/",(char*)));
            total_error /= (2*N);
            cout<<"Total error: "<<total_error<<endl;
            break;
        }
        //if(epoch%save_part == 0){
        //    save(dest);//concat(dest,"/res/e/"));
        //}
        if(verbose){
            total_error /= (2*N);
            cout<<"Total error (epoch "<<epoch<<"): "<<total_error<<endl;
        }
    }
}
