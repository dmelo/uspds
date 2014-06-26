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

	src/lib/vetor2d.h
*/

#ifndef VETOR2D_H
#define VETOR2D_H

/**
 * \file vetor2d.h
 *
 * \author Diogo Oliveira de Melo
 * \date 21/10/2005
 */


/**
 * Classe para manipular vetores em duas dimensões.
 */
class vetor2d {
	public:
		///O construtor.
		vetor2d();

		/**
		 * Construtor que inicializa o vetor2d com as coordenadas (x, y), passadas por parâmetro.
		 *
		 * \param x Coordenada x.
		 * \param y Coordenada y.
		 */
		vetor2d(const float x, const float y);

		/**
		 * Sobrecarrega o operador de atribuição. 
		 *
		 * \param &b Objeto que será atribuido.
		 */
		void operator=(const vetor2d &b);

		/**
		 * Atruibui a função de multiplicação, entre um vetor2d e um escalar, ao operador *.
		 *
		 * \param escalar Número, escalar, que será multiplicado pelo vetor2d.
		 * \return Atribui o resultado da multiplicação entre o vetor2d e o escalar.
		 */
		vetor2d operator*(const float escalar);

		/**
		 * Atruibui a função de divisão, entre um vetor2d e um escalar, ao operador /.
		 *
		 * \param escalar Número, escalar, pelo qual o vetor2d será dividido.
		 * \return Atribui o resultado da divisão entre o vetor2d e o escalar.
		 */

		vetor2d operator/(const float escalar);

		/**
		 * Calcula o produto escalar entre os dois vetor2des fornecidos.
		 *
		 * \param &b Vetor que será usado como operando para calcular o produto escalar.
		 * \return Retorna o produto escalar entre os dois vetor2des.
		 */
		float operator*(const vetor2d &b);

		/**
		 * Atribui a função de soma, entre dois vetor2des, ao operador +.
		 *
		 * \param &b Um dos vetor2des da soma.
		 * \return Atribui o resultado da adição dos vetor2des.
		 */
		vetor2d operator+(const vetor2d &b);

		/**
		 * Adiciona o vetor2d, do lado direito do operador, ao vetor2d do lado esquerdo.
		 * \param &b O vetor2d a ser somado.
		 * \return Atribui o resultado da adição do vetor2d.
		 */
		void operator+=(const vetor2d &b);

		/**
		 * Atribui a função de subtração, entre dois vetor2des, ao operador -.
		 *
		 * \param &b Um dos vetor2des da subtração.
		 * \return Atribui o resultado da subtração dos vetor2des.
		 */
		vetor2d operator-(const vetor2d &b);

		/**
		 * Atribui os valores dados às coordenadas x e y, do vetor2d.
		 *
		 * \param x Coordenada x.
		 * \param y Coordenada y.
		 */
		void setXY(const float x, const float y);

		/**
		 * Atribui o valor fornecido ao módulo do vetor2d.
		 *
		 * \param modulo Novo módulo do vetor2d.
		 */
		void setModulo(const float modulo);

		/**
		 * Atribui o valor fornecido ao ângulo do vetor2d.
		 *
		 * \param ang Novo ângulo, em radianos, do vetor2d.
		 */
		void setAng(const float ang);

		/**
		 * Atribui o valor fornecido ao ângulo do vetor2d.
		 *
		 * \param ang Novo ângulo, em graus, do vetor2d.
		 */
		void setAngGraus(const float ang);

		/**
		 * Fornece o valor da coordenado x.
		 *
		 * \return Retorna a coordenada x.
		 */
		float getX();

		/**
		 * Fornece o valor da coordenada y.
		 *
		 * \return Retorna a coordenada y.
		 */
		float getY();

		/**
		 * Fornece o valor do módulo do vetor2d.
		 *
		 * \return Retorna o valor do módulo do vetor2d.
		 */
		float getModulo();

		/**
		 * Fornece o valor do ângulo do vetor2d, em radianos.
		 *
		 * \return Retorna o valor do ângulo do vetor2d, em radianos.
		 */
		float getAng();

		/**
		 * Fornece o valor do ângulo do vetor2d em graus.
		 *
		 * \return Retorna o valor do ângulo do vetor2d, em graus.
		 */
		float getAngGraus();

		/**
		 * Retorna a projeção do vetor em relação ao angulo base.
		 *
		 * \param base Angulo ao qual o vetor será decomposto.
		 *
		 * \return retorna o vetor decomposto.
		 */
		vetor2d decompor(float base);
	private:
		float x;
		float y;
		float modulo;
		float ang;
		void atualizar();
};

#endif
