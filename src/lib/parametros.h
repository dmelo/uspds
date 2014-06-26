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

	src/lib/parametros.h
*/

#ifndef PARAMETROS_H
#define PARAMETROS_H

#define CST_ERRO 0.002

#define N_SIMULATORS_PER_TIME 200

// definnindo portas.
#define PORTA_GUI 4321
#define PORTA_E1_SEND 4322
#define PORTA_E1_RECV 4323
#define PORTA_E2_SEND 4324
#define PORTA_E2_RECV 4325

#define END_FLOAT 1234.0

#define N_QUADROS_POR_SEGUNDO 30
#define N_ITERACOES_COLISAO 2
#define TEMPO_POR_QUADRO 0.000111111 //Tempo por quadro em segundos.
#define N_JOGADORES_POR_TIME 3
#define SIZE_STACK 60 // 0.1 seg

//#define N_ITERACOES_COLISAO 8
//#define TEMPO_POR_QUADRO 0.001 //Tempo por quadro em segundos.



#define K_GRAVIDADE 9.6 // 9.6 m/s^2.
#define K_DENSIDADE_DO_AR 1.2 // kg/m^3
#define K_COEFICIENTE_DE_ARRASTO_ESFERA 0.47
#define K_FATOR_GEOMETRICO_ESFERA 0.4

#define BOLA_RAIO 0.02135 // raio da bola em metros
#define BOLA_MASSA 0.050 // massa da bola em kilos
#define BOLA_ROBO_ELASTICIDADE 0.7 // coeficiente de restituicao da velocidade da bola, nas colisões com um robô.
#define BOLA_ROBO_VARIACAO_ANGULAR 0.436129 // determina a variacao angular em torno do vertice do robo, q separa colisao entre a aresta e o vertice.
#define BOLA_RESISTENCIA_ROLAGEM 0.055
#define BOLA_CAMPO_ELASTICIDADE 0.7

#define ROBO_ARESTA 0.075 // tamanho da aresta do robô.
//#define ROBO_MASSA 0.5 // massa (em kg) do robô.
#define ROBO_MASSA 0.2 // massa (em kg) do robô.
//#define ROBO_K_ATRITO_ESTATICO_RODAS 0.9
#define ROBO_K_ATRITO_ESTATICO_RODAS 10
//#define ROBO_K_ATRITO_CINETICO_RODAS 0.95
#define ROBO_K_ATRITO_CINETICO_RODAS 10
#define ROBO_K_ATRITO_ESTATICO_LATERAIS 0.4
#define ROBO_K_ATRITO_CINETICO_LATERAIS 0.35
//#define ROBO_MAX_VELOCIDADE 0.5 // Velocidade máxima do robô em m/s.
//#define ROBO_MIN_VELOCIDADE -0.5 // Velocidade mínima do robô em m/s.
#define ROBO_MAX_VELOCIDADE 1.0 // Velocidade máxima do robô em m/s.
#define ROBO_MIN_VELOCIDADE -1.0 // Velocidade mínima do robô em m/s.

#define ROBO_FORCA_MAX 3 // força máxima q cada robo é capaz de fazer.
//#define ROBO_FORCA_MAX 10 // força máxima q cada robo é capaz de fazer.
#define ROBO_FORCA_MAX_2 (ROBO_FORCA_MAX / 2)
#define ROBO_K_ATRITO ((ROBO_FORCA_MAX * 30) / ( K_GRAVIDADE * ROBO_MAX_VELOCIDADE * ROBO_MASSA)) // Resistencia ao movimento.
#define ROBO_CAMPO_ELASTICIDADE 0.5
#define ROBO_ROBO_ELASTICIDADE 1.0
#define ROBO_ROBO_AFASTAMENTO (2 * ROBO_MAX_VELOCIDADE * TEMPO_POR_QUADRO)
//#define ROBO_MAX_V_ANGULAR (ROBO_MAX_VELOCIDADE / (2 * M_PI * (ROBO_ARESTA / 2)))
//#define ROBO_MIN_V_ANGULAR ((-1) * (ROBO_MAX_VELOCIDADE / (2 * M_PI * (ROBO_ARESTA / 2))))
#define ROBO_MAX_V_ANGULAR (ROBO_MAX_VELOCIDADE / (2 * M_PI * (ROBO_ARESTA)))
#define ROBO_MIN_V_ANGULAR ((-1) * (ROBO_MAX_VELOCIDADE / (2 * M_PI * (ROBO_ARESTA))))
#define ROBO_RAIO_RODA 0.018 // Raio da roda (em m)
#define ROBO_MASSA_RODA 0.01 // Massa da roda (em Kg)
#define ROBO_RAIO_EIXO 0.0015 // Raio do eixo (em m)
#define ROBO_MASSA_EIXO 0.002 // Massa do eixo (em Kg)
#define ROBO_RAIO_ENGRENAGEM 0.075 // Raio primitivo da engrenagem (em m)
#define ROBO_MASSA_ENGRENAGEM 0.02 // Massa da engrenagem (em Kg)
#define ROBO_MOMENTO_INERCIA_2 (((ROBO_MASSA_RODA * ROBO_RAIO_RODA * ROBO_RAIO_RODA) + (ROBO_MASSA_EIXO * ROBO_RAIO_EIXO * ROBO_RAIO_EIXO) + (ROBO_MASSA_ENGRENAGEM * ROBO_RAIO_ENGRENAGEM * ROBO_RAIO_ENGRENAGEM)) / 2) // Momento de inércia (Kg m^2) de uma roda (levando em consideração o pinhão do motor, a engrenagem e a roda.
#define ROBO_REDUCAO 3 // Medida da redução entre o eixo do motor e a roda.
#define ROBO_MOTOR_RENDIMENTO 0.6
#define ROBO_MOTOR_RESISTENCIA_TORQUE 0.006414 // Medido em Nm/A
#define ROBO_V_MAX 7.4 // Medida em Volts. Representa a voltagem máxima aplicada ao robô.
#define ROBO_MOTOR_RESISTENCIA_ELETRICA 6.41 // Medida em Ohms.
#define ROBO_MOTOR_RESISTENCIA_ROTACAO 0.00505 // Medida em V s / rad.
#define ROBO_K_ATRITO_ENGRENAGENS 1

#define ROBO_Kg 0.006414 // Resitência de rotação do motor (em Vs/rad).
#define ROBO_Re 0.075 // Raio da engrenagem (em m).
#define ROBO_Rp 0.0015 // Raio do pinhão (em m).
#define ROBO_Rm 6.41 // Resistência elétrica do motor (em Ohms)
#define ROBO_Rr 0.018 // Raio da roda.
#define ROBO_Jr 0.0006125 // Momento de inércia de todo o robô (em Kgm^2)


#define ROBO_FORCA_MAXIMA_ESQUERDA ((ROBO_REDUCAO * ROBO_MOTOR_RENDIMENTO * ROBO_MOTOR_RESISTENCIA_TORQUE * ROBO_V_MAX) / (ROBO_RAIO_RODA * ROBO_MOTOR_RESISTENCIA_ELETRICA))

#define ROBO_FORCA_MAXIMA_DIREITA ROBO_FORCA_MAXIMA_ESQUERDA

#define STRATEGY_TO_SIMULATOR_VOLT 0

#define CAMPO_LARGURA 1.50  //largura do campo em metros
#define CAMPO_ALTURA 1.30 // altura do campo em metros.
#define CAMPO_LADO_TRIANGULO 0.07 // lado do triângulo isóceles em metros.
#define CAMPO_N_PONTOS 16
#define CAMPO_GOL_TAMANHO 0.4
#define CAMPO_GOL_PROFUNDIDADE 0.1
#define CAMPO_X_MIN 0
#define CAMPO_X_MAX (CAMPO_LARGURA + (2 * CAMPO_GOL_PROFUNDIDADE))
#define CAMPO_Y_MIN 0
#define CAMPO_Y_MAX CAMPO_ALTURA
#define CAMPO_DIAGONAL sqrtf(powf(CAMPO_ALTURA, 2) + powf(CAMPO_X_MAX, 2))
#define CAMPO_AREA_GOL_ALTURA 0.7
#define CAMPO_AREA_GOL_LARGURA 0.15

// Constants of FIRA simulator
#define FTOP 77.2392
#define FBOT 6.3730
#define GTOPY 49.6801
#define GBOTY 33.9320
#define GRIGHT 97.3632
#define GLEFT 2.8748
#define FRIGHTX 93.4259
#define FLEFTX 6.8118

#endif
//0.436129
