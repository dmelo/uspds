#include"gene.h"
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

/* Construtor do gene, atribui valor default 0*/
gene::gene() {
    value = 0;
}

gene::gene(double value) {
    this->value = value;
}



/* Retorna o valor do gene*/
double gene::get_value() {
    return value;
}

/* Ajusta do valor do gene*/
void gene::set_value(double value) {
    this->value = value;
}

/* Aplica a mutação ao gene*/
void gene::mutation(Random *r) {
    value = r->nextDouble();
}

gene gene::operator*(const double a){
    return gene(a * value);
}

gene gene::operator+(const gene a){
    return gene(value + a.value);
}
