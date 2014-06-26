/**
	USPDroidsSimulator
	(C) 2007  Diogo Oliveira de Melo
	(C) 2007  Benghur Gonçalvez

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

	src/base/base.cc
*/

#include"base.h"

base::base(int team_number) {
	set_team_number(team_number);
	ve = (float *) new float[N_JOGADORES_POR_TIME];
	vd = (float *) new float[N_JOGADORES_POR_TIME];

	pax = (float *) new float [N_JOGADORES_POR_TIME];
	pay = (float *) new float [N_JOGADORES_POR_TIME];
	paa = (float *) new float [N_JOGADORES_POR_TIME];
	pbx = (float *) new float [N_JOGADORES_POR_TIME];
	pby = (float *) new float [N_JOGADORES_POR_TIME];

	for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
		ve[i] = 0;
		vd[i] = 0;

		pax[i] = 0;
		pay[i] = 0;
		paa[i] = 0;
		pbx[i] = 0;
		pby[i] = 0;
	}

	mensagem_snd = (float *) new float[2 * N_JOGADORES_POR_TIME];
	mensagem_rcv = (float *) new float[2 + (3 * N_JOGADORES_POR_TIME) + (2 * N_JOGADORES_POR_TIME)];

	if(get_team_number() == 1) {
		set_gol_a(0, CAMPO_ALTURA / 2);
		set_gol_b(CAMPO_LARGURA + (2 * CAMPO_GOL_PROFUNDIDADE), CAMPO_ALTURA / 2);
	}
	else {
		set_gol_a(CAMPO_LARGURA + (2 * CAMPO_GOL_PROFUNDIDADE), CAMPO_ALTURA / 2);
		set_gol_b(0, CAMPO_ALTURA / 2);
	}

	meio_campo_x = (CAMPO_LARGURA + (2 * CAMPO_GOL_PROFUNDIDADE)) / 2;
	if(get_team_number() == 1)
		x_goleiro = CAMPO_GOL_PROFUNDIDADE + K_FAIXA_GOLEIRO;
	else
		x_goleiro = CAMPO_LARGURA + CAMPO_GOL_PROFUNDIDADE - K_FAIXA_GOLEIRO;
}

void base::conct() {
	cout << "tentando conexao com: " << hostname << endl;
	hostInfo = gethostbyname(hostname);
	if(hostInfo == NULL) {
		cerr << "erro: problemas para encontrar o servidor." << endl;
		exit(1);
	}

	socketRecv = socket(AF_INET, SOCK_STREAM, 0);
	if(socketRecv < 0) {
		cerr << "erro: não foi possível criar o socket de recepção de dados." << endl;
		exit(1);
	}
	serverAddressRecv.sin_family = hostInfo->h_addrtype;
	memcpy((char *) &serverAddressRecv.sin_addr.s_addr, hostInfo->h_addr_list[0], hostInfo->h_length);
	serverAddressRecv.sin_port = htons(p_er);
	
	if(connect(socketRecv, (struct sockaddr *) &serverAddressRecv, sizeof(serverAddressRecv)) < 0) {
		cerr << "base: conct: error: cannot connect to server." << endl;
		exit(1);
	}
	socketSend = socket(AF_INET, SOCK_STREAM, 0);
	if(socketSend < 0) {
		cerr << "erro: não foi possível criar o socket de transmissão de dados." << endl;
		exit(1);
	}
	serverAddressSend.sin_family = hostInfo->h_addrtype;
	memcpy((char *) &serverAddressSend.sin_addr.s_addr, hostInfo->h_addr_list[0], hostInfo->h_length);
	serverAddressSend.sin_port = htons(p_es);
	if(connect(socketSend, (struct sockaddr *) &serverAddressSend, sizeof(serverAddressSend)) < 0) {
		cerr << "erro: não foi possével alocar um grupo de portas para este jogo." << endl;
		exit(1);
	}
}

bool base::set_team_number(unsigned short int tn) {
	if((tn >= 1)&&(tn <= 2)) {
		team_number = tn;
		return true;
	}
	
	return false;
}

unsigned short int base::get_team_number() {
	return team_number;
}

bool base::set_vel(int robot_number, float nve, float nvd) {
	if(nve > ROBO_MAX_VELOCIDADE)
		ve[robot_number] = ROBO_MAX_VELOCIDADE;
	else if(nve < ROBO_MIN_VELOCIDADE)
		ve[robot_number] = ROBO_MIN_VELOCIDADE;
	else
		ve[robot_number] = nve;
	
	if(nvd > ROBO_MAX_VELOCIDADE)
		vd[robot_number] = ROBO_MAX_VELOCIDADE;
	else if(nvd < ROBO_MIN_VELOCIDADE)
		vd[robot_number] = ROBO_MIN_VELOCIDADE;
	else
		vd[robot_number] = nvd;

	return true;
}

bool base::set_pa(int robot_number, float x, float y, float a) {
	if((robot_number < 0)||(robot_number >= N_JOGADORES_POR_TIME))
		return false;
	if(x < CAMPO_X_MIN)
		return false;
	else if(x > CAMPO_X_MAX)
		return false;
	else
		pax[robot_number] = x;

	if(y < CAMPO_Y_MIN)
		return false;
	else if(y > CAMPO_Y_MAX)
		return false;
	else
		pay[robot_number] = y;

	if(a < 0)
		return false;
	else if(a > 2 * M_PI)
		return false;
	else
		paa[robot_number] = a;
	
	return true;
}

bool base::set_pb(int robot_number, float x, float y) {
	if((robot_number < 0)||(robot_number >= N_JOGADORES_POR_TIME))
		return false;
	if(x < CAMPO_X_MIN)
		return false;
	else if(x > CAMPO_X_MAX)
		return false;
	else
		pbx[robot_number] = x;

	if(y < CAMPO_Y_MIN)
		return false;
	else if(y > CAMPO_Y_MAX)
		return false;
	else
		pby[robot_number] = y;

	return true;
}

bool base::set_b(float x, float y) {
	if(x < CAMPO_X_MIN)
		return false;
	else if(x > CAMPO_X_MAX)
		return false;
	else
		bx = x;

	if(y < CAMPO_Y_MIN)
		return false;
	else if(y > CAMPO_Y_MAX)
		return false;
	else
		by = y;

	return true;
}

float base::get_bx() {
	return bx;
}

float base::get_by() {
	return by;
}

float base::get_vel_e(int robot_number) {
	if((robot_number >= 0)&&(robot_number < N_JOGADORES_POR_TIME))
		return ve[robot_number];
	
	return 1000;
}

float base::get_vel_d(int robot_number) {
	if((robot_number >= 0)&&(robot_number < N_JOGADORES_POR_TIME))
		return vd[robot_number];
	
	return 1000;
}

float base::get_pax(int robot_number) {
	if((robot_number >= 0)&&(robot_number < N_JOGADORES_POR_TIME)) {
		return pax[robot_number];
	}
	
	return -1;
}

float base::get_pay(int robot_number) {
	if((robot_number >= 0)&&(robot_number < N_JOGADORES_POR_TIME))
		return pay[robot_number];
	
	return -1;
}

float base::get_paa(int robot_number) {
	if((robot_number >= 0)&&(robot_number < N_JOGADORES_POR_TIME))
		return paa[robot_number];
	
	return -1;
}

float base::get_pbx(int robot_number) {
	if((robot_number >= 0)&&(robot_number < N_JOGADORES_POR_TIME))
		return pbx[robot_number];
	
	return -1;
}

float base::get_pby(int robot_number) {
	if((robot_number >= 0)&&(robot_number < N_JOGADORES_POR_TIME))
		return pby[robot_number];
	
	return -1;
}

bool base::snd() {
	int tamanho = N_JOGADORES_POR_TIME * 2;
	
	for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
		mensagem_snd[2 * i] = get_vel_e(i);
		mensagem_snd[(2 * i) + 1] = get_vel_d(i);
	}

	if(send(socketSend, mensagem_snd, tamanho * sizeof(float), 0) == -1) {
		return false;
	}
	
	return true;
}

bool base::rcv() {
	int tamanho = 2 + (3 * N_JOGADORES_POR_TIME) + (2 * N_JOGADORES_POR_TIME);

	if(recv(socketRecv, mensagem_rcv, tamanho * sizeof(float), 0) == -1)
		return false;
	// Verifica se é uma mensagem de fim.
	bool fim = true;
	for(int i = 0; i < tamanho; i++) {
	    if(mensagem_rcv[i] != END_FLOAT) {
		fim = false;
		break;
	    }
	}
	if(fim) exit(0);
	//////////////////////////////////////

	if(!set_b(mensagem_rcv[0], mensagem_rcv[1]))
		return false;
	for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
		if(!set_pa(i, mensagem_rcv[2 + (3 * i)], mensagem_rcv[3 + (3 * i)], mensagem_rcv[4 + (3 * i)])) {
			return false;
		}
		if(!set_pb(i, mensagem_rcv[2 + (3 * N_JOGADORES_POR_TIME) + (2 * i)], mensagem_rcv[3 + (3 * N_JOGADORES_POR_TIME) + (2 * i)])) {
			return false;
		}
	}

	return true;
}

bool base::set_hostname(char *nh) {
	int i;
	for(i = 0; nh[i] != '\0'; i++);
	i++;
	hostname = (char *) new char[i];
	strcpy(hostname, nh);

	return true;
}

float base::get_meio_campo_x() {
	return meio_campo_x;
}

bool base::bola_na_defesa() {
	if(get_team_number() == 1) {
		if(get_bx() < get_meio_campo_x())
			return true;
		return false;
	}
	else {
		if(get_bx() < get_meio_campo_x())
			return false;
		return true;
	}
}

bool base::set_gol_a(float x, float y) {
	gol_a_x = x;
	gol_a_y = y;

	return true;
}

bool base::set_gol_b(float x, float y) {
	gol_b_x = x;
	gol_b_y = y;

	return true;
}

float base::get_gol_a_x() {
	return gol_a_x;
}

float base::get_gol_a_y() {
	return gol_a_y;
}

float base::get_gol_b_x() {
	return gol_b_x;
}

float base::get_gol_b_y() {
	return gol_b_y;
}

double base::uspds_to_fira_x(float x) { return (((GRIGHT - GLEFT) * x) / (CAMPO_LARGURA + (2 * CAMPO_GOL_PROFUNDIDADE))) + GLEFT; }
double base::uspds_to_fira_y(float y) { return (((FTOP - FBOT) * y) / CAMPO_ALTURA) + FBOT; }
double base::uspds_to_fira_a(float a) { return (a * 180) / M_PI; }
float base::fira_to_uspds_vel(double v) { return (v / 125) * ROBO_MAX_VELOCIDADE; }

bool base::goToVector(int robot_number, vetor2d *vel) {
	float accuracy = 0.6;
	float arc = 0.5;
	float relative_angle = objeto::padronizar_angulo_2_pi(vel->getAng() - get_paa(robot_number));

	if((relative_angle < accuracy)||((2 * M_PI) - relative_angle < accuracy)) {
		set_vel(robot_number, ROBO_MAX_VELOCIDADE, ROBO_MAX_VELOCIDADE);
		return true;
	}
	if((M_PI + accuracy > relative_angle)&&(M_PI - accuracy < relative_angle)) {
		set_vel(robot_number, ROBO_MIN_VELOCIDADE, ROBO_MIN_VELOCIDADE);
		return true;
	}

	float radius = ((40 - (vel->getModulo()-60)) / 100) * 0.4; // determine the radius by the module of the vector vel.
	if(radius < 0)
		radius = 0;
	if(radius > 0.4)
		radius = 0.4;

	float v_max = ROBO_MAX_VELOCIDADE;
	float v = (v_max * (radius - (ROBO_ARESTA / 2))) / radius + (ROBO_ARESTA / 2);

	if(v > 0) v -= 0.1;
	else v += 0.1;
	
	if((relative_angle < 0)&&(relative_angle < M_PI_2)) {
		set_vel(robot_number, v, v_max);
	} else if((relative_angle > M_PI_2)&&(relative_angle < M_PI)) {
		set_vel(robot_number, -v, -v_max);
	} else if((relative_angle > M_PI)&&(relative_angle < M_PI + M_PI_2)) {
		set_vel(robot_number, -v_max, -v);
	} else {
		set_vel(robot_number, v_max, v);
	}

	return true;
}


/*int main(int argc, char *argv[]) {
	if(argc != 3) {
		cerr << "usage: ./base hostname team_number" << endl;
		exit(1);
	}

	base *cp = new base((int) argv[2][0] - '0');
	cout << "team_number: " << (int) argv[2][0] - '0' << endl;
	cp->set_hostname(argv[1]);
	cp->conct(); // se não conseguir se conectar, ela dá mensagem de erro e sai do programa.
	
	while(true) {
		cp->rcv();
		// MÉTODO DA ESTRATÉGIA
		cp->estrategia();


		cp->snd();

	}

	return 0;
}*/
