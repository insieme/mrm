#include <iostream>

#include "comm.h"
#include "protocol.h"

using namespace std;

void serve() {

	cout << "Start serve ... \n";

	for(int i=0; i<2; i++) {

		// get command
		cout << "Reading commmand ...\n";

		int size = getNextMessageSize();
		byte* data = new byte[size];
		getNextMessage(data);

		// process command
		P_MSG* msg = (P_MSG*)data;
		switch(msg->cmd) {
			case INIT: {
				P_MSG_INIT<int>* cmd = (P_MSG_INIT<int>*)data;
				std::cout << "Init: " << cmd->data << "\n";
				break;
			}
			case KILL: return;
			default: {
				std::cout << "Unknown command: " << msg->cmd << "\n";
			}
		}

		delete [] data;
	}

	cout << "End serve.\n";

}
