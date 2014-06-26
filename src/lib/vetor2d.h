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
 * Classe para manipular vetores em duas dimens�es.
 */
class vetor2d {
	public:
		///O construtor.
		vetor2d();

		/**
		 * Construtor que inicializa o vetor2d com as coordenadas (x, y), passadas por par�metro.
		 *
		 * \param x Coordenada x.
		 * \param y Coordenada y.
		 */
		vetor2d(const float x, const float y);

		/**
		 * Sobrecarrega o operador de atribui��o. 
		 *
		 * \param &b Objeto que ser� atribuido.
		 */
		void operator=(const vetor2d &b);

		/**
		 * Atruibui a fun��o de multiplica��o, entre um vetor2d e um escalar, ao operador *.
		 *
		 * \param escalar N�mero, escalar, que ser� multiplicado pelo vetor2d.
		 * \return Atribui o resultado da multiplica��o entre o vetor2d e o escalar.
		 */
		vetor2d operator*(const float escalar);

		/**
		 * Atruibui a fun��o de divis�o, entre um vetor2d e um escalar, ao operador /.
		 *
		 * \param escalar N�mero, escalar, pelo qual o vetor2d ser� dividido.
		 * \return Atribui o resultado da divis�o entre o vetor2d e o escalar.
		 */

		vetor2d operator/(const float escalar);

		/**
		 * Calcula o produto escalar entre os dois vetor2des fornecidos.
		 *
		 * \param &b Vetor que ser� usado como operando para calcular o produto escalar.
		 * \return Retorna o produto escalar entre os dois vetor2des.
		 */
		float operator*(const vetor2d &b);

		/**
		 * Atribui a fun��o de soma, entre dois vetor2des, ao operador +.
		 *
		 * \param &b Um dos vetor2des da soma.
		 * \return Atribui o resultado da adi��o dos vetor2des.
		 */
		vetor2d operator+(const vetor2d &b);

		/**
		 * Adiciona o vetor2d, do lado direito do operador, ao vetor2d do lado esquerdo.
		 * \param &b O vetor2d a ser somado.
		 * \return Atribui o resultado da adi��o do vetor2d.
		 */
		void operator+=(const vetor2d &b);

		/**
		 * Atribui a fun��o de subtra��o, entre dois vetor2des, ao operador -.
		 *
		 * \param &b Um dos vetor2des da subtra��o.
		 * \return Atribui o resultado da subtra��o dos vetor2des.
		 */
		vetor2d operator-(const vetor2d &b);

		/**
		 * Atribui os valores dados �s coordenadas x e y, do vetor2d.
		 *
		 * \param x Coordenada x.
		 * \param y Coordenada y.
		 */
		void setXY(const float x, const float y);

		/**
		 * Atribui o valor fornecido ao m�dulo do vetor2d.
		 *
		 * \param modulo Novo m�dulo do vetor2d.
		 */
		void setModulo(const float modulo);

		/**
		 * Atribui o valor fornecido ao �ngulo do vetor2d.
		 *
		 * \param ang Novo �ngulo, em radianos, do vetor2d.
		 */
		void setAng(const float ang);

		/**
		 * Atribui o valor fornecido ao �ngulo do vetor2d.
		 *
		 * \param ang Novo �ngulo, em graus, do vetor2d.
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
		 * Fornece o valor do m�dulo do vetor2d.
		 *
		 * \return Retorna o valor do m�dulo do vetor2d.
		 */
		float getModulo();

		/**
		 * Fornece o valor do �ngulo do vetor2d, em radianos.
		 *
		 * \return Retorna o valor do �ngulo do vetor2d, em radianos.
		 */
		float getAng();

		/**
		 * Fornece o valor do �ngulo do vetor2d em graus.
		 *
		 * \return Retorna o valor do �ngulo do vetor2d, em graus.
		 */
		float getAngGraus();

		/**
		 * Retorna a proje��o do vetor em rela��o ao angulo base.
		 *
		 * \param base Angulo ao qual o vetor ser� decomposto.
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
