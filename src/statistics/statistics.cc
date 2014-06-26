#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<vector>
#include"../lib/mstring.h"
#include"../lib/parametros.h"
#include"../lib/objeto.h"
#include"../lib/mmath.h"

#define FD " "

using namespace std;

int main(int argc, char **argv) {
    float *distance = new float[1 + (2 * N_JOGADORES_POR_TIME)];
    float *data = new float[2 + (3 * N_JOGADORES_POR_TIME)];
    float *data_ant = new float[2 + (3 * N_JOGADORES_POR_TIME)];
    vector<float> *vtime = new vector<float>();
    vector<float> *vdistance = new vector<float>[1 + (2 * N_JOGADORES_POR_TIME)];
    char *aux = new char[200];
    int n_numbers;
    int n_balls, n_robots;


    if(argc == 1) {
	printf("usage: ./bin/statistics arq1.uds arq2.uds arq3.uds ...\n\n");
	exit(1);
    }

    for(int index = 1; index < argc; index++) {
	float time = 0.0;
	bool begin = true;


	for(int i = 0; i < 1 + (2 * N_JOGADORES_POR_TIME); i++) distance[i] = 0.0;
	FILE *fd;

	if((fd = fopen(argv[index], "r")) == NULL) {
	    cerr << "statistics: erro: cannot open file " << argv[index] << endl;
	    exit(1);
	}

	char *line = new char[300];

	while(!feof(fd)) {
	    fgets(line, 298, fd);
	    
	    char char_init;

	    sscanf(line, " %c ", &char_init);
	    // Comments.
	    if(char_init == '#')
		continue;

	    n_numbers = mstring::split_string_to_float(line, FD, data);
	    if(begin) {
		for(int i = 0; i < n_numbers; i++)
		    data_ant[i] = data[i];
		begin = false;
		continue;
	    }

	    if(n_numbers >= 2) {
		n_balls = 1;
		n_robots = (n_numbers - 2) / 3;
	    }
	    else {
		n_balls = 0;
		n_robots = 0;
	    }

	    if(n_balls) distance[0] += objeto::distancia(data[0], data[1], data_ant[0], data_ant[1]);
	    if(n_robots) for(int i = 0; i < n_robots; i++) distance[i + 1] += objeto::distancia(data[2 + (3 * i)], data[3 + (3 * i)], data_ant[2 + (3 * i)], data_ant[3 + (3 * i)]);
	    time += 0.033333;

	    for(int i = 0; i < 2 + (3 * N_JOGADORES_POR_TIME); i++)
		data_ant[i] = data[i];
	}

#ifdef DEBUG
	printf("arq: %s ====\n", argv[index]);
	printf("time: %f\n", time);
	if(n_balls)
	    printf("ball: \n    distance: %f\n\n", distance[0]);
	for(int i = 0; i < n_robots; i++)
	    printf("robot %d:\n    distance: %f\n\n", i, distance[i + 1]);
	printf("============================\n");
#endif

	vtime->push_back(time);
	for(int i = 0; i < n_balls; i++)
	    vdistance[i].push_back(distance[i]);
	for(int i = 0; i < n_robots; i++)
	    vdistance[i+1].push_back(distance[i+1]);
	fclose(fd);
    }

#ifdef DEBUG
    printf("FIM ===================\n");
    for(int i = 0; i < argc - 1; i++)
	printf("vtime[%d]: %f\n", i, vtime->at(i));
    for(int i = 0; i < 1 + N_JOGADORES_POR_TIME; i++)
	for(int j = 0; j < vdistance[i].size(); j++)
	    printf("vdistance[%d].at(%d): %f\n", i, j, vdistance[i].at(j));
#endif

    mmath::histogram(vtime, 100, "histogram_time.txt");
    if(n_balls) mmath::histogram(&(vdistance[0]), 100, "histogram_ball.txt");
    for(int i = 0; i < n_robots; i++) {
	sprintf(aux, "histogram_robot_%d.txt", i);
	mmath::histogram(&(vdistance[i + 1]), 100, aux);
    }

    printf("time    mean: %f. variance: %f.\n", mmath::mean(vtime), mmath::variance(vtime));
    printf("ball    mean: %f. variance: %f.\n", mmath::mean(&(vdistance[0])), mmath::variance(&(vdistance[0])));
    for(int i = 0; i < n_robots; i++) printf("robot %d    mean: %f. variance: %f.\n", i, mmath::mean(&(vdistance[i + 1])), mmath::variance(&(vdistance[i + 1])));



    return 0;
}
