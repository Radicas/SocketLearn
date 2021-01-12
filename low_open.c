#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void error_handling(char* message);

int main()
{
	int fd;
	int write_len;
	char buf[] = "Let's go";
	
	fd = open("data.txt",O_CREAT|O_WRONLY|O_TRUNC);
	if(fd == -1)
		error_handling("open() error");
	printf("file descriptor: %d \n",fd);
	write_len = write(fd, buf, sizeof(buf));
	
	if(write_len == -1)
		error_handling("write() error");
	close(fd);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
