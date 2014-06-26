#include"simulator.h"
#include"history.h"

int counter = 1;
int pronto = 0;
bool fim_jogo = false;
pthread_mutex_t mutex_control;
float bx, by;
float *tax = (float *) new float[N_JOGADORES_POR_TIME];
float *tay = (float *) new float[N_JOGADORES_POR_TIME];
float *taa = (float *) new float[N_JOGADORES_POR_TIME];
float *tbx = (float *) new float[N_JOGADORES_POR_TIME];
float *tby = (float *) new float[N_JOGADORES_POR_TIME];
float *tba = (float *) new float[N_JOGADORES_POR_TIME];

float va_e[N_JOGADORES_POR_TIME], va_d[N_JOGADORES_POR_TIME];
float vb_e[N_JOGADORES_POR_TIME], vb_d[N_JOGADORES_POR_TIME];
int estrategia_1_send_connectSocket;
int estrategia_1_recv_connectSocket;
int estrategia_2_send_connectSocket;
int estrategia_2_recv_connectSocket;
int p_eyes, p_es1, p_er1, p_es2, p_er2;
pthread_t kernel, est1_send, est1_recv, est2_send, est2_recv, eyes;
int time_limit = 10 * 60;
int e1s = 0, e2s = 0, e1r = 0, e2r = 0, ker = 0;
history *hist = new history();
char *filename, *gamename;

FILE *fd;
FILE *fd_game = NULL;

void interfacing(simulator *sim) {
    pthread_mutex_lock(&mutex_control);
    bx = sim->b->getX();
    by = sim->b->getY();
    for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
	tax[i] = sim->time1[i]->getX();
	tay[i] = sim->time1[i]->getY();
	taa[i] = sim->time1[i]->getAng();

	tbx[i] = sim->time2[i]->getX();
	tby[i] = sim->time2[i]->getY();
	tba[i] = sim->time2[i]->getAng();
    }
    pthread_mutex_unlock(&mutex_control);
    //while((4 * ker) - (e1s + e1r + e2s + e2r) > 0) objeto::sleep2(1);
    while(ker > e1s || ker > e1r || ker > e2s || ker > e2r) objeto::sleep2(1);
    //printf("ker %d. e1s %d. e1r %d. e2s %d. e2r %d.\n", ker, e1s, e1r, e2s, e2r);
    ker++;
}

void *executar_movimento(void *a) {
    // INITIALIZATION
    int count2 = 1;
    simulator *sim = (simulator *) a;
    struct timeval tv;
    struct timezone tz;
    suseconds_t usec;
    bool first = true;
    int time_s;

    int n_iteracoes_por_quadro = (int) (((float) 1 / (float) N_QUADROS_POR_SEGUNDO) / TEMPO_POR_QUADRO);


    pthread_mutex_lock(&mutex_control);
    for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
        sim->time1[i]->setVel(0.01, 0.01);
        sim->time2[i]->setVel(0.01, 0.01);
    }
    pthread_mutex_unlock(&mutex_control);

    // Waiting for the others modules
    while(pronto != 4) {
        cout << "pronto: " << pronto << endl;
        objeto::sleep2(300);
    }
    
    pthread_mutex_lock(&mutex_control);
    pronto = 5;
    pthread_mutex_unlock(&mutex_control);

    // INTERACTIONS
    while(!fim_jogo) {
	if(counter >= time_limit * N_QUADROS_POR_SEGUNDO * n_iteracoes_por_quadro) {
    	    hist->write_history(filename);
	    fim_jogo = true;
	    break;
	}
        string mensagem;
        if(counter % n_iteracoes_por_quadro == 0) {
	    if(first) {
		first = false;
		gettimeofday(&tv, &tz);
		time_s = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	    } else {
		int time2_s;
		gettimeofday(&tv, &tz);
		time2_s = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		//objeto::sleep2(33 - (time2_s - time_s));
		//printf("tempo: %d.\n", 33 - (time2_s - time_s));
		time_s = time2_s;
		// Verify fouls
		pthread_mutex_lock(&mutex_control);
		if(sim->handle_foul()) hist->inc_n_fouls();
		pthread_mutex_unlock(&mutex_control);
	    }
	    interfacing(sim);
	    hist->calc(*sim);
        }

        pthread_mutex_lock(&mutex_control);
        for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
            sim->time1[i]->setVel(va_e[i], va_d[i]);
            sim->time2[i]->setVel(vb_e[i], vb_d[i]);
        }

        // Calculando atributos.
	int n_collision = 0;

        if(sim->b->calc_atributos(sim->c, N_JOGADORES_POR_TIME, sim->time1, sim->time2))
	    n_collision++;

        for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
            if(sim->time1[i]->calc_atributos(sim->c, sim->b->getX(), sim->b->getY(), sim->b->getVelocidade(), sim->b->getForca_resultante(), sim->time1, sim->time2))
		n_collision++;

            if(sim->time2[i]->calc_atributos(sim->c, sim->b->getX(), sim->b->getY(), sim->b->getVelocidade(), sim->b->getForca_resultante(), sim->time2, sim->time1))
		n_collision++;
        }

	bool verify = false;

	if(counter % 2 == 0) verify = sim->verify_objects();

        // atualizar atributos.
        for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
            sim->time1[i]->atualizar_atributos();
            sim->time2[i]->atualizar_atributos();
        }
        sim->b->atualizar_atributos();
	// Verify gol occurrence
	int gol_marked = sim->gol(sim->b, sim->c);
	if(gol_marked == 1) hist->inc_n_scored_goals();
	else if(gol_marked == 2) hist->inc_n_other_team_goals();
        sim->handle_gol(gol_marked);

	pthread_mutex_unlock(&mutex_control);
        counter++;
        count2++;
	if(counter % ((int)(1 / TEMPO_POR_QUADRO)) == 0) {
	    printf("time: %d secs. Placar: Azul %d x %d Amarelo.\n", counter / ((int)(1 / TEMPO_POR_QUADRO)), sim->t1_get_score(), sim->t2_get_score());
	    if(fd_game != NULL)
		fprintf(fd_game, "%d %d %d\n", counter / ((int)(1 / TEMPO_POR_QUADRO)), sim->t1_get_score(), sim->t2_get_score());
	}
    }

    pthread_exit(NULL);
}
void *estrategia_1_send(void * a) {
    simulator *sim = (simulator *) a;
    int listenSocket;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    int novo_id, aux;
    int on = 1;
    socklen_t clientAddressLength;
    
    //cria socket.
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(listenSocket < 0) {
        cerr << "simulator: estrategia_1_send: erro: não pode criar o socket." << endl;
        exit(1);
    }

    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(p_es1);
    setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if((aux = bind(listenSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress))) < 0) {
        cerr << "simulator: estrategia_1_send: erro: não foi possível dar bind no socket. error number: " << aux << " -- " << strerror(errno) << endl;
        exit(1);
    }
    cout << "esperando conexão da estratégia 1 para send." << endl;
    listen(listenSocket, 5);

    clientAddressLength = sizeof(clientAddress);
    estrategia_1_send_connectSocket = accept(listenSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
    close(listenSocket);
    if(estrategia_1_send_connectSocket < 0) {
        cerr << "erro: não foi possível aceitar a conexão." << endl;
        exit(1);
    }

    pthread_mutex_lock(&mutex_control);
    pronto++;
    pthread_mutex_unlock(&mutex_control);
    while(pronto != 5)
        objeto::sleep2(10);
    //executa loop.
    float bx, by;
    float tax[N_JOGADORES_POR_TIME];
    float tay[N_JOGADORES_POR_TIME];
    float taa[N_JOGADORES_POR_TIME];
    float tbx[N_JOGADORES_POR_TIME];
    float tby[N_JOGADORES_POR_TIME];
    while(!fim_jogo) {
	while(e1s > ker || e1s > e1r + 1) objeto::sleep2(1);
        pthread_mutex_lock(&mutex_control);
        bx = sim->b->getX();
        by = sim->b->getY();
        for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
            tax[i] = sim->time1[i]->getX();
            tay[i] = sim->time1[i]->getY();
            taa[i] = sim->time1[i]->getAng();
            tbx[i] = sim->time2[i]->getX();
            tby[i] = sim->time2[i]->getY();
        }
        pthread_mutex_unlock(&mutex_control);
        int tamanho = (5 * N_JOGADORES_POR_TIME) + 2;
        float *mensagem = (float *) new float[tamanho];
	if(!fim_jogo) {
	    mensagem[0] = bx;
	    mensagem[1] = by;
	    for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
		mensagem[2 + (3 * i)] = tax[i];
		mensagem[3 + (3 * i)] = tay[i];
		mensagem[4 + (3 * i)] = taa[i];
		mensagem[(3 * N_JOGADORES_POR_TIME) + 2 + (2 * i)] = tbx[i];
		mensagem[(3 * N_JOGADORES_POR_TIME) + 3 + (2 * i)] = tby[i];
	    }
	}
	else {
	    for(int i = 0; i < 2 + (N_JOGADORES_POR_TIME * 3); i++)
		mensagem[i] = END_FLOAT;
	}
	e1s++;
        send(estrategia_1_send_connectSocket, mensagem, tamanho * sizeof(float), 0);
        delete []mensagem;
    }

    printf("simulator: estrategia_1_send: socket closed %d\n", close(estrategia_1_send_connectSocket));

    pthread_exit(NULL);
}

void *estrategia_1_recv(void *a) {
    struct sockaddr_in clientAddress;
    int novo_id, estrategia_1_recv_connectSocket;
    socklen_t clientAddressLength;
    simulator *sim = (simulator *) a;
    int listenSocket;
    struct sockaddr_in serverAddress;
    float ve[N_JOGADORES_POR_TIME];
    float vd[N_JOGADORES_POR_TIME];
    int tamanho = (2 * N_JOGADORES_POR_TIME);
    float *mensagem = (float *) new float[tamanho];
    int on = 1;


    //cria socket
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(listenSocket < 0) {
        cerr << "erro: não pode criar o socket." << endl;
        exit(1);
    }

    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(p_er1);
    setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if(bind(listenSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        cerr << "simulator: esrategia_1_recv: erro: não foi possível dar bind no socket." << endl;
        exit(1);
    }
    cout << "esperando conexão da estratégia 1 para recv." << endl;
    listen(listenSocket, 5);
    clientAddressLength = sizeof(clientAddress);
    estrategia_1_recv_connectSocket = accept(listenSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
    close(listenSocket);
    if(estrategia_1_recv_connectSocket < 0) {
        cerr << "erro: não foi possível aceitar a conexão." << endl;
        exit(1);
    }
    pthread_mutex_lock(&mutex_control);
    pronto++;
    pthread_mutex_unlock(&mutex_control);
    while(pronto != 5)
        objeto::sleep2(10);
    //executa loop.
    while(!fim_jogo) {
	while(e1r - ker > 0) objeto::sleep2(1);
        if(recv(estrategia_1_recv_connectSocket, mensagem, tamanho * sizeof(float), 0) != -1) {
            pthread_mutex_lock(&mutex_control);
            for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
                va_e[i] = mensagem[i * 2];
                va_d[i] = mensagem[(i * 2) + 1];
            }
            pthread_mutex_unlock(&mutex_control);
        }
	e1r++;
    }
    printf("simulator: estrategia_1_recv: socket closed %d\n", close(estrategia_1_recv_connectSocket));
    cout << close(listenSocket) << endl;
    delete []mensagem;
    pthread_exit(NULL);
}

void *estrategia_2_send(void * a) {
    struct sockaddr_in clientAddress;
    int novo_id, estrategia_2_send_connectSocket;
    socklen_t clientAddressLength;
    simulator *sim = (simulator *) a;
    int listenSocket;
    struct sockaddr_in serverAddress;
    int on = 1;
    
    //cria socket.
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(listenSocket < 0) {
        cerr << "erro: não pode criar o socket." << endl;
        exit(1);
    }

    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(p_es2);
    setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if(bind(listenSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        cerr << "simulator: estrategia_2_send: erro: não foi possível dar bind no socket." << endl;
        exit(1);
    }
    cout << "esperando conexão da estratégia 1 para send." << endl;
    listen(listenSocket, 5);

    clientAddressLength = sizeof(clientAddress);
    estrategia_2_send_connectSocket = accept(listenSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
    close(listenSocket);
    if(estrategia_2_send_connectSocket < 0) {
        cerr << "erro: não foi possível aceitar a conexão." << endl;
        exit(1);
    }


    pthread_mutex_lock(&mutex_control);
    pronto++;
    pthread_mutex_unlock(&mutex_control);
    while(pronto != 5)
        objeto::sleep2(10);
    //executa loop.
    float bx, by;
    float tax[N_JOGADORES_POR_TIME];
    float tay[N_JOGADORES_POR_TIME];
    float taa[N_JOGADORES_POR_TIME];
    float tbx[N_JOGADORES_POR_TIME];
    float tby[N_JOGADORES_POR_TIME];
    
    while(!fim_jogo) {
	while(e2s > ker || e2s > e2r + 1) objeto::sleep2(1);
        pthread_mutex_lock(&mutex_control);
        bx = sim->b->getX();
        by = sim->b->getY();
        for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
            tax[i] = sim->time2[i]->getX();
            tay[i] = sim->time2[i]->getY();
            taa[i] = sim->time2[i]->getAng();
            tbx[i] = sim->time1[i]->getX();
            tby[i] = sim->time1[i]->getY();
        }
        pthread_mutex_unlock(&mutex_control);
        int tamanho = (5 * N_JOGADORES_POR_TIME) + 2;
        float *mensagem = (float *) new float[tamanho];
	if(!fim_jogo) {
	    mensagem[0] = bx;
	    mensagem[1] = by;
	    for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
		mensagem[2 + (3 * i)] = tax[i];
		mensagem[3 + (3 * i)] = tay[i];
		mensagem[4 + (3 * i)] = taa[i];
		mensagem[(3 * N_JOGADORES_POR_TIME) + 2 + (2 * i)] = tbx[i];
		mensagem[(3 * N_JOGADORES_POR_TIME) + 3 + (2 * i)] = tby[i];
	    }
	}
	else {
	    for(int i = 0; i < 2 + (3 * N_JOGADORES_POR_TIME); i++)
		mensagem[i] = END_FLOAT;
	}
	e2s++;
        send(estrategia_2_send_connectSocket, mensagem, tamanho * sizeof(float), 0);
    }
    printf("tentando fechar...\n");
    printf("simulator: estrategia_2_send: socket closed %d\n", close(estrategia_2_send_connectSocket));
    cout << close(listenSocket) << endl;

    pthread_exit(NULL);
}

void *estrategia_2_recv(void * a) {
    struct sockaddr_in clientAddress;
    int novo_id, estrategia_2_recv_connectSocket;
    socklen_t clientAddressLength;
    simulator *sim = (simulator *) a;
    int listenSocket;
    struct sockaddr_in serverAddress;
    float ve[N_JOGADORES_POR_TIME];
    float vd[N_JOGADORES_POR_TIME];
    int tamanho = (2 * N_JOGADORES_POR_TIME);
    float *mensagem = (float *) new float[tamanho];
    int on = 1;

    //cria socket
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(listenSocket < 0) {
        cerr << "erro: não pode criar o socket." << endl;
        exit(1);
    }

    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(p_er2);
    setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if(bind(listenSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        cerr << "simulator: estrategia_2_recv: erro: não foi possível dar bind no socket." << endl;
        exit(1);
    }
    cout << "esperando conexão da estratégia 1 para recv." << endl;
    listen(listenSocket, 5);
    clientAddressLength = sizeof(clientAddress);
    estrategia_2_recv_connectSocket = accept(listenSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
    close(listenSocket);
    if(estrategia_2_recv_connectSocket < 0) {
        cerr << "erro: não foi possível aceitar a conexão." << endl;
        exit(1);
    }
    pthread_mutex_lock(&mutex_control);
    pronto++;
    pthread_mutex_unlock(&mutex_control);
    while(pronto != 5)
        objeto::sleep2(10);
    //executa loop.
    while(!fim_jogo) {
	while(e2r - ker > 0) objeto::sleep2(1);
        if(recv(estrategia_2_recv_connectSocket, mensagem, tamanho * sizeof(float), 0) != -1) {
            pthread_mutex_lock(&mutex_control);
            for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
                vb_e[i] = mensagem[i * 2];
                vb_d[i] = mensagem[(i * 2) + 1];
            }
            pthread_mutex_unlock(&mutex_control);
        }
	e2r++;
    }
    printf("simulator: estrategia_2_recv: socket closed %d\n", close(estrategia_2_recv_connectSocket));
    cout << close(listenSocket) << endl;

    pthread_exit(NULL);
}

void *eyes_sender(void *c) {
    int n_iteracoes_por_quadro = (int) (((float) 1 / (float) N_QUADROS_POR_SEGUNDO) / TEMPO_POR_QUADRO);
    int n_frames_sent = counter / n_iteracoes_por_quadro;
    struct eyes_client *cli = (struct eyes_client *) c;
    
    string mensagem;
    printf("sending... clientSocket = %d\n", cli->clientSocket);


    while(!fim_jogo) {
	if(counter / n_iteracoes_por_quadro <= n_frames_sent) {
	    usleep(250);
	    continue;
	}

	pthread_mutex_lock(&mutex_control);

	mensagem = protocolo::encode(bx, by, N_JOGADORES_POR_TIME, tax, tay, taa, tbx, tby, tba);
	n_frames_sent++;
	send(cli->clientSocket, mensagem.c_str(), strlen(mensagem.c_str()), 0);

	pthread_mutex_unlock(&mutex_control);
    }
    printf("simulator: eyes_sender: socket closed %d\n", close(cli->clientSocket));
}


void *eyes_main(void *a) {
    pthread_t eyes_s;
    pthread_attr_t attr;
    struct sockaddr_in clientAddress;
    int novo_id, connectSocket;
    socklen_t clientAddressLength;
    simulator *sim = (simulator *) a;
    int listenSocket;
    struct sockaddr_in serverAddress;
    float ve[N_JOGADORES_POR_TIME];
    float vd[N_JOGADORES_POR_TIME];
    int tamanho = (2 * N_JOGADORES_POR_TIME);
    int on = 1;

    //cria socket
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(listenSocket < 0) {
        cerr << "Simulator: Eyes: erro: não pode criar o socket." << endl;
        exit(1);
    }

    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(p_eyes);
    setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if(bind(listenSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        cerr << "Simulator: eyes_main: erro: não foi possível dar bind no socket." << endl;
        exit(1);
    }
    listen(listenSocket, 5);
    clientAddressLength = sizeof(clientAddress);
    cout << "Simulator: Eyes: Ready to receave connection from Eyes." << endl;
    while(1) {
	connectSocket = accept(listenSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
	if(connectSocket < 0) {
	    cerr << "Simulator: Eyes: erro: Cannot accept new connection." << endl;
	    exit(1);
	}
	cout << "Simulator: Eyes: The Eyes is connected." << endl;
	struct hostent *clienthostinfo;
	clienthostinfo = gethostbyaddr(&(clientAddress.sin_addr), 4, AF_INET);
	cout << "The IP client is " << clienthostinfo->h_name << endl;
	struct eyes_client *cli = new struct eyes_client;

	cli->clientSocket = connectSocket;
	printf("connectSocket: %d.\n", connectSocket);
	cli->clientAddress = clientAddress;

	pthread_create(&eyes_s, &attr, eyes_sender, (void *) cli);

    }

    pthread_exit(0);
}

void exit_simulator() {
    int total =0;
    fim_jogo = true;
    objeto::sleep2(500);

	cout << "exit_simulator ====" << endl;
	cout << "shutdown 1" << endl;
	cout << shutdown(estrategia_1_send_connectSocket, SHUT_RD) << endl;
	cout << shutdown(estrategia_1_send_connectSocket, SHUT_WR) << endl;
	cout << "shutdown 2" << endl;
	cout << shutdown(estrategia_1_recv_connectSocket, SHUT_RD) << endl;
	cout << shutdown(estrategia_1_recv_connectSocket, SHUT_WR) << endl;
	cout << "shutdown 3" << endl;
	cout << shutdown(estrategia_2_send_connectSocket, SHUT_RD) << endl;
	cout << shutdown(estrategia_2_send_connectSocket, SHUT_WR) << endl;
	cout << "shutdown 4" << endl;
	cout << shutdown(estrategia_2_recv_connectSocket, SHUT_RD) << endl;
	cout << shutdown(estrategia_2_recv_connectSocket, SHUT_WR) << endl;
	cout << (total = close(estrategia_1_send_connectSocket)) << endl;
	cout << (total += close(estrategia_1_recv_connectSocket)) << endl;
	cout << (total += close(estrategia_2_send_connectSocket)) << endl;
	cout << (total += close(estrategia_2_recv_connectSocket)) << endl;
	cout << "total: " << total << endl;
	cout << "===================" << endl;

    pthread_exit(0);
}

int main(int argc, char *argv[]) {

    /*pthread_mutex_init(&e1s, NULL);
    pthread_mutex_init(&e2s, NULL);
    pthread_mutex_init(&e1r, NULL);
    pthread_mutex_init(&e2r, NULL);*/

    // Portas eyes e1s e1r e2s e2r
    
    filename = new char[400];
    gamename = new char[400];

    if(argc >= 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
	cout << "usage: ./bin/simulator_main [-set_ports p_eyes p_es1 p_er1 p_es2 p_er2]" << endl << endl;
	return 1;
    }

    if(argc >= 8 && strcmp(argv[1], "-set_ports") == 0) {
	sscanf(argv[2], " %d ", &p_eyes);
	sscanf(argv[3], " %d ", &p_es1);
	sscanf(argv[4], " %d ", &p_er1);
	sscanf(argv[5], " %d ", &p_es2);
	sscanf(argv[6], " %d ", &p_er2);
	sscanf(argv[7], " %s ", filename);
	sscanf(argv[8], " %s ", gamename);
	printf("ports: p_eyes %d. p_es1 %d. p_er1 %d. p_es2 %d. p_er2 %d.\n", p_eyes, p_es1, p_er1, p_es2, p_er2);
	fd_game = fopen(gamename, "w");
    } else {
	p_eyes = PORTA_GUI;
	p_es1 = PORTA_E1_SEND;
	p_er1 = PORTA_E1_RECV;
	p_es2 = PORTA_E2_SEND;
	p_er2 = PORTA_E2_RECV;
    }

    printf("simulator_main: ports: p_eyes %d. p_es1 %d. p_er1 %d. p_es2 %d. p_er2 %d.\n", p_eyes, p_es1, p_er1, p_es2, p_er2);

    sched_param schedparam;
    pthread_attr_t attr;
    pthread_attr_t attr_kernel;

    schedparam.sched_priority = 3;

    pthread_attr_init(&attr);
    pthread_attr_init(&attr_kernel);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr, SCHED_RR);
    pthread_attr_setschedparam(&attr, &schedparam);

    srand(time(NULL));
    pthread_mutex_init(&mutex_control, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for(int i = 0; i < N_JOGADORES_POR_TIME; i++) {
        va_e[i] = 0.01;
        va_d[i] = 0.01;
        vb_e[i] = 0.01;
        vb_d[i] = 0.01;
    }

    simulator *sim = new simulator();

    pthread_create(&est1_send, &attr, estrategia_1_send, (void *) sim);
    pthread_create(&est1_recv, &attr, estrategia_1_recv, (void *) sim);
    pthread_create(&est2_send, &attr, estrategia_2_send, (void *) sim);
    pthread_create(&est2_recv, &attr, estrategia_2_recv, (void *) sim);
    pthread_create(&eyes, &attr, eyes_main, (void *) sim);
    pthread_create(&kernel, &attr_kernel, executar_movimento, (void *) sim);
    while(!fim_jogo) objeto::sleep2(100);
    cout << "saindo..." << endl;
    /*
    int status;
    cout << "join 1" << endl;
    pthread_join(est1_send, (void **) &status);
    //pthread_join(est1_recv, (void **) &status);
    cout << "join 2" << endl;
    pthread_join(est2_send, (void **) &status);
    //pthread_join(est2_recv, (void **) &status);
    //pthread_join(eyes, (void **) &status);
    cout << "join 3" << endl;
    pthread_join(kernel, (void **) &status);
    cout << "join 4" << endl;
    pthread_mutex_destroy(&mutex_control);
    cout << "join 5" << endl;
    //pthread_exit(NULL);
    //exit_simulator();*/
    
    if(fd_game != NULL)
	fclose(fd_game);

    return 0;
}
