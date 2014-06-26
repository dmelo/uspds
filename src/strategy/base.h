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

	src/base/base.h
*/

#ifndef BASE_H
#define BASE_H

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include"../lib/parametros.h"
#include"../lib/objeto.h"
#include"../lib/vetor2d.h"
#include"../lib/res_sistema.h"

#define FORCA_PADRAO 50 // N.
#define K_REPULSAO_ROBO_ADVERSARIO 0.5
#define K_REPULSAO_ROBO_COMPANHEIRO 0.4
#define K_REPULSAO_ROBO_COMPANHEIRO_ATACANTE 0.7
#define K_ATRACAO_PONTO 90
#define K_ATRACAO_DEFESA 60
#define K_FAIXA_GOLEIRO ROBO_ARESTA
#define K_FAIXA_DEFESA_1 (0.15 + (ROBO_ARESTA / 2))
#define K_FAIXA_DEFESA_2 (CAMPO_LARGURA / 4)
#define K_FAIXA_TAMANHO 0.05
#define K_DIST_BOLA_P_ATRACAO (ROBO_ARESTA / 2)
#define K_DIST_PROXIMA 0.1
#define K_DIST_ACEITAVEL 0.02

using namespace std;

class base {
	public:
		base(int team_number);
		void conct();
		bool set_team_number(unsigned short int tn);
		unsigned short int get_team_number();
		bool set_hostname(char *nh);
		bool set_vel(int robot_number, float nve, float nvd);
		bool set_pa(int robot_number, float x, float y, float a);
		bool set_pb(int robot_number, float x, float y);
		bool set_b(float x, float y);
		bool set_gol_a(float x, float y);
		bool set_gol_b(float x, float y);
		float get_meio_campo_x();
		float get_bx();
		float get_by();
		float get_vel_e(int robot_number);
		float get_vel_d(int robot_number);
		float get_pax(int robot_number);
		float get_pay(int robot_number);
		float get_paa(int robot_number);
		float get_pbx(int robot_number);
		float get_pby(int robot_number);
		float get_gol_a_x();
		float get_gol_a_y();
		float get_gol_b_x();
		float get_gol_b_y();
		float get_x_goleiro();
		bool snd();
		bool rcv();
		bool bola_na_defesa();

	//protected:
		char *hostname;
		int socketRecv;
		int socketSend;
		struct sockaddr_in serverAddressRecv;
		struct sockaddr_in serverAddressSend;
		struct hostent * hostInfo;
		int team_number;

		float *ve, *vd;
		float bx, by;
		float *pax, *pay, *paa;
		float *pbx, *pby;

		float *mensagem_snd;
		float *mensagem_rcv;

		float gol_a_x, gol_a_y;
		float gol_b_x, gol_b_y;
		float meio_campo_x;
		float x_goleiro;
		double uspds_to_fira_x(float x);
		double uspds_to_fira_y(float y);
		double uspds_to_fira_a(float a);
		float fira_to_uspds_vel(double v);

		int p_es, p_er;

		bool goToVector(int robot_number, vetor2d *vel);
		int m_length;
};

#endif
