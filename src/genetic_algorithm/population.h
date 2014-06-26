#ifndef POPULATION_H
#define POPULATION_H

#include"individuo.h"
#include"individuo_data.h"
#include<algorithm>
#include<limits>
#include<iostream>
#include<set>

using namespace std;

#define ROULETTE_RANK 0
#define ROULETTE_OBJECTIVE 1
#define ROULETTE_MULTIPOINTER_RANK 2
#define ROULETTE_MULTIPOINTER_OBJECTIVE 3

class population {
    private:
	Random *r;
	vector<individuo> pop;
	set<individuo_data> ind_table;

    public:
	// contrutores
	population();
	population(Random *r);
	population(int n_individuos, int n_gene, Random *r);
	population(vector<individuo> i, Random *r);

	// retorna individuos
	vector<individuo> get_population();
	individuo get_individuo(int index);

	// adiciona individuos a pop
	void add_individuo(individuo i);
	void add_individuo(vector<individuo> i);

	// define individuo
	void set_population(vector<individuo> i);
	void set_population(population p);

	// operadores de seleção 
	void calc_fitness();
	void ranking();
	void crowd();
	void sort();

	// info da população
	int size();
	void print();
	void resize(int n);

	// operacores genéticos
	population *elitismo(double pel);
	population *elitismo(int num);

	population *mutation(int num_ind, int num_gene);
	population *mutation(double pmut, int num_gene);
	population *mutation(int num_ind);
	population *mutation(double pmut);

	population *crossover( int ncrv);
	population *crossover( double pcrv);

	population *selection(int num_ind);

	population *tournament(int num_ind, int num_group);
	
	population *roulette(int num_ind, int param);


	// sobrecarga de operadores
	population operator+(const population &p); // concatena duas populacoes
	//population operator+=(const population &p);

};

#endif
