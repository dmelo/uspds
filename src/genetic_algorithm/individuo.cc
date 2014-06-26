#include"individuo.h"

individuo::individuo() {
    rank = -1;
    calculed =false;
}

individuo::individuo(int n_gene, Random *r) {
    rank = -1;
    this->r = r;
    calculed = false;
    crom = *(new cromossomo(n_gene, r));
    obj = *(new objective());
}

individuo::individuo(cromossomo crom, Random *r) {
    rank = -1;
    this->r = r;
    calculed = false;
    this->crom = crom;
}

objective individuo::get_objective() {
    if(!calculed) fitness();
    calculed = true;

    return obj;
}

void individuo::set_objective(objective obj) {
    this->obj = obj;
}

cromossomo individuo::get_cromossomo() {
    return crom;
}

void individuo::set_cromossomo(cromossomo crom) {
    this->crom = crom;
    calculed = false;
}

void individuo::print() {
    if(!calculed) fitness();
    calculed = true;

    printf("Rank: %d ",rank);
    printf("CR:");
    for(int i = 0; i < crom.size(); i++)
	printf(" %lf", crom.get_gene(i).get_value());
    printf(" OB:");
    for(int i = 0; i < obj.size(); i++)
	printf(" %lf", obj.get_objective(i));
    printf(" CW: %lf", crowd);
    printf("\n");
}

void individuo::fitness() {
    vector<double> ob;
    double d, x, y;

    obj.clear();

    x = crom.get_value_cromossomo(0);
    y = crom.get_value_cromossomo(1);

    d = performance_analysis::strategy_performance(2 * x, 2 * x, 2 * y);

    ob.clear();
    ob.push_back(d);

    obj.set_objective(ob);
}

int individuo::get_rank() {
    return rank;
}

void individuo::set_rank(int r) {
    rank = r;
}

double individuo::get_crowd() {
    return crowd;
}

void individuo::set_crowd(double value) {
    crowd = value;
}

double individuo::get_objective(int index) {
    return obj.get_objective(index);
}
	
bool individuo::operator<(const individuo &a) {
    return (this->obj < a.obj);
}

bool individuo::operator>(const individuo &a) {
    return (this->obj > a.obj);
}

bool individuo::operator==(const individuo &a) {
    return (this->obj == a.obj);
}

/* aplica o crossover*/
vector<individuo> individuo::operator+(const individuo &a) {

    cromossomo cromp1,cromp2;
    cromossomo cromf1,cromf2;
    //gene gene1, gene2;
    vector<individuo> filhos;

    double weight = 1;//r->nextDouble();
    int index = r->nextLongInt(crom.size());

    //printf(" %f %d \n",weight,index);

    cromp1 = this->crom;
    cromp2 = a.crom;

    cromf1 = cromossomo(crom.size());
    cromf2 = cromossomo(crom.size());

    for(int i = 0; i < index; i ++){
	cromf1.set_gene(i , cromp1.get_gene(i)*weight + cromp2.get_gene(i)*(1-weight));
	cromf2.set_gene(i , cromp1.get_gene(i)*(1-weight) + cromp2.get_gene(i)*weight);
    }
    for(int i = index; i < crom.size(); i ++){
	cromf1.set_gene(i, cromp1.get_gene(i)*(1-weight) + cromp2.get_gene(i)*weight);
	cromf2.set_gene(i, cromp1.get_gene(i)*weight + cromp2.get_gene(i)*(1-weight));
    }

    individuo ind1 = individuo(cromf1, r);
    individuo ind2 = individuo(cromf2, r);
    filhos.push_back( ind1 );
    filhos.push_back( ind2 );

    return filhos; 

}

individuo individuo::mutation(int n_mutations) {
    cromossomo c = crom;
    c.mutation(n_mutations, r);
    return *(new individuo(c, r));
}


