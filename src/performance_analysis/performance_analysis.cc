#include"performance_analysis.h"

vector<int> performance_analysis::get_five_good_ports() {
    vector<int> port;
    int on = 1;

    int base = (rand() % (UPPER_PORT - LOWER_PORT + 1)) + LOWER_PORT;
    for(int i = 0; i < 5; i++) {
	int listen_socket;
	struct sockaddr_in server_address;
	socklen_t client_address_length;

	while(1) {
	    base++;
	    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	    if(listen_socket < 0)
		return port;
	    bzero((char *) &server_address, sizeof(server_address));
	    server_address.sin_family = AF_INET;
	    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	    server_address.sin_port = htons(base);
	    setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	    if((bind(listen_socket, (struct sockaddr *) &server_address, sizeof(server_address))) < 0)
		continue;
	    if(listen(listen_socket, 5) != 0) continue;
	    port.push_back(base);
	    close(listen_socket);
	    break;
	}
    }
    
    return port;
}

vector<int> performance_analysis::get_five_good_ports2() {
    vector<int> bad_ports = get_busy_ports(), good_ports;
    set<int> set_bad_ports;
    int port = LOWER_PORT;

    for(int i = 0; i < bad_ports.size(); i++)
	set_bad_ports.insert(bad_ports[i]);

    for(int i = 0; i < 5 && port <= UPPER_PORT; i++) {
	while(set_bad_ports.find(port) != set_bad_ports.end())
	    port++;
	if(port <= UPPER_PORT) {
	    good_ports.push_back(port);
	    port++;
	}
    }

    return good_ports;
}

double performance_analysis::get_info_host(char *host_access) {
    int r = rand();
    char *filename, command[500];
    FILE *fd;
    double la;
    int np;

    filename = performance_analysis::gen_tmp_filename();
    sprintf(command, "ssh %s ps aux | grep -i simulator_main | grep -v grep | wc -l > %s", host_access, filename);

    system(command);
    if((fd = fopen(filename, "r")) == NULL) return -10;
    fscanf(fd, " %d ", &np);
    fclose(fd);
    sprintf(command, "rm %s", filename);
    system(command);

    printf("Num process %s: %d\n", host_access, np);

    return (double) np;
}
    
char *performance_analysis::get_host(int *num) {
    FILE *f_config = NULL;
    vector<string> host_access;
    host_access.clear();
    char aux[100];
    char *name = new char[400];

    if((f_config = fopen("config/hosts", "r")) == NULL) {
	cerr << "performance_analysis: get_host: cannot open config/hosts" << endl;
	return NULL;
    }
    while(fscanf(f_config, " %s ", aux) == 1) {
	printf("=== %s\n", aux);
	host_access.push_back(aux);
    }
    fclose(f_config);
    int menor_i = 0, maior_i = 0;
    double menor = 1000, maior = 0;
    double np[host_access.size()];
    for(int i = 0; i < host_access.size(); i++) {
	if(performance_analysis::get_ping((char *) host_access[i].c_str())) {
	    np[i] = performance_analysis::get_info_host((char *) host_access[i].c_str());
	}
    }

    for(int i = 0; i < host_access.size(); i++) {
	if(np[i] < menor) {
	    menor = np[i];
	    menor_i = menor;
	}
    }

    vector<double>var;
    for(int i = 0; i < host_access.size(); i++)
	if(np[i] == menor)
	    var.push_back(i);
    
    menor_i = var[rand() % var.size()];
    menor = np[menor_i];

    *num = menor;
    strcpy(name, (char *) host_access[menor_i].c_str());
    

    return name;
}

char *performance_analysis::gen_tmp_filename() {
    int r;
    char *filename = new char[300];
    FILE *fd = NULL;

    do {
	if(fd != NULL) fclose(fd);
	r = rand();
	sprintf(filename, "/var/tmp/%d.tmp", r);
	fd = fopen(filename, "r");
    } while(fd != NULL);

    return filename;
}
 
void performance_analysis::delete_file(char *filename) {
    char command[500];

    if(remove(filename)) printf("performance_analysis: delete_file: error: problems in delete the file %s.\n", filename);
    delete []filename;
}

int performance_analysis::get_ping(char *host_access) {
    char command[500];
    char host[100];
    int i;
    char *filename = performance_analysis::gen_tmp_filename();
    FILE *fd = NULL;

    // Take the host on the string user@host.
    for(i = 0; i < strlen(host_access) && host_access[i] != '@'; i++);
    i++;
    strcpy(host, &(host_access[i]));

    sprintf(command, "ping -c 1 -w 1 %s | grep -i \"packets transmitted\" | cut -d' ' -f 4 > %s", host, filename);
    system(command);
    if((fd = fopen(filename, "r")) == NULL) {
	printf("performance_analysis: get_ping: error: cannot open file %s for reading.\n", filename);
	performance_analysis::delete_file(filename);
	return performance_analysis::get_ping(host_access);
    }
    fscanf(fd, " %d ", &i);
    fclose(fd);

    performance_analysis::delete_file(filename);

    return i;
}

vector<int> performance_analysis::run_simulator(double e_ataque, double e_defesa, double e_goleiro) {
    char *filename;
    char *gamename;
    vector<int> res;

    filename = performance_analysis::gen_tmp_filename();
    sprintf(gamename, "%s_%lf_%lf_%lf.gamefile", performance_analysis::gen_tmp_filename(), e_ataque, e_defesa, e_goleiro);

    res = performance_analysis::run_simulator(e_ataque, e_defesa, e_goleiro, filename, gamename);

    performance_analysis::delete_file(filename);
    delete []gamename;

    return res;
}

vector<int> performance_analysis::run_simulator(double e_ataque, double e_defesa, double e_goleiro, char *filename, char *gamename) {
    char *host = NULL;
    char *command = new char[400];
    double load_average;
    FILE *fd = NULL;
    FILE *fg = NULL;
    vector<int> result;
    int aux[6];
    int port[5];
    char *s = new char[500];
    FILE *fh;
    int num;

    while(fd == NULL) {
	sleep(rand() % 10);
	host = performance_analysis::get_host(&num);
	printf("ANTES\n");
	while(num > 6 || host == NULL) {
	    printf("--- num %d.\n", num);
	    if(host == NULL) printf("host  is NULL\n");
	    else printf(" HOST %s\n", host);
	    sleep(rand() % 5);
	    host = performance_analysis::get_host(&num);
	}
	printf("DEPOIS\n");

	port[0] = (rand() % 63000) + 2000;
	for(int i = 1; i < 5; i++)
	    port[i] = port[i - 1] + 1;

	fh = fopen("history", "a");
	fprintf(fh, "-- %d %d %d %d %d %s %lf\n", port[0], port[1], port[2], port[3], port[4], host, e_ataque);
	fclose(fh);
	sprintf(command, "ssh %s ' cd %s/uspds ; %s/uspds/executar_auto.sh %d %d %d %d %d %s %s %lf %lf %lf'", host, DIRECTORY, DIRECTORY, port[0], port[1], port[2], port[3], port[4], filename, gamename, e_ataque, e_defesa, e_goleiro);
	system(command);
	sprintf(command, "scp %s:%s %s", host, filename, filename);
	system(command);
	sprintf(command, "scp %s:%s %s", host, gamename, gamename);
	system(command);

	if((fd = fopen(filename, "r")) == NULL) {
	    printf("RUN_SIMULATOR: cannot open file %s for reading - host #%s#\n", filename, host);
	    continue;
	}
	if((fg = fopen(gamename, "r")) == NULL) {
	    printf("RUN_SIMULATOR: cannot open file %s for reading - host #%S#\n", filename, host);
	    continue;
	}
	fclose(fg);

	result.clear();

	for(int i = 0; i < 6; i++) aux[i] = -1;
	fscanf(fd, " %s %d %s %d %s %d %s %d %s %d %s %d ", s, &(aux[0]), s, &(aux[1]), s, &(aux[2]), s, &(aux[3]), s, &(aux[4]), s, &(aux[5]));
	fclose(fd);
	printf("RUN_SIMULATOR: %d %d %d %d %d %d\n", aux[0], aux[1], aux[2], aux[3], aux[4], aux[5]);
	for(int i = 0; i < 6; i++)
	    result.push_back(aux[i]);

	fh = fopen("history", "a");
	fprintf(fh, "++ close %d %d %d %d %d %s %lf\n", port[0], port[1], port[2], port[3], port[4], host, e_ataque);
	fclose(fh);
	break;
    }

    delete []host;
    delete []command;
    delete []s;

    return result;
}

void performance_analysis::init() {
    FILE *fd;
    vector<string> accesshost;
    char *aux = new char[500];
    char *command = new char[500];

    if((fd = fopen("config/hosts", "r")) == NULL) {
	cerr << "performance_analysis: cannot read file config/hosts" << endl;
	exit(1);
    }

    while(fscanf(fd, " %s ", aux) == 1) {
	accesshost.push_back(aux);
    }
    fclose(fd);

#pragma omp parallel for
    for(int i = 0; i < accesshost.size(); i++) {
	int ping = performance_analysis::get_ping((char *) accesshost[i].c_str());
	if(ping) {
	    sprintf(aux, "ssh %s 'rm -rf ~/tt2/uspds'", accesshost[i].c_str());
	    system(aux);
	    sprintf(aux, "ssh %s mkdir %s", accesshost[i].c_str(), DIRECTORY);
	    system(aux);
	    sprintf(aux, "scp -r ~/c/uspds %s:%s", accesshost[i].c_str(), DIRECTORY);
	    system(aux);
	}
    }

}

vector<int> performance_analysis::get_busy_ports() {
    int n_rand = rand();
    char command[300];
    char *filename;
    FILE *fd;
    vector<int> busy_port;
    int b_port;

    filename = performance_analysis::gen_tmp_filename();
    sprintf(command, "netstat -an | grep -i tcp | cut -d:  -f2 | awk '{printf $1 \"\\n\"}' | sort -u > %s", filename);
    system(command);

    if((fd = fopen(filename, "r")) == NULL)
	return busy_port;

    while(fscanf(fd, " %d ", &b_port) == 1)
	busy_port.push_back(b_port);

    fclose(fd);

    for(int i = 0; i < busy_port.size(); i++)
	printf("busy port: %d\n", busy_port[i]);

    performance_analysis::delete_file(filename);

    return busy_port;
}

vector<vector<int> > performance_analysis::run_test_case(double e_ataque, double e_defesa, double e_goleiro) {
    vector<int> total[PLAYS_PER_TEST];
    vector<vector<int> > t;

    t.clear();

#pragma omp parallel for
    for(int i = 0; i < PLAYS_PER_TEST; i++) {
	printf("RUN_TEST_CASE %d - %lf\n", i, e_ataque);
	sleep(i);
	total[i] = run_simulator(e_ataque, e_defesa, e_goleiro);
    }

    for(int i = 0; i < PLAYS_PER_TEST; i++)
	t.push_back(total[i]);

    return t;
}

int performance_analysis::run_pthread_simulator(void *arg) {
    struct pstruct *a =  (struct pstruct *) arg;
    printf("run_pthread_simulator: %lf %lf %lf %s %s\n", a->e_ataque, a->e_defesa, a->e_goleiro, a->filename, a->gamename);
    performance_analysis::run_simulator(a->e_ataque, a->e_defesa, a->e_goleiro, a->filename, a->gamename);

    return NULL;
}

double performance_analysis::strategy_pthread_performance(double *e) {
    double f = performance_analysis::strategy_performance(e[0], e[1], e[2]);
    FILE *fd = fopen("results", "a");
    fprintf(fd, "%lf %lf %lf %lf\n", e[0], e[1], e[2], f);
    fclose(fd);

    return 0.0;
}

double performance_analysis::strategy_performance(double e_ataque, double e_defesa, double e_goleiro) {
    int saldo[10];
    double tot = 0;
    pthread_t pt[10];
    struct pstruct ps[10];
    char *aux = new char[500];
    FILE *fd;

    for(int i = 0; i < 10; i++) {

	ps[i].filename = new char[400];
	ps[i].gamename = new char[400];
	ps[i].e_ataque = e_ataque;
	ps[i].e_defesa = e_defesa;
	ps[i].e_goleiro = e_goleiro;


	ps[i].filename = performance_analysis::gen_tmp_filename();
	ps[i].gamename = performance_analysis::gen_tmp_filename();

	pthread_create(&(pt[i]), NULL, (void * (*)(void *)) performance_analysis::run_pthread_simulator, (void *) &(ps[i]));
    }

    for(int i = 0; i < 10; i++) {
	int team, g1, g2;
	pthread_join(pt[i], NULL);
	fd = fopen(ps[i].filename, "r");
	fscanf(fd, " %s %d %s %d %s %d ", aux, &team, aux, &g1, aux, &g2);
	fclose(fd);
	saldo[i] = g2 - g1;

	performance_analysis::delete_file(ps[i].filename);
	performance_analysis::delete_file(ps[i].gamename);
    }

    for(int i = 0; i < 10; i++) tot += saldo[i];
    tot /= 10;

    return tot;
}

/*vector<vector<vector<int> > > performance_analysis::run_all(vector<double> e_ataque, vector<double> e_defesa, vector<double> e_goleiro) {
    vector<vector<vector<int> > > t;
    vector<int> ret[e_ataque.size()][PLAYS_PER_TEST];
    char task[e_ataque.size()]; // 0 - Task is free
    				// 1 - Task is running
				// 2 - Task is done

    if(e_ataque.size() != e_defesa.size() || e_ataque.size() != e_goleiro.size()) return t;
    
    for(int i = 0; i < e_ataque.size(); i++) task[i] = 0;

    int res[e_ataque.size()][PLAYS_PER_TEST][10];

    #pragma omp parallel for shared task
    for(int i = 0; i < e_ataque.size(); i++) {
	for(int j = 0; j < PLAYS_PER_TEST; j++) {
	    ret[i][j] = performance_analysis::run_simulator(e_ataque[i], e_defesa[i], e_goleiro[i]);
	}
    }

    t = ret;

    return t;
}*/

/*
int main() {
    srand(time(NULL));

    performance_analysis::init();

    omp_set_num_threads(50);
#pragma omp parallel for
    for(int j = 0; j <= 230 ; j += 5) {
	double e_t = ((double) j) / 100;
	cout << "BEGINNING E " << e_t << endl;
	vector<vector<int> > res = performance_analysis::run_test_case(e_t, e_t, e_t);
	#pragma omp critical
	{
	    char *filename = new char[200];
	    
	    sprintf(filename, "%lf.hty2", e_t);
	    FILE *fd = fopen(filename, "w");
	    for(int i = 0; i < res.size(); i++) {
		printf("%d - ", i);
		fprintf(fd, "%d - ", i);
		for(int j = 0; j < res[i].size(); j++) {
		    printf("%d ", res[i][j]);
		    fprintf(fd, "%d ", res[i][j]);
		}
		printf("\n");
	    }
	    fclose(fd);
	    delete []filename;
	}
    }


    return 0;
}*/
