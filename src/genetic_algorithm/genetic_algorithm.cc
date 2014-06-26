#include"Random.h"
#include"individuo.h"
#include"population.h"
#include"../performance_analysis/performance_analysis.h"
#include<iostream>
#include<omp.h>

using namespace std;

float mutation_probability;
int n_points_crossover;
int n_genes = 10;

/*int read_config(char *file) {
    FILE *fconfig;

    if((fconfig = fopen(argv[1], "r")) == NULL)
	return(1);

    while(!feof(fconfig)) {
	char title[100];
	fscanf(fconfig, " %s ", title);

	// Reading configuration file.
	if(strcmp(title, "n_points_crossover") == 0)
	    fscanf(" %d ", &n_points_crossover);
	else if(strcmp(title, "mutation_probability") == 0)
	    fscanf(" %f ", &mutation_probability);
	else if(strcmp(title, "n_genes") == 0)
	    fscanf(" %d ", &n_genes);
    }

    return 0;
}*/

int main(int argc, char **argv) {
    Random *r = new Random();

    /*if(read_config(argv[1])) {
	fprintf(stderr, "error: cannot open configuration file %s.\n", argv[1]);
	exit(1);
    }*/


    population *p = new population(100,2, r);
    population *pe = new population();
    population *pc = new population();
    population *pm = new population();

    printf(" primeira geração");
    p->ranking();
    p->crowd();
    p->sort();
    p->print();

    for (int i=0; i < 200; i ++){
	

       printf(" gen: %d . pop.size: %d\n",i, p->size());
       pe = p->elitismo(10);
       pm = p->mutation(10);
       pc = p->roulette(50, ROULETTE_MULTIPOINTER_OBJECTIVE);
       printf("roulette\n");
       pc->ranking();
       pc = pc->crossover(25);
     
       p->add_individuo(pe->get_population());
       p->add_individuo(pm->get_population());
       p->add_individuo(pc->get_population());

       p->ranking();
       p->crowd();
       p->sort();
       p->resize(100);
       p->ranking();
       p->print();

    }

    printf(" ultima geração \n");
    p->ranking();
    //p->print();
    /*printf("\n\n\n Trounament 30\n");
    p = p->tournament(4, 100);
    p->print();*/




    return 0;
}
