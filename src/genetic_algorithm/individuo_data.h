#ifndef INDIVIDUO_DATA
#define INDIVIDUO_DATA

#include"cromossomo.h"
#include"objective.h"

class individuo_data {
    public:
	individuo_data();
	individuo_data(cromossomo *c, objective *o);
	cromossomo *c;
	objective *o;
};

#endif
