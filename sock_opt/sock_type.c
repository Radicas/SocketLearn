#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

void error_handling(char* message);

int main(int argc, char* argv[])
{
	int tcp_sock, udp_sock;
	int sock_type;
	socklen_t optlen;
	int state;
	
	optlen = sizeof(sock_type);
	tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
	udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
	printf("sock_stream: %d \n", SOCK_STREAM);	
	printf("sock_dgram: %d \n", SOCK_DGRAM);
	
	state = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen);
	if(state)
		error_handling("getsockopt() error");
	printf("tcp sock_type: %d \n", sock_type);

	state = getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen);
	if(state)
		error_handling("getsockopt() error");
	printf("udp sock_type: %d \n", sock_type);
	return 0;	
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}