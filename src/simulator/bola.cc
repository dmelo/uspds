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

	src/simulator/bola.cc
*/

#include"bola.h"
#include"robo.h"
#include<math.h>

#include<iostream>

using namespace std;

bola::bola() : objeto() {
	setMassa(BOLA_MASSA);
	setRaio(BOLA_RAIO);
}

bola::bola(const float x, const float y, const vetor2d *velocidade, const vetor2d *forca_resultante): objeto(x, y, velocidade, forca_resultante) {
	setMassa(BOLA_MASSA);
	setRaio(BOLA_RAIO);
}

bool bola::setRaio(float r) {
	if(r > 0) {
		this->raio = r;
		return true;
	}

	return false;
}

bool bola::colisao_campo(campo *c) {
	bool colidiu = false;

	for(int i = 0; i < CAMPO_N_PONTOS; i++) {
		int a = i;
		int b = (i + 1) % CAMPO_N_PONTOS;

		if(colisao_bola_segmento(getX(), getY(), c->getX(a), c->getY(a), c->getX(b), c->getY(b)) == true) {
			vetor2d forca_r = getVelocidade().decompor(c->getA(a));

			forca_r.setAng(forca_r.getAng() + M_PI);
			/*if(2 * M_PI == forca_r.getAng())
				cout << "deu igual" << endl;
			else
				cout << "desiguais... :(" << endl;*/
			if(objeto::angcmp(forca_r.getAng(), c->getA(a)) == 0) {
				colidiu = true;
				forca_r = forca_r * 2 * BOLA_CAMPO_ELASTICIDADE * BOLA_MASSA / TEMPO_POR_QUADRO;
				add_forca_externa(forca_r);
			}
		}
	}

	return colidiu;
}

float bola::corrigir_trajetoria(float tempo, float x_a, float y_a, float x_b, float y_b) {
	float n_x, n_y;
	float ax, ay;
	float ang_segmento, ang_bola, novo_ang;
	n_x = preverX(tempo);
	n_y = preverY(tempo);

	if(forca_resultante != NULL) {
		ax = forca_resultante->getX() / massa;
		ay = forca_resultante->getY() / massa;
	}
	else {
		ax = ay = 0;
	}

	ang_bola = velocidade->getAng();
	if(x_a == x_b)
		ang_segmento = M_PI_2;
	else
		ang_segmento = atanf(fabs(y_a - y_b) / fabs(x_a - x_b));

	novo_ang = (2 * ang_segmento) - ang_bola;
	this->nova_velocidade = (vetor2d *) velocidade;
	this->nova_forca_resultante = (vetor2d *)forca_resultante;
	if(colisao_b_s == true)
		novo_ang += M_PI;
	if(novo_ang > (2 * M_PI))
		novo_ang -= 2 * M_PI;
	nova_velocidade->setAng(novo_ang);
	
	novo_x = n_x + (nova_velocidade->getX() * (TEMPO_POR_QUADRO - tempo)) + ((ax * (TEMPO_POR_QUADRO - tempo) * (TEMPO_POR_QUADRO - tempo)) / 2);
	novo_y = n_y + (nova_velocidade->getY() * (TEMPO_POR_QUADRO - tempo)) + ((ay * (TEMPO_POR_QUADRO - tempo) * (TEMPO_POR_QUADRO - tempo)) / 2);
	colisao_b_s = true;

	return 1;
}

bool bola::colisao_robo(robo r) {
	float dist_real = objeto::distancia(getX(), getY(), r.getX(), r.getY());
	float dist_minima_necessaria = BOLA_RAIO + (sqrtf(2) * ROBO_ARESTA / 2);
	float ang_limite = atan2f(ROBO_ARESTA / 2, (ROBO_ARESTA / 2) + BOLA_RAIO);

	if(dist_minima_necessaria + CST_ERRO < dist_real)
		return false;
	// talvez ele tenha colidido.
	float ang_coli = atan2f(getY() - r.getY(), getX() - r.getX());
	ang_coli -= r.getAng();
	ang_coli = objeto::padronizar_angulo_2_pi(ang_coli);
	if(ang_coli > M_PI)
		ang_coli = (2 * M_PI) - ang_coli;
	if(ang_coli > M_PI_2)
		ang_coli = M_PI - ang_coli;
	if(ang_coli > M_PI_4)
		ang_coli = M_PI_2 - ang_coli;
	
	float ang_vr;
	if(ang_coli < ang_limite) { // pode ter colidido com a aresta
		float dist = ((ROBO_ARESTA / 2) + BOLA_RAIO) / cos(ang_coli);
		if(dist + (2 * CST_ERRO) < dist_real)
			return false;
		// colidiu com a aresta.
		int lado = r.get_lado(getX(), getY());
		ang_vr = objeto::padronizar_angulo_2_pi(r.getAng() + (lado * M_PI_2));
		float vr_x, vr_y;
		r.ponto_borda(&vr_x, &vr_y, ang_vr);

		float vb_x = getX() - ((vr_x - r.getX()) * BOLA_RAIO / (ROBO_ARESTA / 2));
		float vb_y = getY() - ((vr_y - r.getY()) * BOLA_RAIO / (ROBO_ARESTA / 2));
		float ang_colisao = atan2f(getY() - vb_y, getX() - vb_x);
	}
	else {
		float *px = (float *) new float[4];
		float *py = (float *) new float[4];

		r.get_pontos(&px, &py);
		int i_menor = 0;
		float menor = objeto::distancia(px[0], py[0], getX(), getY());
		float aux;
		for(int i = 1; i < 4; i++) {
			if((aux = objeto::distancia(px[i], py[i], getX(), getY())) < menor) {
				menor = aux;
				i_menor = i;
			}
		}
		float dist = menor;
		if((dist - CST_ERRO > BOLA_RAIO)||(dist + CST_ERRO < BOLA_RAIO)) {
			delete []px;
			delete []py;
			return false;
		}
		ang_vr = atan2f(py[i_menor] - getY(), px[i_menor] - getX());
		float ang_colisao = objeto::padronizar_angulo_pi_sobre_2((r.getAng() - M_PI_4) + (i_menor * M_PI_2));
		delete []px;
		delete []py;
	}
	vetor2d vf1, vf2;
	vetor2d v1 = r.getVelocidade().decompor(ang_vr);
	vetor2d v2 = getVelocidade().decompor(ang_vr);
	
	float dista = objeto::distancia(r.getX() + v1.getX(), r.getY() + v1.getY(), getX() + v2.getX(), getY() + v2.getY());
	float distb = objeto::distancia(r.getX() + v2.getX(), r.getY() + v2.getY(), getX() + v1.getX(), getY() + v1.getY());
	if(dista > distb)
		return false;


	objeto::colisao_elastica(ROBO_MASSA, v1, BOLA_MASSA, v2, &vf1, &vf2);
	
	vf2 = vf2 - v2;
	vetor2d ff2 = vf2 * BOLA_ROBO_ELASTICIDADE * BOLA_MASSA / TEMPO_POR_QUADRO;

	add_forca_externa(ff2);

	return true;
}


float bola::preverX(float tempo) {
	float X, ax;
	if(forca_resultante != NULL)
		ax = forca_resultante->getX() / massa;
	else
		ax = 0;

	if(velocidade != NULL)
		X = x + (velocidade->getX() * tempo) + ((ax * tempo * tempo) / 2);
	else
		X = x;
	return X;
}

float bola::preverY(float tempo) {
	float Y, ay;

	if(forca_resultante != NULL)
		ay = forca_resultante->getY() / massa;
	else
		ay = 0;
	
	if(velocidade != NULL)
		Y = y + (velocidade->getY() * tempo) + ((ay * tempo * tempo) / 2);
	else
		Y = y;

	return Y;
}

bool bola::colisao_bola_segmento(float bola_x, float bola_y, float a_x, float a_y, float b_x, float b_y) {
	float dab, dbolaa, dbolab, a, b, c, aux;
	a = dab = sqrtf(((a_x - b_x)*(a_x - b_x))+((a_y - b_y)*(a_y - b_y)));
	b = dbolaa = sqrtf(((a_x - bola_x)*(a_x - bola_x))+((a_y - bola_y)*(a_y - bola_y)));
	c = dbolab = sqrtf(((bola_x - b_x)*(bola_x - b_x))+((bola_y - b_y)*(bola_y - b_y)));

	if((b > a) && (b > c)) {
		aux = a;
		a = b;
		b = aux;
	}

	if((c > a) && (c > b)) {
		aux = a;
		a = c;
		c = aux;
	}

	if((a <= sqrtf((b * b) + (c * c)))||((dab > dbolaa)&&(dab > dbolab))) {
		// distancia bola reta.
		float area_2 = fabs(bola_x * a_y) + fabs(bola_y * b_x) + fabs(b_y * a_x) - fabs(a_y * b_x) - fabs(bola_y * a_x) - fabs(bola_x * b_y);
		float d;
		
		if(dab != 0)
			d = area_2 / dab;
		else
			d = area_2 / 0.0001;

		d = fabs(d);
		if(d <= BOLA_RAIO + CST_ERRO) {
			return true;
		}
	}
	else {
		// distancia bola extremidade.
		if(dbolaa <= BOLA_RAIO + CST_ERRO)
			return true;
		if(dbolab <= BOLA_RAIO + CST_ERRO)
			return true;
	}

	return false;
}



bool bola::calc_forca() {
	vetor2d resistencia_ar;
	vetor2d resistencia_do_solo;

	// fórmula para resistência do ar.
	// Fr = 1/2 * p * Cx * A * v²
	resistencia_ar.setModulo(0.5 * K_DENSIDADE_DO_AR * K_COEFICIENTE_DE_ARRASTO_ESFERA * (M_PI * powf(BOLA_RAIO, 2)) * powf(getVelocidade().getModulo(), 2));
	resistencia_ar.setAng(getVelocidade().getAng() + M_PI);

	//fómula para atrito com o solo.
	// Fat = K(m*g) / (1 + K)
	if(getVelocidade().getModulo() > CST_ERRO) {
		resistencia_do_solo.setModulo(BOLA_RESISTENCIA_ROLAGEM * BOLA_MASSA * K_GRAVIDADE);
		//resistencia_do_solo.setModulo(K_FATOR_GEOMETRICO_ESFERA * BOLA_MASSA * K_GRAVIDADE / (1 + K_FATOR_GEOMETRICO_ESFERA));
	}
	else 
		resistencia_do_solo.setModulo(0);
	resistencia_do_solo.setAng(getVelocidade().getAng() + M_PI);

	*nova_forca_resultante = get_forca_externa() + resistencia_ar + resistencia_do_solo;


	return true;
}

bool bola::calc_velocidade() {
	if(nova_forca_resultante != NULL)
		*nova_velocidade = getVelocidade() + ((*nova_forca_resultante / BOLA_MASSA) * TEMPO_POR_QUADRO);
	else
		*nova_velocidade = getVelocidade();

	return true;
}

bool bola::calc_atributos(campo *c, int n_robos_por_time, robo *time1[N_JOGADORES_POR_TIME], robo *time2[N_JOGADORES_POR_TIME]) {
	novo_x = 0;
	novo_y = 0;

	int n_collision = 0;
	
	restart_forca_externa();

	for(int i = 0; i < n_robos_por_time; i++) {
	    if(colisao_robo(*time1[i]))
		n_collision++;
	    if(colisao_robo(*time2[i]))
		n_collision++;
	}
	if(colisao_campo(c)) n_collision++;

	calc_forca();
	calc_velocidade();
	calc_deslocamento();


	end_forca_externa();

	if(n_collision) return true;
	return false;
}

bool bola::calc_deslocamento() {
	novo_x = getX() + (nova_velocidade->getX() * TEMPO_POR_QUADRO);
	novo_y = getY() + (nova_velocidade->getY() * TEMPO_POR_QUADRO);

	return true;
}

bool bola::atualizar_atributos() {
	x = novo_x;
	y = novo_y;
	*velocidade = *nova_velocidade;
	*forca_resultante = *nova_forca_resultante;

	return true;
}

bool bola::prever() {
	novo_x = preverX(TEMPO_POR_QUADRO);
	novo_y = preverY(TEMPO_POR_QUADRO);

	return true;
}
