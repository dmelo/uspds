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

	src/simulator/robo.h
*/

/**
 * \file robo.h
 * \author Diogo Oliveira de Melo
 * \date 08-01-2007
 */

#ifndef ROBO_H
#define ROBO_H

#include<iostream>
#include<vector>
#include"campo.h"
#include"../lib/objeto.h"
#include"../lib/parametros.h"

using namespace std;

/**
 * Classe que manipula os dados do robô.
 */

class robo : public objeto {
	private:
		float angulo; ///< Ãngulo do robô no estado corrente.
		float novo_angulo; ///< Ãngulo do robô no próximo estado.
		float bola_x[SIZE_STACK];
		float bola_y[SIZE_STACK];
		float robo_x[SIZE_STACK];
		float robo_y[SIZE_STACK];

		float aceleracao_roda_esquerda;
		float aceleracao_roda_direita;

		float v_roda_esquerda; ///< Velocidade da roda esquerda do robô, no estado corrente.
		float nova_v_roda_esquerda; ///< Velocidade da roda esquerda do robô no próximo estado.
		float v_desejada_roda_esquerda; ///< Velocidade alvo para a roda esquerda do robô.
		float v_roda_direita;///< Velocidade da roda direita do robô, no estado corrente.
		float nova_v_roda_direita;///< Velocidade da roda direita do robô no próximo estado.
		float v_desejada_roda_direita;///< Velocidade alvo para a roda direita do robô.
		
		float v_angular; ///< Velocidade angular do robô no estado corrente.
		float nova_v_angular; ///< Velocidade angular do robô, no próximo estado.


		float f_roda_esquerda; ///< Força aplicada sobre a roda esquerda do robô, no estado corrente.
		float nova_f_roda_esquerda; ///< Força aplicada sobre a roda esquerda do robô, no próximo estado.
		float f_roda_direita; ///< Força aplicada sobre a roda direita do robô, no estado corrente.
		float nova_f_roda_direita; ///< Força aplicada sobre a roda direita do robô, no próximo estado.

		/**
		 * Calcula a força resultante sobre o robô, levando em consideração todas as possíveis colisões.
		 */
		bool calc_forca();
		/**
		 * Calcula a velocidade do robô, leva em consideração a força atuando sobre ele e a variação de tempo considerada.
		 */
		bool calc_velocidade();
		/**
		 * Calcula a nova posição do robô (e o seu novo ânculo), levando em consideração a variação de tempo e a velocidade atual do robô.
		 */
		bool calc_deslocamento();

		/**
		 * Verifica e trata a colisão entre o robô e o campo.
		 *
		 * \param c Campo.
		 */
		bool colisao_robo_campo(campo *c);
		bool add_posicao_robo(float x_robo, float y_robo);
		/**
		 * Verifica e trata a colisão entre o robô e a bola.
		 *
		 * \param x_bola Coordenada X da bola.
		 * \param y_bola Coordenada Y da bola.
		 * \param v_bola Vetor que representa a velocidade da bola.
		 * \param f_bola Vetor que representa a força resultante que atua sobre a bola.
		 */
		bool colisao_robo_bola(float x_bola, float y_bola, vetor2d v_bola, vetor2d f_bola);
		bool add_posicao_bola(float x_bola, float y_bola);
		bool bola_parada();
		/**
		 * Verifica e trata colisão entre este robô e um outro, passado por parâmetro.
		 *
		 * \param Robô.
		 */
		bool colisao_robo_robo(robo *r);



	public:
		/**
		 * Construtor da classe robô.
		 */
		robo();
		/**
		 * Construtor da classe robô que inicializa o robô com os valores passados por parâmetro.
		 *
		 * \param x Coordenada X do robô.
		 * \param y Coordenada Y do robô.
		 * \param ang Ângulo inicial do robô.
		 */
		robo(const float x, const float y, const float ang);
		/**
		 * Calcula todos os atributos que o robô terá no proximo instante de tempo (próximo estado).
		 *
		 * \param c Campo.
		 * \param x_bola Coordenada X da bola.
		 * \param y_bola Coordenada Y da bola.
		 * \param v_bola Velocidade da bola.
		 * \param f_bola Força resultante sobre a bola.
		 * \param time1 Array que contém todos os robôs do time1, exceto o este robô.
		 * \param time2 Array que contém todos os robôs do time adversário.
		 */
		bool calc_atributos(campo *c, float x_bola, float y_bola, vetor2d v_bola, vetor2d f_bola, robo *time1[N_JOGADORES_POR_TIME - 1], robo *time2[N_JOGADORES_POR_TIME]);
		/**
		 * Atualiza os atributos, copiando os atributos do próximo estado para o estado corrente.
		 */
		bool atualizar_atributos();
		/**
		 * Retorna a coordenada X do robô.
		 */
		float getX();
		/**
		 * Retorna a coordenada Y do robô.
		 */
		float getY();
		/**
		 * Retorna o ângulo do robô.
		 */
		float getAng();
		/**
		 * Retorna o novo ângulo do robô.
		 */
		float getNewAng();
		/*
		 * Retorna a velocidade da roda esquerda do robô.
		 */
		float getVelEsq();
		/**
		 * Retorna a velocidade da roda direita do robô.
		 */
		float getVelDir();
		/**
		 * Retorna o ângulo do Robô.
		 */
		float getAngulo();
		/**
		 * Altera a velocidade desejada para as rodas do robô.
		 *
		 * \param esq Velocidade desejada para a roda esquerda do robô.
		 * \param dir Velocidade desejada para a roda direita do robô.
		 */
		bool setVel(float esq, float dir);
		float getVelocidade_por_posicao();
		float getAng_por_posicao();
		/**
		 * Retorna os pontos dos quatro vertices do quadrado que determina o robô.
		 *
		 * \param **px Ponteiro para armazenar as coordenadas X dos pontos.
		 * \param **py Ponteiro para armazenar as coordenadas Y dos pontos.
		 */
		void get_pontos(float **px, float **py);

		/**
		 * Retorna os pontos dos quatro vertices do quadrado que determina o robô no proximo instante.
		 *
		 * \param *px Ponteiro para armazenar as coordenadas X dos pontos.
		 * \param *py Ponteiro para armazenar as coordenadas Y dos pontos.
		 */
		void getNewPontos(float *px, float *py);

		/**
		 * Verifica se o ponto pertence ao robô.
		 *
		 * \param a_x Coordenada x do ponto.
		 * \param a_y Coordenada y do ponto.
		 * \return Retorna true se o ponto estiver contido no robô.
		 */
		bool ponto_pertence(float a_x, float a_y); // verifica se o ponto dado pertence ao robô.u
		/**
		 * Verifica se o robô colidiu com o segmento especificado.
		 *
		 * \param ax Coordenada X do primeiro ponto do segmento.
		 * \param ay Coordenada Y do primeiro ponto do segmento.
		 * \param bx Coordenada X do segundo ponto do segmento.
		 * \param by Coordenada Y do segundo ponto do segmento.
		 */
		float colisao_robo_segmento(float ax, float ay, float bx, float by);

		/**
		 * Verifica se o robô colidiu com determinada aresta do campo.
		 *
		 * \param aresta Número da aresta do campo.
		 */
		float colisao_robo_segmento(campo *c, int aresta);
		/**
		 * Calcula a menor distância entre o ponto dado e a aresta do robô.
		 *
		 * \param c Campo.
		 * \param a_x Coordenada X do ponto.
		 * \param a_y Coordenada Y do ponto.
		 */
		float distancia_ponto_interno_robo(float a_x, float a_y);

		//dado um ponto e um vetor, calcular o vetor forca sobre o centro de massa do robô e o torque.
		/**
		 * Usada para obter a força e o torque sobre determinado ponto do robô.
		 *
		 * \param x Coordenada X do ponto.
		 * \param y Coordenada Y do ponto.
		 * \param forca_aplicada força aplicada sobre o ponto (x, y).
		 * \param *forca_centro Força causada pela forca_aplicada.
		 * \param *torque Módulo do torque resultante da aplicação da forca_aplicada, no ponto (x, y).
		 */
		bool get_forca_e_torque(float x, float y, vetor2d forca_aplicada, vetor2d *forca_centro, float *torque);
		/**
		 * Verifica e trata possíveis erros.
		 */
		bool protecao(float x_bola, float y_bola, robo *time1[N_JOGADORES_POR_TIME - 1], robo *time2[N_JOGADORES_POR_TIME]);
		/**
		 * Retorna a distância do centro do robô até um ponto da borda, tal que o ângulo do segmento formado por esses dois pontos e passado por parâmetro.
		 *
		 * \param angulo_d Ângulo do segmento formado pelo centro do robô e a borda.
		 * \return Retorna a distância calculada.
		 */
		float dist_centro_borda(float angulo_d);
		/**
		 * Calcula o ponto da borda do robô que determinado pelo centro do robô e o ângulo passado por parâmetro.
		 *
		 * \param *x Coordenada X do ponto calculado.
		 * \param *y Coordenada Y do ponto calculado.
		 * \param angulo Ângulo usado para fazer o cálculo.
		 */
		bool ponto_borda(float *x, float *y, float angulo);
		/**
		 * Calcula a verlocidade do ponto da borda do robô.
		 *
		 * \param angulo Ângulo, que em conjunto com o centro do robô, determina o ponto da borda do robô.
		 * \return Retorna o vetor velocidade do ponto.
		 */
		vetor2d velocidade_ponto_borda(float angulo);
		/**
		 * Retorna a velocidade angular do robô.
		 */
		float get_v_angular();
		/**
		 * Retorna o número do lado do robô mais proximo do ponto dado.
		 *
		 * \param x Coordenada X do ponto dado.
		 * \param y Coordenada Y do ponto dado.
		 */
		int get_lado(float x, float y);

		void setAng(float a);


};
#endif
