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

	src/lib/objeto.h
*/

#ifndef OBJETO_H
#define OBJETO_H
/**
 * \file objeto.h
 *
 * \author Diogo Oliveira de Melo
 * \date 03/01/2007
 */

#include<math.h>
#include<iostream>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>
#include"parametros.h"
#include"vetor2d.h"

using namespace std;

/**
 * Classe gen�rica para os objetos do USPDroids Mirosot Simulator.
 */

class objeto {
	protected:
		float x; ///< Armazena o valor da coordenada X do objeto, no estado corrente.
		float novo_x; ///< Armazena o valor da coordenada X do objeto, no pr�ximo estado.
		float y; ///< Armazena o valor da coordenada Y do objeto, no estado corrente.
		float novo_y; ///< Armazena o valor da coordenada Y do objeto, no pr�ximo estado.
		float massa; ///< Armazena o valor da massa do objeto, em kilogramas.
		vetor2d *velocidade; ///< Velocidade do objeto no estado corrente.
		vetor2d *nova_velocidade; ///< Velocidade do objeto no pr�ximo estado.
		vetor2d *forca_resultante; ///< For�a resultante que atua sobre o objeto, no estado corrente.
		vetor2d *nova_forca_resultante; ///< For�a resultante que atua sobre o objeto, no pr�ximo estado.
		vetor2d *forca_externa; ///< Somat�ria das for�as que atuam sobre o objeto mas que n�o s�o diretamente provocadas por este objeto.
		float torque; ///< M�dulo do torque aplicado sobre o objeto.
		float torque_externo; ///< M�dulo do torque resultante das for�as que atuam sobre este objeto.

	
	public:
		/**
		 * Construtor da classe objeto.
		 */
		objeto();
		/**
		 * Construtor da classe objeto, que inicializa as vari�veis com os valores passados por par�metro.
		 * 
		 * \param x Coordenada X do objeto.
		 * \param y Coordenada Y do objeto.
		 * \param *velocidade Vetor velocidade do objeto.
		 * \param *forca_resultante Vetor que representa a for�a resultante que atua sobre o centro de massa do objeto.
		 */
		objeto(const float x, const float y, const vetor2d *velocidade, const vetor2d *forca_resultante);

		/**
		 * Altera a coordenada X do objeto.
		 *
		 * \param x Novo valor da coordenada X do objeto.
		 * \return Retorna true caso a altera��o tenha sido bem sucedida.
		 */
		bool setX(float x);
		/**
		 * Altera a coordenada Y do objeto.
		 *
		 * \param y Novo valor da coordenada Y do objeto.
		 * \return Retorna true caso a altera��o tenha sido bem sucedida.
		 */
		bool setY(float y);
		/** Altera a posi��o do objeto.
		 *
		 * \param x Novo valor da coordenada X do objeto.
		 * \param y Novo valor da coordenada Y do objeto.
		 * \return Retorna true, caso a altera��o tenha sido bem sucedida.
		 */
		bool setXY(float x, float y);
		/**
		 * Altera a coordenada X do objeto.
		 *
		 * \param x Novo valor da coordenada X do objeto.
		 * \return Retorna true caso a altera��o tenha sido bem sucedida.
		 */
		bool setNewX(float x);
		/**
		 * Altera a coordenada Y do objeto.
		 *
		 * \param y Novo valor da coordenada Y do objeto.
		 * \return Retorna true caso a altera��o tenha sido bem sucedida.
		 */
		bool setNewY(float y);
		/** Altera a posi��o do objeto.
		 *
		 * \param x Novo valor da coordenada X do objeto.
		 * \param y Novo valor da coordenada Y do objeto.
		 * \return Retorna true, caso a altera��o tenha sido bem sucedida.
		 */
		bool setNewXY(float x, float y);
		/**
		 * Altera o valor da massa do objeto.
		 *
		 * \param massa Novo valor da massa do objeto.
		 * \return Retorna true, caso a altera��o tenha sido bem sucedida.
		 */

		bool setMassa(float massa);
		/**
		 * Altera a velocidade do objeto.
		 *
		 * \param *velocidade Nova velocidade do objeto.
		 * \return Retorna true, se a altera��o tenha sido bem sucedida.
		 */
		bool setVelocidade(const vetor2d *velocidade);
		/**
		 * Altera a for�a resultante do objeto.
		 *
		 * \param *forca_resultante Nova for�a resultante do objeto.
		 * \return Retorna true, caso a altera��o tenha sido bem suceidada.
		 */
		bool setForca_resultante(const vetor2d *forca_resultante);

		/**
		 * Retorna a coordenada X do objeto.
		 */
		float getX();
		/**
		 * Retorna a coordenada Y do objeto.
		 */
		float getY();
		/**
		 * Retorna a nova coordenada X do objeto.
		 */
		float getNewX();
		/**
		 * Retorna a nova coordenada Y do objeto.
		 */
		float getNewY();

		/**
		 * Retorna o valor da massa do objeto.
		 */
		float getMassa();
		/**
		 * Retorna o vetor velocidade do objeto.
		 */
		vetor2d getVelocidade();
		/**
		 * Retorna o vetor for�a resultante do objeto.
		 */
		vetor2d getForca_resultante();

		/**
		 * Inicializa a for�a externa do objeto.
		 */
		bool restart_forca_externa();
		/**
		 * Adiciona um novo vetor a for�a externa do objeto.
		 */
		bool add_forca_externa(vetor2d nova_forca);
		/**
		 * Retorna a for�a externa do objeto.
		 */
		vetor2d get_forca_externa();
		/**
		 * Finaliza o vetor for�a externa do objeto.
		 */
		bool end_forca_externa();

		/**
		 * Calcula a �rea do tri�ngulo, determinado pelos pontos passados por par�metro.
		 *
		 * \param ax Coordenada X do v�rtice A, do tri�ngulo.
		 * \param ay Coordenada Y do v�rtice A, do tri�ngulo.
		 * \param bx Coordenada X do v�rtice B, do tri�ngulo.
		 * \param by Coordenada Y do v�rtice B, do tri�ngulo.
		 * \param cx Coordenada X do v�rtice C, do tri�ngulo.
		 * \param cy Coordenada Y do v�rtice C, do tri�ngulo.
		 * \return Retorna a �rea do tri�ngulo.
		 */
		static float area_triangulo(float ax, float ay, float bx, float by, float cx, float cy);
		/**
		 * Calcula a dist�ncia entre dois pontos.
		 *
		 * \param ax Coordenada X, do primeiro ponto.
		 * \param ay Coordenada Y, do primeiro ponto.
		 * \param bx Coordenada X, do segundo ponto.
		 * \param by Coordenada Y, do segundo ponto.
		 * \return Retorna a dist�ncia entre os dois pontos.
		 */
		static float distancia(float ax, float ay, float bx, float by);
		/**
		 * Converte um �ngulo (em radianos) para os primeiros quatro quadrantes.
		 *
		 * \param angulo �ngulo a ser convertido.
		 * \return �ngulo convertido.
		 */
		static float padronizar_angulo_2_pi(float angulo);
		/**
		 * Converte um �ngulo (em radianos) para os primeiros dois quadrantes.
		 *
		 * \param angulo �ngulo a ser convertido.
		 * \return �ngulo convertido.
		 */
		static float padronizar_angulo_pi(float angulo);
		/**
		 * Converte um �ngulo (em radianos) para o primeiro quadrante.
		 *
		 * \param angulo �ngulo a ser convertido.
		 * \return �ngulo convertido.
		 */
		static float padronizar_angulo_pi_sobre_2(float angulo);
		/**
		 * Reduz o angulo ao intervalo entre zero e pi sobre quatro.
		 *
		 * \param angulo �ngulo a ser reduzido.
		 * \return �ngulo reduzido.
		 */
		static float padronizar_angulo_pi_sobre_4(float angulo);
		/**
		 * Conpara dois �ngulos.
		 * \param um Primairo �ngulo.
		 * \param dois Segundo �ngulo.
		 * \return Retorna -1 caso o primeiro �ngulo seja menor, 0 se forem iguais e 1 caso o primeiro �ngulo seja maior.
		 */
		static int angcmp(float um, float dois);
		/**
		 * Calcula os novos vetores de velocidade, prodizudos ap�s uma colis�o el�stica.
		 *
		 * \param m1 Massa do primeiro objeto.
		 * \param v1 Vetor velocidade do primeiro objeto.
		 * \param m2 Massa do segundo objeto.
		 * \param v2 Vetor velocidade do segundo objeto.
		 * \param *vf1 Vetor em que ficar� armazenada a velocidade do primeiro objeto ap�s a colis�o.
		 * \param *vf2 Vetor em que ficar� armazenada a velocidade do segundo objeto ap�s a colis�o.
		 */
		static bool colisao_elastica(float m1, vetor2d v1, float m2, vetor2d v2, vetor2d *vf1, vetor2d *vf2);
		/**
		 * Dorme por um determinado tempo.
		 *
		 * \param mseconds Quantidade de tempo que a fun��o dever� dormir (em ms).
		 */
		static void sleep2(long int mseconds);

		/**
		 * Verify if the point (px, py) is inside of the convex poligon witch points is (x[i], y[i]) and every side connect the points (x[i], y[i]) to (x[i+1], y[i+1]).
		 */
		static bool point_inside_convex_polygon(float px, float py, float *x, float *y, int n_points);

		/**
		 * Inicializa a vari�vel respons�vel por armazenar o valor do m�dulo do torque externo.
		 */
		bool restart_torque_externo();
		/**
		 * Adiciona um novo torque externo ao resultante.
		 *
		 * \param novo_torque M�dulo do torque a ser adicionado.
		 */
		bool add_torque_externo(float novo_torque);
		/**
		 * Retorna o valor do torque externo.
		 */
		float get_torque_externo();
		/**
		 * Finaliza a vari�vel que armazena o valor do m�dulo do torque externo.
		 */
		bool end_torque_externo();
};

#endif
