/*
	USPDroidsSimulator
	(C) 2007  Diogo Oliveira de Melo

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	src/lib/vetor2d.cc
*/

#include<math.h>
#include"vetor2d.h"

#define PI 3.1415926535897932384626433

vetor2d aux;

void vetor2d::atualizar() {
	if((x == 0) && (y ==0)) {
		modulo = 0;
		ang = 0;
	}
	else {
		modulo = sqrt(pow(x, 2) + pow(y, 2));
		ang = atan2f(y, x);
	}
}

vetor2d::vetor2d() {
	x = 0;
	y = 0;
	modulo = 0;
	ang = 0;
}

vetor2d::vetor2d(const float a, const float b) {
	x = a;
	y = b;
	atualizar();
}

void vetor2d::operator=(const vetor2d &b) {
	if(this != &b) {
		x = b.x;
		y = b.y;
		modulo = b.modulo;
		ang = b.ang;
	}
}

vetor2d vetor2d::operator*(const float escalar) {
	aux.x = x * escalar;
	aux.y = y * escalar;
	aux.atualizar();

	return aux;
}

vetor2d vetor2d::operator/(const float escalar) {
	float esc = escalar;

	if(esc == 0)
		esc = 0.0001;
	aux.x = x / esc;
	aux.y = y / esc;
	aux.atualizar();

	return aux;
}

float vetor2d::operator*(const vetor2d &b) {
	float aux;

	aux = x * b.x;
	aux += y * b.y;

	return aux;
}

vetor2d vetor2d::operator+(const vetor2d &b) {
	aux.x = x + b.x;
	aux.y = y + b.y;
	aux.atualizar();

	return aux;
}

void vetor2d::operator+=(const vetor2d &b) {
	x = x + b.x;
	y = y + b.y;
	atualizar();
}

vetor2d vetor2d::operator-(const vetor2d &b) {
	aux.x = x - b.x;
	aux.y = y - b.y;
	aux.atualizar();

	return aux;
}

void vetor2d::setXY(const float a, const float b) {
	x = a;
	y = b;
	atualizar();
}

void vetor2d::setModulo(const float modu) {
	x = modu * cos(ang);
	y = modu * sin(ang);
	modulo = modu;
	atualizar();
}

void vetor2d::setAng(const float angulo) {
	float aux = angulo;

	while(aux >= M_PI * 2)
		aux -= M_PI * 2;
	while(aux < 0)
		aux += M_PI * 2;
	x = modulo * cos(aux);
	y = modulo * sin(aux);
	ang = aux;
}

void vetor2d::setAngGraus(const float ang) {
	float ang_rad = ang;

	ang_rad = (ang_rad / 180) * PI;
	setAng(ang_rad);
}

float vetor2d::getX() {
	return x;
}

float vetor2d::getY() {
	return y;
}

float vetor2d::getModulo() {
	return modulo;
}

float vetor2d::getAng() {
	while(ang >= ((2 * M_PI) - 0.0002))
		ang -= 2 * M_PI;
	if(fabs(ang) <= 0.0001)
		ang = 0;
	while(ang < 0)
		ang += 2 * M_PI;

	return ang;
}

float vetor2d::getAngGraus() {
	return (ang / PI) * 180;
}

vetor2d vetor2d::decompor(float base) {
	vetor2d ret;
	ret.setAng(base);
	ret.setModulo(cos(ang - base) * getModulo());

	return ret;
}
