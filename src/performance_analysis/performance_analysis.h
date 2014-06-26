#ifndef PERFORMANCE_ANALYSIS_H
#define PERFORMANCE_ANALYSIS_H

#include<time.h>
#include<string.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>
#include<vector>
#include<set>
#include<omp.h>
#include<pthread.h>

#define LOWER_PORT 10000
#define UPPER_PORT 65535
#define DIRECTORY "~/tt2"
#define PLAYS_PER_TEST 20

using namespace std;

typedef struct pstruct{
    double e_ataque, e_defesa, e_goleiro;
    char *filename, *gamename;
};

class performance_analysis {
    public:
	performance_analysis();

	static vector<int> get_five_good_ports();
	static vector<int> get_five_good_ports2();
	static vector<int> get_busy_ports();
	static vector<int> run_simulator(double e_ataque, double e_defesa, double e_goleiro);
	static vector<int> run_simulator(double e_ataque, double e_defesa, double e_goleiro, char *filename, char *gamename);
        static int run_pthread_simulator(void *arg);
	static void init();

	/**
	 * Uses the file config/hosts to search for the host with minimum load average.
	 *
	 * \return Returns the host access.
	 */
	static char *get_host(int *num);

	/**
	 * Get load average information of the host.
	 *
	 * \param host_access Contain the way that the host must be accessed [user@host]
	 *
	 * \return Returns the load average of the host, or 0 if the host cannot be reached
	 */
	static double get_info_host(char *host_access);

	/** Generate a random filename on /tmp directory.
	 *
	 * \return Return the pointer to the filename generated.
	 */
	static char *gen_tmp_filename();

	/**
	 * Delete file.
	 *
	 * \filename Full path of the file.
	 */
	static void delete_file(char *filename);

	/**
	 * Ping the host to verify if it is online
	 *
	 * \param host_access Contain the way that the host must be accessed [user@host]
	 *
	 * \return Return 1 if the host is online, 0 otherwise.
	 */
	static int get_ping(char *host_access);

	static vector<vector<int> > run_test_case(double e_ataque, double e_defesa, double e_goleiro);

	static vector<vector<vector<int> > > run_all(vector<double> e_ataque, vector<double> e_defesa, vector<double> e_goleiro);

	static double strategy_performance(double e_ataque, double e_defesa, double e_goleiro);

	static double strategy_pthread_performance(double *e);

};

#endif
