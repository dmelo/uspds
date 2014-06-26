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

	src/teste/sockClient.cc
*/

#include<iostream>
#include<stdio.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>

using namespace std;

int main() {
	int socketDescriptor;
	struct sockaddr_in serverAddress;
	struct hostent *hostInfo;

	hostInfo = gethostbyname("luizinho");
	if(hostInfo == NULL) {
		cerr << "erro: problemas para encontrar o servidor." << endl;
		exit(1);
	}

	socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if(socketDescriptor < 0) {
		cout << "erro: não foi possivel encontrar o servidor." << endl;
		exit(1);
	}

	serverAddress.sin_family = hostInfo->h_addrtype;
	memcpy((char *) &serverAddress.sin_addr.s_addr, hostInfo->h_addr_list[0], hostInfo->h_length);
	serverAddress.sin_port = htons(5000);
	if(connect(socketDescriptor, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0) {
		cerr << "erro: não foi possível se conectar ao simulador." << endl;
		exit(1);
	}

	float *numeros = (float *) new float[3];
	while(true);
	while(true) {
		recv(socketDescriptor, numeros, 3 * sizeof(float), 0);
		for(int i = 0; i < 3; i++)
			cout << numeros[i] << " ";
		cout << endl;
	}

	return 0;
}
