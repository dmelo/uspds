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

	src/lib/protocolo.cc
*/

#include"protocolo.h"

string protocolo::encode(float bx, float by, int nJogadores, float *tx, float *ty, float *ta) {
	string mensagem;
	int tamanho = (nJogadores * 3 * 6) + 14;
	char *msn = new char[tamanho + 50];

	if((bx <= 0)||(bx >= 10))
		bx = 9.999;
	if((by <= 0)||(by >= 10))
		by = 9.999;

	for(int i = 0; i < nJogadores; i++) {
		if((tx[i] <= 0)||(tx[i] >= 10))
			tx[i] = 9.999;
		if((ty[i] <= 0)||(ty[i] >= 10))
			ty[i] = 9.999;
		if((ta[i] <= 0)||(ta[i] >= 10))
			ta[i] = 9.999;
	}

	sprintf(msn, "%5.3f#%5.3f", bx, by);
	mensagem = (string) msn;
	for(int i = 0; i < 2 * nJogadores; i++) {
		sprintf(msn, "#%5.3f#%5.3f#%5.3f", tx[i], ty[i], ta[i]);
		mensagem += (string) msn;
	}
	mensagem += "\n";
	delete msn;

	return mensagem;
}
	
string protocolo::encode(float bx, float by, int nJogadores, float *tax, float *tay, float *anga, float *tbx, float *tby, float *angb) {
	string mensagem;
	int tamanho = (nJogadores * 3 * 6) + 14;
	char *msn = new char[tamanho + 50];

	if((bx < 0)||(bx >=10))
		bx = 9.999;
	if((by < 0)||(by >=10))
		by = 9.999;
	for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
		if((tax[i] < 0)||(tax[i] >= 10))
			tax[i] = 9.999;
		if((tay[i] < 0)||(tay[i] >= 10))
			tay[i] = 9.999;
		if((anga[i] < 0)||(anga[i] >= 10))
			anga[i] = 9.999;
		if((tbx[i] < 0)||(tbx[i] >= 10))
			tbx[i] = 9.999;
		if((tby[i] < 0)||(tby[i] >= 10))
			tby[i] = 9.999;
		if((angb[i] < 0)||(angb[i] >= 10))
			angb[i] = 9.999;

	}

	sprintf(msn, "%5.3f#%5.3f", bx, by);
	mensagem = (string) msn;

	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < nJogadores; j++) {
			if(i == 0)
				sprintf(msn, "#%5.3f#%5.3f#%5.3f", tax[j], tay[j], anga[j]);
			else 
				sprintf(msn, "#%5.3f#%5.3f#%5.3f", tbx[j], tby[j], angb[j]);
			mensagem += (string) msn;
		}
	}

	mensagem += "\n";
	delete msn;
	return mensagem;
}

// bx#by#ra1x#ra1y#ra1a#ra2x#ra2y#ra2a#ra3x#ra3y#ra3a#rb1x#rb1y#rb1a#rb2x#rb2y#rb2a#rb3x#rb3y#rb3a
string protocolo::encode(float bx, float by, float *tax, float *tay, float *anga, float *tbx, float *tby) {
	string mensagem;
	int tamanho = (N_JOGADORES_POR_TIME * 3 * 6) + 14;
	char *msn = new char[tamanho];

	if((bx < 0)||(bx >=10))
		bx = 9.999;
	if((by < 0)||(by >=10))
		by = 9.999;
	for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
		if((tax[i] < 0)||(tax[i] >= 10))
			tax[i] = 9.999;
		if((tay[i] < 0)||(tay[i] >= 10))
			tay[i] = 9.999;
		if((anga[i] < 0)||(anga[i] >= 10))
			anga[i] = 9.999;
		if((tbx[i] < 0)||(tbx[i] >= 10))
			tbx[i] = 9.999;
		if((tby[i] < 0)||(tby[i] >= 10))
			tby[i] = 9.999;
	}


	sprintf(msn, "%5.3f#%5.3f", bx, by);
	mensagem = (string) msn;

	for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
		sprintf(msn, "#%5.3f#%5.3f#%5.3f", tax[i], tay[i], anga[i]);
		mensagem += (string) msn;
	}

	for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
		sprintf(msn, "#%5.3f#%5.3f", tbx[i], tby[i]);
		mensagem += (string) msn;
	}

	mensagem += "\n";
	delete []msn;
}

bool protocolo::decode(char *msn, float *v_e, float *v_d) {
	// Reescrever este método para que o número de velocidade lidas seja dependente de N_JOGADORES_POR_TIME.
	// Do modo que está, só lê as velocidades de 3 jogadores.
	
	if(sscanf(msn, " %f#%f#%f#%f#%f#%f# ", &(v_e[0]), &(v_d[0]), &(v_e[1]), &(v_d[1]), &(v_e[2]), &(v_d[2])) == 6)
		return true;
	
	return false;
}
bool protocolo::decode(char *msn, float *aux_bx, float *aux_by, float *aux_x, float *aux_y, float *aux_a) {
	char *nmsn = new char[300];
	char *aux = new char[300];
	float bx, by;
	float *x = new float[2 * N_JOGADORES_POR_TIME];
	float *y = new float[2 * N_JOGADORES_POR_TIME];
	float *a = new float[2 * N_JOGADORES_POR_TIME];

	//sscanf(msn, "%f#%f#%f#%f#%f#%f#%f#%f#%f#%f#%f#%f#%f#%f#%f#%f#%f#%f#%f#%f", bx, by, &(x[0]), &(y[0]), &(a[0]), &(x[1]), &(y[1]), &(a[1]), &(x[2]), &(y[2]), &(a[2]), &(x[3]), &(y[3]), &(a[3]), &(x[4]), &(y[4]), &(a[4]), &(x[5]), &(y[5]), &(a[5]));
	
	sscanf(msn, "%f#%f%s", &bx, &by, nmsn);
	//printf("--- %s\n", msn);
	for(int i = 0; i < 2 * N_JOGADORES_POR_TIME; i++) {
		if(i  == (2 * N_JOGADORES_POR_TIME) - 1)
			sscanf(nmsn, "#%f#%f#%f", &(x[i]), &(y[i]), &(a[i]));
		else
			sscanf(nmsn, "#%f#%f#%f%s", &(x[i]), &(y[i]), &(a[i]), aux);
		nmsn = aux;
	}

	if(bx != 9.999)
		*aux_bx = bx;
	if(by != 9.999)
		*aux_by = by;
	for(int i = 0; i < 2 * N_JOGADORES_POR_TIME; i++) {
		if(x[i] != 9.999)
			aux_x[i] = x[i];
		if(y[i] != 9.999)
			aux_y[i] = y[i];
		if(y[i] != 9.999)
			aux_a[i] = a[i];
	}


	delete []nmsn;
	delete []x;
	delete []y;
	delete []a;
	return true;
}

char **protocolo::str_split(char *phrase, char *part, int *n_results) {
// Variáveis
	char *temp, *temp2, **res;
	int counter = -1;

	res = (char **) malloc(sizeof(char *) * 50);
	for(int i = 0; i < 50; i++)
	    res[i] = (char *) malloc(sizeof(char) * 50);

	temp = phrase;
// separa a string contida em temp em substrings, a partir da string delimitadora part, e as salva no vetor res
	do {
		counter++;
		res[counter] = strtok_r(temp, part, &temp2);
		temp = temp2;
	} while(res[counter] != NULL);
	*n_results = counter;

	return res;
} 

string protocolo::encode_objects(float bx, float by, float *x, float *y, float *a) {
    string *res = new string("$O$");
    char *aux = new char[200];

    sprintf(aux, "%5.3f#%5.3f", bx, by);
    *res += aux;
    for(int i = 0; i < 2 * N_JOGADORES_POR_TIME; i++) {
	sprintf(aux, "#%5.3f#%5.3f#%5.3f", x[i], y[i], a[i]);
	*res += aux;
    }
    *res += "\n";
    delete []aux;

    return *res;
}

bool protocolo::decode_objects(string msn, float *bx, float *by, float *tax, float *tay, float *taa, float *tbx, float *tby, float *tba) {
    char *cpy = new char[500];
    int len;
    int n_num;
    char **array;

    strcpy(cpy, msn.c_str());
    if(!((cpy[0] == '$')&&(cpy[1] == 'O')&&(cpy[2] == '$')))
	return false;
    len = strlen(cpy);
    for(int i = 0; i <= len - 3; i++)
	cpy[i] = cpy[i+3];

    array = protocolo::str_split(cpy, "#", &n_num);
    if(n_num != 2 + (6 * N_JOGADORES_POR_TIME))
	return false;


    sscanf(array[0], "%f", bx);
    sscanf(array[1], "%f", by);
    for(int i = 2; i < (N_JOGADORES_POR_TIME * 3) + 2; i += 3) {
	sscanf(array[i], "%f", &(tax[(i - 2) / 3]));
	sscanf(array[i + 1], "%f", &(tay[(i - 2) / 3]));
	sscanf(array[i + 2], "%f", &(taa[(i - 2) / 3]));
    }
    for(int i = (N_JOGADORES_POR_TIME * 3) + 2; i < (N_JOGADORES_POR_TIME * 6) + 2; i += 3) {
	sscanf(array[i], "%f", &(tbx[(i - 2 - (3 * N_JOGADORES_POR_TIME)) / 3]));
	sscanf(array[i + 1], "%f", &(tby[(i - 2 - (3 * N_JOGADORES_POR_TIME)) / 3]));
	sscanf(array[i + 2], "%f", &(tba[(i - 2 - (3 * N_JOGADORES_POR_TIME)) / 3]));
    }

    delete []array;
    delete []cpy;

    return true;
}

string protocolo::encode_strategy(float bx, float by, float *x, float *y, float *a) {
    string *res = new string("$S$");
    char *aux = new char[200];

    sprintf(aux, "%5.3f#%5.3f", bx, by);
    *res += aux;
    for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
	sprintf(aux, "#%5.3f#%5.3f#%5.3f", x[i], y[i], a[i]);
	*res += aux;
    }
    for(int i = N_JOGADORES_POR_TIME; i < 2 * N_JOGADORES_POR_TIME; i++) {
	sprintf(aux, "#%5.3f#%5.3f", x[i], y[i]);
	*res += aux;
    }
    *res += "\n";
    delete []aux;

    return *res;
}

bool protocolo::decode_strategy(string msn, float *bx, float *by, float *tax, float *tay, float *taa, float *tbx, float *tby) {
    char *cpy = new char[500];
    int len;
    int n_num;
    char **array;

    strcpy(cpy, msn.c_str());
    if(!((cpy[0] == '$')&&(cpy[1] == 'S')&&(cpy[2] == '$')))
	return false;
    len = strlen(cpy);
    for(int i = 0; i <= len - 3; i++)
	cpy[i] = cpy[i+3];

    array = protocolo::str_split(cpy, "#", &n_num);
    if(n_num != 2 + (5 * N_JOGADORES_POR_TIME))
	return false;


    sscanf(array[0], "%f", bx);
    sscanf(array[1], "%f", by);
    for(int i = 2; i < (N_JOGADORES_POR_TIME * 3) + 2; i += 3) {
	sscanf(array[i], "%f", &(tax[(i - 2) / 3]));
	sscanf(array[i + 1], "%f", &(tay[(i - 2) / 3]));
	sscanf(array[i + 2], "%f", &(taa[(i - 2) / 3]));
    }
    for(int i = (N_JOGADORES_POR_TIME * 3) + 2; i < (N_JOGADORES_POR_TIME * 5) + 2; i += 2) {
	sscanf(array[i], "%f", &(tbx[(i - 2 - (3 * N_JOGADORES_POR_TIME)) / 2]));
	sscanf(array[i + 1], "%f", &(tby[(i - 2 - (3 * N_JOGADORES_POR_TIME)) / 2]));
    }

    delete []array;
    delete []cpy;

    return true;
}

string protocolo::encode_command(float *vl, float *vr) {
    string *res = new string("");
    char *aux = new char[40];

   *res = "$C$";
   sprintf(aux, "%5.3f#%5.3f", vl[0], vr[0]);
   *res += aux;
   for(int i = 1; i < N_JOGADORES_POR_TIME; i++) {
       sprintf(aux, "#%5.3f#%5.3f", vl[i], vr[i]);
       *res += aux;
   }
   *res += "\n";
   delete []aux;
}


string protocolo::encode_score(int t1, int t2) {
    string *res = new string("");
    char *aux = new char[40];

   *res = "$C$";
   sprintf(aux, "%d", t1);
   *res += aux;
   *res += "#";
   sprintf(aux, "%d", t2);
   *res += aux; 
   *res += "\n";
   delete []aux;

   return *res;
}

bool protocolo::decode_score(string msn, int *t1, int *t2) {
    if((sscanf(msn.c_str(), "$C$%d#%d\n", t1, t2) == 2) && (msn.c_str()[0] == '$') && (msn.c_str()[1] == 'C') && (msn.c_str()[2] == '$'))
	return true;
    return false;
}

string protocolo::encode_time(int time) {
    string *res = new string("$T$");
    char *aux = new char[30];

    sprintf(aux, "%d\n", time);
    *res += aux;

    return *res;
}

bool protocolo::decode_time(string msn, int *time) {
    if((sscanf(msn.c_str(), "$T$%d\n", time) == 1) && (msn.c_str()[0] == '$') && (msn.c_str()[1] == 'T') && (msn.c_str()[2] == '$'))
	return true;
    return false;
}

string protocolo::encode_vision_objects(int bx, int by, int *x, int *y, int *a) {
    string *res = new string("$V$");
    char *aux = new char[200];

    sprintf(aux, "%d,%d", bx, by);
    *res += aux;
    for(int i = 0; i < 2 * N_JOGADORES_POR_TIME; i++) {
	sprintf(aux, ",%d,%d,%d", x[i], y[i], a[i]);
	*res += aux;
    }
    *res += "\n";
    delete []aux;

    return *res;
}

bool protocolo::decode_vision_objects(string msn, int *bx, int *by, int *tax, int *tay, int *taa, int *tbx, int *tby, int *tba) {
    char *cpy = new char[500];
    int len;
    int n_num;
    char **array;

    strcpy(cpy, msn.c_str());
    if(!((cpy[0] == '$')&&(cpy[1] == 'V')&&(cpy[2] == '$')))
	return false;
    len = strlen(cpy);
    for(int i = 0; i <= len - 3; i++)
	cpy[i] = cpy[i+3];

    array = protocolo::str_split(cpy, ",", &n_num);
    if(n_num != 2 + (6 * N_JOGADORES_POR_TIME))
	return false;


    sscanf(array[0], "%d", bx);
    sscanf(array[1], "%d", by);
    for(int i = 2; i < (N_JOGADORES_POR_TIME * 3) + 2; i += 3) {
	sscanf(array[i], "%d", &(tax[(i - 2) / 3]));
	sscanf(array[i + 1], "%d", &(tay[(i - 2) / 3]));
	sscanf(array[i + 2], "%d", &(taa[(i - 2) / 3]));
    }
    for(int i = (N_JOGADORES_POR_TIME * 3) + 2; i < (N_JOGADORES_POR_TIME * 6) + 2; i += 3) {
	sscanf(array[i], "%d", &(tbx[(i - 2 - (3 * N_JOGADORES_POR_TIME)) / 3]));
	sscanf(array[i + 1], "%d", &(tby[(i - 2 - (3 * N_JOGADORES_POR_TIME)) / 3]));
	sscanf(array[i + 2], "%d", &(tba[(i - 2 - (3 * N_JOGADORES_POR_TIME)) / 3]));
    }

    delete []array;

    return true;
}

string protocolo::encode_vision_field(int *x, int *y) {
    string *res = new string("$F$");
    char *aux = new char[200];

    sprintf(aux, "%d,%d", x[0], y[0]);
    *res += aux;
    for(int i = 1; i < CAMPO_N_PONTOS; i++) {
	sprintf(aux, ",%d,%d", x[i], y[i]);
	*res += aux;
    }
    *res += "\n";
    delete []aux;

    return *res;
}
   
bool protocolo::decode_vision_field(string msn, int *x, int *y) {
    char *cpy = new char[500];
    int len;
    int n_num;
    char **array;

    strcpy(cpy, msn.c_str());
    if(!((cpy[0] == '$')&&(cpy[1] == 'F')&&(cpy[2] == '$')))
	return false;
    len = strlen(cpy);
    for(int i = 0; i <= len - 3; i++)
	cpy[i] = cpy[i+3];

    array = protocolo::str_split(cpy, ",", &n_num);
    if(n_num != 2 * CAMPO_N_PONTOS)
	return false;


    for(int i = 0; i < CAMPO_N_PONTOS * 2; i += 2) {
	sscanf(array[i], "%d", &(x[i / 2]));
	sscanf(array[i + 1], "%d", &(y[i / 2]));
    }
    delete []array;

    return true;
}
