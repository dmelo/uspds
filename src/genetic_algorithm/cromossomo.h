#ifndef CROMOSSOMO_H
#define CROMOSSOMO_H
#include<vector>
#include<set>
#include"Random.h"
#include"gene.h"

using namespace std;

class cromossomo {
    protected:
      	vector<gene> crom;
	int n_genes;
	
    public:
        cromossomo();
        cromossomo(int n_genes);
	cromossomo(Random *r);
	cromossomo(int n_genes, Random *r);
	cromossomo(vector<gene> crom);

	vector<gene> get_cromossomo();
	gene get_gene(int index);
	int get_n_gene();

	double get_value_cromossomo(int index);
//	void set_random(Random *r);
	void set_gene(int index, gene gen);

	void mutation(int n_mutations, Random *r);
	void mutation(int n_mutations, int *index, Random *r);
	void mutation(vector <int>index, Random *r);

	cromossomo operator+(const cromossomo &a);
	cromossomo operator*(const double &a);

	int size();
};


#endif


