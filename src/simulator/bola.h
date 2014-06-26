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

	src/simulator/bola.h
*/

/**
 * \file bola.h
 * \author Diogo Oliveira de Melo
 * \date 08-01-2007
 */

#ifndef BOLA_H
#define BOLA_H

#include"campo.h"
#include"../lib/objeto.h"
#include"../lib/parametros.h"
#include"robo.h"


/**
 * Classe que manipula os dados da bola.
 */
class bola : public objeto {
	private:
		
		float raio; ///< Raio da bola
		bool colisao_b_s; ///< Se for true indica que houve colis�o com o campo no quandro anterior
		bool colisao_b_r; ///< Se for true indica que houve colis�o com o rob� no quadro anterior.
	
	public:
		/// Construtor da Classe Bola.
		bola();
		/**
		 * Contrutor que j� inicializa as vari�veis com os dados passados por par�metro.
		 *
		 * \param x Posi��o da bola no eixo x.
		 * \param y posi��o da bola no eixo y.
		 * \param *velocidade vetor que representa a velocidade da bola.
		 * \param *forca_resultante vetor que representa a for�a resultante sobre a bola.
		 */
		bola(const float x, const float y, const vetor2d *velocidade, const vetor2d *forca_resultante);
		/**
		 * Altera o valor do raio da bola.
		 *
		 * \param r Novo raio da bola.
		 * \return Retorna true caso a altera��o tenha sido bem sucedida.
		 */
		bool setRaio(float r);
		/**
		 * Verifica e trata colis�es entre a bola e o campo.
		 *
		 * \param c Campo.
		 * \return Retorna true caso tenha havido colis�o.
		 */
		bool colisao_campo(campo *c);
		/**
		 * Verifica e trata colis�es entre a bola e o rob�.
		 *
		 * \param r Rob�.
		 * \return Retorna true caso tenha havido colis�o.
		 */
		bool colisao_robo(robo r);
		/**
		 * Antigo m�todo que tratava da corre��o da trajet�ria da bola, em caso de colis�o.
		 */
		float corrigir_trajetoria(float tempo, float x_a, float y_a, float x_b, float y_b);
		/**
		 * Calcula a posi��o, no eixo X,  da bola desconsiderando colis�es.
		 *
		 * \param tempo Varia��o de tempo que ser� utilizada no c�lculo da previs�o.
		 * \return Retorna a posi��o, no eixo X, prevista.
		 */
		float preverX(float tempo);
		/**
		 * Calcula a posi��o, no eixo Y,  da bola desconsiderando colis�es.
		 *
		 * \param tempo Varia��o de tempo que ser� utilizada no c�lculo da previs�o.
		 * \return Retorna a posi��o, no eixo Y, prevista.
		 */
		float preverY(float tempo);
		/**
		 * Verifica se a bola est� em posi��o de colis�o, em rela��o ao segmento dado, para determinar o segmento, debem ser passadas as posi��es dos dois ponstos extremos do segmento.
		 *
		 * \param bola_x Posi��o da bola no eixo X.
		 * \param bola_y Posi��o da bola no eixo Y.
		 * \param a_x Coordenada do eixo X do primeiro ponto que determina o segmento.
		 * \param a_y Coordenada do eixo Y do primeiro ponto que determina o segmento.
		 * \param b_x Coordenada do eixo X do segundo ponto que determina o segmento.
		 * \param b_y Coordenada do eixo Y do segundo ponto que determina o segmento.
		 * \return Retorna true caso a bola esteja em posi��o de colis�o.
		 */
		bool colisao_bola_segmento(float bola_x, float bola_y, float a_x, float a_y, float b_x, float b_y);
		/**
		 * Calcula a for�a resultante sobre a bola, levando em considera��o todas as possiveis colis�es.
		 */
		bool calc_forca();
		/**
		 * Calcula a velocidade da bola, leva em considera��o a velocidade atual, a varia��o de tempo e a for�a resultante atuando sobre a bola.
		 */
		bool calc_velocidade();
		/**
		 * Calcula a nova posi��o da bola, levando em considera��o a velocidade e a varia��o de tempo.
		 */
		bool calc_deslocamento();
		/**
		 * Calcula todos os atributos da bola mas, n�o altera os atributos atuais.
		 *
		 * \param *c Campo
		 * \param n_robos_por_time N�mero de rob�s por time.
		 * \param **time1 Vetor que cont�m todos os rob�s do primeiro time.
		 * \param **time2 Vetor que cont�m todos os rob�s do segundo time.
		 */
		bool calc_atributos(campo *c, int n_robos_por_time, robo *time1[N_JOGADORES_POR_TIME], robo *time2[N_JOGADORES_POR_TIME]);
		/**
		 * Atualiza os atributos da bola, utilizando os novos atributos calculados pelo m�todo calc_atributos.
		 */
		bool atualizar_atributos();
		/**
		 * Preve a nova posi��o da bola, utiliza os m�todos preverX e preverY.
		 */
		bool prever();
};

#endif
