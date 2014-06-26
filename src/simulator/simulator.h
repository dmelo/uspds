/*
	USPDroidsSimulator
	(C) 2007  Diogo Oliveira de Melo
	(c) 2008  Vinicius Reis

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

	src/simulator/simulator.h
*/

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include<time.h>
#include<string.h>
#include<iostream>
#include<stdio.h>
#include<strings.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>
#include<vector>
#include<errno.h>
#include<pthread.h>
#include"../lib/objeto.h"
#include"bola.h"
#include"robo.h"
#include"campo.h"
#include"../lib/protocolo.h"

struct eyes_client {
    struct sockaddr_in clientAddress;
    int clientSocket;
};

void exit_simulator();

class simulator {
	public:
		campo *c; ///< Campo.
		bola *b; ///< Bola. 
		robo *time1[N_JOGADORES_POR_TIME]; ///< Time 1.
		robo *time2[N_JOGADORES_POR_TIME]; ///< Time 2.
		int score_t1;
		int score_t2;
		int n_frames_ball_stoped;
		float last_ball_x, last_ball_y;

		/**
		 * Construtor da classe simulator. Begins the simulation with 3 robot on each side of the field.
		 */
		simulator();

		/**
		 * Verifica se todos os objetos do campo estão em posições fisicamente possíveis. Caso ocorra alguma anomalia, o método rearranja os objetos até que a anomalia desapareça.
		 */
		bool verify_objects();
		bool move_robot_ball(float dist, robo *r, bola *b);
		bool move_robot_robot(float dist, robo *r1, robo *r2);
		bool move_field_ball(float dist, campo *c, bola *b);
		bool move_field_robot(float dist, campo *c, robo *r);
		float dist_overlap_robot_robot(robo *r1, robo *r2);
		float dist_overlap_robot_ball(bola *b, robo *r);
		float dist_overlap_field_ball(bola *b, campo *c);
		float dist_overlap_field_robot(robo *r, campo *c);

		/**
		 * Verifies if a goal was scored.
		 *
		 * \param *b Ball object.
		 * \param *c Field object.
		 * \return If no goal was scored, 0 value is returned. If team 1 make the goal, value 1 is returned. The last possibility, if team 2 make the goal, value 2 is returned.
		 */
		int gol(bola *b, campo *c);

		/**
		 * Register more one goal for team 1.
		 */
		void t1_score();

		/**
		 * Register more one goal for team 2.
		 */
		void t2_score();

		/** 
		 * Gives the number of goals scored by team 1.
		 *
		 * return Return the number of goals scored by team 1.
		 */
		int t1_get_score();

		/**
		 * Gives the number of goals scored by team 2.
		 *
		 * return Return the number of goals scored by team 2.
		 */
		int t2_get_score();

		/**
		 * Initialize the score.
		 */
		void init_score();

		/**
		 * Generates a random number with uniform distribution U[-1,1].
		 *
		 * \return Returns a number between -1 and 1 with uniform distribution.
		 */
		static float uniform_distribution();

		/**
		 * Gives the random number to be added to on the position of the robot.
		 *
		 * \return Returns a random number to robot's position.
		 */
		static float add_random_robot_pos();

		/**
		 * Gives the random number to be added to on the angle of the robot.
		 *
		 * \return Returns a random number to robot's angle.
		 */
		static float add_random_robot_angle();

		/**
		 * Gives the random number to be added to on the position of the ball.
		 *
		 * \return Returns a random number to ball's position.
		 */
		static float add_random_ball();

		/**
		 * If a goal was scored, this method will put each robot on the right position and set the velocities of the objects to zero.
		 *
		 * \param gol See gol(bola *b, campo *c) for more information.
		 */
		void handle_gol(int gol);

		bool handle_foul();

		void reset_positions();
};

#endif
