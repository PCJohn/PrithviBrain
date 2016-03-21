#define MAX_LAYERS      20
#define MAX_LAYER_LEN   10000

#define HIDDEN     0
#define OUTPUT    1

#define TANH        0
#define SIGM        1
#define SMAX        2

#define DER         3
#define TANH_DER    3
#define SIGM_DER    4

#define RAND        0
#define ONE         1
#define ROOT        2

#define BUFF_LEN    4096
#define ERR_LIM     1.0e-20
#define L_THRESH    1.0e-10
#define MOD_LRATE_DEC   0.5
#define MOD_LRATE_INC   1.025
#define MIN_LRATE   0.005
#define MAX_LRATE   0.7

#ifndef net_H_INCLUDED
#define net_H_INCLUDED

    class Net{
    	public:
	    float *** wt, *** del_w;
        int lay_count, * node_count, * lay_type;
    	float ** fan_in, ** del_in;
    	float ** fan_f, ** del_f;
    	float lrate;
        float mtm;
        float total_error, prev_error;
    	int in_len, out_len;
    	int init_type;
        bool updated;

        public:
	    Net();
        void add_layer(int,int,int);
	    void add_train(float *, float *);
        float * feed(float *);
        float * mul(float **,int,int,float *);
        void update_wt(bool);
        //IO functions
        void save(char *);
        void load(char *);
        void print();
        //Train functions
        void train(char *,char *,int,float,bool,float,int,bool,int);
    };
    //Math functions
    float activation(float,int);
#endif
