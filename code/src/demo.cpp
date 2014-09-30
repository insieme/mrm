

#include "master.h"
#include "slave.h"

#include <omp.h>

int main() {

	#pragma omp parallel
	{
		if (omp_get_thread_num() == 0) {
			govern();
		} else {
			serve();
		}
	}

	return 0;
}
