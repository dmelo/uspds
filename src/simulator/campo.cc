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

	src/simulator/campo.cc
*/

#include"campo.h"

campo::campo() : objeto() {
	x[0] = CAMPO_GOL_PROFUNDIDADE + CAMPO_LADO_TRIANGULO;
	y[0] = 0;
	a[0] = M_PI_4;

	x[1] = CAMPO_GOL_PROFUNDIDADE;
	y[1] = CAMPO_LADO_TRIANGULO;
	a[1] = 0;

	x[2] = x[1];
	y[2] = (CAMPO_ALTURA - CAMPO_GOL_TAMANHO) / 2;
	a[2] = M_PI_2;

	x[3] = 0;
	y[3] = y[2];
	a[3] = 0;

	x[4] = 0;
	y[4] = CAMPO_ALTURA - y[2];
	a[4] = M_PI + M_PI_2;

	x[5] = x[1];
	y[5] = y[4];
	a[5] = 0;

	x[6] = x[1];
	y[6] = CAMPO_ALTURA - CAMPO_LADO_TRIANGULO;
	a[6] = M_PI + M_PI_2 + M_PI_4;

	x[7] = x[0];
	y[7] = CAMPO_ALTURA;
	a[7] = a[4];

	x[8] = CAMPO_GOL_PROFUNDIDADE + CAMPO_LARGURA - CAMPO_LADO_TRIANGULO;
	y[8] = y[7];
	a[8] = M_PI + M_PI_4;
	
	x[9] = x[8] + CAMPO_LADO_TRIANGULO;
	y[9] = y[6];
	a[9] = M_PI;

	x[10] = x[9];
	y[10] = y[4];
	a[10] = M_PI + M_PI_2;

	x[11] = CAMPO_GOL_PROFUNDIDADE + CAMPO_LARGURA + CAMPO_GOL_PROFUNDIDADE;
	y[11] = y[4];
	a[11] = M_PI;

	x[12] = x[11];
	y[12] = y[2];
	a[12] = M_PI_2;

	x[13] = x[10];
	y[13] = y[2];
	a[13] = M_PI;

	x[14] = x[9];
	y[14] = y[1];
	a[14] = M_PI_2 + M_PI_4;

	x[15] = x[8];
	y[15] = 0;
	a[15] = M_PI_2;
}

float campo::getX(int i) {
	if((i >= 0)&&(i < CAMPO_N_PONTOS))
		return x[i];
	
	return -1;
}

float campo::getY(int i) {
	if((i >= 0)&&(i < CAMPO_N_PONTOS))
		return y[i];
	
	return -1;
}

float campo::getA(int i) {
	if((i >= 0)&&(i < CAMPO_N_PONTOS))
		return a[i];
	
	return -10;
}

bool campo::is_inside(float px, float py) {
    if((px < getX(3))||(px > getX(12))||(py < getY(0))||(py > getY(7))) return false;
    if((px > getX(0))&&(px < getX(15))&&(py > getY(1))&&(py < getY(6))) return true;

    float f_x[12], f_y[12];
    float g1_x[4], g1_y[4];
    float g2_x[4], g2_y[4];
    bool f, g1, g2;

    f_x[0] = getX(0); f_y[0] = getY(0);
    f_x[1] = getX(1); f_y[1] = getY(1);
    f_x[2] = getX(2); f_y[2] = getY(2);
    f_x[3] = getX(5); f_y[3] = getY(5);
    f_x[4] = getX(6); f_y[4] = getY(6);
    f_x[5] = getX(7); f_y[5] = getY(7);
    f_x[6] = getX(8); f_y[6] = getY(8);
    f_x[7] = getX(9); f_y[7] = getY(9);
    f_x[8] = getX(10); f_y[8] = getY(10);
    f_x[9] = getX(13); f_y[9] = getY(13);
    f_x[10] = getX(14); f_y[10] = getY(14);
    f_x[11] = getX(15); f_y[11] = getY(15);

    g1_x[0] = getX(2); g1_y[0] = getY(2);
    g1_x[1] = getX(3); g1_y[1] = getY(3);
    g1_x[2] = getX(4); g1_y[2] = getY(4);
    g1_x[3] = getX(5); g1_y[3] = getY(5);


    g2_x[0] = getX(10); g2_y[0] = getY(10);
    g2_x[1] = getX(11); g2_y[1] = getY(11);
    g2_x[2] = getX(12); g2_y[2] = getY(12);
    g2_x[3] = getX(13); g2_y[3] = getY(13);

    f = objeto::point_inside_convex_polygon(px, py, f_x, f_y, 12);
    g1 = objeto::point_inside_convex_polygon(px, py, g1_x, g1_y, 4);
    g2 = objeto::point_inside_convex_polygon(px, py, g2_x, g2_y, 4);

    if(f || g1 || g2)
	return true;
    return false;
}
