#ifndef INDIVIUO_H
#define INDIVIUO_H

#include"cromossomo.h"
#include"objective.h"
#include"../performance_analysis/performance_analysis.h"
#include<math.h>

using namespace std;

class individuo {
    private:
	objective obj;
	cromossomo crom;
	bool calculed;
	Random *r;
	int rank;
	double crowd;

	void fitness();

    public:
	individuo();
	individuo(int n_crom, Random *r);
	individuo(cromossomo crom, Random *r);

	objective get_objective();
	double get_objective(int index);
	void set_objective(objective obj);
	
	cromossomo get_cromossomo();
	void set_cromossomo(cromossomo crom);

	individuo mutation(int n_mutations);

	int get_rank();
	void set_rank(int r);

	double get_crowd();
	void set_crowd(double value);

	void print();

	bool operator<(const individuo &a);
	bool operator>(const individuo &a);
	bool operator==(const individuo &a);
	vector<individuo> operator+(const individuo &a);
};
#endif
