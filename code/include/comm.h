

//typedef unsigned char byte;
typedef char byte;

//  sending
void send(int rank, const byte* data, int size);

// receiving
// returns -1 if there is no message
int getNextMessageSize();
void getNextMessage(byte* target);

