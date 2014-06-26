#include"individuo_data.h"

individuo_data::individuo_data() {
    c = NULL;
    o = NULL;
}

individuo_data::individuo_data(cromossomo *c, objective *o) {
    this->c = c;
    this->o = o;
}
