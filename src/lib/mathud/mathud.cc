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

	src/lib/mathud/mathud.cc
*/

#include"mathud.h"

mathud::mathud() {
	values = (float *) new float[N];
	sinud = (float *) new float[N];
	cosud = (float *) new float[N];
	tanfud = (float *) new float[N];

	values[0] = 0;
	long double diff = M_PI * 2 / N;

	for(int i = 0; i < N; i++)
		values[i] = i * (M_PI * 2) / N;

	for(int i = 0; i < N; i++) {
		sinud[i] = sin(values[i]);
		cosud[i] = cos(values[i]);
		tanfud[i] = tanf(values[i]);
	}
}

float mathud::sin_ud(float ang) {
	ang = reduzir_2_pi(ang);
	return sinud[((int) ((ang / (2 * M_PI)) * N))];
}

float mathud::cos_ud(float ang) {
	ang = reduzir_2_pi(ang);
	return cosud[((int) ((ang / (2 * M_PI)) * N))];
}

float mathud::tanf_ud(float ang) {
	ang = reduzir_2_pi(ang);
	return tanfud[((int) ((ang / (2 * M_PI)) * N))];
}

float mathud::atanf_ud(float tg) {
	int i = N/2;
	int max = 3*N/4;
	int min = N/4;

	while((tg > tanfud[i+1])||(tg < tanfud[i])) {
		if(tanfud[i] < tg) {
			min = i;
			i = (i + max) / 2;
		}
		else {
			max = i;
			i = (i + min) / 2;
		}
	}

	return values[i] - M_PI;
}

float mathud::reduzir_2_pi(float ang) {
	while(ang >= 2 * M_PI)
		ang -= 2 * M_PI;
	while(ang < 0)
		ang += 2 * M_PI;

	return ang;
}
