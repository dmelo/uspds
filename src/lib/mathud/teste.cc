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

	src/lib/mathud/teste.cc
*/

#include<sys/time.h>
#include<time.h>
#include<iostream>
#include<stdio.h>
#include"mathud.h"

using namespace std;

int main() {
	mathud *a = new mathud();
	struct timeval tv;
	struct timezone tz;

	/*cout << "a->sin_ud((M_PI/6)): " << a->sin_ud((M_PI/6)) << endl;
	cout << "sin((M_PI/6)): " << sin((M_PI/6)) << endl << endl;

	cout << "a->sin_ud((M_PI/6) + M_PI_2): " << a->sin_ud((M_PI/6) + M_PI_2) << endl;
	cout << "sin((M_PI/6) + M_PI_2): " << sin((M_PI/6) + M_PI_2) << endl << endl;

	cout << "a->sin_ud((M_PI/6) + M_PI): " << a->sin_ud((M_PI/6) + M_PI) << endl;
	cout << "sin((M_PI/6) + M_PI): " << sin((M_PI/6) + M_PI) << endl << endl;

	cout << "a->sin_ud((M_PI/6) + M_PI_2 + M_PI): " << a->sin_ud((M_PI/6) + M_PI_2 + M_PI) << endl;
	cout << "sin((M_PI/6) + M_PI_2 + M_PI): " << sin((M_PI/6) + M_PI_2 + M_PI) << endl << endl << endl;

	cout << "a->sin_ud((M_PI/6)): " << a->sin_ud((M_PI/6)) << endl;
	cout << "sin((M_PI/6)): " << sin((M_PI/6)) << endl << endl;

	cout << "a->sin_ud((M_PI/6) + M_PI_2): " << a->sin_ud((M_PI/6) + M_PI_2) << endl;
	cout << "sin((M_PI/6) + M_PI_2): " << sin((M_PI/6) + M_PI_2) << endl << endl;

	cout << "a->sin_ud((M_PI/6) + M_PI): " << a->sin_ud((M_PI/6) + M_PI) << endl;
	cout << "sin((M_PI/6) + M_PI): " << sin((M_PI/6) + M_PI) << endl << endl;

	cout << "a->sin_ud((M_PI/6) + M_PI_2 + M_PI): " << a->sin_ud((M_PI/6) + M_PI_2 + M_PI) << endl;
	cout << "sin((M_PI/6) + M_PI_2 + M_PI): " << sin((M_PI/6) + M_PI_2 + M_PI) << endl << endl << endl;



	cout << "a->cos_ud((M_PI/6)): " << a->cos_ud((M_PI/6)) << endl;
	cout << "cos((M_PI/6)): " << cos((M_PI/6)) << endl << endl;

	cout << "a->cos_ud((M_PI/6) + M_PI_2): " << a->cos_ud((M_PI/6) + M_PI_2) << endl;
	cout << "cos((M_PI/6) + M_PI_2): " << cos((M_PI/6) + M_PI_2) << endl << endl;

	cout << "a->cos_ud((M_PI/6) + M_PI): " << a->cos_ud((M_PI/6) + M_PI) << endl;
	cout << "cos((M_PI/6) + M_PI): " << cos((M_PI/6) + M_PI) << endl << endl;

	cout << "a->cos_ud((M_PI/6) + M_PI_2 + M_PI): " << a->cos_ud((M_PI/6) + M_PI_2 + M_PI) << endl;
	cout << "cos((M_PI/6) + M_PI_2 + M_PI): " << cos((M_PI/6) + M_PI_2 + M_PI) << endl << endl << endl;

	cout << "a->cos_ud((M_PI/6)): " << a->cos_ud((M_PI/6)) << endl;
	cout << "cos((M_PI/6)): " << cos((M_PI/6)) << endl << endl;

	cout << "a->cos_ud((M_PI/6) + M_PI_2): " << a->cos_ud((M_PI/6) + M_PI_2) << endl;
	cout << "cos((M_PI/6) + M_PI_2): " << cos((M_PI/6) + M_PI_2) << endl << endl;

	cout << "a->cos_ud((M_PI/6) + M_PI): " << a->cos_ud((M_PI/6) + M_PI) << endl;
	cout << "cos((M_PI/6) + M_PI): " << cos((M_PI/6) + M_PI) << endl << endl;

	cout << "a->cos_ud((M_PI/6) + M_PI_2 + M_PI): " << a->cos_ud((M_PI/6) + M_PI_2 + M_PI) << endl;
	cout << "cos((M_PI/6) + M_PI_2 + M_PI): " << cos((M_PI/6) + M_PI_2 + M_PI) << endl << endl << endl;


	cout << "a->tanf_ud((M_PI/6)): " << a->tanf_ud((M_PI/6)) << endl;
	cout << "tanf((M_PI/6)): " << tanf((M_PI/6)) << endl << endl;

	cout << "a->tanf_ud((M_PI/6) + M_PI_2): " << a->tanf_ud((M_PI/6) + M_PI_2) << endl;
	cout << "tanf((M_PI/6) + M_PI_2): " << tanf((M_PI/6) + M_PI_2) << endl << endl;

	cout << "a->tanf_ud((M_PI/6) + M_PI): " << a->tanf_ud((M_PI/6) + M_PI) << endl;
	cout << "tanf((M_PI/6) + M_PI): " << tanf((M_PI/6) + M_PI) << endl << endl;

	cout << "a->tanf_ud((M_PI/6) + M_PI_2 + M_PI): " << a->tanf_ud((M_PI/6) + M_PI_2 + M_PI) << endl;
	cout << "tanf((M_PI/6) + M_PI_2 + M_PI): " << tanf((M_PI/6) + M_PI_2 + M_PI) << endl << endl << endl;

	cout << "a->tanf_ud((M_PI/6)): " << a->tanf_ud((M_PI/6)) << endl;
	cout << "tanf((M_PI/6)): " << tanf((M_PI/6)) << endl << endl;

	cout << "a->tanf_ud((M_PI/6) + M_PI_2): " << a->tanf_ud((M_PI/6) + M_PI_2) << endl;
	cout << "tanf((M_PI/6) + M_PI_2): " << tanf((M_PI/6) + M_PI_2) << endl << endl;

	cout << "a->tanf_ud((M_PI/6) + M_PI): " << a->tanf_ud((M_PI/6) + M_PI) << endl;
	cout << "tanf((M_PI/6) + M_PI): " << tanf((M_PI/6) + M_PI) << endl << endl;

	cout << "a->tanf_ud((M_PI/6) + M_PI_2 + M_PI): " << a->tanf_ud((M_PI/6) + M_PI_2 + M_PI) << endl;
	cout << "tanf((M_PI/6) + M_PI_2 + M_PI): " << tanf((M_PI/6) + M_PI_2 + M_PI) << endl << endl << endl;*/


	float soma = 0;
	long double inicio = 0;
	long double diff = M_PI * 2 / (N * 10);
	float res;

	cout << "Teste de desempenho, das funções da math_ud,  em relação às funções implementadas na math." << endl;
	// TESTE DA SIN
	gettimeofday(&tv, &tz);
	res = tv.tv_usec + tv.tv_sec * 1000000;
	for(int k = 0; k < 100; k++) {
		for(int i = 0; i < N * 10; i++) {
			//soma += a->sin_ud(((float) inicio + diff));
			soma += sin(((float) i));
			inicio += diff;
		}
		inicio = 0;
	}
	gettimeofday(&tv, &tz);
	float tempo_sin = ((tv.tv_sec * 1000000 + tv.tv_usec) - res) / 1000;
	/////////////////////////


	// TESTE DA SINUD
	gettimeofday(&tv, &tz);
	inicio = 0;
	res = tv.tv_usec + tv.tv_sec * 1000000;
	for(int k = 0; k < 100; k++) {
		for(int i = 0; i < N * 10; i++) {
			soma += a->sin_ud(((float) inicio + diff));
			//soma += sin(((float) i));
			inicio += diff;
		}
		inicio = 0;
	}
	gettimeofday(&tv, &tz);
	float tempo_sin_ud = ((tv.tv_sec * 1000000 + tv.tv_usec) - res) / 1000;
	float percent = 100 * (tempo_sin_ud / tempo_sin);
	printf("sin_ud: %.2f%% do tempo da sin.\n", percent);
	/////////////////////////
	

	// TESTE DA COS
	gettimeofday(&tv, &tz);
	inicio = 0;
	res = tv.tv_usec + tv.tv_sec * 1000000;
	for(int k = 0; k < 100; k++) {
		for(int i = 0; i < N * 10; i++) {
			//soma += a->sin_ud(((float) inicio + diff));
			soma += cos(((float) i));
			inicio += diff;
		}
		inicio = 0;
	}
	gettimeofday(&tv, &tz);
	float tempo_cos = ((tv.tv_sec * 1000000 + tv.tv_usec) - res) / 1000;
	/////////////////////////


	// TESTE DA COSUD
	gettimeofday(&tv, &tz);
	inicio = 0;
	res = tv.tv_usec + tv.tv_sec * 1000000;
	for(int k = 0; k < 100; k++) {
		for(int i = 0; i < N * 10; i++) {
			soma += a->cos_ud(((float) inicio + diff));
			//soma += sin(((float) i));
			inicio += diff;
		}
		inicio = 0;
	}
	gettimeofday(&tv, &tz);
	float tempo_cos_ud = ((tv.tv_sec * 1000000 + tv.tv_usec) - res) / 1000;
	percent = 100 * (tempo_cos_ud / tempo_cos);
	printf("cos_ud: %.2f%% do tempo da cos.\n", percent);

	/////////////////////////
	

	
	// TESTE DA TANF
	gettimeofday(&tv, &tz);
	inicio = 0;
	res = tv.tv_usec + tv.tv_sec * 1000000;
	for(int k = 0; k < 100; k++) {
		for(int i = 0; i < N * 10; i++) {
			//soma += a->sin_ud(((float) inicio + diff));
			soma += tanf(((float) i));
			inicio += diff;
		}
		inicio = 0;
	}
	gettimeofday(&tv, &tz);
	float tempo_tanf = ((tv.tv_sec * 1000000 + tv.tv_usec) - res) / 1000;
	/////////////////////////


	// TESTE DA TANFiUD
	gettimeofday(&tv, &tz);
	inicio = 0;
	res = tv.tv_usec + tv.tv_sec * 1000000;
	for(int k = 0; k < 100; k++) {
		for(int i = 0; i < N * 10; i++) {
			soma += a->tanf_ud(((float) inicio + diff));
			//soma += sin(((float) i));
			inicio += diff;
		}
		inicio = 0;
	}
	gettimeofday(&tv, &tz);
	float tempo_tanf_ud = ((tv.tv_sec * 1000000 + tv.tv_usec) - res) / 1000;
	percent = 100 * (tempo_tanf_ud / tempo_tanf);
	printf("tanf_ud: %.2f%% do tempo da tanf.\n", percent);
	/////////////////////////
	
	// TESTE DA ATANF
	gettimeofday(&tv, &tz);
	inicio = 0;
	res = tv.tv_usec + tv.tv_sec * 1000000;
	for(int k = 0; k < 100; k++) {
		for(int i = 0; i < N * 10; i++) {
			//soma += a->sin_ud(((float) inicio + diff));
			soma += atanf(((float) i));
			inicio += diff;
		}
		inicio = 0;
	}
	gettimeofday(&tv, &tz);
	float tempo_atanf = ((tv.tv_sec * 1000000 + tv.tv_usec) - res) / 1000;
	/////////////////////////


	// TESTE DA TANFUD
	gettimeofday(&tv, &tz);
	inicio = 0;
	res = tv.tv_usec + tv.tv_sec * 1000000;
	for(int k = 0; k < 100; k++) {
		for(int i = 0; i < N * 10; i++) {
			soma += a->atanf_ud(((float) inicio + diff));
			//soma += sin(((float) i));
			inicio += diff;
		}
		inicio = 0;
	}
	gettimeofday(&tv, &tz);
	float tempo_atanf_ud = ((tv.tv_sec * 1000000 + tv.tv_usec) - res) / 1000;
	percent = 100 * (tempo_atanf_ud / tempo_atanf);
	printf("tanf_ud: %.2f%% do tempo da atanf.\n", percent);
	/////////////////////////
	
	
	cout << "Ignore esta linha: " << soma << endl;

	for(int i = -10; i <= 10; i++) 
		cout << i << ": " << atanf((float)i) << " " << a->atanf_ud((float)i) << endl;
	
	return 0;
}
