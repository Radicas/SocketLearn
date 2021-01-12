#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 100
void error_handling(char* message);

int main()
{
	int fd;
	int data_len;
	char buf[BUF_SIZE];
	
	fd = open("data.txt", O_RDONLY);
	printf("file descriptor: %d \n", fd);
	data_len = read(fd, buf, sizeof(buf));
	
	if(data_len == -1)
		error_handling("read() error");
	
	printf("read() return : %d \n", data_len);
	printf("data is: %s", buf);
	close(fd);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
