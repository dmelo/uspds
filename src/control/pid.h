#ifndef PID_H
#define PID_H

#include<string.h>
#include<stdio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include"../lib/parametros.h"

using namespace std;

class pid {
    private:
	int counter;
	FILE *fpid_log_des;
	FILE *fpid_log_ang;

	double P_des, I_des, D_des;
	double Kp_des, Ki_des, Kd_des;

	double P_ang, I_ang, D_ang;
	double Kp_ang, Ki_ang, Kd_ang;

	double erro_des[6];
	double erro_ang[6];
    public:
	pid();
	int controle_pid(double deslocamento, double angulo, int *ve, int *vd);
};

#endif
