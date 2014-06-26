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

	src/lib/res_sistema.cc
*/

#include"res_sistema.h"

//mxn * nx1 = mx1
//
//retorna 0 em caso de sucesso, SPD.
//retorna -1 em caso de falha, SPI ou SI.

int somar_linha(double **matriz, int des, int ori, double fator, int n_colunas, double *res) {
	for(int i = 0; i < n_colunas; i++)
		matriz[des][i] += matriz[ori][i] * fator;
	
	res[des] += res[ori] * fator;
	
	return 0;
}

int cortar_linha(double **matriz, int *m, int n, double *res, int linha) {
	for(int i = linha; i < *m - 1; i++) {
		for(int j = 0; j < n; j++)
			matriz[i][j] = matriz[i+1][j];

		res[i] = res[i+1];
	}

	(*m)--;

	return 0;
}

int cortar_linhas_nulas(double **matriz, int *m, int n, double *res) { // retorna 1 se for SI.
	for(int i = 0; i < *m; i++) {
		bool nula = true;
		for(int j = 0; j < n; j++) {
			if(matriz[i][j] != 0) {
				nula = false;
				break;
			}
		}
		if(nula == true) {
			if(res[i] != 0)
				return 1;
			cortar_linha(matriz, m, n, res, i);
			i--;
		}
	}

	return 0;
}

int e_ld(double **matriz, int m, int n, int i1, int i2, double *res) { // supoe que no tem linhas nulas.
	for(int i = 0; i < n; i++)
		if((matriz[i1][i] == 0)||(matriz[i2][i] == 0))
			if(!(((matriz[i1][i] == 0)&&(matriz[i2][i] == 0))))
				return 0;
	
	int i;
	for(i = 0; matriz[i1][i] == 0; i++);
	float razao = matriz[i2][i] / matriz[i1][i];
	i++;
	for(i; i < n; i++)
		if(matriz[i1][i] != 0)
			if(matriz[i2][i] / matriz[i1][i] != razao)
				return 0;
	if(res[i1] * razao != res[i2])
		return 2;
	return 1;
}

int trocar(double **matriz, int l1, int l2, int n, double *res) {
	double aux;

	for(int i = 0; i < n; i++) {
		aux = matriz[l1][i];
		matriz[l1][i] = matriz[l2][i];
		matriz[l2][i] = aux;
	}
	aux = res[l1];
	res[l1] = res[l2];
	res[l2] = aux;

	return 0;
}

int zeros_esq_dir(double **matriz, int n, int linha) {
	int i = 0;

	for(i = 0; matriz[linha][i] != 0; i++);
	
	return i;
}

int tratar_linhas(double **matriz, int *m, int n, double *res) {
	cortar_linhas_nulas(matriz, m, n, res);
	int r_e_ld;
	for(int i = 0; i < *m - 1; i++) {
		for(int j = i + 1; j < *m; j++) {
			if((r_e_ld = e_ld(matriz, *m, n, i, j, res)) == 1)
				cortar_linha(matriz, m, n, res, j);
			else if(r_e_ld == 2)
				return 1;
		}
	}

	for(int i = 0; i < *m - 1; i++)
		for(int j = i + 1; j < *m; j++)
			if(zeros_esq_dir(matriz, n, i) < zeros_esq_dir(matriz, n, j))
				trocar(matriz, i, j, n, res);

	
	return 0;
}


//retorna 0 ==> SPD, sistema resolvido.
//retorna 1 ==> SPI, sistema nao resolvido.
//retorna 2 ==> SI, sistema nao resolvido.

int res_sistema(double **matriz, int *m, int n, double *res, double *coef) {
	if(tratar_linhas(matriz, m, n, res) == 1)
		return 2;
	if(*m < n)
		return 1;

	//SPD
	*m = n;


	for(int i = 0; i < n; i++) {
		int i_maior = 0;
		int l_chave = n - i - 1;
		double maior = matriz[0][i];

		for(int j = 1; j <= l_chave; j++) {
			if(fabs(matriz[i][j]) > fabs(maior)) {
				maior = matriz[i][j];
				i_maior = j;
			}
		}
		trocar(matriz, i_maior, l_chave, n, res);

		for(int j = l_chave - 1; j >= 0; j--) {
			if(fabs(matriz[l_chave][i]) <= 0.000000001)
				continue;
			double razao = matriz[j][i] / matriz[l_chave][i];
			somar_linha(matriz, j, l_chave, -razao, n, res);
		}
	}

		

	for(int i = 0; i < *m; i++) {
		if(matriz[i][n - i - 1] == 0)
			coef[n - i - 1] = 0;
		else {
			coef[n - i - 1] = res[i];
			for(int j = n - i; j < n; j++)
				coef[n - i - 1] -= matriz[i][j] * coef[j];
			coef[n - i - 1] /= matriz[i][n - i - 1];
		}
	}

	return 0;
}

int print(double **matriz, int m, int n, double *res, double *coef) {
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++)
			printf("%9.3f ", matriz[i][j]);
		if(i == m/2)
			printf("  X  %9.3f  =  %9.3f\n", coef[i], res[i]);
		else
			printf("     %9.3f     %9.3f\n", coef[i], res[i]);
	}
	
	return 0;
}

/*int main() {
	double *res;
	double *coef;
	double **matriz;
	int m = 3, n = 3;

	matriz = new double*[m];
	for(int i = 0; i < m; i++)
		matriz[i] = new double[n];
	
	res = new double[m];
	coef = new double[m];
	res[0] = 136;
	res[1] = 64;
	res[2] = 114;
	res[3] = 134;
	res[4] = 124;

	matriz[0][0] = 1;
	matriz[0][1] = 3;
	matriz[0][2] = 5;
	matriz[0][3] = 4;
	matriz[0][4] = 6;

	matriz[1][0] = 5;
	matriz[1][1] = 7;
	matriz[1][2] = 1;
	matriz[1][3] = 0;
	matriz[1][4] = 2;

	matriz[2][0] = 7;
	matriz[2][1] = 8;
	matriz[2][2] = 5;
	matriz[2][3] = 1;
	matriz[2][4] = 3;

	matriz[3][0] = 3;
	matriz[3][1] = 5;
	matriz[3][2] = 1;
	matriz[3][3] = 4;
	matriz[3][4] = 7;

	matriz[4][0] = 2;
	matriz[4][1] = 9;
	matriz[4][2] = 1;
	matriz[4][3] = 6;
	matriz[4][4] = 3;

	res[0] = 14;
	res[1] = -5;
	res[2] = 45;

	matriz[0][0] = 5;
	matriz[0][1] = 0;
	matriz[0][2] = 10;

	matriz[1][0] = 5;
	matriz[1][1] = 0;
	matriz[1][2] = 0;

	matriz[2][0] = 10;
	matriz[2][1] = 0;
	matriz[2][2] = 34;

	res[0] = -12;
	res[1] = -3;
	res[2] = 40;

	matriz[0][0] = 3;
	matriz[0][1] = 0;
	matriz[0][2] = -5;

	matriz[1][0] = 4;
	matriz[1][1] = 1;
	matriz[1][2] = -3;

	matriz[2][0] = 10;
	matriz[2][1] = 0;
	matriz[2][2] = 10;


	print(matriz, m, n, res, coef);
	cout << endl << endl;
	if(res_sistema(matriz, &m, n, res, coef) == 0)
		print(matriz, m, n, res, coef);
	else
		printf("SPI o SI\n");

	return 0;
}*/
