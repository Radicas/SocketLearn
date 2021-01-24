#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	pid_t pid = fork();
	
	if(pid==0)
	{
		puts("im child process");
	}else
	{
		printf("Child process ID: %d \n", pid);
		sleep(10);
	}

	if(pid==0)
	{
		puts("end child process");
	}else
	{
		puts("end father process");
	}
	return 0;
}
