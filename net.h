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

#ifndef net_H_INCLUDED
#define net_H_INCLUDED

    class Net{
    	public:
	    float *** wt, *** del_w;
        int lay_count, * node_count, * lay_type;
    	float ** fan_in, ** del_in;
    	float ** fan_f, ** del_f;
    	float lrate;
    	int in_len, out_len;
    	int init_type;

        public:
	    Net();
        void add_layer(int,int,int);
	    void add_train(float *, float *);
	    int get_in_len();
	    int get_out_len();
	    void set_init(int);
	    void set_learn_rate(float);
        float * feed(float *);
        float * mul(float **,int,int,int,float *);
    };

    //Math functions
    float activation(float,int);
    //Net IO functions
    void save(Net,char *);
    void load(Net *,char *);
    void print(Net);
#endif
