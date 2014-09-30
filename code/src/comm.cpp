#include "comm.h"

#include <cassert>

#include <iostream>
#include <array>
#include <vector>
#include <list>

#include "omp.h"

using namespace std;



int getLocalRank() {
	return omp_get_thread_num();
}


struct Msg;
std::ostream& operator<<(std::ostream& out, const Msg& );

struct Msg {

	byte* data;
	int size;

	Msg() : data(nullptr), size(0) {}
	
	Msg(const byte* data, int size) {
		copyIn(data,size);
	}

	Msg(const Msg& other) {
		copyIn(other);
	}

	Msg(Msg&& other) : data(other.data), size(other.size) {
//cout << "    Moving MSG " << other << " to " << *this << "\n";

		other.data = nullptr;
		other.size = 0;
	}

	Msg& operator=(const Msg& other) {
		if (this == &other) return *this;
		if (data == other.data) return *this;
		
		clean();
		copyIn(other);
		return *this;
	}



	~Msg() {
		clean();
	}

private:

	void clean() {
//cout << "    Clearing MSG " << *this << " of size " << size << " bytes from " << (void*)data << "\n";
		delete [] data;
		data = nullptr;
		size = 0;
	}

	void copyIn(const Msg& other) {
		copyIn(other.data, other.size);
	}

	void copyIn(const byte* data, int size) {
		this->data = new byte[size];
//cout << "Copying into MSG " << *this << " " << size << " bytes from " << (void*)data << " to " << (void*)(this->data) << " by " << getLocalRank() << "\n";
		for(int i=0; i<size; i++) {
			this->data[i] = data[i];
		}
		this->size = size;
	}
	

};

std::ostream& operator<<(std::ostream& out, const Msg& msg) {
	return out << (void*)(msg.data) << " in " << &msg;
}


array<list<Msg>,50> COMM;

//  sending
void send(int rank, const byte* data, int size) {
	#pragma omp critical(COM)
	COMM[rank].insert(COMM[rank].end(),Msg(data,size));
}

// receiving
// returns -1 if there is no message
int getNextMessageSize() { 
	auto& c = COMM[getLocalRank()];
	while(c.empty()) {};
	return c.front().size;
}


void getNextMessage(byte* target) {
	auto& c = COMM[getLocalRank()];
	while(c.empty()) {};

	#pragma omp critical(COM)
 	{
		const Msg msg = c.front();
		for(int i=0; i<msg.size; i++) {
			target[i] = msg.data[i];
		}
		c.pop_front();
	}
}



