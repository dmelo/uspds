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

	src/simulator/robo.cc
*/

#include"robo.h"
#include"bola.h"

robo::robo() : objeto() {
	angulo = 0;

	v_roda_esquerda = 0;
	v_roda_direita = 0;

	nova_v_roda_esquerda = 0;
	nova_v_roda_direita = 0;

	v_desejada_roda_esquerda = 0;
	v_desejada_roda_direita = 0;

	x = 0;
	y = 0;

	velocidade->setAng(angulo);
	forca_resultante->setAng(angulo);
}

robo::robo(const float x, const float y, const float ang) {
	this->x = x;
	this->y = y;

	this->v_roda_esquerda = 0;
	this->v_roda_direita = 0;

	nova_v_roda_esquerda = 0;
	nova_v_roda_direita = 0;

	v_desejada_roda_esquerda = 0;
	v_desejada_roda_direita = 0;

	this->angulo = ang;	
	
	velocidade->setAng(angulo);
	forca_resultante->setAng(angulo);

}

// A ordem dos pontos no vetor é a ordem como os pontos estão distposto no robô. Indo no sentido anti-horário, começando pelo ponto 45 graus a direita do referencial do robô.
void robo::get_pontos(float **px, float **py) {
	float ang = angulo;
	float tam = ROBO_ARESTA * (sqrt((double)2) / 2);

	ang -= M_PI_4;
	for(int i = 0; i < 4; i++) {
		(*px)[i] = (tam * cos(ang)) + x;
		(*py)[i] = (tam * sin(ang)) + y;
		ang += M_PI_2;
	}
}

void robo::getNewPontos(float *px, float *py) {
    float ang = getNewAng();
    float tam = ROBO_ARESTA * (sqrt((double)2) / 2);

    ang -= M_PI_4;
    for(int i = 0; i < 4; i++) {
	px[i] = (tam * cos(ang)) + getNewX();
	py[i] = (tam * sin(ang)) + getNewY();
	ang += M_PI_2;
    }
}


bool robo::calc_forca() {
	float aux_ang = velocidade->getAng() - angulo;
	vetor2d f_atrito_rodas;

	aux_ang = objeto::padronizar_angulo_2_pi(aux_ang);

	float aceleracao_angular_roda_esquerda = aceleracao_roda_esquerda / ROBO_RAIO_RODA;
	float aceleracao_angular_roda_direita = aceleracao_roda_direita / ROBO_RAIO_RODA;

	/*float v_angular_esquerda = v_angular * (ROBO_ARESTA / 2) / ROBO_Rr;
	float v_angular_direita = -v_angular_esquerda;*/

	float v_angular_esquerda = ((-v_angular * (ROBO_ARESTA / 2)) + velocidade->getModulo()) / ROBO_Rr;
	float v_angular_direita = ((v_angular * (ROBO_ARESTA / 2)) + velocidade->getModulo()) / ROBO_Rr;

	double ne, nd;

	if(STRATEGY_TO_SIMULATOR_VOLT) {
	    nova_v_roda_esquerda = ((v_desejada_roda_esquerda * ROBO_Kg * ROBO_Re) / (ROBO_Rp * ROBO_Rm)) - ((v_angular_esquerda * ROBO_Kg * ROBO_Re * ROBO_Re) / (ROBO_Rp * ROBO_Rp * ROBO_Rm)) - (ROBO_Jr * aceleracao_angular_roda_esquerda);

	    ne /= ROBO_Rr;

	    nd = ((v_desejada_roda_direita * ROBO_Kg * ROBO_Re) / (ROBO_Rp * ROBO_Rm)) - ((v_angular_direita * ROBO_Kg * ROBO_Re * ROBO_Re) / (ROBO_Rp * ROBO_Rp * ROBO_Rm)) - (ROBO_Jr * aceleracao_angular_roda_direita);

	    nd /= ROBO_Rr;

	    //if(v_desejada_roda_esquerda < 0) nova_f_roda_esquerda = - ne;
	    //if(v_desejada_roda_direita < 0) nova_f_roda_direita = - nd;


	} else {
	    if(v_desejada_roda_esquerda > ROBO_MAX_VELOCIDADE) v_desejada_roda_esquerda = ROBO_MAX_VELOCIDADE;
	    else if(v_desejada_roda_esquerda < ROBO_MIN_VELOCIDADE) v_desejada_roda_esquerda = ROBO_MIN_VELOCIDADE;
	    if(v_desejada_roda_direita > ROBO_MAX_VELOCIDADE) v_desejada_roda_direita = ROBO_MAX_VELOCIDADE;
	    else if(v_desejada_roda_direita < ROBO_MIN_VELOCIDADE) v_desejada_roda_direita = ROBO_MIN_VELOCIDADE;

	    nova_f_roda_esquerda = ((v_desejada_roda_esquerda - v_roda_esquerda) / TEMPO_POR_QUADRO) * ROBO_MASSA / 2;
	    nova_f_roda_direita = ((v_desejada_roda_direita - v_roda_direita) / TEMPO_POR_QUADRO) * ROBO_MASSA / 2;
	}


	//printf("f_esq: %lf. f_dir: %lf.\n", ne, nd);





	// Adicionando força causada pelos motores.
	nova_forca_resultante->setAng(angulo);
	nova_forca_resultante->setModulo(nova_f_roda_esquerda + nova_f_roda_direita);


	// Adicionando força de atrito causada pelas rodas.
	
	f_atrito_rodas = velocidade->decompor(angulo + M_PI_2);
	f_atrito_rodas.setAng(f_atrito_rodas.getAng() + M_PI);
	f_atrito_rodas.setModulo(f_atrito_rodas.getModulo() * ROBO_MASSA / TEMPO_POR_QUADRO);
	float forca_maxima = ROBO_K_ATRITO_ESTATICO_RODAS * K_GRAVIDADE * ROBO_MASSA;
	if(f_atrito_rodas.getModulo() > forca_maxima)
		f_atrito_rodas.setModulo(forca_maxima);


	*nova_forca_resultante += f_atrito_rodas;
	// Adicionando forças externas.
	if(forca_externa != NULL)
		(*nova_forca_resultante) += get_forca_externa();

	// TORQUE

	// Diferença da força entre as rodas.	
	torque = (nova_f_roda_direita - nova_f_roda_esquerda) * (ROBO_ARESTA / 2);

	// Adicionando torque responsável por forças externas (nada sobrenatual... hehehe)
	torque += get_torque_externo();

	return true;
}

bool robo::calc_velocidade() {
	// roda esquerda.

	*nova_velocidade = (*velocidade) + ((*nova_forca_resultante) * TEMPO_POR_QUADRO / ROBO_MASSA);

	nova_v_angular = v_angular + ((torque / (ROBO_MASSA * pow(ROBO_ARESTA / 2, 2))) * TEMPO_POR_QUADRO);

	nova_v_roda_esquerda = (nova_velocidade->getModulo() * cos(nova_velocidade->getAng() - angulo)) - ((ROBO_ARESTA / 2) * nova_v_angular);
	nova_v_roda_direita = (nova_velocidade->getModulo() * cos(nova_velocidade->getAng() - angulo)) + ((ROBO_ARESTA / 2) * nova_v_angular);

	aceleracao_roda_esquerda = (nova_v_roda_esquerda - v_roda_esquerda) / TEMPO_POR_QUADRO;
	aceleracao_roda_direita = (nova_v_roda_direita - v_roda_direita) / TEMPO_POR_QUADRO;


	return true;
}

bool robo::calc_deslocamento() {
	float dx = cos(nova_velocidade->getAng()) * nova_velocidade->getModulo() * TEMPO_POR_QUADRO;
	float dy = sin(nova_velocidade->getAng()) * nova_velocidade->getModulo() * TEMPO_POR_QUADRO;
	
	novo_angulo = angulo + (TEMPO_POR_QUADRO * nova_v_angular);
	while(novo_angulo < 0)
		novo_angulo += 2 * M_PI;
	while(novo_angulo >= 2 * M_PI)
		novo_angulo -= 2 * M_PI;

	novo_x += x + dx;
	novo_y += y + dy;

	return true;
}

bool robo::calc_atributos(campo *c, float x_bola, float y_bola, vetor2d v_bola, vetor2d f_bola, robo *time1[N_JOGADORES_POR_TIME - 1], robo *time2[N_JOGADORES_POR_TIME]) {

	//zerando atributos de deslocamento.
	novo_angulo = 0;
	novo_x = 0;
	novo_y = 0;
	add_posicao_bola(x_bola, y_bola);
	add_posicao_robo(getX(), getY());

	restart_forca_externa();
	restart_torque_externo();

	int n_collision = 0;

	for(int i = 0; i < N_JOGADORES_POR_TIME - 1; i++) {
		if(colisao_robo_robo(time1[i]))
		    n_collision++;
		if(colisao_robo_robo(time2[i]))
		    n_collision++;
	}
	
	//colisao_robo_robo(time2[N_JOGADORES_POR_TIME - 1]);

	if(colisao_robo_campo(c))
	    n_collision++;
	if(colisao_robo_bola(x_bola, y_bola, v_bola, f_bola))
	    n_collision++;

	calc_forca();
	calc_velocidade();
	calc_deslocamento();
	protecao(x_bola, y_bola, time1, time2);


	end_forca_externa();
	end_torque_externo();

	if(n_collision) return true;
	return false;
}

bool robo::atualizar_atributos() {
	*forca_resultante = *nova_forca_resultante;
	*velocidade = *nova_velocidade;
	v_angular = nova_v_angular;
	v_roda_esquerda = nova_v_roda_esquerda;
	v_roda_direita = nova_v_roda_direita;
	f_roda_esquerda = nova_f_roda_esquerda;
	x = novo_x;
	y = novo_y;
	angulo = novo_angulo;

	return true;
}

bool robo::protecao(float x_bola, float y_bola, robo *time1[N_JOGADORES_POR_TIME - 1], robo *time2[N_JOGADORES_POR_TIME]) {
	if(nova_v_roda_direita > ROBO_MAX_VELOCIDADE)
		nova_v_roda_direita = ROBO_MAX_VELOCIDADE;
	if(nova_v_roda_direita < ROBO_MIN_VELOCIDADE)
		nova_v_roda_direita = ROBO_MIN_VELOCIDADE;
	
	if(nova_v_roda_esquerda > ROBO_MAX_VELOCIDADE)
		nova_v_roda_esquerda = ROBO_MAX_VELOCIDADE;
	if(nova_v_roda_esquerda < ROBO_MIN_VELOCIDADE)
		nova_v_roda_esquerda = ROBO_MIN_VELOCIDADE;
	
	/*if(nova_v_angular > ROBO_MAX_V_ANGULAR)
		nova_v_angular = ROBO_MAX_V_ANGULAR;
	if(nova_v_angular < ROBO_MIN_V_ANGULAR)
		nova_v_angular = ROBO_MIN_V_ANGULAR;*/


	

	

	return true;
}


float robo::getX() {
	return x;
}

float robo::getY() {
	return y;
}

float robo::getVelEsq() {
	return v_roda_esquerda;
}

float robo::getVelDir() {
	return v_roda_direita;
}

float robo::getAngulo() {
	while(angulo >= (2 * M_PI))
		angulo -= 2 * M_PI;
	while(angulo < 0)
		angulo += 2 * M_PI;

	return angulo;
}

bool robo::setVel(float esq, float dir) {
	if(esq > ROBO_MAX_VELOCIDADE)
		esq = ROBO_MAX_VELOCIDADE;
	if(dir > ROBO_MAX_VELOCIDADE)
		dir = ROBO_MAX_VELOCIDADE;
	if(esq < ROBO_MIN_VELOCIDADE)
		esq = ROBO_MIN_VELOCIDADE;
	if(dir < ROBO_MIN_VELOCIDADE)
		dir = ROBO_MIN_VELOCIDADE;

	v_desejada_roda_esquerda = esq;
	v_desejada_roda_direita = dir;

	return true;
}

float robo::colisao_robo_segmento(campo *c, int aresta) {
	return colisao_robo_segmento(c->getX(aresta), c->getY(aresta), c->getX((aresta + 1) % 16), c->getY((aresta + 1) % 16));
}

float robo::colisao_robo_segmento(float ax, float ay, float bx, float by) {
	float area_triag = objeto::area_triangulo(ax, ay, bx, by, getX(), getY());

	area_triag /= objeto::distancia(ax, ay, bx, by);
	area_triag *= 2;
	if(area_triag >= sqrtf(2) * ROBO_ARESTA / 2)
		return -1;

	float dist_pontos = objeto::distancia(ax, ay, bx, by);
	float perim_triag = dist_pontos + objeto::distancia(getX(), getY(), ax, ay) + objeto::distancia(getX(), getY(), bx, by);

	if(perim_triag > 2 * (dist_pontos + (ROBO_ARESTA * sqrtf(2) * 0.5)))
		return -1;

	float ang_relativo = objeto::padronizar_angulo_pi_sobre_2((atan2f(by - ay, bx - ax) + M_PI_2) - getAng());

	if(ang_relativo > M_PI_4)
		ang_relativo = M_PI_2 - ang_relativo;
	float dist_limite = cos(M_PI_4 - ang_relativo) * (ROBO_ARESTA * sqrtf(2) * 0.5);

	if(dist_limite > area_triag)
		return (0.5 * sqrt(2) * ROBO_ARESTA) - area_triag;
	
	
	

	return -1;
}
	

bool robo::colisao_robo_campo(campo *c) { // Seguindo o modelo de uma esfera batendo no campo (com atrito).
	bool colidiu = false;

	for(int i = 0; i < 16; i++) {
		int a = i, b = (i + 1) % 16;
		float dist;

		if((dist = colisao_robo_segmento(c->getX(a), c->getY(a), c->getX(b), c->getY(b))) > 0) {
			novo_x += dist * cos(c->getA(a));
			novo_y += dist * sin(c->getA(a));

			colidiu = true;
		}
	}


	return colidiu;
}

float robo::getAng() {
	while(angulo < 0)
		angulo += 2 * M_PI;
	while(angulo >= 2 * M_PI)
		angulo -= 2 * M_PI;
	
	return angulo;
}

bool robo::add_posicao_robo(float x_robo, float y_robo) {
	for(int i = 0; i < SIZE_STACK - 1; i++) {
		robo_x[i + 1] = robo_x[i];
		robo_y[i + 1] = robo_y[i];
	}
	robo_x[0] = x_robo;
	robo_y[0] = y_robo;

	return true;
}

float robo::getVelocidade_por_posicao() {
	float media_a_x = 0;
	float media_a_y = 0;
	float media_b_x = 0; 
	float media_b_y = 0;

	float d_x, d_y;
	float v_x, v_y;
	float v;
	for(int i = 0; i < (SIZE_STACK / 2) - 1; i++) {
		media_a_x += (robo_x[i + 1] - robo_x[i]);
		media_a_y += (robo_y[i + 1] - robo_y[i]);
	}
	if(SIZE_STACK >= 2) {
		media_a_x /= SIZE_STACK / 2;
		media_a_y /= SIZE_STACK / 2;
	}
		
	for(int i = (SIZE_STACK / 2); i < SIZE_STACK - 1; i++) {
		media_b_x += (robo_x[i + 1] - robo_x[i]);
		media_b_y += (robo_y[i + 1] - robo_y[i]);
	}
	if(SIZE_STACK >= 2) {
		media_a_x /= SIZE_STACK - (SIZE_STACK / 2);
		media_a_y /= SIZE_STACK - (SIZE_STACK / 2);
	}

	d_x = media_a_x - media_b_x;
	d_y = media_a_y - media_b_y;

	v_x = d_x / ((SIZE_STACK / 2) * TEMPO_POR_QUADRO);
	v_y = d_y / ((SIZE_STACK / 2) * TEMPO_POR_QUADRO);

	v = sqrt(pow(v_x, 2) + pow(v_y, 2));

	return v;
}

float robo::getAng_por_posicao() {
	float media_a_x = 0;
	float media_a_y = 0;
	float media_b_x = 0; 
	float media_b_y = 0;

	float d_x, d_y;
	float v_x, v_y;
	float v;
	for(int i = 0; i < (SIZE_STACK / 2) - 1; i++) {
		media_a_x += (robo_x[i + 1] - robo_x[i]);
		media_a_y += (robo_y[i + 1] - robo_y[i]);
	}
	if(SIZE_STACK >= 2) {
		media_a_x /= SIZE_STACK / 2;
		media_a_y /= SIZE_STACK / 2;
	}
		
	for(int i = (SIZE_STACK / 2); i < SIZE_STACK - 1; i++) {
		media_b_x += (robo_x[i + 1] - robo_x[i]);
		media_b_y += (robo_y[i + 1] - robo_y[i]);
	}
	if(SIZE_STACK >= 2) {
		media_a_x /= SIZE_STACK - (SIZE_STACK / 2);
		media_a_y /= SIZE_STACK - (SIZE_STACK / 2);
	}

	/*for(int i = 0; i < SIZE_STACK; i++)
		cout << "robo_x[" << i << ":]  " << robo_x[i];
	cout << endl;
	
	for(int i = 0; i < SIZE_STACK; i++)
		cout << "robo_y[" << i << ":]  " << robo_y[i];
	cout << endl;*/

	d_x = media_a_x - media_b_x;
	d_y = media_a_y - media_b_y;

	return atan2f(d_y, d_x);
}

bool robo::add_posicao_bola(float x_bola, float y_bola) {
	for(int i = 0; i < SIZE_STACK - 1; i++) {
		bola_x[i + 1] = bola_x[i];
		bola_y[i + 1] = bola_y[i];
	}
	bola_x[0] = x_bola;
	bola_y[0] = y_bola;

	return true;
}

bool robo::bola_parada() {
	float area = 0.005 * 0.005;
	float menor_x = bola_x[0], menor_y = bola_y[0], maior_x = bola_x[0], maior_y = bola_y[0];
	for(int i = 1; i < SIZE_STACK; i++) {
		if(menor_x > bola_x[i])
			menor_x = bola_x[i];
		if(maior_x < bola_x[i])
			maior_x = bola_x[i];
		if(menor_y > bola_y[i])
			menor_y = bola_y[i];
		if(maior_y < bola_y[i])
			maior_y = bola_y[i];
	}

	if(sqrt(pow(maior_x - menor_x, 2) + pow(maior_y - menor_y, 2)) <= area)
		return true;
	
	return false;
}

bool robo::colisao_robo_bola(float x_bola, float y_bola, vetor2d v_bola, vetor2d f_bola) {
	float dist_real = objeto::distancia(getX(), getY(), x_bola, y_bola);
	float dist_minima_necessaria = BOLA_RAIO + (sqrtf(2) * ROBO_ARESTA / 2);
	float ang_limite = atan2f(ROBO_ARESTA / 2, (ROBO_ARESTA / 2) + BOLA_RAIO);

	if(dist_minima_necessaria < dist_real)
		return false;
	// talvez ele tenha colidido.
	float ang_coli = atan2f(y_bola - getY(), x_bola - getX());
	ang_coli -= getAng();
	ang_coli = objeto::padronizar_angulo_2_pi(ang_coli);
	if(ang_coli > M_PI)
		ang_coli = (2 * M_PI) - ang_coli;
	if(ang_coli > M_PI_2)
		ang_coli = M_PI - ang_coli;
	if(ang_coli > M_PI_4)
		ang_coli = M_PI_2 - ang_coli;
	
	float ang_vr;
	float vb_x, vb_y;
	if(ang_coli < ang_limite) { // pode ter colidido com a aresta
		float dist = ((ROBO_ARESTA / 2) + BOLA_RAIO) / cos(ang_coli);
		if((dist - CST_ERRO > dist_real)||(dist + CST_ERRO < dist_real))
			return false;
		// colidiu com a aresta.
		int lado = get_lado(x_bola, y_bola);
		ang_vr = objeto::padronizar_angulo_2_pi(getAng() + (lado * M_PI_2));
		float vr_x, vr_y;
		ponto_borda(&vr_x, &vr_y, ang_vr);

		vb_x = x_bola - ((vr_x - getX()) * BOLA_RAIO / (ROBO_ARESTA / 2));
		vb_y = y_bola - ((vr_y - getY()) * BOLA_RAIO / (ROBO_ARESTA / 2));
		float ang_colisao = atan2f(y_bola - vb_y, x_bola - vb_x);
	}
	else {
		/*float *px = (float *) new float[4];
		float *py = (float *) new float[4];*/
		float *px = new float[4];
		float *py = new float[4];

		get_pontos(&px, &py);
		int i_menor = 0;
		float menor = objeto::distancia(px[0], py[0], x_bola, y_bola);
		float aux;
		for(int i = 1; i < 4; i++) {
			if((aux = objeto::distancia(px[i], py[i], x_bola, y_bola)) < menor) {
				menor = aux;
				i_menor = i;
			}
		}
		float dist = menor;
		if((dist - CST_ERRO > dist_real)||(dist + CST_ERRO < dist_real)) {
			delete []px;
			delete []py;

			return false;
		}
		ang_vr = atan2f(py[i_menor] - y_bola, px[i_menor] - x_bola);
		vb_x = px[i_menor];
		vb_y = py[i_menor];
		float ang_colisao = objeto::padronizar_angulo_pi_sobre_2((getAng() - M_PI_4) + (i_menor * M_PI_2));
		delete []px;
		delete []py;
	}
	vetor2d vf1, vf2;
	vetor2d v1 = getVelocidade().decompor(ang_vr);
	vetor2d v2 = v_bola.decompor(ang_vr);

	float dista = objeto::distancia(getX() + v1.getX(), getY() + v1.getY(), x_bola + v2.getX(), y_bola + v2.getY());
	float distb = objeto::distancia(getX() + v2.getX(), getY() + v2.getY(), x_bola + v1.getX(), y_bola + v1.getY());

	if(dista > distb)
		return false;

	objeto::colisao_elastica(ROBO_MASSA, v1, BOLA_MASSA, v2, &vf1, &vf2);

	vf1 = vf1 - v1;
	vetor2d ff1 = vf1 * BOLA_ROBO_ELASTICIDADE * BOLA_MASSA / TEMPO_POR_QUADRO;
	vetor2d fc1;
	float torq;
	get_forca_e_torque(vb_x, vb_y, ff1, &fc1, &torq);
	add_forca_externa(fc1);
	add_torque_externo(torq);

	return true;
}

// A colisão entre os robôs é tratada como colisão entre esferas.

bool robo::colisao_robo_robo(robo *r) {
	float *a_px = new float[4], *a_py = new float[4];
	float *b_px = new float[4], *b_py = new float[4];
	float area_robo = ROBO_ARESTA * ROBO_ARESTA;
	vector<int> arestas_com_colisao;
	int colisions_counter = 0;

	if(objeto::distancia(getX(), getY(), r->getX(), r->getY()) > (sqrt((double)2) * ROBO_ARESTA) + CST_ERRO) {
		delete []a_px;
		delete []a_py;
		delete []b_px;
		delete []b_py;
		return false;
	}
	
	if((getX() == r->getX())&&(getY() == r->getY())) {
		delete []a_px;
		delete []a_py;
		delete []b_px;
		delete []b_py;
		return false;
	}

	get_pontos(&a_px, &a_py);
	
	r->get_pontos(&b_px, &b_py);
	
	// Este modelo nao preve colisoes entre os vertices dos robos.

	for(int i = 0; i < 4; i++) {
		float x_impacto, y_impacto;
		bool colidiu = false;
		if((ponto_pertence(b_px[i], b_py[i]) == true)&&(colisions_counter < 3)) {// verificando se os pontos do outro robo pertencem a este robo.
			x_impacto = b_px[i];
			y_impacto = b_py[i];
			colidiu = true;
		}
		if((r->ponto_pertence(a_px[i], a_px[i]) == true)&&(colisions_counter < 3)) { // verificando se os pontos deste robô pertencem ao ponto do outro robô.
			x_impacto = a_px[i];
			y_impacto = a_px[i];
			colidiu = true;
		}
		

		if(colidiu == true) {
			vetor2d aiv; // robo a, inicial, vertical à colisão.
			vetor2d aih; // robo a, inicial, horizontal à colisão.
			vetor2d biv;
			vetor2d bih;

			vetor2d hma; // horizontal, médio (vetor médio entres os vetores horizontais à colisão).
			vetor2d hmb; // horizontal, médio (vetor médio entres os vetores horizontais à colisão).

			vetor2d af;
	
			vetor2d n_forca;

			float ang_h_colisao; // angulo horizontal à colisão.
			float ang_v_colisao; // angulo vertical à colisão.

			ang_h_colisao = atan2f(r->getY() - getY(), r->getX() - getX());
			ang_v_colisao = objeto::padronizar_angulo_2_pi(ang_h_colisao + M_PI_2);

			aiv = getVelocidade().decompor(ang_v_colisao);
			aih = getVelocidade().decompor(ang_h_colisao);

			biv = r->getVelocidade().decompor(ang_v_colisao);
			bih = r->getVelocidade().decompor(ang_h_colisao);
			
			hma.setModulo((aih.getModulo() + bih.getModulo()) / 2);
			if(bih.getModulo() == 0)
				hma.setAng(aih.getAng());
			else
				hma.setAng(bih.getAng());


			af = (hma * ROBO_ROBO_ELASTICIDADE) + aiv;

			// o vetor af é o vetor velocidade que o robô deverá ter após a colisão.

			n_forca = af - getVelocidade();
			n_forca = n_forca * ROBO_MASSA / TEMPO_POR_QUADRO;
			add_forca_externa(n_forca);
			
			af.setModulo(ROBO_ROBO_AFASTAMENTO);
			af.setAng(atan2f(getY() - r->getY(), getX() - r->getX()));
			novo_x += 2 * af.getX();
			novo_y += 2 * af.getY();

			delete []a_px;
			delete []a_py;
			delete []b_px;
			delete []b_py;

			return true;
		}
	}
	delete []a_px;
	delete []a_py;
	delete []b_px;
	delete []b_py;

	return false;
}

bool robo::ponto_pertence(float a_x, float a_y) {
	float dist_centro = objeto::distancia(a_x, a_y, getX(), getY());

	if(dist_centro <= ROBO_ARESTA / 2)
		return true;
	if(dist_centro > (ROBO_ARESTA * sqrt((double)2) / 2))
		return false;
	
	float ang_c_ponto = fabs(atan2f(a_y - getY(), a_x - getX()) - getAng());

	/*while(ang_c_ponto < 0)
		ang_c_ponto += M_PI_2;
	while(ang_c_ponto >= M_PI_2)
		ang_c_ponto -= M_PI_2;
	
	if(ang_c_ponto >= M_PI_4)
		ang_c_ponto = fabs(M_PI_2 - ang_c_ponto);
	
	float dist_limite = ROBO_ARESTA / (2 * cos(ang_c_ponto));

	if(dist_limite >= dist_centro)
		return true;*/
	float borda_x, borda_y;
	ponto_borda(&borda_x, &borda_y, ang_c_ponto);
	float dist_p_borda = objeto::distancia(borda_x, borda_y, getX(), getY());
	if(dist_p_borda >= dist_centro)
		return true;
	
	return false;
}

float robo::distancia_ponto_interno_robo(float a_x, float a_y) {
	if(ponto_pertence(a_x, a_y) == false)
		return -1;
	
	float *b_x = new float[4];
	float *b_y = new float[4];
	float menor_distancia =  ROBO_ARESTA;

	get_pontos(&b_x, &b_y);
	for(int i = 0; i < 4; i++) {
		int a = i;
		int b = (i + 1) % 4;
		float area = objeto::area_triangulo(a_x, a_y, b_x[a], b_y[a], b_x[b], b_y[b]);
		float dist = (area * 2) / objeto::distancia(b_x[a], b_y[a], b_x[b], b_y[b]);

		if(dist < menor_distancia)
			menor_distancia = dist;
	}

	delete []b_x;
	delete []b_y;

	return menor_distancia;
}

bool robo::get_forca_e_torque(float x_i, float y_i, vetor2d forca_aplicada, vetor2d *forca_centro, float *torque) {
	vetor2d fh; // decomposta horizontal.
	vetor2d fv; // decomposta vertical.

	fh = forca_aplicada.decompor(atan2f(y_i - getY(), x_i - getX()));
	fv = forca_aplicada.decompor(atan2f(y_i - getY(), x_i - getX()) + M_PI_2);

	*forca_centro = fh;

	if(objeto::padronizar_angulo_2_pi(forca_aplicada.getAng() + M_PI_2) == fv.getAng())
		*torque = fv.getModulo() * objeto::distancia(getX(), getY(), x_i, y_i);
	else
		*torque = (-1) * fv.getModulo() * objeto::distancia(getX(), getY(), x_i, y_i);
	
	return true;
}

float robo::dist_centro_borda(float angulo_d) {
	float aux_ang = objeto::padronizar_angulo_pi_sobre_2(angulo_d - getAng());
	float dist;

	if(aux_ang > M_PI_4)
		aux_ang = M_PI_2 - aux_ang;
	dist = ROBO_ARESTA / (2 * cos(aux_ang));

	return dist;
}

bool robo::ponto_borda(float *x, float *y, float angulo) {
	float dist = dist_centro_borda(angulo);

	*x = getX() + (cos(angulo) * dist);
	*y = getY() + (sin(angulo) * dist);

	return true;
}

vetor2d robo::velocidade_ponto_borda(float angulo) {
	vetor2d vang;
	vang.setAng(getAng() + M_PI_2);
	float dist = dist_centro_borda(angulo);

	vang.setModulo(dist * vang.getModulo());

	return vang + getVelocidade();
}

float robo::get_v_angular() {
	return v_angular;
}

int robo::get_lado(float fx, float fy) {
	int a = 0;
	int b = 1;
	int i_menor = 0;

	float *px = (float *) new float[4];
	float *py = (float *) new float[4];
	get_pontos(&px, &py);

	float menor_dist = objeto::distancia(px[a], py[a], fx, fy) + objeto::distancia(px[b], py[b], fx, fy);
	for(int i = 1; i < 4; i++) {
		a = i;
		b = (i + 1) % 4;

		float aux = objeto::distancia(px[a], py[a], fx, fy) + objeto::distancia(px[b], py[b], fx, fy);
		if(aux < menor_dist) {
			menor_dist = aux;
			i_menor = a;
		}
	}

	delete []px;
	delete []py;

	return i_menor;
}

float robo::getNewAng() {
    return novo_angulo;
}

void robo::setAng(float a) {
    angulo = a;
}
