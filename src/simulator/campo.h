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

	src/simulator/campo.h
*/

/**
 * \file campo.h
 * \author Diogo Oliveira de Melo
 * \date 08-01-2007
 */

#ifndef CAMPO_H
#define CAMPO_H

#include"../lib/objeto.h"

/**
 * Classe que manipula os dados do campo.
 */
class campo : public objeto {
	private:
		float x[CAMPO_N_PONTOS]; ///< Contém as coordenadas, do eixo X, dos pontos que determinam o campo.
		float y[CAMPO_N_PONTOS]; ///< Contém as coordenadas, do eixo Y, dos pontos que determinam o campo.
		float a[CAMPO_N_PONTOS]; ///< Contém os ângulos perpendiculares às arestas do campo.

	public:
		/**
		 * Construtor da classe campo.
		 */
		campo();
		/**
		 * Retorna a coordenada X do ponto do campo.
		 *
		 * \param i Índice do ponto.
		 */
		float getX(int i);
		/**
		 * Retorna a coordenada Y do ponto do campo.
		 *
		 * \param i Índice do ponto.
		 */
		float getY(int i);
		/**
		 * Retorna o ângulo perpendicular a aresta do campo.
		 *
		 * \param i Índice do ponto.
		 */
		float getA(int i);

		/** Determine if the point is inside of the field.
		 *
		 * \param px Coordinate X of the point.
		 * \param py Coordinate Y of the point.
		 * \return Return true if the point is inside of the field, else return false.
		 */
		bool is_inside(float px, float py);
};

#endif
