#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define DEFAULT_PORT 3000
#define DEFAULT_ADDR ""

void * t_main(void * arg);
void errhandle(char *errmsg);

int main(int argc, char *argv[]){
	int clnt_sock;
	struct sockaddr_in serv_addr;
	pthread_t th1;
	clnt_sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));

	struct hostent *host;
	if(argc == 2)
		host = gethostbyname(argv[1]);
	else
		host = gethostbyname(DEFAULT_ADDR);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));
	if(argc == 3) 
		serv_addr.sin_port = htons(atoi(argv[2]));
	else
		serv_addr.sin_port = htons(DEFAULT_PORT);

	if(connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
		errhandle((char *)"connect() error");
	}

	return 0;
}

void * t_main(void * arg){
	return NULL;
}

void errhandle(char *errmsg){
	fputs(errmsg, stderr);
	fputc('\n', stderr);
	exit(1);
}
