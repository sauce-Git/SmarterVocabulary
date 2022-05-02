#include "base_server_header.h"
#include "serverinfo.h"
#define MAX_SOCK_NUM 100


void errhandle(char *errmsg);

int main(){
	int serv_sock[MAX_SOCK_NUM], clnt_sock[MAX_SOCK_NUM];
	struct sockaddr_in st_serv_addr;
	struct sockaddr_in st_clnt_addr;
	struct hostent *host;

	host = gethostbyname(SADDR);
	
	for(int i = 0; i < MAX_SOCK_NUM; i++){
		serv_sock[i] = socket(PF_INET, SOCK_STREAM, 0);

		if(serv_sock[i] == -1){
			errhandle((char *)"socket() ERR!");
		}

		memset(&st_serv_addr, 0, sizeof(st_serv_addr));

		st_serv_addr.sin_family = AF_INET;
		st_serv_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));
		st_serv_addr.sin_port = htons(PORT);

		if(bind(serv_sock[i], (struct sockaddr*) &st_serv_addr, sizeof(st_serv_addr)) == -1){
			errhandle((char *)"bind() ERR!");
		}

	}
	return 0;
}

void errhandle(char *errmsg){
	fputs(errmsg, stderr);
	fputc('\n', stderr);
	exit(1);
}
