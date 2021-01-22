#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define TRUE 1
#define FALSE 0
void error_handling(char* message);

int main(int argc, char* argv[])
{
	int serv_sock;	//socket描述符
	int clnt_sock;
	int str_len, option, i;
	char message[BUF_SIZE];
	struct sockaddr_in serv_addr;	//sockaddr_in 结构体
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size, optlen;
	
	if(argc!=2)
	{
		printf("Usege: %s <port> \n", argv[0]);
		exit(1);
	}
	
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);	//创建server套接字，还不是服务器socket
	if(serv_sock == -1)
		error_handling("socket() error");
/*
使用SO_REUSEADDR套接字选项，可以在time-wait状态下使用端口号
*/
	optlen = sizeof(option);	
	option = TRUE;
	setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, optlen);

	memset(&serv_addr, 0, sizeof(serv_addr));	//init struct sockaddr_in
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)))	//初始化的地址信息分配给socket，绑定ip和端口
		error_handling("bind() error");

	if(listen(serv_sock, 5) == -1)	//参数为fd和请求等待队列大小,此时serv_sock才是服务器socket
		error_handling("listen() error");

	clnt_addr_size = sizeof(clnt_addr);
	for(i=0; i<5; i++)
	{
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
		if(clnt_sock == -1)
			error_handling("accept() error");
		else
			printf("Connect client %d \n", i+1);
		
		while((str_len = read(clnt_sock, message, BUF_SIZE))!=0)
		{
			printf("Message from client: %s", message);
			write(clnt_sock, message, strlen(message));	
		}
		close(clnt_sock);
	}
	close(serv_sock);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
