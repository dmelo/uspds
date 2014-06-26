#ifndef M_PI
#define M_PI 3.1415923
#endif

#include "strategy.h"

void PredictBall ( Environment *env, Ball b );
void Velocity ( Robot *robot, int vl, int vr );
void Angle ( Robot *robot, int desired_angle );
void Goto (Robot *robot, double desired_angle );
void GotoXY( Robot *robot, double x, double y );


void EquacaoReta(double pontoInicialX, double pontoInicialY, double pontofinalX, double pontofinalY, double &a, double &b);

