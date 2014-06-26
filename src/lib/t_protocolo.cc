#include"protocolo.h"
#include<iostream>

using namespace std;

int main() {
    float bx = 5.0;
    float by = 4.0;
    float x[2 * N_JOGADORES_POR_TIME];
    float y[2 * N_JOGADORES_POR_TIME];
    float a[2 * N_JOGADORES_POR_TIME];

    float tax[N_JOGADORES_POR_TIME];
    float tay[N_JOGADORES_POR_TIME];
    float taa[N_JOGADORES_POR_TIME];
    float tbx[N_JOGADORES_POR_TIME];
    float tby[N_JOGADORES_POR_TIME];
    float tba[N_JOGADORES_POR_TIME];

    float aux = 1.0;

    int t1, t2;
    int dbx = 4, dby = 5;
    int dtax[N_JOGADORES_POR_TIME], dtay[N_JOGADORES_POR_TIME], dtaa[N_JOGADORES_POR_TIME];
    int dtbx[N_JOGADORES_POR_TIME], dtby[N_JOGADORES_POR_TIME], dtba[N_JOGADORES_POR_TIME];
    int dx[2 * N_JOGADORES_POR_TIME], dy[2 * N_JOGADORES_POR_TIME], da[2 * N_JOGADORES_POR_TIME];
    int auxd = 1;
    int px[CAMPO_N_PONTOS];
    int py[CAMPO_N_PONTOS];

    string t;

    for(int i = 0; i < 2 * N_JOGADORES_POR_TIME; i++) {
	x[i] = aux;
	aux += 0.1;
	y[i] = aux;
	aux += 0.1;
	a[i] = aux;
	aux += 0.1;
    }
    for(int i = 0; i < 2 * N_JOGADORES_POR_TIME; i++) {
	dx[i] = auxd++;
	dy[i] = auxd++;
	da[i] = auxd++;
    }
    auxd = 100;
    for(int i = 0; i < CAMPO_N_PONTOS; i++) {
	px[i] = auxd++;
	py[i] = auxd++;
    }

    t = protocolo::encode_strategy(bx, by, x, y, a);

    cout << t;

    cout << protocolo::decode_strategy(t, &bx, &by, tax, tay, taa, tbx, tby) << endl;
    printf("bx %f. by %f\n", bx, by);
    for(int i = 0; i < N_JOGADORES_POR_TIME; i++) printf("tax: %f. tay: %f. taa %f.\n", tax[i], tay[i], taa[i]);
    for(int i = 0; i < N_JOGADORES_POR_TIME; i++) printf("tbx: %f. tby: %f.\n", tbx[i], tby[i]);

    t = protocolo::encode_score(2, 1);
    cout << t;
    cout << protocolo::decode_score(t, &t1, &t2) << endl;
    cout << t1 << " X " << t2 << endl;
    string *g = new string("$R$4#5\n");
    cout << "fake: " << protocolo::decode_score(*g, &t1, &t2) << endl;
    cout << "time------------" << endl;
    cout << "time: " << protocolo::decode_time(protocolo::encode_time(4000), &t1) << endl;
    cout << "t1: " << t1 << endl;
    cout << "time2: " << protocolo:: decode_time("$T$9jkfjd\n", &t1) << endl;
    cout << "t1: " << t1 << endl;

    cout << "vision objects" << endl;
    int adbx, adby;
    int adtax[N_JOGADORES_POR_TIME], adtay[N_JOGADORES_POR_TIME], adtaa[N_JOGADORES_POR_TIME];
    int adtbx[N_JOGADORES_POR_TIME], adtby[N_JOGADORES_POR_TIME], adtba[N_JOGADORES_POR_TIME];
    cout << protocolo::decode_vision_objects(protocolo::encode_vision_objects(dbx, dby, dx, dy, da), &adbx, &adby, adtax, adtay, adtaa, adtbx, adtby, adtba) << endl;
    printf("dbx %d. dby %d\n", adbx, adby);
    for(int i = 0; i < N_JOGADORES_POR_TIME; i++) printf("dtax: %d. dtay: %d. dtaa %d.\n", adtax[i], adtay[i], adtaa[i]);
    for(int i = 0; i < N_JOGADORES_POR_TIME; i++) printf("dtbx: %d. dtby: %d. dtba %d \n", adtbx[i], adtby[i], adtba[i]);

    cout << "vision field" << endl;
    cout << protocolo::encode_vision_field(px, py);
    int apx[CAMPO_N_PONTOS];
    int apy[CAMPO_N_PONTOS];
    cout << protocolo::decode_vision_field(protocolo::encode_vision_field(px, py), apx, apy);
    for(int i = 0; i < CAMPO_N_PONTOS; i++) cout << "apx: " << apx[i] << ". apy: " << apy[i] << endl;


    return 0;
}
