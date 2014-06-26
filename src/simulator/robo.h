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
 * Classe que manipula os dados do rob�.
 */

class robo : public objeto {
	private:
		float angulo; ///< �ngulo do rob� no estado corrente.
		float novo_angulo; ///< �ngulo do rob� no pr�ximo estado.
		float bola_x[SIZE_STACK];
		float bola_y[SIZE_STACK];
		float robo_x[SIZE_STACK];
		float robo_y[SIZE_STACK];

		float aceleracao_roda_esquerda;
		float aceleracao_roda_direita;

		float v_roda_esquerda; ///< Velocidade da roda esquerda do rob�, no estado corrente.
		float nova_v_roda_esquerda; ///< Velocidade da roda esquerda do rob� no pr�ximo estado.
		float v_desejada_roda_esquerda; ///< Velocidade alvo para a roda esquerda do rob�.
		float v_roda_direita;///< Velocidade da roda direita do rob�, no estado corrente.
		float nova_v_roda_direita;///< Velocidade da roda direita do rob� no pr�ximo estado.
		float v_desejada_roda_direita;///< Velocidade alvo para a roda direita do rob�.
		
		float v_angular; ///< Velocidade angular do rob� no estado corrente.
		float nova_v_angular; ///< Velocidade angular do rob�, no pr�ximo estado.


		float f_roda_esquerda; ///< For�a aplicada sobre a roda esquerda do rob�, no estado corrente.
		float nova_f_roda_esquerda; ///< For�a aplicada sobre a roda esquerda do rob�, no pr�ximo estado.
		float f_roda_direita; ///< For�a aplicada sobre a roda direita do rob�, no estado corrente.
		float nova_f_roda_direita; ///< For�a aplicada sobre a roda direita do rob�, no pr�ximo estado.

		/**
		 * Calcula a for�a resultante sobre o rob�, levando em considera��o todas as poss�veis colis�es.
		 */
		bool calc_forca();
		/**
		 * Calcula a velocidade do rob�, leva em considera��o a for�a atuando sobre ele e a varia��o de tempo considerada.
		 */
		bool calc_velocidade();
		/**
		 * Calcula a nova posi��o do rob� (e o seu novo �nculo), levando em considera��o a varia��o de tempo e a velocidade atual do rob�.
		 */
		bool calc_deslocamento();

		/**
		 * Verifica e trata a colis�o entre o rob� e o campo.
		 *
		 * \param c Campo.
		 */
		bool colisao_robo_campo(campo *c);
		bool add_posicao_robo(float x_robo, float y_robo);
		/**
		 * Verifica e trata a colis�o entre o rob� e a bola.
		 *
		 * \param x_bola Coordenada X da bola.
		 * \param y_bola Coordenada Y da bola.
		 * \param v_bola Vetor que representa a velocidade da bola.
		 * \param f_bola Vetor que representa a for�a resultante que atua sobre a bola.
		 */
		bool colisao_robo_bola(float x_bola, float y_bola, vetor2d v_bola, vetor2d f_bola);
		bool add_posicao_bola(float x_bola, float y_bola);
		bool bola_parada();
		/**
		 * Verifica e trata colis�o entre este rob� e um outro, passado por par�metro.
		 *
		 * \param Rob�.
		 */
		bool colisao_robo_robo(robo *r);



	public:
		/**
		 * Construtor da classe rob�.
		 */
		robo();
		/**
		 * Construtor da classe rob� que inicializa o rob� com os valores passados por par�metro.
		 *
		 * \param x Coordenada X do rob�.
		 * \param y Coordenada Y do rob�.
		 * \param ang �ngulo inicial do rob�.
		 */
		robo(const float x, const float y, const float ang);
		/**
		 * Calcula todos os atributos que o rob� ter� no proximo instante de tempo (pr�ximo estado).
		 *
		 * \param c Campo.
		 * \param x_bola Coordenada X da bola.
		 * \param y_bola Coordenada Y da bola.
		 * \param v_bola Velocidade da bola.
		 * \param f_bola For�a resultante sobre a bola.
		 * \param time1 Array que cont�m todos os rob�s do time1, exceto o este rob�.
		 * \param time2 Array que cont�m todos os rob�s do time advers�rio.
		 */
		bool calc_atributos(campo *c, float x_bola, float y_bola, vetor2d v_bola, vetor2d f_bola, robo *time1[N_JOGADORES_POR_TIME - 1], robo *time2[N_JOGADORES_POR_TIME]);
		/**
		 * Atualiza os atributos, copiando os atributos do pr�ximo estado para o estado corrente.
		 */
		bool atualizar_atributos();
		/**
		 * Retorna a coordenada X do rob�.
		 */
		float getX();
		/**
		 * Retorna a coordenada Y do rob�.
		 */
		float getY();
		/**
		 * Retorna o �ngulo do rob�.
		 */
		float getAng();
		/**
		 * Retorna o novo �ngulo do rob�.
		 */
		float getNewAng();
		/*
		 * Retorna a velocidade da roda esquerda do rob�.
		 */
		float getVelEsq();
		/**
		 * Retorna a velocidade da roda direita do rob�.
		 */
		float getVelDir();
		/**
		 * Retorna o �ngulo do Rob�.
		 */
		float getAngulo();
		/**
		 * Altera a velocidade desejada para as rodas do rob�.
		 *
		 * \param esq Velocidade desejada para a roda esquerda do rob�.
		 * \param dir Velocidade desejada para a roda direita do rob�.
		 */
		bool setVel(float esq, float dir);
		float getVelocidade_por_posicao();
		float getAng_por_posicao();
		/**
		 * Retorna os pontos dos quatro vertices do quadrado que determina o rob�.
		 *
		 * \param **px Ponteiro para armazenar as coordenadas X dos pontos.
		 * \param **py Ponteiro para armazenar as coordenadas Y dos pontos.
		 */
		void get_pontos(float **px, float **py);

		/**
		 * Retorna os pontos dos quatro vertices do quadrado que determina o rob� no proximo instante.
		 *
		 * \param *px Ponteiro para armazenar as coordenadas X dos pontos.
		 * \param *py Ponteiro para armazenar as coordenadas Y dos pontos.
		 */
		void getNewPontos(float *px, float *py);

		/**
		 * Verifica se o ponto pertence ao rob�.
		 *
		 * \param a_x Coordenada x do ponto.
		 * \param a_y Coordenada y do ponto.
		 * \return Retorna true se o ponto estiver contido no rob�.
		 */
		bool ponto_pertence(float a_x, float a_y); // verifica se o ponto dado pertence ao rob�.u
		/**
		 * Verifica se o rob� colidiu com o segmento especificado.
		 *
		 * \param ax Coordenada X do primeiro ponto do segmento.
		 * \param ay Coordenada Y do primeiro ponto do segmento.
		 * \param bx Coordenada X do segundo ponto do segmento.
		 * \param by Coordenada Y do segundo ponto do segmento.
		 */
		float colisao_robo_segmento(float ax, float ay, float bx, float by);

		/**
		 * Verifica se o rob� colidiu com determinada aresta do campo.
		 *
		 * \param aresta N�mero da aresta do campo.
		 */
		float colisao_robo_segmento(campo *c, int aresta);
		/**
		 * Calcula a menor dist�ncia entre o ponto dado e a aresta do rob�.
		 *
		 * \param c Campo.
		 * \param a_x Coordenada X do ponto.
		 * \param a_y Coordenada Y do ponto.
		 */
		float distancia_ponto_interno_robo(float a_x, float a_y);

		//dado um ponto e um vetor, calcular o vetor forca sobre o centro de massa do rob� e o torque.
		/**
		 * Usada para obter a for�a e o torque sobre determinado ponto do rob�.
		 *
		 * \param x Coordenada X do ponto.
		 * \param y Coordenada Y do ponto.
		 * \param forca_aplicada for�a aplicada sobre o ponto (x, y).
		 * \param *forca_centro For�a causada pela forca_aplicada.
		 * \param *torque M�dulo do torque resultante da aplica��o da forca_aplicada, no ponto (x, y).
		 */
		bool get_forca_e_torque(float x, float y, vetor2d forca_aplicada, vetor2d *forca_centro, float *torque);
		/**
		 * Verifica e trata poss�veis erros.
		 */
		bool protecao(float x_bola, float y_bola, robo *time1[N_JOGADORES_POR_TIME - 1], robo *time2[N_JOGADORES_POR_TIME]);
		/**
		 * Retorna a dist�ncia do centro do rob� at� um ponto da borda, tal que o �ngulo do segmento formado por esses dois pontos e passado por par�metro.
		 *
		 * \param angulo_d �ngulo do segmento formado pelo centro do rob� e a borda.
		 * \return Retorna a dist�ncia calculada.
		 */
		float dist_centro_borda(float angulo_d);
		/**
		 * Calcula o ponto da borda do rob� que determinado pelo centro do rob� e o �ngulo passado por par�metro.
		 *
		 * \param *x Coordenada X do ponto calculado.
		 * \param *y Coordenada Y do ponto calculado.
		 * \param angulo �ngulo usado para fazer o c�lculo.
		 */
		bool ponto_borda(float *x, float *y, float angulo);
		/**
		 * Calcula a verlocidade do ponto da borda do rob�.
		 *
		 * \param angulo �ngulo, que em conjunto com o centro do rob�, determina o ponto da borda do rob�.
		 * \return Retorna o vetor velocidade do ponto.
		 */
		vetor2d velocidade_ponto_borda(float angulo);
		/**
		 * Retorna a velocidade angular do rob�.
		 */
		float get_v_angular();
		/**
		 * Retorna o n�mero do lado do rob� mais proximo do ponto dado.
		 *
		 * \param x Coordenada X do ponto dado.
		 * \param y Coordenada Y do ponto dado.
		 */
		int get_lado(float x, float y);

		void setAng(float a);


};
#endif
