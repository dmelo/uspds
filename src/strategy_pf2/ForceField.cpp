#include "ForceField.h"
#include <math.h>

#define PI  3.1415926535897932384626433832795
tVector sum,sub,mult;

//inicialização
void tVector::initialize()
{
  x = 0; y = 0;
  theta=0;
  module=0;
}
//construtor com cópia
tVector::tVector(const tVector &C)
{
  x = C.x;
  y = C.y;
  module = C.module;
  theta = C.theta;
}
//operador de atribuicao
void tVector::operator=(const tVector &C)
{
  if (this != &C)
  {
      x = C.x;
      y = C.y;
      module = C.module;
      theta = C.theta;
  }
}

//operador de atribuicao
void tVector::operator+=(const tVector &C)
{
      x += C.x;
      y += C.y;
      if(x == 0) x = 0.00000001;
      theta = atan2(y,x)*180/PI;
      module = sqrt(x*x + y*y);
}

// operador de soma
tVector& tVector::operator +(const tVector &C)
{

  sum = C;

  sum.x = x + C.x;
  sum.y = y + C.y;

  if(sum.x == 0)
    sum.x = 0.00000001;

  sum.theta = atan2(sum.y,sum.x)*180/PI;
  sum.module = sqrt(sum.x*sum.x + sum.y*sum.y);

  return sum;
}

// operador de subtração
tVector& tVector::operator -(const tVector &C)
{
  sub = C;

  sub.x = x - C.x;
  sub.y = y - C.y;

  if(sub.x == 0)
    sub.x = 0.0000001;

  sub.theta = atan2(sub.y,sub.x)*180/PI;
  sub.module = sqrt(sub.x*sub.x + sub.y*sub.y);

  return sub;
}

// operador de multiplica o módulo
tVector& tVector::operator *(double value)
{
  mult.module = module * value;
  mult.theta = theta;

  if(mult.module==0){
        mult.theta = 0;
        mult.x = 0;
        mult.y = 0;
  }else{
        mult.x = (mult.module * x)/module;
        mult.y = (mult.module * y)/module;
  }

  return mult;
}

void tForce::setXY(double distX, double distY)
{
	long double d,d3;

	d = sqrt(distX*distX + distY*distY);
	d3= d*d*d;

	if(d==0)
	{
		x = 0; y=0; module=0; theta=0;
	}
	else
	{
		x = distX / d3;
		y = distY / d3;

		module = 1/(d*d);

		if(x==0)
			x = 0.0000001;

		theta = atan2(y,x)*180/PI;
	}
}

void tForce::setXYMod(double distX, double distY, double d)
{
	double a;
	int sinalx,sinaly;
   if(distX == 0) distX = 0.000000001;
   a = distY/distX;


	sinalx = distX<0? -1: 1;
	sinaly = distY<0? -1: 1;

	x = d / sqrt(1+a*a);
	y = fabs(a * x);

	x *= sinalx;
	y *= sinaly;

	module = d;
   if(x == 0) x = 0.000000001;

	theta = atan2(y,x)*180/PI;
}

void tForce::setMT(double mod, double direction)
{
	module = mod;
	theta = direction;

	x= mod * cos((theta*PI)/180.0);
	y= mod * sin((theta*PI)/180.0);
}
