#include<omp.h>
#include<stdio.h>
#include<iostream>

using namespace std;

int main() {
    omp_set_num_threads(50);
    #pragma omp parallel
    for(int i = 0; i < 30; i++) {
	//#pragma omp parallel
	for(int j = 0; j < 30; j++) {
	    //#pragma omp parallel
	    for(int k = 0; k < 30; k++) {
		printf("%d\n", omp_get_thread_num());
		sleep(1);
	    }
	}
    }

    return 0;
}
