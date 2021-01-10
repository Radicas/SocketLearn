#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
	struct sockaddr_in sockaddr1, sockaddr2;
	char* str_ptr;
	char str_arr[20];

	sockaddr1.sin_addr.s_addr = htonl(0x10203040);	//整形主机序转网络字节序
	sockaddr2.sin_addr.s_addr = htonl(0x10101010);

	/*
	*inet_ntoa返回char类型指针，第二次调用会覆盖前一次，所以长时间有效需要复制出来
	*
	*/
	str_ptr =inet_ntoa(sockaddr1.sin_addr);
	strcpy(str_arr, str_ptr);
	printf("Dotted-Decimal notation1: %s \n", str_ptr);
	
	inet_ntoa(sockaddr2.sin_addr);
	printf("Dotted-Decimal notation2: %s \n", str_ptr);
	printf("Dotted-Decimal notation3: %s \n", str_arr);

	return 0;
	
}
