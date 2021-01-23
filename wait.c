#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int status;
	pid_t pid = fork();
	
	if(pid==0)
	{
		return 3;
	}else
	{
		printf("Child pid: %d", pid);
		pid = fork();
		if(pid==0)
		{
			exit(7);
		}else
		{
			printf("Child pid: %d", pid);
			wait(&status);
			if(WIFEXITED(status))
				printf("Child send one: %d", WEXITSTATUS(status));

			wait(&status);
			if(WIFEXITED(status))
				printf("Child send two: %d", WEXITSTATUS(status));
			sleep(10);
		}
	}
	return 0;
}
