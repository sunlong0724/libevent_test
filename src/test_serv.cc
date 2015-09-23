
#include <iostream>
#include <event.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using std::cout;
using std::endl;
using std::string;

struct event_base *base;

void on_read(int fd, short event, void *arg){
	int len;
	char buf[1500];

	len = recv(fd, buf, sizeof(buf), 0);
	if (len < 0){
		cout << "client closed!" << endl;
		struct event *pev_read = (struct event*)arg;
		event_del(pev_read);
		close(fd);
		return;
	}
	buf[len] = 0;
	cout << "client info:"<<buf<<endl;
}

void on_accept(int fd, short event, void *arg){
	int icli_fd;
	struct sockaddr_in scli_addr;
	socklen_t isin_size = sizeof(scli_addr);

	struct event *pev_read = new struct event;
	event_set(pev_read,icli_fd, EV_READ|EV_PERSIST,on_read, pev_read);
	event_base_set(base, pev_read);
	event_add(pev_read,NULL);	
}
int main(int argc,char* argv[]){

	int iserv_fd;
	struct sockaddr_in sserv_addr;
	bzero(&sserv_addr,sizeof(sserv_addr));

	sserv_addr.sin_family = AF_INET;
	sserv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sserv_addr.sin_port = htons(8888);

	iserv_fd = socket(AF_INET, SOCK_STREAM, 0);
	bind(iserv_fd,(const sockaddr*)&sserv_addr, sizeof(sserv_addr));
	listen(iserv_fd,10);

	base = event_base_new();
	struct event ev_listen;
	event_set(&ev_listen, iserv_fd, EV_READ|EV_PERSIST, on_accept, NULL);

	event_base_set(base, &ev_listen);

	event_add(&ev_listen, NULL);

	event_base_dispatch(base);
	
	return 0;
}
