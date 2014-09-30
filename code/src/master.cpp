#include <iostream>

#include <omp.h>

#include "comm.h"
#include "protocol.h"

#include <unistd.h>

using namespace std;

void govern() {

	cout << "Start govern ... \n";

	int numSlaves = omp_get_num_threads() - 1;

	Protocol<int> p;

	// send messages to each slave
	for(int j=1; j<=numSlaves; j++) {
		p.init(j, j*2);
	}

	// kill all slaves
	for(int j=1; j<=numSlaves; j++) {
		p.kill(j);
	}

	cout << "End govern.\n";

}
