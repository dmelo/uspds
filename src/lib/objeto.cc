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

	src/lib/objeto.cc
*/

#include"objeto.h"

objeto::objeto() {
	x = 0;
	y = 0;
	novo_x = 0;
	novo_y = 0;
	massa = BOLA_MASSA;
	velocidade = new vetor2d();
	nova_velocidade = new vetor2d();
	forca_resultante = new vetor2d();
	nova_forca_resultante = new vetor2d();
	forca_externa = new vetor2d();
}

objeto::objeto(const float x, const float y, const vetor2d *velocidade, const vetor2d *forca_resultante) {
	objeto();
	if(setX(x) == false)
		this->x = 0;
	if(setY(y) == false)
		this->y = 0;
	if(setVelocidade(velocidade) == false)
		this->velocidade = new vetor2d();
	if(setForca_resultante(forca_resultante) == false)
		this->forca_resultante = new vetor2d();
	nova_velocidade = new vetor2d();
	nova_forca_resultante = new vetor2d();

	*nova_velocidade = *velocidade;
	*nova_forca_resultante = *forca_resultante;
}

bool objeto::setX(float x) {
	if((x < 0)||(x > 150))
		return false;
	
	this->x = x;

	return true;
}

bool objeto::setY(float y) {
	if((y < 0)||(y > 130))
		return false;
	
	this->y = y;

	return true;
}

bool objeto::setXY(float x, float y) {
	if((x < 0)||(x > 150)||(y < 0)||(y > 130))
		return false;
	
	this->x = x;
	this->y = y;

	return true;
}

bool objeto::setNewX(float x) {
    this->novo_x = x;
    return true;
}

bool objeto::setNewY(float y) {
    this->novo_y = y;
    return true;
}

bool objeto::setNewXY(float x, float y) {
    this->novo_x = x;
    this->novo_y = y;
    return true;
}

bool objeto::setMassa(float massa) {
	if(massa < 0)
		return false;
	
	this->massa = massa;

	return true;
}

bool objeto::setVelocidade(const vetor2d *velocidade) {
	this->velocidade = (vetor2d*) velocidade;

	return true;
}

bool objeto::setForca_resultante(const vetor2d *forca_resultante) {
	this->forca_resultante = (vetor2d*) forca_resultante;

	return true;
}

float objeto::getX() {
	return x;
}

float objeto::getY() {
	return y;
}

float objeto::getNewX() {
    return novo_x;
}

float objeto::getNewY() {
    return novo_y;
}

float objeto::getMassa() {
	return massa;
}

vetor2d objeto::getVelocidade() {
	if(velocidade == NULL) {
		vetor2d r;
		r.setModulo(0);
		r.setAng(0);
		return r;
	}

	return *velocidade;
}

vetor2d objeto::getForca_resultante() {
	if(forca_resultante == NULL) {
		vetor2d r;
		r.setModulo(0);
		r.setAng(0);
		return r;
	}

	return *forca_resultante;
}
float objeto::area_triangulo(float ax, float ay, float bx, float by, float cx, float cy) {
	return fabs((ax * by) + (ay * cx) + (bx * cy) - (ax * cy) - (ay * bx) - (by * cx)) / 2;
}

float objeto::distancia(float ax, float ay, float bx, float by) {
	return sqrtf(powf(ax - bx, 2) + powf(ay - by, 2));
}

bool objeto::restart_forca_externa() {
	forca_externa = new vetor2d();

	return true;
}

bool objeto::add_forca_externa(vetor2d nova_forca) {
	*forca_externa += nova_forca;

	return true;
}

vetor2d objeto::get_forca_externa() {
	return *forca_externa;
}

bool objeto::end_forca_externa() {
	delete []forca_externa;

	return true;
}


bool objeto::restart_torque_externo() {
	torque_externo = 0;

	return true;
}

bool objeto::add_torque_externo(float novo_torque) {
	torque_externo += novo_torque;

	return true;
}

float objeto::get_torque_externo() {
	return torque_externo;
}

bool objeto::end_torque_externo() {
	torque_externo = 0;

	return true;
}

float objeto::padronizar_angulo_2_pi(float angulo) {
	while(angulo < 0)
		angulo += 2 * M_PI;
	while(angulo >= 2 * M_PI)
		angulo -= 2 * M_PI;
	
	return angulo;
}

float objeto::padronizar_angulo_pi(float angulo) {
	while(angulo < 0)
		angulo += M_PI;
	while(angulo >= M_PI)
		angulo -= M_PI;
	
	return angulo;
}

float objeto::padronizar_angulo_pi_sobre_2(float angulo) {
	while(angulo < 0)
		angulo += M_PI_2;
	while(angulo >= M_PI_2)
		angulo -= M_PI_2;
	
	return angulo;
}
float objeto::padronizar_angulo_pi_sobre_4(float angulo) {
	while(angulo < 0)
		angulo += M_PI_4;
	while(angulo >= M_PI_4)
		angulo -= M_PI_4;
	
	return angulo;
}

int objeto::angcmp(float um, float dois) {
	if(fabs(um - dois) <= 0.0001)
		return 0;
	if(um < dois)
		return -1;
	
	return 1;
}

// pré-supões que os vetores tem a mesma direção.
bool objeto::colisao_elastica(float m1, vetor2d v1, float m2, vetor2d v2, vetor2d *vf1, vetor2d *vf2) {
	// ajeitando as coisas...
	bool inverteu = false;

	vetor2d vc = ((v1 * m1)+(v2 * m2))/(m1 + m2);

	if(v1.getModulo() > v2.getModulo()) {
		*vf1 = (vc * 2) - v1;
		*vf2 = (vc * 2) + v2;
	}
	else {
		*vf1 = (vc * 2) - v1;
		*vf2 = (vc * 2) - v2;
	}

	return true;
}

void objeto::sleep2(long int mseconds) {
	if(mseconds <= 0)
		return;
	struct timespec timeOut, remains;

	timeOut.tv_sec = mseconds / 1000;
	timeOut.tv_nsec = 1000000 * mseconds;
	nanosleep(&timeOut, &remains);
}

bool objeto::point_inside_convex_polygon(float px, float py, float *x, float *y, int n_points) {
    float middle_x = 0.0, middle_y = 0.0;
    float total_area = 0.0;
    float virtual_area = 0.0;

    for(int i = 0; i < n_points; i++) {
	middle_x += x[i];
	middle_y += y[i];
    }
    middle_x /= n_points;
    middle_y /= n_points;

    for(int i = 0; i < n_points; i++) total_area += objeto::area_triangulo(middle_x, middle_y, x[i], y[i], x[(i+1)%n_points], y[(i+1)%n_points]);
    for(int i = 0; i < n_points; i++) virtual_area += objeto::area_triangulo(px, py, x[i], y[i], x[(i+1)%n_points], y[(i+1)%n_points]);

    if(fabs(virtual_area - total_area) < 0.00001)
	return true;
    return false;
}
