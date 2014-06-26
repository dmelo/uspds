#include "basicMove.h"
#include <math.h>

void Velocity ( Robot *robot, int vl, int vr )
{
	robot->velocityLeft = vl;
	robot->velocityRight = vr;
}

// robot soccer system p329
void Angle ( Robot *robot, int desired_angle)
{
	int theta_e, vl, vr;
	theta_e = desired_angle - (int)robot->rotation;
	
	while (theta_e > 180) theta_e -= 360;
	while (theta_e < -180) theta_e += 360;

	if (theta_e < -90) theta_e += 180;
	
	else if (theta_e > 90) theta_e -= 180;

	if (fabs(theta_e) > 50) 
	{
		vl = (int)(-9./90.0 * (double) theta_e);
		vr = (int)(9./90.0 * (double)theta_e);
	}
	else if (fabs(theta_e) > 20)
	{
		vl = (int)(-11.0/90.0 * (double)theta_e);
		vr = (int)(11.0/90.0 * (double)theta_e);
	}
	Velocity (robot, vl, vr);
}

//a velocidade de rotação depende do valor do angulo desejado
//quando maior a distancia a ser girada maior será a velocidade
void Goto( Robot *robot, double destino)
{
	double origem,theta, mod_theta;
	double VelMAX; //velocidade máxima
	int vel; bool inverte=false;

	origem = robot->rotation; //[-180,180]
	
	while(true)
	{
	  while(origem > 180)
			origem = origem - 360.0;
      while(destino > 180)
			destino = destino - 360.0;

		theta = (destino - origem); //destino - origem

		if(theta > 180) //existe uma distancia menor anti-horário
			theta = theta - 360;
		else if(theta < -180)
			theta = theta + 360;

		mod_theta = fabs(theta);

		//inverter o robô -- passa a andar para trás
		if(mod_theta > 90)  //meta está atrás do robô
		{
			origem += 180;
			inverte = true;
		}
		else
			break;

	} //end while(true)

	
  //vel varia entre 125 e -125 para theta entre 0 e 90 respectivamente
  //quando theta=0 [125,125], theta=90 [125,-125]
  //para theta negativo inverta as velocidades das rodas da dir com esq: theta=-90 [-125,125]
  // reta que transforma ang em vel
  //a = 250/90; //a=deltaY/deltaX
  //b = 125;    //yo = ax + b => b= yo - ax

  //vel = (int)(1.422222222*fabs(theta) + 64 );
   VelMAX = -1.388888889*mod_theta + 126;
	vel = (int)(2.777777778*mod_theta + VelMAX);

	if(vel < 0)
	    vel += 10;
	else
	    vel -= 10;
    
  if(theta < 0) 
  {
	if(inverte) Velocity(robot,(int) -VelMAX,(int) -vel);
	else Velocity(robot,(int) vel,(int) VelMAX);  //-- virar para esquerda
  }
  else  //virar para direita
  {
 	if(inverte) Velocity(robot,(int) -vel,(int) -VelMAX);
	else Velocity(robot,(int) VelMAX,(int) vel);   //-- virar para esquerda
  }
	  
}

void GotoXY( Robot *robot, double x, double y )
{
	int desired_angle;
	double dx, dy;

	dx = x - robot->pos.x;
	dy = y - robot->pos.y;

	if(dx==0) dx=0.0000001;

	desired_angle = (int)( atan2(dy,dx)*180/M_PI );

	if(fabs(x-robot->pos.x)>1 || fabs(y-robot->pos.y)>1)
		Goto(robot,desired_angle);
	else
		Velocity(robot,0,0);
}


void PredictBall ( Environment *env, Ball predictedBall )
{
	double dx = env->currentBall.pos.x - env->lastBall.pos.x;
	double dy = env->currentBall.pos.y - env->lastBall.pos.y;
	predictedBall.pos.x = env->currentBall.pos.x + dx;
	predictedBall.pos.y = env->currentBall.pos.y + dy;
}


void EquacaoReta(double poX, double poY, double pX, double pY, double &a, double &b)
{
	double dx,dy;
	if(poX < pX)
	{
		dx = pX - poX;
		dy = pY - poY;
	}
	else
	{
		dx = poX - pX;
		dy = poY - poY;
	}
	
	a = dy/dx;
	b = poY - a * poX;
}
