#include"population.h"

population::population() {
	pop.clear();
}

population::population(Random *r) {
    pop.clear();
    this->r = r;
}

population::population(int n_individuos, int n_gene, Random *r) {
    pop.clear();
    for(int i = 0; i < n_individuos; i++) pop.push_back(*(new individuo(n_gene, r)));
    this->r = r;
}

population::population(vector<individuo> i, Random *r) {
    pop = i;
    this->r = r;
}

vector<individuo> population::get_population() {
    return pop;
}

void population::set_population(vector<individuo> i) {
    pop = i;
}

void population::set_population(population p) {
    pop = p.get_population();
}

int population::size() {
    return pop.size();
}

void population::print() {
    for(int i = 0; i < size(); i++) pop[i].print();
}

population *population::elitismo(double pel) {
    int num = (int) (pel * ((double) size()));
    return elitismo(num);
}

population *population::elitismo(int num) {
    ranking();
    vector<individuo> newp;
    newp.clear();

    for(int i = 0; i < num; i++)
	newp.push_back(pop[i]);

    return (new population(newp, r));
}

void population::calc_fitness() {
    for(int i = 0; i < size(); i++) pop[i].get_objective();
}

void population::ranking() {
    calc_fitness();
    for(int i = 0; i < size() - 1; i++) {
	for(int j = i + 1; j < size(); j++) {
	    if(pop[i] < pop[j]) {
		individuo aux = pop[i];
		pop[i] = pop[j];
		pop[j] = aux;
	    }
	}
    }
    int counter = 0;
    pop[size() - 1].set_rank(0);
    for(int i = size() - 2; i >= 0; i--) {
	if(pop[i] > pop[i+1]) counter++;
	pop[i].set_rank(counter);
    }
}

void population::crowd() {
    calc_fitness();
    double *crowd = new double[size()];
    for(int i = 0; i < size(); i++)
	crowd[i] = 0;

    for(int i = 0; i < pop[0].get_objective().size(); i++) {
	// ordena por objetivo.
	for(int j = 0; j < size(); j++) {
	    for(int k = j + 1; k < size(); k++) {
		if(pop[j].get_objective(i) > pop[k].get_objective(i))
		    swap(pop[j], pop[k]);
	    }
	}

	for(int j = 1; j < size() - 1; j++)
	    crowd[j] += pop[j + 1].get_objective(i) - pop[j - 1].get_objective(i);
	crowd[0] = crowd[size() - 1] = 3000; //numeric_limits<double>::infinity();
    }

    
    for(int i = 0; i < size(); i++)
	pop[i].set_crowd(crowd[i]);
}

void population::sort() {
    for(int i = 0; i < size() - 1; i++) {
	for(int j = i + 1; j < size(); j++) {
	    if(pop[i].get_rank() < pop[j].get_rank()) {
		swap(pop[i], pop[j]);
	    } else if(pop[i].get_rank() == pop[j].get_rank() && pop[i].get_crowd() < pop[j].get_crowd()) {
		swap(pop[i], pop[j]);
	    }
	}
    }
}


	

population population::operator+(const population &p) {
    vector<individuo> n;

    n = p.pop;
    for(int i = 0; i < pop.size(); i++) n.push_back(pop[i]);
    return *(new population(n, r));
}

//population population::operator+=(const population &p) {return *this  = *this + p;}
	
population *population::mutation(int num_ind, int num_gene) {
    printf("mut a\n");
    population *newp = new population(num_ind, pop[0].get_cromossomo().get_n_gene(), r);
    printf("mut b\n");
    for(int i = 0; i < num_ind; i++) {
	newp->pop[i] = pop[r->nextLongInt(pop.size())].mutation(num_gene);
    }
    printf("mut c\n");

    return newp;
}

population *population::mutation(int num_ind) { return mutation(num_ind, 1);}

population *population::mutation(double pmut, int num_gene) {
    int num_ind = (int) (pmut * ((double) pop.size()));
    return mutation(num_ind,num_gene);
}

population *population::mutation(double pmut) { return mutation(pmut, 1);}

individuo population::get_individuo(int index){
	return pop[index];
}

void population::add_individuo(individuo i){ pop.push_back(i);}
void population::add_individuo(vector<individuo> i){ 
	for (int index = 0; index < i.size(); index ++){
		add_individuo(i[index]);
	}
}

population *population::crossover( double pcrv){
	int ncrv =  (int) (pcrv * ((double) size()));
	return crossover(ncrv);
}

population *population::crossover( int ncrv){
     population *p = new population();
	
     for (int i = 0; i < ncrv; i ++ ) {
          p->add_individuo(pop[r->nextLongInt(size())] + pop[r->nextLongInt(size())]);
     }
     return p;
}

population *population::tournament(int num_ind, int num_group) {
    printf("inicio\n");
    vector<individuo> group;
    if(num_ind < 1) return NULL;

    population *newp = new population(r);

    for(int i = 0; i < num_ind; i++) {
	group.clear();
	for(int j = 0; j < num_group; j++)
	    group.push_back(pop[r->nextLongInt(pop.size())]);
	individuo maior = group[0];
	for(int j = 1; j < group.size(); j++)
	    if(group[j] > maior)
		maior = group[j];
	newp->add_individuo(maior);
    }

    printf("fim\n");
    return newp;
}

population *population::roulette(int num_ind, int param) {
    population *newp = new population(r);
    double max = 0;

    vector<double> roulette;

    roulette.clear();

    if(param == ROULETTE_RANK || param == ROULETTE_MULTIPOINTER_RANK) {
	for(int i = 0; i < pop.size(); i++) {
	    max += (double) pop[i].get_rank();
	    roulette.push_back(max);
	}
    } else {
	for(int i = 0; i < pop.size(); i++) {
	    max += pop[i].get_objective(0);
	    roulette.push_back(max);
	}
    }

    if(param == ROULETTE_RANK || param == ROULETTE_OBJECTIVE) {
	for(int i = 0; i < num_ind; i++) {
	    double pointer = r->nextDouble(max);
	    int j;
	    for(j = 0; roulette[j] < pointer; j++);
	    newp->add_individuo(pop[j]);
	}
    }
    else {
	double pointer;
	double delta = max / (double) num_ind;
	pointer = r->nextDouble(max / (double) num_ind);
	int j = 0;
	for(int i = 0; i < num_ind; i++) {
	    for(j; roulette[j] < pointer; j++);
	    newp->add_individuo(pop[j]);
	    pointer += delta;
	}
    }

    return newp;
}

void population::resize(int n ){ 
    if(n < pop.size())
	pop.resize(n);
}
