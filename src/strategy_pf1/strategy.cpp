// Strategy.cpp : Defines the entry point for the DLL application.
//
#define STRATEGY_EXPORTS
#define _STDC_

//#include "stdafx.h"
#include "strategy.h"
#include "futbot.h"
#include "basicMove.h"
#include "ForceField.h"
#include "../strategy/base.h"
#include <math.h>


//#define GRAVAR_DADO

//um ou outro (REDE, TECLADO, FUNCAO)
#define FUNCAO

float pIn[NO_OF_IN_UNITS];
float pOut[NO_OF_OUT_UNITS];


/*BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	

    

	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}*/

char myMessage[200]; //big enough???

///////////////////////////////////////
// Constants that have to be optimized.
int Q; //20
int Qi; //5
///////////////////////////////////////

float best_gaussian(float *y);
FILE *arq;

/*extern "C" STRATEGY_API void Create ( Environment *env )
{
	// allocate user data and assign to env->userData
	// eg. env->userData = ( void * ) new MyVariables ();
	Init_Net();

	//env->lastBall.pos.x = (FRIGHTX+FLEFTX)/2;
	//env->lastBall.pos.y = (FBOT+FTOP)/2;

	#ifdef GRAVAR_DADO
	arq = fopen("c:\\strategy\\rastroVFF.txt","wt");
	#endif
}

extern "C" STRATEGY_API void Destroy ( Environment *env )
{
	// free any user data created in Create ( Environment * )

	// eg. if ( env->userData != NULL ) delete ( MyVariables * ) env->userData;
	#ifdef GRAVAR_DADO
	fclose(arq);
	#endif
}*/



void Defesa(Environment *env, Robot *robot, int X)
{
	double py,px,a,b,Y;
	//Ball predictedBall;

   #ifdef BLUE
		px = GRIGHT;
	#else
		px = GLEFT;
	#endif
	py = GTOPY - (GTOPY-GBOTY)/2;

	//PredictBall(env, predictedBall);

	EquacaoReta(px,py,env->currentBall.pos.x,env->currentBall.pos.y,a,b);
   Y = a * X + b;

#ifdef BLUE
	if(env->currentBall.pos.x > X+3)
		Y = py;
	else if(env->currentBall.pos.x > X-12)
	{
		X = (double) env->currentBall.pos.x; Y = (double) env->currentBall.pos.y;
	}
	
#else
	if(env->currentBall.pos.x < X-3)
		Y = py;
	else if(env->currentBall.pos.x < X+12)
	{
		X = env->currentBall.pos.x; Y = env->currentBall.pos.y;
	}	
#endif

   if(robot == env->home) //goleiro
	{
		if(Y > GTOPY+6) Y = GTOPY + 5;
		else if(Y < GBOTY-6) Y = GBOTY - 5;
	}

GotoXY(robot,X,Y);	

}

int chute;
void FollowBall(Environment *env, Robot *robot)
{
	const int K=1;
	
	tForce F,Fa,Fr,Fro,Fbola;
	//Ball predictedBall;
	double dx,dy,px,py,aux;
	int i;
	double j,k,a,b,ra,rb;

	//PredictBall(env, predictedBall);
	//calculo da força de atraçao com a bola
	dx = env->currentBall.pos.x - robot->pos.x;
	dy = env->currentBall.pos.y - robot->pos.y;
	
	Fa.setXYMod(dx,dy,K); //módulo constante

	//para cada robô calcular a força de repulsao
	/*for(i=0; i<5; i++)
	{
		if(robot != env->home+i)
		{
			dx = env->home[i].pos.x - robot->pos.x;
			dy = env->home[i].pos.y - robot->pos.y;

			F.setXY(dx,dy);
			Fr = Fr - F;
		}

		
		dx = env->opponent[i].pos.x - robot->pos.x;
		dy = env->opponent[i].pos.y - robot->pos.y;

		F.setXY(dx,dy);
		Fro = Fro - F;
	}
	if(robot == env->home + 2) {
	    dx = env->home[3].pos.x - robot->pos.x;
	    dy = env->home[3].pos.y - robot->pos.y;
	    Fr.setXY(-dx, -dy);
	}*/


	//para fazer o robô encontrar o ângulo certo para chutar a bola!
	py = (GTOPY + GBOTY)/2;
	#ifdef BLUE
		px = GLEFT;
	#else
		px = GRIGHT;
	#endif

	//encontrado o ponto atras da reta que direciona para o gol
	EquacaoReta(px,py,env->currentBall.pos.x,env->currentBall.pos.y,a,b);
	dx = 10.0 / sqrt(a*a + 1); //circunferencia de raio 6
	dy = dx * a;

	//econtrar o coeficiente angular entre o gol e o robo (ra)
	EquacaoReta(px,py,robot->pos.x,robot->pos.y,ra,rb);

	px = env->currentBall.pos.x;
	py = env->currentBall.pos.y;
		
	//se o robô nao estiver na faixa permitida para chute entao
	//bola repele e ponto atrás da bola atrai (se o ponto estiver no campo)
	//faixa permitida inclinacao da reta bola-ponto menos a a inclinacao da reta bola-robo
	//ou seja se dejejarmos uma fatia de 5° entao |ra-a|=tan(5°)
	//EquacaoReta(robot->pos.x,robot->pos.y,predictedBall.pos.x,predictedBall.pos.y,ra,rb);
	
	//if(py < FTOP && py > FBOT && px > FLEFTX && px < FRIGHTX)
	//if(fabs(dx)>3 || fabs(dy)>2)
	
    rb = fabs(fabs(ra)-fabs(a)); //subtracao dos coeficientes angulares

#ifdef BLUE
	if(robot->pos.x < env->currentBall.pos.x || rb > 0.364) //20 graus
#else
	if(robot->pos.x > env->currentBall.pos.x || rb > 0.364) //20 graus
#endif
	if(py > FBOT && py < FTOP) //se o ponto está dentro do campo
	{
		//novo ponto de atração atrás da bola
		dx = px - robot->pos.x;
		dy = py - robot->pos.y;
		Fa.setXYMod(dx,dy,K);
		
		//bola repele
		dx = env->currentBall.pos.x - robot->pos.x;
		dy = env->currentBall.pos.y - robot->pos.y;
		F.setXY(dx,dy); //bola repelindo
		F = F*2;
		Fr = Fr - F;  //repele na 2*intensidade dos amigos)
	}
			
	//Força Resultante
	Fr = Fr  * Q;
	Fro= Fro * Qi;
	
	F = Fr + Fro;
	F = F + Fa;
	//Fa.setXY(((FRIGHTX + FLEFTX) / 2) - robot->pos.x, ((FTOP + FBOT) / 2) - robot->pos.y);
	//F = Fa + Fr;

	//GotoXY(robot, ((FRIGHTX + FLEFTX) / 2), ((FTOP + FBOT) / 2));
	Goto(robot,F.ang());		
}



float best_gaussian(float *y)
{	
	float min_err, b, xi, err, a=0.0, aux=0.0;
	int i;
  
	min_err = 100000.0;
	for (b=-180.0; b<=528.0; b+=12.0 )
		{
			err = 0.0;
			for ( i=0; i < 60; i++ )
				{
					xi = (float) (i-15) * 12.0;
					aux = (float)exp((double)(-1)*((xi - b)*(xi - b)) * 50);
					err += (y[i]  - aux)* (y[i]  - aux);
				}
			if (err < min_err)
				{
					min_err = err;
					a = b;
				}
		}      
  
	return  a;
  
}




// Estrategia p/ 4 robos

//extern "C" STRATEGY_API void Strategy ( Environment *env )
int main(int argc, char **argv) {
    Environment *env = new Environment();
    base *cp = new base((int) (argv[2][0] - '0'));

    if(argc < 5) {
	cerr << "usage ./bin/strategy_pf2 hostname team_number Q Qi" << endl;
	exit(1);
    }

    if(argc >= 8 && strcmp(argv[3], "-set_ports") == 0) {
	sscanf(argv[4], " %d ", &(cp->p_es));
	sscanf(argv[5], " %d ", &(cp->p_er));
	printf("strategy_pf2: ports: send %d. recv %d.\n", cp->p_es, cp->p_er);
	sscanf(argv[6], " %d ", &Q);
	sscanf(argv[7], " %d ", &Qi);

    } else {
	sscanf(argv[3], " %d ", &Q);
	sscanf(argv[4], " %d ", &Qi);
	if(cp->get_team_number() == 1) {
	    cp->p_es = PORTA_E1_RECV;
	    cp->p_er = PORTA_E1_SEND;
	} else {
	    cp->p_es = PORTA_E2_RECV;
	    cp->p_er = PORTA_E2_SEND;
	}
    }

    cp->set_hostname(argv[1]);
    cp->conct();

    while(1) {
	cp->rcv();

	env->lastBall.pos.x = env->currentBall.pos.x;
	env->lastBall.pos.y = env->currentBall.pos.y;
	//printf("========= begin\n");
	env->currentBall.pos.x = cp->uspds_to_fira_x(cp->get_bx());
	env->currentBall.pos.y = cp->uspds_to_fira_y(cp->get_by());
	for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
		env->home[i].pos.x = cp->uspds_to_fira_x(cp->get_pax(i));
		env->home[i].pos.y = cp->uspds_to_fira_y(cp->get_pay(i));
		env->home[i].rotation = cp->uspds_to_fira_a(cp->get_paa(i));
		env->opponent[i].pos.x = cp->uspds_to_fira_x(cp->get_pbx(i));
		env->opponent[i].pos.y = cp->uspds_to_fira_y(cp->get_pby(i));

	}

	FollowBall(env, env->home+2);
	FollowBall(env, env->home+1);
	FollowBall(env, env->home+0);

	
	//printf("\n\n");
	for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
	    cp->set_vel(i, cp->fira_to_uspds_vel(env->home[i].velocityLeft), cp->fira_to_uspds_vel(env->home[i].velocityRight));
	}
	cp->snd();
    }

	return 0;
}
