
#include <iostream>
#include <event.h>

using std::cout;
using std::endl;
using std::string;

void onTime(int sock, short event, void *arg){
	cout << "Game over!" << endl;
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 1000;

	event_add((struct event*)arg, &tv);

}

int main(int argc,char* argv[]){
	event_init();

	struct event evTime;
	evtimer_set(&evTime,onTime,&evTime);

	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 1000;

	event_add(&evTime, &tv);

	event_dispatch();

	return 0;
}
