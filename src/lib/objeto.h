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
 * Classe genérica para os objetos do USPDroids Mirosot Simulator.
 */

class objeto {
	protected:
		float x; ///< Armazena o valor da coordenada X do objeto, no estado corrente.
		float novo_x; ///< Armazena o valor da coordenada X do objeto, no próximo estado.
		float y; ///< Armazena o valor da coordenada Y do objeto, no estado corrente.
		float novo_y; ///< Armazena o valor da coordenada Y do objeto, no próximo estado.
		float massa; ///< Armazena o valor da massa do objeto, em kilogramas.
		vetor2d *velocidade; ///< Velocidade do objeto no estado corrente.
		vetor2d *nova_velocidade; ///< Velocidade do objeto no próximo estado.
		vetor2d *forca_resultante; ///< Força resultante que atua sobre o objeto, no estado corrente.
		vetor2d *nova_forca_resultante; ///< Força resultante que atua sobre o objeto, no próximo estado.
		vetor2d *forca_externa; ///< Somatória das forças que atuam sobre o objeto mas que não são diretamente provocadas por este objeto.
		float torque; ///< Módulo do torque aplicado sobre o objeto.
		float torque_externo; ///< Módulo do torque resultante das forças que atuam sobre este objeto.

	
	public:
		/**
		 * Construtor da classe objeto.
		 */
		objeto();
		/**
		 * Construtor da classe objeto, que inicializa as variáveis com os valores passados por parâmetro.
		 * 
		 * \param x Coordenada X do objeto.
		 * \param y Coordenada Y do objeto.
		 * \param *velocidade Vetor velocidade do objeto.
		 * \param *forca_resultante Vetor que representa a força resultante que atua sobre o centro de massa do objeto.
		 */
		objeto(const float x, const float y, const vetor2d *velocidade, const vetor2d *forca_resultante);

		/**
		 * Altera a coordenada X do objeto.
		 *
		 * \param x Novo valor da coordenada X do objeto.
		 * \return Retorna true caso a alteração tenha sido bem sucedida.
		 */
		bool setX(float x);
		/**
		 * Altera a coordenada Y do objeto.
		 *
		 * \param y Novo valor da coordenada Y do objeto.
		 * \return Retorna true caso a alteração tenha sido bem sucedida.
		 */
		bool setY(float y);
		/** Altera a posição do objeto.
		 *
		 * \param x Novo valor da coordenada X do objeto.
		 * \param y Novo valor da coordenada Y do objeto.
		 * \return Retorna true, caso a alteração tenha sido bem sucedida.
		 */
		bool setXY(float x, float y);
		/**
		 * Altera a coordenada X do objeto.
		 *
		 * \param x Novo valor da coordenada X do objeto.
		 * \return Retorna true caso a alteração tenha sido bem sucedida.
		 */
		bool setNewX(float x);
		/**
		 * Altera a coordenada Y do objeto.
		 *
		 * \param y Novo valor da coordenada Y do objeto.
		 * \return Retorna true caso a alteração tenha sido bem sucedida.
		 */
		bool setNewY(float y);
		/** Altera a posição do objeto.
		 *
		 * \param x Novo valor da coordenada X do objeto.
		 * \param y Novo valor da coordenada Y do objeto.
		 * \return Retorna true, caso a alteração tenha sido bem sucedida.
		 */
		bool setNewXY(float x, float y);
		/**
		 * Altera o valor da massa do objeto.
		 *
		 * \param massa Novo valor da massa do objeto.
		 * \return Retorna true, caso a alteração tenha sido bem sucedida.
		 */

		bool setMassa(float massa);
		/**
		 * Altera a velocidade do objeto.
		 *
		 * \param *velocidade Nova velocidade do objeto.
		 * \return Retorna true, se a alteração tenha sido bem sucedida.
		 */
		bool setVelocidade(const vetor2d *velocidade);
		/**
		 * Altera a força resultante do objeto.
		 *
		 * \param *forca_resultante Nova força resultante do objeto.
		 * \return Retorna true, caso a alteração tenha sido bem suceidada.
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
		 * Retorna o vetor força resultante do objeto.
		 */
		vetor2d getForca_resultante();

		/**
		 * Inicializa a força externa do objeto.
		 */
		bool restart_forca_externa();
		/**
		 * Adiciona um novo vetor a força externa do objeto.
		 */
		bool add_forca_externa(vetor2d nova_forca);
		/**
		 * Retorna a força externa do objeto.
		 */
		vetor2d get_forca_externa();
		/**
		 * Finaliza o vetor força externa do objeto.
		 */
		bool end_forca_externa();

		/**
		 * Calcula a área do triângulo, determinado pelos pontos passados por parâmetro.
		 *
		 * \param ax Coordenada X do vértice A, do triângulo.
		 * \param ay Coordenada Y do vértice A, do triângulo.
		 * \param bx Coordenada X do vértice B, do triângulo.
		 * \param by Coordenada Y do vértice B, do triângulo.
		 * \param cx Coordenada X do vértice C, do triângulo.
		 * \param cy Coordenada Y do vértice C, do triângulo.
		 * \return Retorna a área do triângulo.
		 */
		static float area_triangulo(float ax, float ay, float bx, float by, float cx, float cy);
		/**
		 * Calcula a distância entre dois pontos.
		 *
		 * \param ax Coordenada X, do primeiro ponto.
		 * \param ay Coordenada Y, do primeiro ponto.
		 * \param bx Coordenada X, do segundo ponto.
		 * \param by Coordenada Y, do segundo ponto.
		 * \return Retorna a distância entre os dois pontos.
		 */
		static float distancia(float ax, float ay, float bx, float by);
		/**
		 * Converte um ângulo (em radianos) para os primeiros quatro quadrantes.
		 *
		 * \param angulo Ângulo a ser convertido.
		 * \return Ângulo convertido.
		 */
		static float padronizar_angulo_2_pi(float angulo);
		/**
		 * Converte um ângulo (em radianos) para os primeiros dois quadrantes.
		 *
		 * \param angulo Ângulo a ser convertido.
		 * \return Ângulo convertido.
		 */
		static float padronizar_angulo_pi(float angulo);
		/**
		 * Converte um ângulo (em radianos) para o primeiro quadrante.
		 *
		 * \param angulo Ângulo a ser convertido.
		 * \return Ângulo convertido.
		 */
		static float padronizar_angulo_pi_sobre_2(float angulo);
		/**
		 * Reduz o angulo ao intervalo entre zero e pi sobre quatro.
		 *
		 * \param angulo Ângulo a ser reduzido.
		 * \return Ângulo reduzido.
		 */
		static float padronizar_angulo_pi_sobre_4(float angulo);
		/**
		 * Conpara dois ângulos.
		 * \param um Primairo ângulo.
		 * \param dois Segundo ângulo.
		 * \return Retorna -1 caso o primeiro ângulo seja menor, 0 se forem iguais e 1 caso o primeiro ângulo seja maior.
		 */
		static int angcmp(float um, float dois);
		/**
		 * Calcula os novos vetores de velocidade, prodizudos após uma colisão elástica.
		 *
		 * \param m1 Massa do primeiro objeto.
		 * \param v1 Vetor velocidade do primeiro objeto.
		 * \param m2 Massa do segundo objeto.
		 * \param v2 Vetor velocidade do segundo objeto.
		 * \param *vf1 Vetor em que ficará armazenada a velocidade do primeiro objeto após a colisão.
		 * \param *vf2 Vetor em que ficará armazenada a velocidade do segundo objeto após a colisão.
		 */
		static bool colisao_elastica(float m1, vetor2d v1, float m2, vetor2d v2, vetor2d *vf1, vetor2d *vf2);
		/**
		 * Dorme por um determinado tempo.
		 *
		 * \param mseconds Quantidade de tempo que a função deverá dormir (em ms).
		 */
		static void sleep2(long int mseconds);

		/**
		 * Verify if the point (px, py) is inside of the convex poligon witch points is (x[i], y[i]) and every side connect the points (x[i], y[i]) to (x[i+1], y[i+1]).
		 */
		static bool point_inside_convex_polygon(float px, float py, float *x, float *y, int n_points);

		/**
		 * Inicializa a variável responsável por armazenar o valor do módulo do torque externo.
		 */
		bool restart_torque_externo();
		/**
		 * Adiciona um novo torque externo ao resultante.
		 *
		 * \param novo_torque Módulo do torque a ser adicionado.
		 */
		bool add_torque_externo(float novo_torque);
		/**
		 * Retorna o valor do torque externo.
		 */
		float get_torque_externo();
		/**
		 * Finaliza a variável que armazena o valor do módulo do torque externo.
		 */
		bool end_torque_externo();
};

#endif
