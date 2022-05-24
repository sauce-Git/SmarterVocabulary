#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

#define DEFAULT_PORT 3000

#define MAX_CLNT 64
#define BUF_SIZE 300
#define MAX_LISTEN_NUMBER 5

void * t_main(void * arg);
void errhandle(char *errmsg);

int clnt_count = 0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutex;

int main(int argc, char *argv[]){
	int serv_sock, clnt_sock;
	int clnt_adr_sz;
	struct sockaddr_in serv_adr, clnt_adr;
	pthread_t t_id;
	pthread_mutex_init(&mutex, NULL);	
	
	if(argc > 2){
		printf("Usage : %s <port>\n", argv[0]);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(argc == 2) serv_adr.sin_port = htons(atoi(argv[1]));
	else if(argc == 1) serv_adr.sin_port = htons(DEFAULT_PORT);
	else errhandle((char *)"port error");

	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1) 
		errhandle((char *)"bind() error");

	if(listen(serv_sock, MAX_LISTEN_NUMBER) == -1)
		errhandle((char *)"listen() error");

	while(1){
		clnt_adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_adr, (socklen_t*) &clnt_adr_sz);
		
		pthread_mutex_lock(&mutex);
		clnt_socks[clnt_count++] = clnt_sock;
		pthread_mutex_unlock(&mutex);
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
