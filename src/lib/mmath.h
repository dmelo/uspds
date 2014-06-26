#ifndef GEOMETRY_H
#define GEOMETRY

/**
 * \file mmath.h
 *
 * \author Diogo Oliveira de Melo
 * \date 02/07/2008
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include<iostream>

using namespace std;


/**
 * Classe que contém métodos para calculos de geometria
 */
class mmath {
    public:
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
	 * Verify if the point (px, py) is inside of the convex poligon witch points is (x[i], y[i]) and every side connect the points (x[i], y[i]) to (x[i+1], y[i+1]).
	 */
	static bool point_inside_convex_polygon(float px, float py, float *x, float *y, int n_points);

	/**
	 * Create a histogram on the file filename using the GNUPlot format.
	 *
	 * \param *data Data that will form the histogram.
	 * \param n_bars Number of bars that will compose the histogram
	 * \param *filename File that will be used to store the histogram.
	 *
	 * \return Return true if no errors occurs.
	 */
	static bool histogram(vector<float> *data, int n_bars, char *filename);

	/**
	 * Calculates the mean of the numbers inside the vector data.
	 *
	 * \param *data Vector that contains values of a random variable.
	 *
	 * \return Return the mean of the random variable.
	 */
	static float mean(vector<float> *data);

	/**
	 * Calculates the variance of the numbers inside the vector data.
	 *
	 * \param *data Vector that contains values of a random variable.
	 *
	 * \return Return the variance of the random variable.
	 */
	static float variance(vector<float> *data);
};

#endif
