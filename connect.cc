/**
 * \file connect.cc
 * \author Diogo Oliveira de Melo
 * \date 20/12/2006
 */

#include<iostream>
#include<string.h>
#include<stdio.h>

using namespace std;

char **ips;
char login[20];
char senha[20];
int n_ips;
void erro_use();

void get_ips(int *n_ips, char ***ips, char *comando);
/**
 * Se conecta a todos os computadores da rede que consegue e depois executa um script em cada um dos computadores alcançados.
 */

int main(int argc, char *argv[]) {
	char comando[100];

	if(argc != 3)
		erro_use();

	printf("Login: ");
	scanf("%s", login);
	system("stty -echo");
	printf("Password: ");
	scanf("%s", senha);
	printf("\n\n\n\n");
	system("stty sane");
	system("cp ~/uspds/bin/* ~/uspds_bin/\n");
	/*FILE *exp;
	char nome_arq[20];
	cout << "Iniciando atualização do pandoraClient..." << endl;
	strcpy(nome_arq, "atualizar.exp");
	exp = fopen(nome_arq, "w");*/
	FILE *exp;
	char nome_arq[60], nome_maquina[50], port[50];
	strcpy(nome_maquina, argv[1]);
	strcpy(port, argv[2]);
	sprintf(nome_arq, "%s.exp", nome_maquina);


	exp = fopen(nome_arq, "w");
	fputs("#!/usr/bin/expect\nset timeout -1\nspawn ssh ", exp);
	fputs(nome_maquina, exp);
	fputs(" -l ", exp);
	fputs(login, exp);
	fputs(" -p ", exp);
	fputs(port, exp);
	fputs("\nexpect \"assword:\" { send \"", exp);
	fputs(senha, exp);
	fputs("\\r\" } \"yes\" { send \"yes\\r\"\nexpect \"assword:\"\nsend \"", exp);
	fputs(senha, exp);
	fputs("\\r\"}\nexpect \"@\"\nsend \"sh ~/script.sh\\r\"\nsleep 5\nexpect \"@\"\nexit", exp);
	fclose(exp);
	
	system("xterm -e ~/uspds/bin/eyes --infinity &\n");

	strcpy(comando, "expect ");
	strcat(comando, nome_maquina);
	strcat(comando, ".exp");
	system(comando);
	
	strcpy(comando, "rm ");
	strcat(comando, nome_maquina);
	strcat(comando, ".exp");
	system(comando);

	printf("\n\n\nfim.\n");

	return 0;
}

/**
 * Mostra a forma de uso do programa.
 */

void erro_use() {
	cout << "use: ./connect hostname" << endl;

	exit(1);
}
