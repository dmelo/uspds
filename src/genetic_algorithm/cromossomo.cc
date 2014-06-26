#include"cromossomo.h"

cromossomo::cromossomo() {
}

cromossomo::cromossomo(int n_genes) {
	this->n_genes = n_genes;

    for(int i = 0; i < n_genes; i++) {
	crom.push_back(*(new gene()));
	crom[i].set_value(0);
    }
}

/* Construtor que gera um cromossomo de 50 genes com valores aleatórios*/
cromossomo::cromossomo(Random *r) {
    cromossomo(50, r);
}

/* Construtor que cria um cromossomo de n_genes genes com valores aleatórios*/
cromossomo::cromossomo(int n_genes, Random *r) {
    this->n_genes = n_genes;

    for(int i = 0; i < n_genes; i++) {
	crom.push_back(*(new gene()));
	crom[i].mutation(r);
    }
}

/* Define o cromossomo para valores determinados*/
cromossomo::cromossomo(vector<gene> crom) {
    this->crom = crom;
    n_genes = crom.size();
}

/* Retorna o cromossomo*/
vector<gene> cromossomo::get_cromossomo() {
    return crom;
}

/* Aplica a mutação de n_mutations genes aleatórios do cromossomo*/
void cromossomo::mutation(int n_mutations, Random *r) {
    set<int> mutated;

    mutated.clear();

    // caso em que deve-se mutar mais genes do que existente
    if(n_mutations > n_genes) n_mutations = n_genes;

    for(int i = 0; i < n_mutations; i++) {
	// seleciona aleatoriamente um gene
	int index = r->nextLongInt(n_genes);
	// se o gene já foi mutado seleciona o anterior
	if(mutated.find(index) != mutated.end()) {
	    i--;
	    continue;
	}
	crom[index].mutation(r);
    }
}

void cromossomo::mutation(int n_mutations, int *index, Random *r) {
    if(n_mutations > n_genes) n_mutations = n_genes;
    for(int i = 0; i < n_mutations; i++) crom[index[i]].mutation(r);
}

void cromossomo::mutation(vector <int>index, Random *r) {
    for(int i = 0; i < index.size() && i < n_genes; i++) crom[index[i]].mutation(r);
}

int cromossomo::size() {
    return crom.size();
}

double cromossomo::get_value_cromossomo(int index) {
    return crom[index].get_value();
}

gene cromossomo::get_gene(int index) {
    if(index >= n_genes) index = n_genes - 1;
    return crom[index];
}

int cromossomo::get_n_gene() {
    return n_genes;
}

void cromossomo::set_gene(int index, gene gen) { crom[index] = gen;}

cromossomo cromossomo::operator+(const cromossomo &a){

	/*vector<gene> ncrom = a.crom;

	for(int i = 0; i < n_genes; i++){
		ncrom.push_back(crom[i]);
	}*/
	vector<gene> ncrom = crom;

	for(int i = 0; i < n_genes; i++){
		ncrom.push_back(a.crom[i]);
	}
	return cromossomo(ncrom);
}

cromossomo cromossomo::operator*(const double &a){
    cromossomo cromn(n_genes);

    for (int i = 0; i < n_genes; i ++){
	cromn.set_gene(i, this->get_gene(i)*a);
    }

    return cromn;
}
