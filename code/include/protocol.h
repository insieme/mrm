

enum CMD {
	INIT, MAP_REDUCE, REDUCE, GET, KILL
};


struct P_MSG {
	CMD cmd;
};


template<typename D>
struct P_MSG_INIT {
	CMD cmd;
	D data;
};


template<
	typename D
	// data has to be a POD object
>
struct Protocol {


	void init(int rank, const D& data = D()) {
		P_MSG_INIT<D> init;
		init.cmd = INIT;
		init.data = data;
		send(rank, (const byte*)&init, sizeof(init));
	}

	void mapReduce(int rank, const D& data) {

	}

	void reduce(int rank, const D& data) {

	}

	D get(int rank) {

	}

	void kill(int rank) {
		P_MSG kill;
		kill.cmd = KILL;
		send(rank, (const byte*)&kill, sizeof(P_MSG));
	}
};

