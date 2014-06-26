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

	src/teste/sockServer.cc
*/

#include<iostream>
#include<stdio.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>

using namespace std;

int main() {
	int listenSocket;
	struct sockaddr_in serverAddress;
	int connectSocket;
	socklen_t serverAddressLength;

	listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(listenSocket < 0) {
		cerr << "erro: não pode criar o socket." << endl;
		exit(1);
	}
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(5000);
	if(bind(listenSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
		cerr << "erro: não foi possível dar bind no socket." << endl;
		exit(1);
	}
	listen(listenSocket, 5);
	serverAddressLength = sizeof(serverAddress);
	cout << "esperando..." << endl;
	connectSocket = accept(listenSocket, (struct sockaddr *) &serverAddress, &serverAddressLength);
	if(connectSocket < 0) {
		cerr << "erro: não foi possível aceitar a conexão." << endl;
		exit(1);
	}
	cout << "conectado." << endl;
	float *numeros = (float *) new float[3];
	numeros[0] = 1;
	numeros[1] = 2;
	numeros[2] = 3;
	while(true) {
		for(int i = 0; i < 3; i++)
			numeros[i] += 3;
		send(connectSocket, numeros, 3 * sizeof(float), 0);
		cout << "enviado: ";
		for(int i = 0; i < 3; i++)
			cout << numeros[i] << " ";
		cout << endl;
	}

	return 0;
}
