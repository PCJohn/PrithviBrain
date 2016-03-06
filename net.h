#define MAX_LAYERS      20
#define MAX_LAYER_LEN   10000

#define BIAS_ON     0
#define BIAS_OFF    1

#define TANH        0
#define SIGM        1
#define SMAX        2

#define DER         3
#define TANH_DER    3
#define SIGM_DER    4

#define FEED        0
#define REV         1

#define RAND        0
#define ONE         1
#define ROOT        2

#define LIM         0.00001

#ifndef net_H_INCLUDED
#define net_H_INCLUDED

    class Net{
    	public:
	    float *** wt, *** del_w;
        int lay_count, * node_count, * lay_type;
    	float ** fan_in, ** del_in;
    	float ** fan_f, ** del_f;
    	float lrate;
        float total_error;
    	int in_len, out_len;
    	int init_type;

        public:
	    Net();
        void add_layer(int,int,int);
	    void add_train(float *, float *);
        float * feed(float *);
        float * mul(float **,int,int,int,float *);
        void update_wt();
        //IO functions
        void save(char *);
        void load(char *);
        void print();
        //Train functions
        void train(char *,char *,int,float,int,bool,int);
    };
    //Math functions
    float activation(float,int);
#endif
