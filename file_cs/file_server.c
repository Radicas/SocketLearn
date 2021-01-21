#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char* message);

int main(int argc, char* argv[])
{
	int serv_sock, clnt_sock;
	FILE* fp;
	char buf[BUF_SIZE];
	char buf2[10];
	int read_clnt;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_size;
	
	if(argc!=2)
	{
		printf("Usege: %s <port> \n", argv[0]);
		exit(1);
	}
	
	fp = fopen("file_server.c", "rb");
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);	//创建socket
	if(serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	//htonl主机字节序号转化网络字节序，long类型
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)))	//
		error_handling("bind() error");

	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
	if(clnt_sock == -1)
		error_handling("accpet() error");

	while(1)
	{
		read_clnt = fread((void*)buf, 1, BUF_SIZE, fp);
		if(read_clnt<BUF_SIZE)
		{
			write(clnt_sock, buf, read_clnt);
			break;
		}
		write(clnt_sock, buf, BUF_SIZE);
	}

	shutdown(clnt_sock, SHUT_WR);
	read(clnt_sock, buf2, sizeof(buf2));
	printf("Message from client: %s \n", buf2);
	fclose(fp);
	close(serv_sock);
	close(clnt_sock);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
