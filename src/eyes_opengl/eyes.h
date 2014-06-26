/*
	USPDroidsSimulator
	(C) 2007  Anderson Henrique Constantino Maia
	(C) 2007  Diogo Oliveira de Melo
	(C) 2007  João Antônio Angelleti Guimarães

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

	src/eyes_opengl/eyes.h
*/

/**
 * \file eyes.h
 * \author Anderson Henrique Constantino Maia
 * \author Diogo Oliveira de Melo
 * \author João Antônio Angeletti Guimarães
 * \date 08-02-2007
 */

#ifndef EYES_H
#define EYES_H

#include<GL/gl.h>	     
#include<GL/glu.h>	    
#include<GL/glut.h>    
#include<stdio.h>      
#include<stdlib.h>     
#include<math.h>
#include<pthread.h>
#include<time.h>
#include<string.h>
#include<iostream>
#include<stdio.h>
#include<strings.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<math.h>
#include<unistd.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>
#include"../lib/parametros.h"
#include"../lib/objeto.h"
#include"../lib/protocolo.h"
#include"../simulator/campo.h"
#include"../revel/revel.h"

#define CAMPO_Z 0.05
#define CAMPO_THICK 0.025
#define CAMPO_LINE_THICK 0.004
#define VETOR_TAM  15 * 60 * 30

#define WIDTH  1680
#define HEIGHT 1050

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1
#define BRANCO   1.0, 1.0, 1.0
#define PRETO    0.1, 0.1, 0.1
#define LARANJA  0.8, 0.6, 0.1

#define AMARELO  1.0, 1.0, 0.0
#define AZUL     0.0, 0.0, 1.0

#define VERMELHO 1.0, 0.0, 0.0 //VERMELHO
#define VERDE    0.0, 1.0, 0.0 //VERDE
#define CYAN     1.0, 0.0, 1.0 //CYAN
#define ROSEO    0.7, 0.1, 0.6 //ROSEO
#define CINZA    0.6, 0.6, 0.6 //CINZA
#define MAGENTA  1.0, 0.0, 1.0 //MAGENTA

#define KEY_ESC 27
#define KEY_SPC 32

void init_scene();
GLvoid initGL();
void init_scene();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
void sair();
static void window_key(unsigned char key, int x, int y);
/**
 * Desenha o robô.
 *
 * \param id ID do robô que será desenhado.
 * \param px Coordenada X do robô.
 * \param py Coordenada Y do robô.
 * \param ang Âgnulo do robô.
 */
void robo(int id, float px, float py, float ang);
/**
 * Desenha todos  os objetos que compõem a cena.
 */
void render_scene();
/**
 * Contém o código que é executado antes da apresentação do jogo.
 */
void animation();
/**
 * Função reopnsável por coordenar função que forma a cena a cada período de tempo.
 */
void Timer(int value);
/**
 * Desenha um círculo paralelo ao plano XY, com centro e raio específicos.
 *
 * \param x Coordenada X do centro do círculo.
 * \param y Coordenada Y do centro do círculo.
 * \param z Coordenada Z do centro do círculo.
 * \param raio Raio do círculo.
 */
void circulo(float x, float y, float z, float raio);
/**
 * Desenha a cruz, utilizada nas marcações do campo.
 *
 * \param x Coordenada X do centro da figura.
 * \param y Coordenada Y do centro da figura.
 * \param z Coordenada Z do centro da figura.
 */
void cruz(float x, float y, float z);
/**
 * Desenha a marcação de Free-Ball no campo.
 *
 * \param x Coordenada X do centro da marcação.
 * \param y Coordenada Y do centro da marcação.
 * \param z Coordenada Z do centro da marcação.
 */
void free_ball(float x, float y, float z);
/**
 * Desenha o campo.
 */
void d_campo();
/**
 * Desenha a bola no ponto especificado por parâmetro.
 *
 * \param px Coordenada X do centro da bola.
 * \param py Coordenada Y do centro da bola.
 */
void bola(float px, float py);
/**
 * Grava as informções do jogo em um arquivo.
 * 
 * \param *filename Nome do arquivo em que será gravado o jogo.
 */
void record_file(char *filename);
/**
 * Grava as infrmações de um frame na estrutura de dados.
 *
 * \param *coorinates String que contém as informções de um quadro de jogo.
 */
void read_coordinates(char *coordinates);
/**
 * Função principal do OpenGL.
 */
void *opengl_main(void *p);
/**
 * Responsável por receber os dados do jogo, pelo socket.
 */
void *receve(void *p);
/**
 * Rotaciona a câmera em torno do eixo X ou Z.
 *
 * \param axis Eixo ao em torno do qual a câmera será rotacionada.
 * \param passo Angulo que será rotacionado (em graus).
 */
void rotate(char axis, int passo);
/**
 * Seta os parâmetros para a câmera global.
 */
void global_init();

#endif
