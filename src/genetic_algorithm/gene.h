/* declarações para os objeos genes. Esse tipo de objeto tem seu operador de
 * mutação que auterará seu valor para um valore aleatório. A ideia é ter no
 * futuro um objeto que representará diferentes tipos de variáveis (Double,
 * Float, Integer, Unsigned, structures definidas para um dado problema, etc).
 * Porém ainda não temos ideia de como fazer isso. Por agora está implementado
 * apenas para variáveis double.
 */

#ifndef GENE_H
#define GENE_H

#include"Random.h"

class gene {
    public:
	gene();
	gene(double value);

	double get_value();
	void set_value(double value);
	void mutation(Random *r);
	gene operator*(const double a);
	gene operator+(const gene a);

    protected:
	double value;
};

#endif
