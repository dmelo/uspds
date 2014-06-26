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

	src/lib/res_sistema.h
*/

#ifndef RES_SISTEMA_H
#define RES_SISTEMA_H

#include<iostream>
#include<stdio.h>
#include<math.h>

using namespace std;

int somar_linha(double **matriz, int des, int ori, double fator, int n_colunas, double *res);
int cortar_linha(double **matriz, int *m, int n, double *res, int linha);
int cortar_linhas_nulas(double **matriz, int *m, int n, double *res);
int e_ld(double **matriz, int m, int n, int i1, int i2, double *res);
int tratar_linhas(double **matriz, int *m, int n, double *res);
int trocar(double **matriz, int l1, int l2, int n, double *res);
int res_sistema(double **matriz, int *m, int n, double *res, double *coef);
int print(double **matriz, int m, int n, double *res, double *coef);
int zeros_esq_dir(double **matriz, int n, int linha);

#endif
