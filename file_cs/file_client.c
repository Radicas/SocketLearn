#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 30
void error_handling(char* message);

int main(int argc, char* argv[])
{
	int sock;
	int read_clnt;
	FILE* fp;
	char buf[BUF_SIZE];
	struct sockaddr_in serv_addr;
	if(argc!=3)
	{
		printf("Useage: %s <IP> <port> \n", argv[0]);
		exit(1);
	}
	
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));	//结构体变量成员初始化为0
	serv_addr.sin_family = AF_INET;	//协议族，ipv4
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);	//ip地址,inet_addr将ip字符串转化32位整形
	serv_addr.sin_port = htons(atoi(argv[2]));	//端口，htons主机字节序转化为网络字节序号，short类型

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)	//发起connect
		error_handling("connect() error");
	fp = fopen("receive.dat", "wb");	
	
	while((read_clnt=read(sock, buf, BUF_SIZE))!=0)
		fwrite((void*)buf, 1, read_clnt, fp);

	fputs("Recevied file data", stdout);
	write(sock, "THINKS", 7);
	fclose(fp);
	close(sock);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
