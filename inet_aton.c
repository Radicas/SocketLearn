#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
	struct sockaddr_in sockaddr;
	char* addr1 = "127.0.0.1";
	char* addr2	= "333,444,555,666";

	if(!inet_aton(addr1,&sockaddr.sin_addr))
		printf("%s is wrong ip address \n",addr1);
	else
		printf("127.0.0.1 int type is: %d",sockaddr.sin_addr.s_addr);
	return 0;
	
}
