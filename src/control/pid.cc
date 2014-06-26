#include"pid.h"

pid::pid() {
    for(int i = 0; i < 6; i++) erro_des[i] = 0;
    for(int i = 0; i < 6; i++) erro_ang[i] = 0;


    /////////////////////////////
    Kp_des = 40;
    Kp_ang = 20;

    Ki_des = 27;
    Ki_ang = 5;
    //Ki_des = 0;
    //Ki_ang = 0;

    Kd_des = /*5*/0;
    Kd_ang = /*2*/ 0;


    counter = 0;

}

int pid::controle_pid(double deslocamento, double angulo, int *ve, int *vd) {
    double angulo_e;
    double tol_ang = 0.08;
    double tol_des = 0.02;

    if(fabs(deslocamento) < tol_des) deslocamento = 0;
    else if(deslocamento > 0) deslocamento += 0.07;
    else deslocamento -= 0.07;
    if(angulo < tol_ang || angulo > (2 * M_PI) - tol_ang) angulo = 0;
    if(angulo > M_PI - tol_ang && angulo < M_PI + tol_ang) angulo = M_PI;

    if(angulo < M_PI_2) angulo = angulo;
    if(angulo >= M_PI_2 && angulo < M_PI) angulo = angulo - M_PI;
    if(angulo >= M_PI && angulo < M_PI + M_PI_2) angulo = angulo - M_PI;
    if(angulo > M_PI + M_PI_2) angulo = angulo - (2 * M_PI);



    for(int i = 0; i < 3; i++) erro_des[i] = erro_des[i+1];
    erro_des[3] = deslocamento;
    for(int i = 0; i < 3; i++) erro_ang[i] = erro_ang[i+1];
    erro_ang[3] = angulo;

    // Proporcional
    P_des = deslocamento * Kp_des;
    P_ang = angulo * Kp_ang;

    I_des = 0;
    I_ang = 0;
    for(int i = 1; i < 4; i++) I_des += 0.0333 * erro_des[i] * Ki_des;
    for(int i = 1; i < 4; i++) I_ang += 0.0333 * erro_ang[i] * Ki_ang;
    //I_ang = 0;

    D_des = Kd_des * (erro_des[3] - erro_des[2]) / 0.0333;
    D_ang = Kd_ang * (erro_ang[3] + erro_ang[2] - erro_ang[1] - erro_ang[0]) / (4 * 0.0333);


    *ve = (int) (P_des - P_ang + I_des - I_ang + D_des - D_ang);
    *vd = (int) (P_des + P_ang + I_des + I_ang + D_des + D_ang);




    counter++;

    return 0;
}



/*int pid::controle_pid(double deslocamento, double angulo, int *ve, int *vd) {
    deslocamento_erro[0] = deslocamento_erro[1];               //faz as variaveis serem atualizadas pelo valor mais recente
    deslocamento_erro[1] = deslocamento_erro[2];
    deslocamento_erro[2] = fabs(deslocamento);          

    angulo_erro[0] = angulo_erro[1];               //faz as variaveis serem atualizadas pelo valor mais recente
    angulo_erro[1] = angulo_erro[2];
    angulo_erro[2] = angulo;          

    vs[0] = vs[1];                         //o pwm antigo pega o valor da ultima iteracao
    v_theta[0] = v_theta[1];                         //o pwm antigo pega o valor da ultima iteracao

    double q0, q1, q2;                     //define variaveis que serão usadas no método recursivo
    double To, Ti, Td, K;                  //define os ganhos do PID(K,Ti,Td) e o tempo do ciclo da visao To


    Ti = 0.0001;                            //valores dos ganhos
    Td = 0.0001;
    K  = 0.0001;
    To = 0.033;                            //ciclo da visao

    q0 = K*(1 + (Td/To));
    q1 = -K*(1 + (2*Td/To) - (To/Ti));
    q2 = K*(Td/To);

    vs[1] = vs[0] + q0*deslocamento_erro[2] + q1*deslocamento_erro[1] + q2*deslocamento_erro[0];

    Ti = 0.0001;                            //valores dos ganhos
    Td = 0.0001;
    K  = 0.0001;
    To = 0.033;                            //ciclo da visao

    q0 = K*(1 + (Td/To));
    q1 = -K*(1 + (2*Td/To) - (To/Ti));
    q2 = K*(Td/To);
    
    v_theta[1] = v_theta[0] + q0*angulo_erro[2] + q1*angulo_erro[1] + q2*angulo_erro[0];

    double dve, dvd;


    dve = v_theta[1];
    dvd = (2 * vs[1]) - v_theta[1];

    if(dve > 7.4) dve = 7.4;
    if(dve < -7.4) dve = -7.4;

    if(dvd > 7.4) dvd = 7.4;
    if(dvd < -7.4) dvd = -7.4;


    counter++;
    if(counter % 30 == 0) printf("v_theta: %f. vs: %f. dve: %f. dvd: %f.\n", v_theta[1], vs[1], dve, dvd);

    *ve = (int) (31 * (dve / 7.4));
    *vd = (int) (31 * (dvd / 7.4));

    return 0;
}*/
