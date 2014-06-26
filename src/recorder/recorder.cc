#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<iostream>
#include<unistd.h>
#include<netinet/in.h>
#include"../lib/parametros.h"

using namespace std;

int main(int *argc, char **argv) {
	bool connection = false;
	struct hostent *hostInfo;
	struct sockaddr_in serverAddressRecv;
	int socketRecv, n = 0;
	char *buf = new char[400];
	FILE *play;
	char *filename;
	socklen_t serverAddressRecvLen;

	filename = new char[200];

	sprintf(filename, "%d.uds", time(NULL));

	cout << "recorder: trying connection with " << argv[1] << endl;
	hostInfo = gethostbyname(argv[1]);
	if(hostInfo == NULL) {
		cerr << "error: problems to find a server." << endl;
		exit(1);
	}

	do {
		socketRecv = socket(AF_INET, SOCK_STREAM, 0);
		if(socketRecv < 0) {
			cerr << "erro: i can't create the connection with the simulator." << endl;
			exit(1);
		}
		serverAddressRecv.sin_family = hostInfo->h_addrtype;
		memcpy((char *) &serverAddressRecv.sin_addr.s_addr, hostInfo->h_addr_list[0], hostInfo->h_length);
		serverAddressRecv.sin_port = htons(PORTA_GUI + (n * 5));
		if(bind(socketRecv, (struct sockaddr *) &serverAddressRecv, sizeof(serverAddressRecv)) < 0) {
			printf("erro: não foi possível dar bind no socket.\n");
			exit(1);
		}
		printf("esperando a conexão do simulador.\n");
		listen(socketRecv, 5);

		serverAddressRecvLen = sizeof(serverAddressRecv);
		socketRecv = accept(socketRecv, (struct sockaddr *) &serverAddressRecv, &serverAddressRecvLen);
		if(socketRecv < 0) {
			printf("erro: não foi possível aceitar a conexão.\n");
		}
		else {
			printf("conectado! :D\n");
			connection = true;
		}

	} while((connection == false)&&(n <= N_SIMULATORS_PER_TIME));

	if((play = fopen(filename, "w")) == NULL) {
		cerr << "error: I can't open the file " << filename << ", for write.\n" << endl;
		exit(1);
	}
	while(recv(socketRecv, buf, 300 * sizeof(char), 0) != -1)
		fprintf(play, "%s", buf);

	return 0;
}
