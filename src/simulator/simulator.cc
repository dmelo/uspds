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

    src/simulator/simulator.cc
*/

#include"simulator.h"

// Begins the simulation with 3 robot on each side of the field.

simulator::simulator() {
    c = new campo();
    b = new bola(((c->getX(0) + c->getX(15)) / 2) + add_random_ball(), ((c->getY(3) + c->getY(4)) / 2) + add_random_ball(), new vetor2d(0.0, 0.0), new vetor2d(0, 0));

    for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
	time1[i] = new robo((((c->getX(1) * 3) + c->getX(14)) / 4) + add_random_robot_pos(), (((c->getY(7) * (3 - i)) + (c->getY(0) * (i + 1))) / 4) + add_random_robot_pos(), add_random_robot_angle());
	time2[i] = new robo((((c->getX(14) * 3) + c->getX(1)) / 4) + add_random_robot_pos(), (((c->getY(7) * (3 - i)) + (c->getY(0) * (i + 1))) / 4) + add_random_robot_pos(), add_random_robot_angle());
    }
    n_frames_ball_stoped = 0;
}



int simulator::gol( bola *b, campo *c ) {
    if((b->getY() > c->getY(5) - BOLA_RAIO)||(b->getY() < c->getY(2) + BOLA_RAIO))
	return 0;
    if ( ( b->getX() < c->getX(2) - BOLA_RAIO ) && ( !b->colisao_bola_segmento( b->getX(), b->getY(), c->getX(2), c->getY(2), c->getX(5), c->getY(5) ) ) ) return 2;
    if ( ( b->getX() > c->getX(10) + BOLA_RAIO ) && ( !b->colisao_bola_segmento(b->getX(), b->getY(), c->getX(10), c->getY(10), c->getX(13), c->getY(13)) ) ) return 1;
    return 0;
}


bool simulator::handle_foul() {
    if((fabs(last_ball_x - b->getX()) * fabs(last_ball_x - b->getX())) + (fabs(last_ball_y - b->getY()) * fabs(last_ball_y - b->getY())) <= 0.005 * 0.005) n_frames_ball_stoped++;
    else n_frames_ball_stoped = 0;

    last_ball_x = b->getX();
    last_ball_y = b->getY();

    if(n_frames_ball_stoped >= N_QUADROS_POR_SEGUNDO * 10) { // Falta
	reset_positions();
	n_frames_ball_stoped = 0;
	return true;
    }
    return false;
}

void simulator::reset_positions() {
    b->setX(((c->getX(0) + c->getX(15))/2) + simulator::add_random_ball());
    b->setY(((c->getY(2) + c->getY(5))/2) + simulator::add_random_ball());
    b->setVelocidade( new vetor2d(0,0) );
    for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {

	time1[i]->setXY((((c->getX(1) * 3) + c->getX(14)) / 4) + simulator::add_random_robot_pos(), (((c->getY(7) * (3 - i)) + (c->getY(0) * (i + 1))) / 4) + simulator::add_random_robot_pos());
	time1[i]->setAng(simulator::add_random_robot_angle());

	time2[i]->setXY((((c->getX(14) * 3) + c->getX(1)) / 4) + simulator::add_random_robot_pos(), (((c->getY(7) * (3 - i)) + (c->getY(0) * (i + 1))) / 4) + simulator::add_random_robot_pos());
	time2[i]->setAng(simulator::add_random_robot_angle() + M_PI);


	time1[i]->setVelocidade(new vetor2d(0,0));
	time2[i]->setVelocidade(new vetor2d(0,0));
    }
}


void simulator::handle_gol(int gol) {
    if(!gol) return;

    reset_positions();

    if(gol == 1)
	t1_score();
    else
	t2_score();
    printf("placar: Azul %d X %d Amarelo", t1_get_score(), t2_get_score());
}

bool simulator::verify_objects() {
    bool finish, used = false;

    do {
	finish = true;
	float dist;
	for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
	    while((dist = dist_overlap_robot_ball(b, time1[i])) != 0.0) {
		finish = false;
		move_robot_ball(dist, time1[i], b);
		// afastar os objetos;
		//printf("Simulator: verify_objects: robot ball anomaly detected\n");
	    }
	    while((dist = dist_overlap_robot_ball(b, time2[i])) != 0.0) {
		finish = false;
		move_robot_ball(dist, time2[i], b);
		// afastar os objetos;
		//printf("Simulator: verify_objects: robot ball anomaly detected\n");
	    }
	    while((dist = dist_overlap_field_robot(time1[i], c)) != 0.0) {
		finish = false;
		move_field_robot(dist, c, time1[i]);
		//printf("Simulator: verify_objects: robot field anomaly detected\n");
	    }
	    while((dist = dist_overlap_field_robot(time2[i], c)) != 0.0) {
		finish = false;
		move_field_robot(dist, c, time2[i]);
		//printf("Simulator: verify_objects: robot field anomaly detected\n");
	    }
	    for(int j = 0; j < N_JOGADORES_POR_TIME; j++) {
		// time1 time2
		while((dist = dist_overlap_robot_robot(time1[i], time2[j])) != 0.0) {
		    finish = false;
		    move_robot_robot(dist, time1[i], time2[j]);
		    //printf("Simulator: verify_objects: robot robot anomaly detected\n");
		}
		// time1 time1
		if(i != j) {
		    while((dist =  dist_overlap_robot_robot(time1[i], time1[j])) != 0.0) {
			finish = false;
			move_robot_robot(dist, time1[i], time1[j]);
			//printf("Simulator: verify_objects: robot robot anomaly detected\n");
		    }
		    //time2 time2
		    while((dist =  dist_overlap_robot_robot(time2[i], time2[j])) != 0.0) {
			finish = false;
			move_robot_robot(dist, time2[i], time2[j]);
			//printf("Simulator: verify_objects: robot robot anomaly detected\n");
		    }
		}
	    }
	}
	
	while((dist = dist_overlap_field_ball(b, c)) != 0.0) {
	    finish = false;
	    move_field_ball(dist, c, b);
	    //printf("Simulator: verify_objects: field ball anomaly detected\n");
	}
	if(finish == false) used = true;
	finish = true;
    } while(!finish);
    //printf("verify_objects: terminei.\n");
    return used;
}

float simulator::dist_overlap_robot_robot(robo *r1, robo *r2) {
    if(objeto::distancia(r1->getNewX(), r1->getNewY(), r2->getNewX(), r2->getNewY()) > ROBO_ARESTA * sqrt(2))
	return 0.0;
    float p1x[4], p1y[4];
    float p2x[4], p2y[4];

    r1->getNewPontos(p1x, p1y);
    r2->getNewPontos(p2x, p2y);

    for(int i = 0; i < 4; i++)
	if(ROBO_ARESTA * ROBO_ARESTA == objeto::area_triangulo(p1x[i], p1y[i], p2x[0], p2y[0], p2x[1], p2y[1]) +
		objeto::area_triangulo(p1x[i], p1y[i], p2x[1], p2y[1], p2x[2], p2y[2]) +
		objeto::area_triangulo(p1x[i], p1y[i], p2x[2], p2y[2], p2x[3], p2y[3]) +
		objeto::area_triangulo(p1x[i], p1y[i], p2x[3], p2y[3], p2x[0], p2y[0]))
	    return 0.0005;
    for(int i = 0; i < 4; i++)
	if(ROBO_ARESTA * ROBO_ARESTA == objeto::area_triangulo(p2x[i], p2y[i], p1x[0], p1y[0], p1x[1], p1y[1]) +
		objeto::area_triangulo(p2x[i], p2y[i], p1x[1], p1y[1], p1x[2], p1y[2]) +
		objeto::area_triangulo(p2x[i], p2y[i], p1x[2], p1y[2], p1x[3], p1y[3]) +
		objeto::area_triangulo(p2x[i], p2y[i], p1x[3], p1y[3], p1x[0], p1y[0]))
	    return 0.0005;

    return 0.0;

}

float simulator::dist_overlap_robot_ball(bola *b, robo *r) {
    float dist_real = objeto::distancia(r->getNewX(), r->getNewY(), b->getNewX(), b->getNewY());
    if(dist_real > ROBO_ARESTA + BOLA_RAIO) return 0.0;
    float ang = atan2f(b->getNewY() - r->getNewY(), b->getNewX() - b->getNewX()) - r->getNewAng();

    ang = objeto::padronizar_angulo_pi_sobre_2(ang);
    if(ang > M_PI_4) ang = M_PI_2 - ang;
    float dist_min = ((ROBO_ARESTA / 2) + BOLA_RAIO) / cos(ang);
    if(dist_real < dist_min) return (dist_min - dist_real + 0.0002) / 2;

    return 0.0;
}

float simulator::dist_overlap_field_ball(bola *b, campo *c) {
    if((b->getNewX() > c->getX(7) + BOLA_RAIO)&&(b->getNewX() < c->getX(8) - BOLA_RAIO)&&(b->getNewY() > c->getY(1) + BOLA_RAIO)&&(b->getNewY() < c->getY(6) - BOLA_RAIO))
	return 0.0;

    for(int i = 0; i < CAMPO_N_PONTOS; i++) {
	if(b->colisao_bola_segmento(b->getNewX(), b->getNewY(), c->getX(i), c->getY(i), c->getX((i + 1)%CAMPO_N_PONTOS), c->getY((i + 1)%CAMPO_N_PONTOS)) || !c->is_inside(b->getNewX(), b->getNewY())) {
	    return 0.001;
	}
    }

    return 0.0;
}

float simulator::dist_overlap_field_robot(robo *r, campo *c){
    float robo_diagonal_2 = ROBO_ARESTA * sqrt(2) * 0.5;
    if((r->getNewX() > c->getX(7) + robo_diagonal_2)&&(r->getNewX() < c->getX(8) - robo_diagonal_2)&&(r->getNewY() > c->getY(1) + robo_diagonal_2)&&(r->getNewY() < c->getY(6) - robo_diagonal_2))
	return 0.0;

    for(int i = 0; i < CAMPO_N_PONTOS; i++) {
	//if(r->colisao_robo_segmento(c, i) != -1 || !c->is_inside(r->getNewX(), r->getNewY()))
	if(!c->is_inside(r->getNewX(), r->getNewY()))
	    return 0.0005;
    }

    return 0.0;
}

// dist detona a distância que cada objeto deve ser deslocado.
bool simulator::move_robot_ball(float dist, robo *r, bola *b) {
    float angb = atan2f(b->getNewY() - r->getNewY(), b->getNewX() - r->getNewX());

    b->setNewX(b->getNewX() + (dist * cos(angb)));
    b->setNewY(b->getNewY() + (dist * sin(angb)));

    angb += M_PI;
    r->setNewX(r->getNewX() + (dist * cos(angb)));
    r->setNewY(r->getNewY() + (dist * sin(angb)));

    return true;
}

bool simulator::move_robot_robot(float dist, robo *r1, robo *r2) {
    float angb = atan2f(r1->getNewY() - r2->getNewY(), r1->getNewX() - r2->getNewX());

    r1->setNewX(r1->getNewX() + (dist * cos(angb)));
    r1->setNewY(r1->getNewY() + (dist * sin(angb)));

    angb += M_PI;
    r2->setNewX(r2->getNewX() + (dist * cos(angb)));
    r2->setNewY(r2->getNewY() + (dist * sin(angb)));

    return true;
}

bool simulator::move_field_ball(float dist, campo *c, bola *b) {
    float cx = (c->getX(0) + c->getX(15)) / 2;
    float cy = (c->getY(0) + c->getY(7)) / 2;

    float angb = atan2f(cy - b->getNewY(), cx - b->getNewX());

    b->setNewX(b->getNewX() + (dist * cos(angb)));
    b->setNewY(b->getNewY() + (dist * sin(angb)));

    return true;
}

bool simulator::move_field_robot(float dist, campo *c, robo *r) {
    float cx = (c->getX(0) + c->getX(15)) / 2;
    float cy = (c->getY(0) + c->getY(7)) / 2;

    float angb = atan2f(cy - r->getNewY(), cx - r->getNewX());

    r->setNewX(r->getNewX() + (dist * cos(angb)));
    r->setNewY(r->getNewY() + (dist * sin(angb)));

    return true;
}

void simulator::init_score() { score_t1 = score_t2 = 0;}
void simulator::t1_score() { score_t1++;}
void simulator::t2_score() { score_t2++;}
int simulator::t1_get_score() { return score_t1;}
int simulator::t2_get_score() { return score_t2;}


float simulator::uniform_distribution() {
int num = rand() % 20000;
    num -= 10000;
    return ((float) num) / 10000;
}   

float simulator::add_random_robot_pos() {
    return uniform_distribution() * 0.03;
}

float simulator::add_random_robot_angle() {
    return uniform_distribution() * (M_PI / 8);
}

float simulator::add_random_ball() {
    return uniform_distribution() * 0.05;
}
