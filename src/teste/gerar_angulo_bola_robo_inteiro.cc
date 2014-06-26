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

	src/teste/gerar_angulo_bola_robo_inteiro.cc
*/

#include<iostream>
#include<math.h>
#include"parametros.h"

using namespace std;

int main() {
	float ang = 2 * fabs(atan2f(ROBO_ARESTA/2, (ROBO_ARESTA/2) + BOLA_RAIO) - M_PI_4);

	cout << ang << endl;

	return 0;
}
