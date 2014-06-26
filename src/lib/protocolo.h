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

	src/lib/protocolo.h
*/

/**
 * \file protocolo.h
 * \author Diogo Oliveira de Melo
 * \date 08-02-2007
 */

#ifndef PROTOCOLO_H
#define PROTOCOLO_H
#include"parametros.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<string>

using namespace std;

/**
 * Classe responsável por codificar e decodificar mensagens do protocolo utilizado pelo simulador.
 */

class protocolo {
	public: 
		/**
		 * Codifica uma mensagem que deverá conter as posiçõe e o ângulo de todos os jogadores e a posição da bola.
		 *
		 * \param bx Coordenada X da bola.
		 * \param by Coordenada Y da bola.
		 * \param nJogadores Número de jogadores por time.
		 * \param *tx Vetor que contém as coordenadas do eixo X de todos os jogadores.
		 * \param *ty Vetor que contém as coordenadas do eixo Y de todos os jogadores.
		 * \param *ta Vetor que contém ângulos de todos os jogadores.
		 * \return Retorna a string que contém a mensagem codificada.
		 */
		static string encode(float bx, float by, int nJogadores, float *tx, float *ty, float *ta);
		/**
		 * Codifica uma mensagem que deverá conter as posiçõe e o ângulo de todos os jogadores e a posição da bola.
		 *
		 * \param bx Coordenada X da bola.
		 * \param by Coordenada Y da bola.
		 * \param nJogadores Número de jogadores por time.
		 * \param *tax Vetor que contém as coordenadas do eixo X de todos os jogadores do time A.
		 * \param *tay Vetor que contém as coordenadas do eixo Y de todos os jogadores do time A.
		 * \param *anga Vetor que contém ângulos de todos os jogadores do time A.
		 * \param *tbx Vetor que contém as coordenadas do eixo X de todos os jogadores do time B.
		 * \param *tby Vetor que contém as coordenadas do eixo Y de todos os jogadores do time B.
		 * \param *angb Vetor que contém ângulos de todos os jogadores do time B.
		 * \return Retorna a string que contém a mensagem codificada.
		 */
		static string encode(float bx, float by, int nJogadores, float *tax, float *tay, float *anga, float *tbx, float *tby, float *angb);
		/**
		 * Codifica uma mensagem contendo as informações sobre a bola, todas as informações sobre os jogadores do time A, e as posições dos jogadores do time B (sem os ângulos).
		 * \param bx Coordenada X da bola.
		 * \param by Coordenada Y da bola.
		 * \param nJogadores Número de jogadores por time.
		 * \param *tax Vetor que contém as coordenadas do eixo X de todos os jogadores do time A.
		 * \param *tay Vetor que contém as coordenadas do eixo Y de todos os jogadores do time A.
		 * \param *anga Vetor que contém ângulos de todos os jogadores do time A.
		 * \param *tbx Vetor que contém as coordenadas do eixo X de todos os jogadores do time B.
		 * \param *tby Vetor que contém as coordenadas do eixo Y de todos os jogadores do time B.
		 * \return Retorna a string que contém a mensagem codificada.
		 */
		static string encode(float bx, float by, float *tax, float *tay, float *anga, float *tbx, float *tby);
		/**
		 * Decodifica uma mensagem contendo as velocidades das rodas dos robôs de um time.
		 *
		 * \param *msn Array que contém a mensagem a ser decodificada.
		 * \param *v_e Vetor que contém as velocidades das rodas esquedas.
		 * \param *v_d Vetor que contém as velocidades das rodas direitas.
		 */
		static bool decode(char *msn, float *v_e, float *v_d);
		/**
		 * Decodifica uma mensagem que contém informações sobre a posição da bola, e as posições e os ângulos de todos os jogadores.
		 * \param *msn Array que contém a mensagem a ser decodificada.
		 * \param *bx Variável que armazenará a coordenada X da bola.
		 * \param *by Variável que armazenará a coordenada Y da bola.
		 * \param *x Array que armazenará as coordenadas X dos jogadores dos dois times.
		 * \param *y Array que armazenará as coordenadas Y dos jogadores dos dois times.
		 * \param *a Array que armazenará os ângulos dos jogadores dos dois times.
		 */
		static bool decode(char *msn, float *bx, float *by, float *x, float *y, float *a);

		/**
		 \brief Cria novas strings a partir da string contida em "phrase". A string "phrase" é separada em "n_results" strings utilizando como fator de separação a cadeia de caracteres contida em "part".
		 \param phrase - string original que será dividida (in)
		 \param part - string delimitadora (in)
		 \param n_results - número de strings em que "phrase" foi quebrado (out)
		 \return strings separadas pela cadeia delimitadora
		 */
		static char **str_split(char *phrase, char *part, int *n_results);

		static string encode_objects(float bx, float by, float *x, float *y, float *a);
		static bool decode_objects(string msn, float *bx, float *by, float *tax, float *tay, float *taa, float *tbx, float *tby, float *tba);
		static string encode_strategy(float bx, float by, float *x, float *y, float *a);
		static bool decode_strategy(string msn, float *bx, float *by, float *tax, float *tay, float *taa, float *tbx, float *tby);
		static string encode_command(float *vl, float *vr);
		static string encode_score(int t1, int t2);
		static bool decode_score(string msn, int *t1, int *t2);
		static string encode_time(int time);
		static bool decode_time(string msn, int *time);
		static string encode_vision_objects(int bx, int by, int *x, int *y, int *a);
		static bool decode_vision_objects(string msn, int *bx, int *by, int *tax, int *tay, int *taa, int *tbx, int *tby, int *tba);
		static string encode_vision_field(int *x, int *y);
		static bool decode_vision_field(string msn, int *x, int *y);

};

#endif
